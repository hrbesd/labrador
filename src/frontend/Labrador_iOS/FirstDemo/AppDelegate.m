//
//  AppDelegate.m
//  FirstDemo
//
//  Created by 鑫容 郭 on 12-6-22.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "AppDelegate.h"
#import "GDataXMLElement+Labrador.h"
#import "LANodeListViewController.h"

@implementation AppDelegate

@synthesize window = _window;
@synthesize nodeListViewController = _nodeListViewController;
@synthesize rootElement = _rootElement;
@synthesize xmlDoc = _xmlDoc;

- (void)loadRealRootNode {
    
    NSString *xmlPath = [[NSBundle mainBundle] pathForResource:@"harbin.gov.cn_dir" ofType:@"xml"];
    NSData *xmlData = [NSMutableData dataWithContentsOfFile:xmlPath];
    NSError *error;
    self.xmlDoc = [[GDataXMLDocument alloc] initWithData:xmlData options:0 error:&error];
    
    if (error) {
        NSLog(@"%@",[error localizedDescription]);
        return;
    }
    
    if (_xmlDoc == nil) {
        NSLog(@"xml doc nil!");
        return;
    }
    
    //NSLog(@"%@", xmlDoc.rootElement); // DO NOT DO THIS, More than 1MB
    
    //NSString *rootNodeXPath = @"//website/node[1]";
    
    //self.rootElement = [[xmlDoc nodesForXPath:rootNodeXPath error:&error] objectAtIndex:0];
    
    self.rootElement = [[_xmlDoc.rootElement elementsForName:@"node"] objectAtIndex:0];
    
    //NSLog(@"%@", [self.rootElement url]);
    //NSLog(@"%@", [[[[[(GDataXMLElement *)[[self.rootElement elementsForName:@"nodeList"] objectAtIndex:0] elementsForName:@"node"] objectAtIndex:0] elementsForName:@"name"] objectAtIndex:0] XMLString]);
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    // Override point for customization after application launch.
    self.window.backgroundColor = [UIColor whiteColor];
    [self.window makeKeyAndVisible];
    
    [self loadRealRootNode];
    
    self.nodeListViewController = [[LANodeListViewController alloc] initWithStyle:UITableViewStylePlain nodeList:self.rootElement.nodeList];
    
    UINavigationController *navController = [[UINavigationController alloc] initWithRootViewController:_nodeListViewController];
    
    [_nodeListViewController setTitle:_rootElement.nodeName];
    
    [_window setRootViewController:navController];
    
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
