//
//  AppDelegate.h
//  FirstDemo
//
//  Created by 鑫容 郭 on 12-6-22.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import <UIKit/UIKit.h>

@class LANodeListViewController;
@class GDataXMLElement;
@class GDataXMLDocument;

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (strong, nonatomic) LANodeListViewController *nodeListViewController;

@property (strong, nonatomic) GDataXMLElement *rootElement;

@property (strong, nonatomic) GDataXMLDocument *xmlDoc;

@end
