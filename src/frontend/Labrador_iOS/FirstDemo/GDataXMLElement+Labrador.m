//
//  GDataXMLElement+Labrador.m
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-22.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "GDataXMLElement+Labrador.h"

@implementation GDataXMLElement (Labrador)

@dynamic nodeName;
@dynamic url;
@dynamic refreshRate;
@dynamic hashName;
@dynamic nodeList;

- (NSString *)nodeName {
    return [[[self elementsForName:@"name"] objectAtIndex:0] stringValue];
}

- (NSString *)url {
    return [[[self elementsForName:@"url"] objectAtIndex:0] stringValue];
}

- (NSString *)hashName {
    return [[[self elementsForName:@"hashName"] objectAtIndex:0] stringValue];
}

- (NSArray *)nodeList {
    //return [(GDataXMLElement *)[[self elementsForName:@"nodeList"] objectAtIndex:0] elementsForName:@"node"];
    return [[[self elementsForName:@"nodeList"] objectAtIndex:0] elementsForName:@"node"];
    //return [self nodesForXPath:@"/nodeList" error:nil];
}


@end
