//
//  LACategoryItemView.h
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-28.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import <UIKit/UIKit.h>

@class LACategoryItem;

@protocol LACategoryItemViewDelegate;

static NSInteger categoryImageCounter = 0; // Temporarily used

/**
 * LACategoryItemView
 * Items place in the LACategoryView
 */

@interface LACategoryItemView : UIView

@property (weak, nonatomic) id<LACategoryItemViewDelegate> delegate;
@property (strong, nonatomic) UIButton *button;
@property (strong, nonatomic) UILabel *textLabel;

- (id)initWithFrame:(CGRect)frame item:(LACategoryItem *)item;

@end

@protocol LACategoryItemViewDelegate <NSObject>

@optional

- (void)categoryItemViewSelected:(LACategoryItemView *)itemView;

@end