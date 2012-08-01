//
//  LACategoryItemView.m
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-28.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "LACategoryItemView.h"
#import "LACategoryItem.h"
#import "UIButton+WebStorage.h"
#import <QuartzCore/QuartzCore.h>

@implementation LACategoryItemView

@synthesize delegate = _delegate;
@synthesize button = _button;
@synthesize textLabel = _textLabel;

- (id)initWithFrame:(CGRect)frame item:(LACategoryItem *)item {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        //[self.layer setBorderColor:[[UIColor greenColor] CGColor]];
        //[self.layer setBorderWidth:2];
        
        CGRect buttonFrame;
        buttonFrame.size.width = 65;
        buttonFrame.size.height = 65;
        buttonFrame.origin.x = frame.size.width / 2 - buttonFrame.size.width / 2;
        buttonFrame.origin.y = 5;
            
        self.button = [[UIButton alloc] initWithFrame:buttonFrame];
        
        UIImage *placeholderImage = [UIImage imageNamed:[NSString stringWithFormat:@"TempIcon%d.png", item.text.length % 5 + 1]]; 
        
        [_button setStorageImageWithURL:[NSURL URLWithString:item.imageURL] placeholderImage:placeholderImage];
        //[_button setBackgroundImage:[UIImage imageNamed:@"TestIcon3.png"] forState:UIControlStateNormal];
        [_button addTarget:self action:@selector(buttonTochUpInside:) forControlEvents:UIControlEventTouchUpInside];
        
        [_button.layer setBorderColor:[[UIColor grayColor] CGColor]];
        [_button.layer setBorderWidth:2];
        
        
        self.textLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, CGRectGetMaxY(buttonFrame) + 5, frame.size.width, 15)];
        [_textLabel setTextAlignment:UITextAlignmentCenter];
        
        [_textLabel setText:item.text];
        
        //[_textLabel.layer setBorderColor:[[UIColor blueColor] CGColor]];
        //[_textLabel.layer setBorderWidth:2];
        
        [_textLabel setIsAccessibilityElement:NO];
        [_button setIsAccessibilityElement:YES];
        [_button setAccessibilityLabel:_textLabel.text];
        [_button setAccessibilityTraits:UIAccessibilityTraitButton];

        
        [self addSubview:_button];
        [self addSubview:_textLabel];
    }
    return self;
}

- (void)buttonTochUpInside:(id)sender {
    if ([_delegate respondsToSelector:@selector(categoryItemViewSelected:)]) {
        [_delegate categoryItemViewSelected:self];
    }

}

@end
