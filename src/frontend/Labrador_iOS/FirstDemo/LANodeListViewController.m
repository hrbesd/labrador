//
//  LANodeListViewController.m
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-22.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "LANodeListViewController.h"
#import "GDataXMLElement+Labrador.h"
#import "LADetailViewController.h"
#import <QuartzCore/QuartzCore.h>

@interface LANodeListViewController ()

@end

@implementation LANodeListViewController

@synthesize nodeList = _nodeList;
@synthesize accessibilityAnnounceText = _accessibilityAnnounceText;

- (id)initWithStyle:(UITableViewStyle)style nodeList:(NSArray *)nodeList {
    self = [super initWithStyle:style];
    if (self) {
        self.nodeList = [NSMutableArray arrayWithArray:nodeList];
    }
    return self;
}

- (id)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
    if (self) {
        self.nodeList = [NSMutableArray array];
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

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    //UIAccessibilityPostNotification(UIAccessibilityAnnouncementNotification, self.accessibilityAnnounceText);
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
    return [_nodeList count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
        [cell setAccessibilityTraits:UIAccessibilityTraitButton];
    }
    
    GDataXMLElement *currentElem = (GDataXMLElement *)[_nodeList objectAtIndex:indexPath.row];
    
    [cell.textLabel setText:currentElem.nodeName];
    [cell.textLabel setLineBreakMode:UILineBreakModeWordWrap];
    [cell.textLabel setNumberOfLines:0];
    
    NSString *path = [[NSBundle mainBundle] pathForResource:currentElem.hashName ofType:@"xml"];
    
    NSFileManager *fileManager = [NSFileManager defaultManager];
    
    
    BOOL fileExist = YES;
    
    if ([currentElem.hashName length] == 0 || ![fileManager fileExistsAtPath:path]) {
        fileExist = NO;
    }
    
    if (currentElem.nodeList != nil) {
        [cell setAccessoryType:UITableViewCellAccessoryDisclosureIndicator];
        [cell setAccessibilityHint:@"连按两次进入目录"];
    }
    else if (fileExist) {
        [cell setAccessoryType:UITableViewCellAccessoryDisclosureIndicator];
        [cell setAccessibilityHint:@"连按两次浏览正文"];
    }
    else {
        //[cell setAccessibilityTraits:UIAccessibilityTraitNotEnabled];
        [cell setAccessibilityHint:@"目录下没有内容"];
    }
    
    //[cell.textLabel.layer setBorderColor:[[UIColor greenColor] CGColor]];
    //[cell.textLabel.layer setBorderWidth:2];
    
    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    GDataXMLElement *currentElem = (GDataXMLElement *)[_nodeList objectAtIndex:indexPath.row];
    
    CGSize size = [currentElem.nodeName sizeWithFont:[UIFont systemFontOfSize:20.0f] forWidth:280 lineBreakMode:UILineBreakModeWordWrap];
    
    size = [currentElem.nodeName sizeWithFont:[UIFont systemFontOfSize:20.0f] constrainedToSize:CGSizeMake(280, 9999) lineBreakMode:UILineBreakModeWordWrap];
    
    //NSLog(@"%@", NSStringFromCGSize(size));
    
    return fmaxf(size.height + 10, 40.0f);
}

#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    GDataXMLElement *currentElem = (GDataXMLElement *)[_nodeList objectAtIndex:indexPath.row];
    
    if (currentElem.nodeList != nil) {
        LANodeListViewController *nodeListVC = [[LANodeListViewController alloc] initWithStyle:UITableViewStylePlain nodeList:currentElem.nodeList];
        [nodeListVC setTitle:currentElem.nodeName];
        [self.navigationController pushViewController:nodeListVC animated:YES];
    }
    else {
        if ([[tableView cellForRowAtIndexPath:indexPath] accessoryType] == UITableViewCellAccessoryDisclosureIndicator) {
            LADetailViewController *detailVC = [[LADetailViewController alloc] initWithHashName:currentElem.hashName];
            [detailVC setTitle:@"正文"];
            [self.navigationController pushViewController:detailVC animated:YES];
        }        
        else {
            [tableView deselectRowAtIndexPath:indexPath animated:YES];
        }
    }
    
}

@end
