//
//  LAList.m
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-27.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "LAList.h"
#import "LogTools.h"
#import "GDataXMLNode.h"

@interface LAList ()

@property (strong, nonatomic) NSMutableData *data;
@property (strong, nonatomic) NSURLConnection *connection;
@property (strong, nonatomic) GDataXMLDocument *xmlDoc;

@end

@implementation LAList

@synthesize data = _data;
@synthesize connection = _connection;
@synthesize xmlDoc = _xmlDoc;

@synthesize delegate = _delegate;
@synthesize listData = _listData;

- (id)initWithURL:(NSString *)urlStr {
    self = [super init];
    if (self) {
        self.data = [NSMutableData data];
        self.listData = [NSArray array];
        // TODO: Load data form disk
        BOOL isDataInDisk = NO;
        
        if (isDataInDisk) {
            // TODO: Check update
        }
        else {
            [self requestWithURL:urlStr];
        }
    }
    return self;
}

- (void)requestWithURL:(NSString *)urlStr {
    NSURLRequest *request = [NSURLRequest requestWithURL:[NSURL URLWithString:urlStr] cachePolicy:NSURLCacheStorageNotAllowed timeoutInterval:30];

    // TODO: only one connection 
    self.connection = [[NSURLConnection alloc] initWithRequest:request delegate:self];
}

#pragma mark - NSURLConnectionDataDelegate

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response {
    DLog("");
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data {
    [_data appendData:data];
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection {
    NSError *err;
    self.xmlDoc = [[GDataXMLDocument alloc] initWithData:_data options:0 error:&err];
    
    if (err == nil) {
        GDataXMLElement *rootElem = [_xmlDoc rootElement];
        NSArray *nodes = [rootElem elementsForName:@"node"];
        
        if ([nodes count] != 0) {
            // TEMP: deal with index.xml
            rootElem = [nodes objectAtIndex:0];
        }
        
        rootElem = [[rootElem elementsForName:@"nodeList"] objectAtIndex:0];
        self.listData = [rootElem elementsForName:@"node"];
        
        [_delegate listDidFinishLoading:self];
    }
    else {
        // TODO: send err to delegate
    }
    
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error {
    DLog("");
}

@end
