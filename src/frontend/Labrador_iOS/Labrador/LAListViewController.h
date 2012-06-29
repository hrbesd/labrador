//
//  LAListViewController.h
//  Labrador
//
//  Created by Guo Xinrong on 12-6-27.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LAList.h"

@interface LAListViewController : UITableViewController  <LAListDelegate>

@property (strong, nonatomic) LAList *list;

- (id)initWithStyle:(UITableViewStyle)style url:(NSString *)urlStr;

@end
