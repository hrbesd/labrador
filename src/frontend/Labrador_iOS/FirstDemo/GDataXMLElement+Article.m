//
//  GDataXMLElement+Article.m
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-23.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "GDataXMLElement+Article.h"

@implementation GDataXMLElement (Article)

@dynamic title;
@dynamic author;
@dynamic lastModified;
@dynamic bodyData;

- (NSString *)title {
    return [[[self elementsForName:@"title"] objectAtIndex:0] stringValue];
}

- (NSString *)author {
    return [[[self elementsForName:@"author"] objectAtIndex:0] stringValue];
}

- (NSString *)lastModified {
    NSString *timeStr = [[[self elementsForName:@"lastModified"] objectAtIndex:0] stringValue];
    NSTimeInterval time = [timeStr doubleValue] / 1000;
    NSDate *date = [NSDate dateWithTimeIntervalSince1970:time];
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"yyyy年MM月dd日"];
    
    return [dateFormatter stringFromDate:date];
}

- (NSString *)bodyData {
    return [[[self elementsForName:@"bodyData"] objectAtIndex:0] stringValue];
}

@end
