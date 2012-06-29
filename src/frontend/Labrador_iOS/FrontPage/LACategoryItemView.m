//
//  LACategoryItemView.m
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-28.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "LACategoryItemView.h"
#import <QuartzCore/QuartzCore.h>

@implementation LACategoryItemView

@synthesize button = _button;
@synthesize textLabel = _textLabel;

- (id)initWithFrame:(CGRect)frame item:(LACategoryItem *)item {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        [self.layer setBorderColor:[[UIColor greenColor] CGColor]];
        [self.layer setBorderWidth:2];
        
        
        
    }
    return self;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end
