//
//  GDataXMLElement+Labrador.m
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-22.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "GDataXMLElement+List.h"

@implementation GDataXMLElement (List)

@dynamic nodeName;
@dynamic url;
@dynamic pageURL;
@dynamic refreshRate;
@dynamic hashName;
@dynamic nodeList;
@dynamic imageUrl;

- (NSString *)nodeName {
    NSString *str = [[[self elementsForName:@"name"] objectAtIndex:0] stringValue];
    return str;
}

- (NSString *)url {
    NSString *str = [[[self elementsForName:@"url"] objectAtIndex:0] stringValue];
    return str;
}

- (NSString *)pageURL {
    NSString *str = [[[self elementsForName:@"pageurl"] objectAtIndex:0] stringValue];
    return str;
}

- (NSString *)hashName {
    NSString *str = [[[self elementsForName:@"hashname"] objectAtIndex:0] stringValue];
    return str;
}

- (NSArray *)nodeList {
    //return [(GDataXMLElement *)[[self elementsForName:@"nodeList"] objectAtIndex:0] elementsForName:@"node"];
    return [[[self elementsForName:@"nodelist"] objectAtIndex:0] elementsForName:@"node"];
    //return [self nodesForXPath:@"/nodeList" error:nil];
}

- (NSString *)imageUrl {
    NSString *imageUrl = [[[self elementsForName:@"imageUrl"] objectAtIndex:0] stringValue];
    return imageUrl;
}

- (NSString *)title {
    NSString *str = [[[self elementsForName:@"title"] objectAtIndex:0] stringValue];
    return str;
}

@end
