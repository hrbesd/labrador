//
//  GDataXMLElement+Article.m
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-23.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "GDataXMLElement+Article.h"

@implementation GDataXMLElement (Article)

@dynamic articleTitle;
@dynamic author;
@dynamic lastModified;
@dynamic bodyData;

- (NSString *)articleTitle {
    NSString *title = [[[[[self elementsForName:@"title"] objectAtIndex:0] elementsForName:@"span"] objectAtIndex:0] stringValue];
    //NSLog(@"title[%@]", title);
    return title;
}

- (NSString *)author {
    NSString *author = [[[[[self elementsForName:@"author"] objectAtIndex:0] elementsForName:@"span"] objectAtIndex:0] stringValue];
    //NSLog(@"author[%@]", author);
    return author;
}

- (NSString *)lastModified {
    /*NSString *timeStr = [[[self elementsForName:@"lastModified"] objectAtIndex:0] stringValue];
    NSTimeInterval time = [timeStr doubleValue] / 1000;
    NSDate *date = [NSDate dateWithTimeIntervalSince1970:time];
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"yyyy年MM月dd日"];
    
    return [dateFormatter stringFromDate:date];*/
    
    NSString *lastModified = [[[[[self elementsForName:@"lastmodified"] objectAtIndex:0] elementsForName:@"span"] objectAtIndex:0] stringValue];
    //NSLog(@"lastModified[%@]", lastModified);
    return lastModified;
}

- (NSString *)bodyData {
    //NSLog(@"%@", [[[self elementsForName:@"bodydata"] objectAtIndex:0] stringValue]);
    /*NSString *path = [[NSBundle mainBundle] pathForResource:@"test" ofType:@"txt"];
    
    NSString *str = [NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:nil];
    
    //NSLog(@"%@", str);
    
    return str;*/
    //NSLog(@"%@", [[[self elementsForName:@"bodydata"] objectAtIndex:0] XMLString]);
    
    return [[[self elementsForName:@"bodydata"] objectAtIndex:0] XMLString];
}

@end
