//
//  LAArticleViewController.h
//  Labrador
//
//  Created by 鑫容 郭 on 12-7-3.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LAXMLData.h"

@interface LAArticleViewController : UIViewController <LAXMLDataDelegate>

@property (strong, nonatomic) LAXMLData *xmlData;

- (id)initWithURL:(NSString *)urlStr;

@end
