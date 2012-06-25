//
//  LANodeListViewController.h
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-22.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface LANodeListViewController : UITableViewController

@property (strong, nonatomic) NSMutableArray *nodeList;
@property (strong, nonatomic) NSString *accessibilityAnnounceText;

- (id)initWithStyle:(UITableViewStyle)style nodeList:(NSArray *)nodeList;

@end
