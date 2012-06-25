//
//  LACategoryNode.m
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-22.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "LANode.h"

@implementation LANode

@synthesize name = _name;
@synthesize url = _url;
@synthesize refreshRate = _refreshRate;
@synthesize hashName = _hashName;
@synthesize nodeList = _nodeList;

- (id)initWithName:(NSString *)name url:(NSString *)url refreshRate:(NSString *)refreshRate hashName:(NSString *)hashName nodeList:(NSArray *)nodeList {
    
    self = [super init];
    
    if (self) {
        self.name = name;
        self.url = url;
        self.refreshRate = refreshRate;
        self.hashName = hashName;
        self.nodeList = [NSMutableArray arrayWithArray:nodeList];
    }
    
    return self;
}

@end
