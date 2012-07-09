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
#import "LACategoryItem.h"
#import "LAHeadlinesView.h"
#import "LAHighlightsView.h"
#import "LogTools.h"
#import "LAXMLData.h"
#import "GDataXMLElement+List.h"
#import "NSString+URL.h"
#import "LAListViewController.h"
#import <QuartzCore/QuartzCore.h>

@interface LAHomePageViewController ()

@property (strong, nonatomic) NSMutableArray *items;

- (void)loadItems;

@end

@implementation LAHomePageViewController

@synthesize tabVC = _tabVC;
@synthesize categoryView = _categoryView;
@synthesize headlinesView = _headlinesView;
@synthesize highlightsView = _highlightsView;
@synthesize list = _list;

@synthesize items = _items;

- (id)initWithURL:(NSString *)urlStr {
    self = [super init];
    if (self) {
        
        self.list = [[LAXMLData alloc] initWithURL:urlStr type:XMLDataType_List];
        [_list setDelegate:self];
        
        [self loadItems];
        
        self.headlinesView = [[LAHeadlinesView alloc] initWithFrame:CGRectZero];
        self.highlightsView = [[LAHighlightsView alloc] initWithFrame:CGRectMake(0, 0, 320, 160)];
        self.categoryView = [[LACategoryView alloc] initWithItems:_items];
        [_categoryView setDelegate:self];
        
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

- (id)init {
    return [self initWithURL:nil];
}

- (void)loadItems {
    NSMutableArray *itemsArr = [NSMutableArray arrayWithCapacity:[_list.listData count]];
    
    for (GDataXMLElement *xmlElem in _list.listData) {
        LACategoryItem *item = [[LACategoryItem alloc] init];
        item.text = xmlElem.nodeName;
        [itemsArr addObject:item];
    }
    
    self.items = itemsArr;
    
    [_categoryView updateWithItems:_items];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma mark - LACategoryView Delegate

- (void)categoryView:(LACategoryView *)categoryView selectedItemAtIndex:(NSUInteger)index {
    DLog(@"%d selected", index);
    GDataXMLElement *currentElem = (GDataXMLElement *)[_list.listData objectAtIndex:index];
    
    NSString *url = [NSString URLWithPath:currentElem.pageURL];
    
    LAListViewController *listVC = [[LAListViewController alloc] initWithStyle:UITableViewStylePlain url:url];
    [listVC setTitle:currentElem.nodeName];
    
    [self.navigationController pushViewController:listVC animated:YES];
    
}

#pragma mark - LAListDelegate

- (void)listDidFinishLoading:(LAXMLData *)list {
    // not a good 
    [self loadItems];
    
}


@end
