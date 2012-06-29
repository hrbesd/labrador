//
//  LAHomePageViewController.m
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-28.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "LAHomePageViewController.h"
#import "BHTabsViewController.h"
#import "BHTabStyle.h"
#import "LACategoryView.h"
#import "LAHeadlinesView.h"
#import "LAHighlightsView.h"
#import "LogTools.h"
#import <QuartzCore/QuartzCore.h>

@interface LAHomePageViewController ()

@end

@implementation LAHomePageViewController

@synthesize tabVC = _tabVC;
@synthesize categoryView = _categoryView;
@synthesize headlinesView = _headlinesView;
@synthesize highlightsView = _highlightsView;

- (id)init {
    self = [super init];
    if (self) {
        NSArray *testItems = [NSArray arrayWithObjects:@"", @"", @"", @"", @"", @"", @"", @"", @"", @"", nil];
        
        self.headlinesView = [[LAHeadlinesView alloc] initWithFrame:CGRectZero];
        self.highlightsView = [[LAHighlightsView alloc] initWithFrame:CGRectMake(0, 0, 320, 160)];
        self.categoryView = [[LACategoryView alloc] initWithItems:testItems];
        
        NSArray *tabViews = [NSArray arrayWithObjects:_categoryView, _headlinesView, nil];
        NSArray *tabTitles = [NSArray arrayWithObjects:@"分类", @"头条", nil];
        
        self.tabVC = [[BHTabsViewController alloc] initWithViews:tabViews titles:tabTitles style:[BHTabStyle defaultStyle]];
        [self.tabVC.view setFrame:CGRectMake(0, 160, 320, 480 - 20 - 44 - 160)];
        //[self.tabVC.view.layer setBorderWidth:2];
        //[self.tabVC.view.layer setBorderColor:[[UIColor redColor] CGColor]];
        
        [self.view addSubview:_highlightsView];
        [self.view addSubview:_tabVC.view];
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

@end
