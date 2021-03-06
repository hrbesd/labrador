//
//  ListCellBgView.h
//  Labrador
//
//  Created by 鑫容 郭 on 12-7-1.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 * LAListCellBgView
 * Background View of the cell of the tableView(list)
 */

@interface LAListCellBgView : UIView

@property (strong, nonatomic) UIColor *rectColor;

- (id)initWithFrame:(CGRect)frame color:(UIColor *)rectColor;

@end
