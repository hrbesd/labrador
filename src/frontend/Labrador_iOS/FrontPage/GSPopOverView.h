//
//  GSPopOverView.h
//  Labrador
//
//  Created by 鑫容 郭 on 12-7-1.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol GSPopOverViewDelegate;

@interface GSPopOverView : UIView

@property (assign, nonatomic) CGPoint point;

@property (weak, nonatomic) id<GSPopOverViewDelegate> delegate;

//- (id)initAtPoint:(CGPoint)point backgroundBounds:(CGRect)bounds;

- (id)initWithBounds:(CGRect)bounds;

@end


@protocol GSPopOverViewDelegate <NSObject>

- (void)popOverViewTouchOutside:(GSPopOverView *)popOverView;

@end