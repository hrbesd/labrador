//
//  LAListViewController.h
//  Labrador
//
//  Created by Guo Xinrong on 12-6-27.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LAXMLData.h"

/**
 * LAListViewController
 * Show the category as a list
 */

@interface LAListViewController : UITableViewController  <LAXMLDataDelegate>

@property (strong, nonatomic) LAXMLData *xmlData;

- (id)initWithStyle:(UITableViewStyle)style url:(NSString *)urlStr;

@end
