//
//  LACategoryVieww.h
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-28.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface LACategoryView : UIView <UIScrollViewDelegate>

@property (strong, nonatomic) NSArray *items;
@property (assign, nonatomic) NSUInteger numberOfRows;
@property (assign, nonatomic) NSUInteger numberOfCols;

- (id)initWithItems:(NSArray *)items;

- (void)updateWithItems:(NSArray *)items;

@end
