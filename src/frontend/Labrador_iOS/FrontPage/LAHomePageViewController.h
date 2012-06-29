//
//  LAHomePageViewController.h
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-28.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LACategoryView.h"

@class BHTabsViewController;
@class LAHeadlinesView;
@class LAHighlightsView;

@interface LAHomePageViewController : UIViewController <LACategoryViewDelegae>

@property (strong, nonatomic) BHTabsViewController *tabVC;
@property (strong, nonatomic) LACategoryView *categoryView;
@property (strong, nonatomic) LAHeadlinesView *headlinesView;
@property (strong, nonatomic) LAHighlightsView *highlightsView;

@end
