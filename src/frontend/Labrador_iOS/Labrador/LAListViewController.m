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
#import "MBProgressHUD.h"

@interface LAListViewController ()

@property (strong, nonatomic) MBProgressHUD *hud;
@property (strong, nonatomic) NSString *urlStr;

@end

@implementation LAListViewController

@synthesize xmlData = _xmlData;
@synthesize hud = _hud;
@synthesize urlStr = _urlStr;

- (id)initWithStyle:(UITableViewStyle)style url:(NSString *)urlStr
{
    self = [super initWithStyle:style];
    if (self) {
        self.urlStr = urlStr;
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    // custom style
    //[self.tableView setSeparatorColor:[UIColor clearColor]];
    
    self.xmlData = [[LAXMLData alloc] initWithURL:_urlStr type:XMLDataType_List delegate:self];
    
    UIBarButtonItem *updateButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"更新" style:UIBarButtonItemStyleBordered target:self action:@selector(updateData)];
    [self.navigationItem setRightBarButtonItem:updateButtonItem];
    
    [self.view bringSubviewToFront:_hud];
}

- (void)updateData {
    [_xmlData forceUpdate];
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
    NSUInteger count = [_xmlData.listData count];
    if (count == 0) {
        [self.tableView setSeparatorStyle:UITableViewCellSeparatorStyleNone];
    }
    else {
        [self.tableView setSeparatorStyle:UITableViewCellSeparatorStyleSingleLine];
    }
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
    
    //DLog(@"%@", currentElem.pageURL);
    
    NSArray *urlElements = [currentElem.pageURL componentsSeparatedByString:@"/"];
    
    NSString *dir = [urlElements objectAtIndex:1];
    
    NSMutableString *rebuildPath = [NSMutableString stringWithString:dir];
    
    for (int i = 2; i < [urlElements count]; i++) {
        [rebuildPath appendFormat:@"/%@", [urlElements objectAtIndex:i]];
    }
    
    url = [NSString URLWithPath:rebuildPath];
    
    DLog(@"%@", url);
    
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

- (void)listWillStartLoading:(LAXMLData *)list {
    self.hud = [[MBProgressHUD alloc] initWithView:self.tableView];
    [self.view addSubview:_hud];
    
    [_hud setLabelText:@"更新数据中"];
    UIAccessibilityPostNotification(UIAccessibilityAnnouncementNotification, @"更新数据中");
    
    [_hud show:YES];
}

- (void)listDidFinishLoading:(LAXMLData *)list {
    // not a good 
    [self.tableView reloadData];
    UIAccessibilityPostNotification(UIAccessibilityAnnouncementNotification, @"更新完成");
    [_hud hide:YES];
}

- (void)list:(LAXMLData *)list failWithError:(NSError *)error {
    [_hud hide:YES];
    self.hud = [[MBProgressHUD alloc] initWithView:self.view];
    [_hud setLabelText:@"更新出错"];
    [self.view addSubview:_hud];
    [_hud show:YES];
    [_hud hide:YES afterDelay:2];
    UIAccessibilityPostNotification(UIAccessibilityAnnouncementNotification, @"更新出错");
    NSLog(@"更新出错");
}


@end
