//
//  LAListViewController.m
//  Labrador
//
//  Created by Guo Xinrong on 12-6-27.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "LAListViewController.h"
#import "LogTools.h"
#import "LAList.h"
#import "LAListCell.h"
#import "GDataXMLElement+List.h"
#import "NSString+URL.h"
#import "LAListCellBgView.h"

@interface LAListViewController ()

@end

@implementation LAListViewController

@synthesize list = _list;

- (id)initWithStyle:(UITableViewStyle)style url:(NSString *)urlStr
{
    self = [super initWithStyle:style];
    if (self) {
        // custom style
        //[self.tableView setSeparatorColor:[UIColor clearColor]];
        
        self.list = [[LAList alloc] initWithURL:urlStr];
        [_list setDelegate:self];
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
    return [_list.listData count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    
    if (!cell) {
        cell = [[LAListCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    
    GDataXMLElement *currentElem = [_list.listData objectAtIndex:indexPath.row];
    
    [cell.textLabel setText:currentElem.nodeName];
    
    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    GDataXMLElement *currentElem = (GDataXMLElement *)[_list.listData objectAtIndex:indexPath.row];
    
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
    GDataXMLElement *currentElem = (GDataXMLElement *)[_list.listData objectAtIndex:indexPath.row];
    
    NSString *url = [NSString URLWithPath:currentElem.pageURL];
    
    DLog(@"%@", currentElem.pageURL);
    
    LAListViewController *listVC = [[LAListViewController alloc] initWithStyle:UITableViewStylePlain url:url];
    [listVC setTitle:currentElem.nodeName];
    
    [self.navigationController pushViewController:listVC animated:YES];
    
}

#pragma mark - LAListDelegate

- (void)listDidFinishLoading:(LAList *)list {
    // not a good 
    [self.tableView reloadData];
}


@end
