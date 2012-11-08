//
//  NSString+URL.m
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-27.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "NSString+URL.h"

@implementation NSString (URL)

+ (NSString *)URLWithPath:(NSString *)path {
    //NSString *finalURL = [NSString stringWithFormat:@"http://harbin-test.yunmd.info/%@", path];
    NSString *finalURL = [NSString stringWithFormat:@"http://yunmd.mangren.com/%@", path];
    //NSString *finalURL = [NSString stringWithFormat:@"http://localhost/nav/%@", path];
    return finalURL;
}

@end
