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

@property (strong, nonatomic) UIImageView *backgroundView;

- (CGRect)frameWithPoint:(CGPoint)point bounds:(CGRect)bounds;

@end

@implementation GSPopOverView

@synthesize backgroundView = _backgroundView;
@synthesize point = _point;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self setBackgroundColor:[UIColor clearColor]];
        
        UIImage *image = [UIImage imageNamed:@"UIPopoverViewGrayBackgroundArrowUpRight.png"];
        UIEdgeInsets insects = UIEdgeInsetsMake(26, 8, 8, 42);
        self.backgroundView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, frame.size.width, frame.size.height)];
        [_backgroundView setImage:[image resizableImageWithCapInsets:insects]];
        [_backgroundView setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];
        [self addSubview:_backgroundView];
        
        //[self.layer setBorderColor:[[UIColor greenColor] CGColor]];
        //[self.layer setBorderWidth:2];
        [_backgroundView.layer setShadowRadius:10];

        [_backgroundView.layer setShadowColor:[[UIColor blackColor] CGColor]];
        [_backgroundView.layer setShadowOpacity:0.7];
        [_backgroundView.layer setShouldRasterize:YES];
        
        
        //[_backgroundView.layer setBorderColor:[[UIColor redColor] CGColor]];
        //[_backgroundView.layer setBorderWidth:2];
    }
    return self;
}

- (id)initAtPoint:(CGPoint)point bounds:(CGRect)bounds {
    CGRect frame = [self frameWithPoint:point bounds:bounds];
    
    return [self initWithFrame:frame];
}

- (CGRect)frameWithPoint:(CGPoint)point bounds:(CGRect)bounds {
    CGRect frame;
    frame.origin.x = point.x - bounds.size.width + 24;
    frame.origin.y = point.y;
    frame.size.width = bounds.size.width;
    frame.size.height = bounds.size.height;
    
    return frame;
}

- (void)setPoint:(CGPoint)point {
    
    _point = point;
    
    CGRect frame = [self frameWithPoint:_point bounds:self.bounds];
    
    [self setFrame:frame];
    
    //DLog(@"%@", NSStringFromCGRect(self.frame));
}


@end
