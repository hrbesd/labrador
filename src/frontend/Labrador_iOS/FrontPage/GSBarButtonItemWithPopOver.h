//
//  GSBarButtonItemWithPopOver.h
//  Labrador
//
//  Created by 鑫容 郭 on 12-7-1.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface GSBarButtonItemWithPopOver : UIBarButtonItem

@property (strong, nonatomic) UIView *popOverView;
@property (readonly, nonatomic) BOOL popOverShowUp;

- (id)initWithTitle:(NSString *)title style:(UIBarButtonItemStyle)style popUpBounds:(CGRect)bounds;

@end
