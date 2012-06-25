//
//  LADetailViewController.h
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-22.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import <UIKit/UIKit.h>

@class GDataXMLDocument;

@interface LADetailViewController : UIViewController

@property (strong, nonatomic) GDataXMLDocument *xmlDoc;
@property (strong, nonatomic) UIWebView *webView;
@property (strong, nonatomic) NSString *hashName;


- (id)initWithHashName:(NSString *)hashName;

@end
