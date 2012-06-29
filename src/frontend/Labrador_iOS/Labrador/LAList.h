//
//  LAList.h
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-27.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol LAListDelegate;

@interface LAList : NSObject <NSURLConnectionDataDelegate>

@property (weak, nonatomic) id<LAListDelegate> delegate;

@property (strong, nonatomic) NSMutableArray *listData;

- (id)initWithURL:(NSString *)urlStr;
//- (void)requestWithURL:(NSString *)urlStr;

@end

@protocol LAListDelegate <NSObject>

@optional

- (void)listDidFinishLoading:(LAList *)list;

@end
