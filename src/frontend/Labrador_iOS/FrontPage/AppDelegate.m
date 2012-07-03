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

#define isRetina ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(640, 960), [[UIScreen mainScreen] currentMode].size) : NO)

@implementation AppDelegate

@synthesize window = _window;
@synthesize navController = _navController;

- (UIImage *)backgroundImageWithStrokeColor:(UIColor *)strokeColor fillColor:(UIColor *)fillColor {
    CGFloat scale = isRetina ? 2.0f : 1.0f;

    UIGraphicsBeginImageContext(CGSizeMake(20 * scale, 44 * scale));
    CGContextRef context = UIGraphicsGetCurrentContext();
    UIBezierPath *bezierPath = [UIBezierPath bezierPathWithRoundedRect:CGRectMake(0 * scale, 0 * scale, 19 * scale, 43 * scale) cornerRadius:6 * scale];
    
    CGAffineTransform ctm = CGAffineTransformMakeTranslation(0.5 * scale, 0.5 * scale);
    CGContextConcatCTM(context, ctm);
    
    CGContextSaveGState(context);
    CGContextAddPath(context, bezierPath.CGPath);
    CGContextSetFillColorWithColor(context, fillColor.CGColor);
    CGContextFillPath(context);
    CGContextRestoreGState(context);
    
    CGContextSaveGState(context);
    CGContextAddPath(context, bezierPath.CGPath);
    CGContextSetStrokeColorWithColor(context, strokeColor.CGColor);
    CGContextSetLineWidth(context, 1 * scale);
    CGContextStrokePath(context);
    CGContextRestoreGState(context);

    UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    image = [UIImage imageWithCGImage:image.CGImage scale:scale orientation:UIImageOrientationUp];
    //return image;
    return [image resizableImageWithCapInsets:UIEdgeInsetsMake(0, 7, 0, 7)];
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    
    LAHomePageViewController *homePageVC = [[LAHomePageViewController alloc] initWithURL:[NSString URLWithPath:@"index.xml"]];
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
    
    GSBarButtonItemWithPopOver *popOverBarButton = [[GSBarButtonItemWithPopOver alloc] initWithTitle:@"工具栏" style:UIBarButtonItemStyleBordered popUpBounds:CGRectMake(0, 0, 200, 100)];
    
    [homePageVC.navigationItem setRightBarButtonItem:popOverBarButton];
    
    UIView *popOverView = popOverBarButton.popOverView;
    
    
    UIButton *fontSmaller = [UIButton buttonWithType:UIButtonTypeCustom];
    
    //[fontSmaller.layer setBorderColor:[[UIColor redColor] CGColor]];
    //[fontSmaller.layer setBorderWidth:2];
    
    [fontSmaller setTitle:@"＋" forState:UIControlStateNormal];
    [fontSmaller setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [fontSmaller setBackgroundImage:[self backgroundImageWithStrokeColor:[UIColor grayColor] fillColor:[UIColor whiteColor]] forState:UIControlStateNormal];
    [fontSmaller setBackgroundImage:[self backgroundImageWithStrokeColor:[UIColor grayColor] fillColor:[UIColor lightGrayColor]] forState:UIControlStateHighlighted];
    [fontSmaller setFrame:CGRectMake(11, 27, 80, 44)];
    
    
    UIButton *fontBigger = [UIButton buttonWithType:UIButtonTypeCustom];
    [fontBigger setTitle:@"－" forState:UIControlStateNormal];
    [fontBigger setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [fontBigger setBackgroundImage:[self backgroundImageWithStrokeColor:[UIColor grayColor] fillColor:[UIColor whiteColor]] forState:UIControlStateNormal];
    [fontBigger setBackgroundImage:[self backgroundImageWithStrokeColor:[UIColor grayColor] fillColor:[UIColor lightGrayColor]] forState:UIControlStateHighlighted];
    [fontBigger setFrame:CGRectMake(11 + 80 + 18, 27, 80, 44)];
    
    [popOverView addSubview:fontSmaller];
    [popOverView addSubview:fontBigger];
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
