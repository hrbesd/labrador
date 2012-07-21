//
//  LADetailViewController.m
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-22.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "LADetailViewController.h"
#import "GDataXMLElement+Article.h"
#import "GRMustache.h"
#import "NSString+HTML.h"
#import <QuartzCore/QuartzCore.h>

@interface LADetailViewController ()

@end

@implementation LADetailViewController

@synthesize xmlDoc = _xmlDoc;
@synthesize webView = _webView;
@synthesize hashName = _hashName;

- (id)initWithHashName:(NSString *)hashName {
    self = [super init];
    if (self) {
        self.hashName = hashName;
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	
    
    // load article xml
    NSString *xmlPath = [[NSBundle mainBundle] pathForResource:_hashName ofType:@"xml"];
    NSData *xmlData = [NSMutableData dataWithContentsOfFile:xmlPath];
    NSError *error;
    self.xmlDoc = [[GDataXMLDocument alloc] initWithData:xmlData options:0 error:&error];
    
    if (error) {
        NSLog(@"%@", [error localizedDescription]);
    }
    
    if (_xmlDoc == nil) {
        NSLog(@"xml doc nil");
    }
    
    GDataXMLElement *articleElem = [_xmlDoc rootElement];
    NSLog(@"%@", articleElem.title);
    
    // load html template
    NSString *templatePath = [[NSBundle mainBundle] pathForResource:@"content_template" ofType:@"html"];
    
    GRMustacheTemplate *template = [GRMustacheTemplate templateFromContentsOfFile:templatePath error:&error];
    
    if (error) {
        NSLog(@"%@", [error localizedDescription]);
    }
    
    NSDictionary *contentDic = [NSDictionary dictionaryWithObjectsAndKeys:
                                articleElem.title, @"title",
                                articleElem.lastModified, @"ptime",
                                articleElem.author, @"author",
                                @"", @"content_image",
                                [articleElem.bodyData stringWithNewLinesAsBRs], @"body",
                                nil];
    
    NSString *renderedHTMLStr = [template renderObject:contentDic];
    renderedHTMLStr = [renderedHTMLStr stringByDecodingHTMLEntities];
    
    NSLog(@"%@", renderedHTMLStr);
    
    self.webView = [[UIWebView alloc] initWithFrame:CGRectMake(0, 0, 320, 480 - 20 - 44)];
    [self.view addSubview:_webView];
    
    [_webView loadHTMLString:renderedHTMLStr baseURL:[NSURL fileURLWithPath:[[NSBundle mainBundle] bundlePath]]];
    
    /*[self.view.layer setBorderColor:[[UIColor greenColor] CGColor]];
    [self.view.layer setBorderWidth:2];
    
    [_webView.layer setBorderColor:[[UIColor blueColor] CGColor]];
    [_webView.layer setBorderWidth:2];*/
    
    UIBarButtonItem *increaseFontSizeBarButton = [[UIBarButtonItem alloc] initWithTitle:@"+" style:UIBarButtonItemStyleBordered target:self action:@selector(changeFontSizeBarButtonTouchUpInside:)];
    [increaseFontSizeBarButton setTag:0];
    
    [increaseFontSizeBarButton setAccessibilityLabel:@"增加字体大小"];
    
    UIBarButtonItem *decreaseFontSizeBarButton = [[UIBarButtonItem alloc] initWithTitle:@"-" style:UIBarButtonItemStyleBordered target:self action:@selector(changeFontSizeBarButtonTouchUpInside:)];
    [decreaseFontSizeBarButton setTag:1];
    
    [decreaseFontSizeBarButton setAccessibilityLabel:@"减小字体大小"];

    
    [self.navigationItem setRightBarButtonItems:[NSArray arrayWithObjects:increaseFontSizeBarButton, decreaseFontSizeBarButton, nil]];
}

- (void)changeFontSizeWithMultiplier:(int)multiplier {
    NSString *increaseScript = [NSString stringWithFormat:@"resizeText(%d)", multiplier];
    [_webView stringByEvaluatingJavaScriptFromString:increaseScript];
    //NSLog(@"excuted");
}

- (void)changeFontSizeBarButtonTouchUpInside:(UIBarButtonItem *)sender {
    switch (sender.tag) {
        case 0:
            [self changeFontSizeWithMultiplier:1];
            break;
        case 1:
            [self changeFontSizeWithMultiplier:-1];
            break;
        default:
            NSLog(@"error barbutton");
            break;
    }
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

@end
