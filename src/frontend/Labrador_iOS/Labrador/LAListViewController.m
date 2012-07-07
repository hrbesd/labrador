//
//  LAListViewController.m
//  Labrador
//
//  Created by Guo Xinrong on 12-6-27.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "LAListViewController.h"
#import "LogTools.h"
#import "LAXMLData.h"
#import "LAListCell.h"
#import "GDataXMLElement+List.h"
#import "NSString+URL.h"
#import "LAListCellBgView.h"
#import "LAArticleViewController.h"

@interface LAListViewController ()

@end

@implementation LAListViewController

@synthesize xmlData = _xmlData;

- (id)initWithStyle:(UITableViewStyle)style url:(NSString *)urlStr
{
    self = [super initWithStyle:style];
    if (self) {
        // custom style
        //[self.tableView setSeparatorColor:[UIColor clearColor]];
        
        self.xmlData = [[LAXMLData alloc] initWithURL:urlStr type:XMLDataType_List];
        [_xmlData setDelegate:self];
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
 
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [_xmlData.listData count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    
    if (!cell) {
        cell = [[LAListCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    
    GDataXMLElement *currentElem = [_xmlData.listData objectAtIndex:indexPath.row];
    
    [cell.textLabel setText:currentElem.nodeName];
    
    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    GDataXMLElement *currentElem = (GDataXMLElement *)[_xmlData.listData objectAtIndex:indexPath.row];
    
    CGSize size = [currentElem.nodeName sizeWithFont:[UIFont systemFontOfSize:20.0f] forWidth:280 lineBreakMode:UILineBreakModeWordWrap];
    
    size = [currentElem.nodeName sizeWithFont:[UIFont systemFontOfSize:20.0f] constrainedToSize:CGSizeMake(280, 9999) lineBreakMode:UILineBreakModeWordWrap];
    
    //NSLog(@"%@", NSStringFromCGSize(size));
    //NSLog(@"index:[%d] height:[%f]", indexPath.row, fmaxf(size.height + 10, 40.0f));
    
    return 53.0f;
    return fmaxf(size.height + 10, 40.0f);
}

#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    GDataXMLElement *currentElem = (GDataXMLElement *)[_xmlData.listData objectAtIndex:indexPath.row];
    
    NSString *url = [NSString URLWithPath:currentElem.pageURL];
    
    DLog(@"%@", currentElem.pageURL);
    
    NSString *dir = [[currentElem.pageURL componentsSeparatedByString:@"/"] objectAtIndex:0];
    
    if ([dir isEqualToString:@"a"]) {
        // this is article
        LAArticleViewController *articleVC = [[LAArticleViewController alloc] initWithURL:url];
        [articleVC setTitle:@"新闻"];
        
        [self.navigationController pushViewController:articleVC animated:YES];
    }
    else {
        // this is category
        LAListViewController *listVC = [[LAListViewController alloc] initWithStyle:UITableViewStylePlain url:url];
        [listVC setTitle:currentElem.nodeName];
        
        [self.navigationController pushViewController:listVC animated:YES];
    }
    
    
    
}

#pragma mark - LAXMLDataDelegate

- (void)listDidFinishLoading:(LAXMLData *)list {
    // not a good 
    [self.tableView reloadData];
}


@end
