//
//  ListCellBgView.m
//  Labrador
//
//  Created by 鑫容 郭 on 12-7-1.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "LAListCellBgView.h"
#import "LogTools.h"

@implementation LAListCellBgView

#define vPercentOfHeight 0.8f
#define vRectWidth 7.0f

@synthesize rectColor = _rectColor;

- (id)initWithFrame:(CGRect)frame color:(UIColor *)rectColor {
    self = [super initWithFrame:frame];
    if (self) {
        self.rectColor = rectColor;
        self.backgroundColor = [UIColor clearColor];
        
    }
    return self;
}

- (id)initWithFrame:(CGRect)frame {
    return [self initWithFrame:frame color:[UIColor colorWithRed:51 green:181 blue:229 alpha:1.0]];
}

- (CGPathRef)makePath {
    CGFloat height = self.frame.size.height;
    CGFloat rectHeight = height * vPercentOfHeight;
    CGFloat originY = height * ((1 - vPercentOfHeight) / 2);
    
    CGRect rect = CGRectMake(0, originY, vRectWidth, rectHeight);

    CGPathRef path = CGPathCreateWithRect(rect, NULL);

    return path;
}

- (void)drawRect:(CGRect)rect {
    //DLog(@"%@", NSStringFromCGRect(self.frame));
    
    [super drawRect:rect];
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGPathRef path = [self makePath];
    
    CGContextSaveGState(context);
    CGContextAddPath(context, path);
    CGContextSetFillColorWithColor(context, _rectColor.CGColor);
    CGContextFillPath(context);
    CGContextRestoreGState(context);
    
    CFRelease(path);
}


@end
