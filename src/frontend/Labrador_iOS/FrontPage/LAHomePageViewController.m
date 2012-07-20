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
#import "LAHighlightsItem.h"
#import "CycleScrollView.h"
#import "LAListCell.h"
#import "LAArticleViewController.h"
#import <QuartzCore/QuartzCore.h>

@interface LAHomePageViewController ()

@property (strong, nonatomic) NSMutableArray *items;
@property (strong, nonatomic) NSMutableArray *highlightItems; // headlines with pic
@property (strong, nonatomic) NSMutableArray *headlineItems; // headlines without pic

@property (strong, nonatomic) NSMutableArray *highlightsTitles;
@property (strong, nonatomic) NSMutableArray *highlightsImages;

@property (strong, nonatomic) NSIndexPath *selectedPath;

- (void)loadItems;

@end

@implementation LAHomePageViewController

@synthesize tabVC = _tabVC;
@synthesize categoryView = _categoryView;
@synthesize headlinesView = _headlinesView;
@synthesize highlightsView = _highlightsView;
@synthesize cycleScrollView = _cycleScrollView;
@synthesize list = _list;
@synthesize headLines = _headLines;

@synthesize items = _items;
@synthesize highlightItems = _highlightItems;
@synthesize headlineItems = _headlineItems;

@synthesize highlightsTitles = _highlightsTitles;
@synthesize highlightsImages = _highlightsImages;

@synthesize selectedPath = _selectedPath;

- (id)initWithCategoryURL:(NSString *)categoryURLStr headlinesURL:(NSString *)headLinesURLStr{
    self = [super init];
    if (self) {
        
        self.list = [[LAXMLData alloc] initWithURL:categoryURLStr type:XMLDataType_List];
        [_list setDelegate:self];
        
        self.headLines = [[LAXMLData alloc] initWithURL:headLinesURLStr type:XMLDataType_List];
        [_headLines setDelegate:self];
        
        [self loadItems];
        [self loadHeadlines];
        
        self.headlinesView = [[LAHeadlinesView alloc] initWithFrame:CGRectZero];
        [_headlinesView setDataSource:self];
        [_headlinesView setDelegate:self];
        //self.highlightsView = [[LAHighlightsView alloc] initWithFrame:CGRectMake(0, 0, 320, 160)];
        self.cycleScrollView = [[CycleScrollView alloc] initWithFrame:CGRectMake(0, 0, 320, 160) cycleDirection:CycleDirectionLandscape pictures:_highlightsImages titles:_highlightsTitles];
        [_cycleScrollView setDelegate:self];
        
        //[self.cycleScrollView.layer setBorderWidth:2];
        //[self.cycleScrollView.layer setBorderColor:[[UIColor redColor] CGColor]];
        
        self.categoryView = [[LACategoryView alloc] initWithItems:_items];
        [_categoryView setDelegate:self];
        
        NSArray *tabViews = [NSArray arrayWithObjects:_categoryView, _headlinesView, nil];
        NSArray *tabTitles = [NSArray arrayWithObjects:@"分类", @"头条", nil];
        
        self.tabVC = [[BHTabsViewController alloc] initWithViews:tabViews titles:tabTitles style:[BHTabStyle defaultStyle]];
        [self.tabVC.view setFrame:CGRectMake(0, 160, 320, 480 - 20 - 44 - 160)];
        //[self.tabVC.view.layer setBorderWidth:2];
        //[self.tabVC.view.layer setBorderColor:[[UIColor redColor] CGColor]];
        
        [self.view addSubview:_highlightsView];
        [self.view addSubview:_cycleScrollView];
        [self.view addSubview:_tabVC.view];
        
        
    }
    return self;
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

- (void)loadHeadlines {
    NSMutableArray *highlightsArr = [NSMutableArray array];
    NSMutableArray *headlinesArr = [NSMutableArray array];
    
    NSMutableArray *images = [NSMutableArray arrayWithCapacity:[_headLines.listData count]];
    NSMutableArray *titles = [NSMutableArray arrayWithCapacity:[_headLines.listData count]];
    
    for (GDataXMLElement *xmlElem in _headLines.listData) {
        LAHighlightsItem *item = [[LAHighlightsItem alloc] init];
        item.title = xmlElem.title;
        item.imageURL = xmlElem.imageUrl;
        item.url = xmlElem.url;
        
        if (item.imageURL != nil) {
            [highlightsArr addObject:item];
            [images addObject:xmlElem.imageUrl];
            [titles addObject:xmlElem.nodeName];
        }
        else {
            [headlinesArr addObject:item];
        }
    }

    self.highlightItems = highlightsArr;
    self.headlineItems = headlinesArr;
    
    self.highlightsTitles = titles;
    self.highlightsImages = images;
    
    [_cycleScrollView reloadWithPictures:_highlightsImages titles:_highlightsTitles];
    [_headlinesView reloadData];
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
    if (list == _list) { // category loaded
        [self loadItems];
    }
    else { // headlines loaded
        [self loadHeadlines];
    }
}

#pragma mark - headlines

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    [_headlinesView deselectRowAtIndexPath:_selectedPath animated:YES];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [_headLines.listData count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    
    if (!cell) {
        cell = [[LAListCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    
    GDataXMLElement *currentElem = [_headLines.listData objectAtIndex:indexPath.row];
    
    [cell.textLabel setText:currentElem.nodeName];
    
    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 53.0f;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    self.selectedPath = indexPath;
    
    GDataXMLElement *currentElem = (GDataXMLElement *)[_headLines.listData objectAtIndex:indexPath.row];
    
    NSString *url = [NSString URLWithPath:currentElem.url];
    
    //DLog(@"%@", currentElem.url);
    
    NSArray *urlElements = [currentElem.url componentsSeparatedByString:@"/"];
    
    NSString *dir = [urlElements objectAtIndex:1];
    
    NSMutableString *rebuildPath = [NSMutableString stringWithString:dir];
    
    for (int i = 2; i < [urlElements count]; i++) {
        [rebuildPath appendFormat:@"/%@", [urlElements objectAtIndex:i]];
    }
    
    url = [NSString URLWithPath:rebuildPath];
    
    DLog(@"%@", url);
    
    // this is article
    LAArticleViewController *articleVC = [[LAArticleViewController alloc] initWithURL:url];
    [articleVC setTitle:@"新闻"];
    
    [self.navigationController pushViewController:articleVC animated:YES];
}

#pragma mark - CycleScroll Delegate

- (void)cycleScrollViewDelegate:(CycleScrollView *)cycleScrollView didSelectImageView:(int)index {    
    LAHighlightsItem *currentItem = [_highlightItems objectAtIndex:index];
    NSString *url = [NSString URLWithPath:currentItem.url];
    
    //DLog(@"%@", currentItem.url);
    
    NSArray *urlElements = [currentItem.url componentsSeparatedByString:@"/"];
    
    NSString *dir = [urlElements objectAtIndex:1];
    
    NSMutableString *rebuildPath = [NSMutableString stringWithString:dir];
    
    for (int i = 2; i < [urlElements count]; i++) {
        [rebuildPath appendFormat:@"/%@", [urlElements objectAtIndex:i]];
    }
    
    url = [NSString URLWithPath:rebuildPath];
    
    DLog(@"%@", url);
    
    // this is article
    LAArticleViewController *articleVC = [[LAArticleViewController alloc] initWithURL:url];
    [articleVC setTitle:@"新闻"];
    
    [self.navigationController pushViewController:articleVC animated:YES];
    
}


@end
