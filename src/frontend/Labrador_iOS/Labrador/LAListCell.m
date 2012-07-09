//
//  LAListCell.m
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-27.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "LAListCell.h"
#import "LAListCellBgView.h"
#import "LogTools.h"
#import <QuartzCore/QuartzCore.h>

@implementation LAListCell

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        //UIColor *bgColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"cell_bg.png"]];
        
        //UIView *backgroundView = [[UIView alloc] initWithFrame:CGRectZero];
        //[backgroundView setAutoresizingMask:UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth];
        //[backgroundView setBackgroundColor:bgColor];
        //[self setBackgroundView:backgroundView];
        
        LAListCellBgView *bgView = [[LAListCellBgView alloc] initWithFrame:CGRectZero color:[UIColor colorWithRed:200 / 255.0 green:200 / 255.0 blue:200 / 255.0 alpha:1.0]];
        [bgView setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];
        
        LAListCellBgView *selectedBgView = [[LAListCellBgView alloc] initWithFrame:CGRectZero color:[UIColor colorWithRed:51.0 / 255.0 green:181.0 / 255.0 blue:229.0 / 255.0 alpha:1.0]];
        [selectedBgView setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];
        
        [self setBackgroundView:bgView];
        [self setSelectedBackgroundView:selectedBgView];
        
        [self.textLabel setLineBreakMode:UILineBreakModeWordWrap];
        [self.textLabel setFont:[UIFont boldSystemFontOfSize:17.0f]];
        [self.textLabel setNumberOfLines:2];
        [self.textLabel setHighlightedTextColor:[UIColor blackColor]];
        [self.textLabel setBackgroundColor:[UIColor clearColor]];
        //[self.textLabel.layer setBorderColor:[[UIColor redColor] CGColor]];
        //[self.textLabel.layer setBorderWidth:2];
        
        UIImageView *accessoryView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"LAAccessoryView.png"]];
        [self setAccessoryView:accessoryView];
        
        
    }
    return self;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];
    // Configure the view for the selected state
}

- (void)layoutSubviews {
    [super layoutSubviews];
    //DLog(@"%@", NSStringFromCGRect(self.textLabel.frame));
    [self.textLabel setFrame:CGRectMake(13, 0, 270 - 3, 52)];
    //DLog(@"%@", NSStringFromCGRect(self.textLabel.frame));
}

@end
