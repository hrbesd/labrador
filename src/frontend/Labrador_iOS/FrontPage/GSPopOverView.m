//
//  GSPopOverView.m
//  Labrador
//
//  Created by 鑫容 郭 on 12-7-1.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "GSPopOverView.h"
#import "LogTools.h"
#import <QuartzCore/QuartzCore.h>

@interface GSPopOverView ()

@property (strong, nonatomic) UIImageView *popOverView;
@property (strong, nonatomic) UIButton *invisibleButton;

- (CGRect)backgrounFrameWithPoint:(CGPoint)point bounds:(CGRect)bounds;

@end

@implementation GSPopOverView

@synthesize popOverView = _popOverView;
@synthesize point = _point;
@synthesize delegate = _delegate;
@synthesize invisibleButton = _invisibleButton;

- (id)initWithBounds:(CGRect)bounds {
    self = [super initWithFrame:CGRectZero];
    if (self) {
        [self setBackgroundColor:[UIColor clearColor]];
        
        self.invisibleButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [_invisibleButton setFrame:CGRectZero];
        [_invisibleButton addTarget:self action:@selector(invisibleButtonTouchUpInside:) forControlEvents:UIControlEventTouchUpInside];
        
        [_invisibleButton setAccessibilityLabel:@"关闭工具栏"];

        [super addSubview:_invisibleButton];
        
        
        UIImage *image = [UIImage imageNamed:@"UIPopoverViewGrayBackgroundArrowUpRight.png"];
        UIEdgeInsets insects = UIEdgeInsetsMake(26, 8, 8, 42);
        self.popOverView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, bounds.size.width, bounds.size.height)];
        [_popOverView setImage:[image resizableImageWithCapInsets:insects]];
        [_popOverView setUserInteractionEnabled:YES];
        [super addSubview:_popOverView];
        
        //[self.layer setBorderColor:[[UIColor greenColor] CGColor]];
        //[self.layer setBorderWidth:2];
        
        [_popOverView.layer setShadowRadius:10];

        [_popOverView.layer setShadowColor:[[UIColor blackColor] CGColor]];
        [_popOverView.layer setShadowOpacity:0.7];
        [_popOverView.layer setShouldRasterize:YES];
        
        //[_popOverView.layer setBorderColor:[[UIColor redColor] CGColor]];
        //[_popOverView.layer setBorderWidth:2];
        
        //UITapGestureRecognizer *tapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(handleTapGesture:)];
        //[self addGestureRecognizer:tapGestureRecognizer];
    }
    return self;
}

/*- (id)initAtPoint:(CGPoint)point backgroundBounds:(CGRect)bounds {
    CGRect frame = [self frameWithPoint:point bounds:bounds];
    
    return [self initWithFrame:frame];
}*/

- (CGRect)backgrounFrameWithPoint:(CGPoint)point bounds:(CGRect)bounds {
    CGRect frame;
    frame.origin.x = point.x - bounds.size.width + 24;
    frame.origin.y = point.y;
    frame.size.width = bounds.size.width;
    frame.size.height = bounds.size.height;
    
    return frame;
}

- (void)addSubview:(UIView *)view {
    [_popOverView addSubview:view];
}

- (void)didMoveToSuperview {
    UIView *view = self.superview;
    
    [self setFrame:view.frame];
    [_invisibleButton setFrame:CGRectMake(0, 0, view.frame.size.width, view.frame.size.height)];
    
    CGRect backgroundFrame = [self backgrounFrameWithPoint:_point bounds:_popOverView.bounds];
    [_popOverView setFrame:backgroundFrame];
}

#pragma mark - Button Event

- (void)invisibleButtonTouchUpInside:(UIButton *)button {
    //DLog(@"invisible tap");
    [_delegate popOverViewTouchOutside:self];
}

@end
