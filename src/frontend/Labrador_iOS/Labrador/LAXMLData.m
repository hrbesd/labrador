//
//  LAList.m
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-27.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "LAXMLData.h"
#import "LogTools.h"
#import "GDataXMLNode.h"
#import <CommonCrypto/CommonDigest.h>

@interface LAXMLData ()

@property (strong, nonatomic) NSMutableData *data;
@property (strong, nonatomic) NSURLConnection *connection;
@property (strong, nonatomic) GDataXMLDocument *xmlDoc;
@property (strong, nonatomic) NSString *urlStr;
@property (assign, nonatomic) XMLDataType type;

- (NSString *)docPathForKey:(NSString *)key;

@end

@implementation LAXMLData

@synthesize data = _data;
@synthesize connection = _connection;
@synthesize xmlDoc = _xmlDoc;
@synthesize urlStr = _urlStr;

@synthesize delegate = _delegate;
@synthesize listData = _listData;
@synthesize articleElem = _articleElem;
@synthesize type = _type;

- (void)dealloc {
    [self cancleConnection];
    self.delegate = nil;
}

- (id)initWithURL:(NSString *)urlStr type:(XMLDataType)type delegate:(id<LAXMLDataDelegate>)delegate{
    self = [super init];
    if (self) {
        self.data = [NSMutableData data];
        self.listData = [NSArray array];
        self.urlStr = urlStr;
        self.type = type;
        self.delegate = delegate;
        NSFileManager *fileManager = [NSFileManager defaultManager];
        
        NSString *path = [self docPathForKey:_urlStr];
        //DLog(@"%@", path);
        if ([fileManager fileExistsAtPath:path]) {
            NSData *xmlData = [NSData dataWithContentsOfFile:path];
            NSError *err;
            self.xmlDoc = [[GDataXMLDocument alloc] initWithData:xmlData options:0 error:&err];
            
            if (err == nil) {
                GDataXMLElement *rootElem = [_xmlDoc rootElement];
                
                if (type == XMLDataType_List) {
                    rootElem = [[rootElem elementsForName:@"nodelist"] objectAtIndex:0];

                    self.listData = [NSMutableArray arrayWithArray:[rootElem elementsForName:@"indexnode"]];
                    
                    if ([_listData count] == 0) {
                        // not an index.xml
                        self.listData = [NSMutableArray arrayWithArray:[rootElem elementsForName:@"node"]];
                    }
                }
                else {
                    self.articleElem = rootElem;
                }
                
            }
            else {
                // TODO: send err to delegate
            }
            
            // TODO: Check updates
        }
        else {
            [self requestWithURL:_urlStr];
        }
        
    }
    return self;
}

- (id)initWithURL:(NSString *)urlStr type:(XMLDataType)type {
    return [self initWithURL:urlStr type:type delegate:nil];
}

- (void)forceUpdate {
    [self requestWithURL:_urlStr];
}

- (NSString *)docPathForKey:(NSString *)key {
    const char *str = [key UTF8String];
    unsigned char r[CC_MD5_DIGEST_LENGTH];
    CC_MD5(str, (CC_LONG)strlen(str), r);
    NSString *filename = [NSString stringWithFormat:@"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
                          r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[7], r[8], r[9], r[10], r[11], r[12], r[13], r[14], r[15]];
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *docPath = [[paths objectAtIndex:0] stringByAppendingPathComponent:@"XMLs"];
    
    if (![[NSFileManager defaultManager] fileExistsAtPath:docPath])
    {
        [[NSFileManager defaultManager] createDirectoryAtPath:docPath
                                  withIntermediateDirectories:YES
                                                   attributes:nil
                                                        error:NULL];
    }
    
    return [docPath stringByAppendingPathComponent:filename];
}

#pragma mark - public methods

- (void)requestWithURL:(NSString *)urlStr {
    NSURLRequest *request = [NSURLRequest requestWithURL:[NSURL URLWithString:urlStr] cachePolicy:NSURLCacheStorageNotAllowed timeoutInterval:30];

    // only one connection 
    if (_connection == nil) {
        self.data = [NSMutableData data];
        self.connection = [[NSURLConnection alloc] initWithRequest:request delegate:self];
        if ([_delegate respondsToSelector:@selector(listWillStartLoading:)]) {
            [_delegate listWillStartLoading:self];
        }
    }
    else {
        if ([_delegate respondsToSelector:@selector(listAlreadyLoading:)]) {
            [_delegate listAlreadyLoading:self];
        }
    }
}

- (void)cancleConnection {
    [_connection cancel];
    self.connection = nil;
}

#pragma mark - NSURLConnectionDataDelegate

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response {
    //DLog("");
    // TODO: add response detail
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data {
    [_data appendData:data];
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection {
    //DLog(@"%@", [[NSString alloc] initWithData:_data encoding:NSUTF8StringEncoding]);
    
    [self cancleConnection];
    
    NSError *err;
    self.xmlDoc = [[GDataXMLDocument alloc] initWithData:_data options:0 error:&err];
    
    if (err == nil) {
        GDataXMLElement *rootElem = [_xmlDoc rootElement];
        
        if (_type == XMLDataType_List) {
            rootElem = [[rootElem elementsForName:@"nodelist"] objectAtIndex:0];
            self.listData = [NSMutableArray arrayWithArray:[rootElem elementsForName:@"indexnode"]];
            
            if ([_listData count] == 0) {
                // not an index.xml
                self.listData = [NSMutableArray arrayWithArray:[rootElem elementsForName:@"node"]];
            }
        }
        else {
            self.articleElem = rootElem;
        }
        
        // save data to disk
        NSString *path = [self docPathForKey:_urlStr];
        //DLog(@"%@", path);
        if (![_data writeToFile:path atomically:YES]) {
            NSLog(@"errrrr");
        }
        if ([_delegate respondsToSelector:@selector(listDidFinishLoading:)]) {
            [_delegate listDidFinishLoading:self];
        }
    }
    else {
        // TODO: detail error info
        if ([_delegate respondsToSelector:@selector(list:failWithError:)]) {
            [_delegate list:self failWithError:nil];
        }
    }
    
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error {
    DLog("");
    [self cancleConnection];
    
    if ([_delegate respondsToSelector:@selector(list:failWithError:)]) {
        [_delegate list:self failWithError:error];
    }
}

@end
