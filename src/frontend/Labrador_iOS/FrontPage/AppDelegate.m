//
//  AppDelegate.m
//  FrontPage
//
//  Created by 鑫容 郭 on 12-6-28.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "AppDelegate.h"
#import "LAHomePageViewController.h"
#import "UIImageView+WebStorage.h"
#import "UIButton+WebStorage.h"
#import "NSString+URL.h"
#import "LAListCellBgView.h"
#import "GSPopOverView.h"
#import "GSBarButtonItemWithPopOver.h"
#import <QuartzCore/QuartzCore.h>

@implementation AppDelegate

@synthesize window = _window;
@synthesize navController = _navController;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    
    LAHomePageViewController *homePageVC = [[LAHomePageViewController alloc] initWithCategoryURL:[NSString URLWithPath:@"index.xml"] headlinesURL:[NSString URLWithPath:@"mobile_headlines.xml"]];
    [homePageVC setTitle:@"首页"];
    self.navController = [[UINavigationController alloc] initWithRootViewController:homePageVC];
    //[_navController.navigationBar setTintColor:[UIColor blackColor]];
    //[_navController.navigationBar setBackgroundImage:[UIImage imageNamed:@"nav-bar-bg-silver"] forBarMetrics:UIBarMetricsDefault];
    
    NSDictionary *textAttributes = [NSDictionary dictionaryWithObjectsAndKeys:[UIColor blackColor], UITextAttributeTextColor, [UIColor whiteColor], UITextAttributeTextShadowColor, nil];
    
    [[UINavigationBar appearance] setTitleTextAttributes:textAttributes];
    [[UINavigationBar appearance] setBackgroundImage:[UIImage imageNamed:@"nav-bar-bg-silver"] forBarMetrics:UIBarMetricsDefault];
    
    [[UIBarButtonItem appearance] setTintColor:[UIColor colorWithRed:228.0 / 255.0 green:228.0 / 255.0 blue:228.0 / 255.0 alpha:1.0]];
    [[UIBarButtonItem appearance] setTitleTextAttributes:textAttributes forState:UIControlStateNormal];
    [[UIBarButtonItem appearance] setTitleTextAttributes:textAttributes forState:UIControlStateHighlighted];
    
    
    self.window.backgroundColor = [UIColor whiteColor];
    [self.window setRootViewController:_navController];
    [self.window makeKeyAndVisible];
    
    // TEST CODE
    //LAListCellBgView *bgView = [[LAListCellBgView alloc] initWithFrame:CGRectMake(0, 0, 100, 100) color:[UIColor colorWithRed:0 / 255.0 green:200 / 255.0 blue:200 / 255.0 alpha:1.0]];
    //[self.window addSubview:bgView];
    
    //GSPopOverView *pop = [[GSPopOverView alloc] initWithFrame:CGRectMake(0, 20, 100, 100)];
    //[self.window addSubview:pop];
    
    
    // TEST END
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
