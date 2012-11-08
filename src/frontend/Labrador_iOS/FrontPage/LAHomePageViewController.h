//
//  LAHomePageViewController.h
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-28.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LACategoryView.h"
#import "LAXMLData.h"
#import "CycleScrollView.h"

@class BHTabsViewController;
@class LAHeadlinesView;
@class LAHighlightsView;

/**
 * LAHomePageViewController
 * The home page of the app
 */

@interface LAHomePageViewController : UIViewController <LACategoryViewDelegae, LAXMLDataDelegate, UITableViewDelegate, UITableViewDataSource, CycleScrollViewDelegate>

@property (strong, nonatomic) BHTabsViewController *tabVC;
@property (strong, nonatomic) LACategoryView *categoryView;
@property (strong, nonatomic) LAHeadlinesView *headlinesView;
@property (strong, nonatomic) LAHighlightsView *highlightsView;
@property (strong, nonatomic) CycleScrollView *cycleScrollView;

@property (strong, nonatomic) LAXMLData *list;
@property (strong, nonatomic) LAXMLData *headLines;

- (id)initWithCategoryURL:(NSString *)categoryURLStr headlinesURL:(NSString *)headLinesURLStr;

@end
