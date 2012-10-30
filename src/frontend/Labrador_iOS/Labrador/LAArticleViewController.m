//
//  LAArticleViewController.m
//  Labrador
//
//  Created by 鑫容 郭 on 12-7-3.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "LAArticleViewController.h"
#import "LAXMLData.h"
#import "GSBarButtonItemWithPopOver.h"
#import "GRMustache.h"
#import "NSString+HTML.h"
#import "GDataXMLElement+Article.h"
#import "MBProgressHUD.h"

@interface LAArticleViewController ()

@property (strong, nonatomic) UIWebView *webView;
@property (strong, nonatomic) NSString *urlStr;
@property (strong, nonatomic) MBProgressHUD *hud;

@end

@implementation LAArticleViewController

@synthesize xmlData = _xmlData;
@synthesize webView = _webView;
@synthesize urlStr = _urlStr;
@synthesize hud = _hud;

- (id)initWithURL:(NSString *)urlStr {
    self = [super init];
    if (self) {
        self.urlStr = urlStr;
        
    }
    return self;
}

- (void)showArticle {
    // load html template
    NSError *error;
    NSString *templatePath = [[NSBundle mainBundle] pathForResource:@"content_template" ofType:@"html"];
    
    GRMustacheTemplate *template = [GRMustacheTemplate templateFromContentsOfFile:templatePath error:&error];
    
    if (error) {
        NSLog(@"%@", [error localizedDescription]);
    }
    
    //NSLog(@"%@", [_xmlData.articleElem.bodyData stringWithNewLinesAsBRs]);
    
    NSDictionary *contentDic = [NSDictionary dictionaryWithObjectsAndKeys:
                                _xmlData.articleElem.articleTitle, @"title",
                                _xmlData.articleElem.lastModified, @"ptime",
                                _xmlData.articleElem.author, @"author",
                                @"", @"content_image",
                                //[_xmlData.articleElem.bodyData stringWithNewLinesAsBRs], @"body",
                                _xmlData.articleElem.bodyData, @"body",
                                nil];
    
    NSString *renderedHTMLStr = [template renderObject:contentDic];
    renderedHTMLStr = [renderedHTMLStr stringByDecodingHTMLEntities];
    
    //NSLog(@"%@", renderedHTMLStr);
    
    [_webView loadHTMLString:renderedHTMLStr baseURL:[NSURL fileURLWithPath:[[NSBundle mainBundle] bundlePath]]];
}

#define isRetina ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(640, 960), [[UIScreen mainScreen] currentMode].size) : NO)

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

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.xmlData = [[LAXMLData alloc] initWithURL:_urlStr type:XMLDataType_Article delegate:self];
    
    self.webView = [[UIWebView alloc] initWithFrame:CGRectMake(0, 0, 320, 480 - 20 -44)];
    [self.view addSubview:_webView];
    
    GSBarButtonItemWithPopOver *popOverBarButton = [[GSBarButtonItemWithPopOver alloc] initWithTitle:@"工具栏" style:UIBarButtonItemStyleBordered popUpBounds:CGRectMake(0, 0, 200, 100)];
    
    [self.navigationItem setRightBarButtonItem:popOverBarButton];
    
    UIView *popOverView = popOverBarButton.popOverView;
    
    
    UIButton *fontSmaller = [UIButton buttonWithType:UIButtonTypeCustom];
    
    //[fontSmaller.layer setBorderColor:[[UIColor redColor] CGColor]];
    //[fontSmaller.layer setBorderWidth:2];
    
    [fontSmaller setTitle:@"＋" forState:UIControlStateNormal];
    [fontSmaller setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [fontSmaller setBackgroundImage:[self backgroundImageWithStrokeColor:[UIColor grayColor] fillColor:[UIColor whiteColor]] forState:UIControlStateNormal];
    [fontSmaller setBackgroundImage:[self backgroundImageWithStrokeColor:[UIColor grayColor] fillColor:[UIColor lightGrayColor]] forState:UIControlStateHighlighted];
    [fontSmaller setFrame:CGRectMake(11, 27, 80, 44)];
    
    [fontSmaller addTarget:self action:@selector(changeFontSizeButtonTouchUpInside:) forControlEvents:UIControlEventTouchUpInside];
    [fontSmaller setTag:0];
    
    [fontSmaller setAccessibilityLabel:@"增加字体大小"];
    
    
    UIButton *fontBigger = [UIButton buttonWithType:UIButtonTypeCustom];
    [fontBigger setTitle:@"－" forState:UIControlStateNormal];
    [fontBigger setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [fontBigger setBackgroundImage:[self backgroundImageWithStrokeColor:[UIColor grayColor] fillColor:[UIColor whiteColor]] forState:UIControlStateNormal];
    [fontBigger setBackgroundImage:[self backgroundImageWithStrokeColor:[UIColor grayColor] fillColor:[UIColor lightGrayColor]] forState:UIControlStateHighlighted];
    [fontBigger setFrame:CGRectMake(11 + 80 + 18, 27, 80, 44)];
    
    [fontBigger addTarget:self action:@selector(changeFontSizeButtonTouchUpInside:) forControlEvents:UIControlEventTouchUpInside];
    [fontBigger setTag:1];
    
    [fontBigger setAccessibilityLabel:@"降低字体大小"];
    
    [popOverView addSubview:fontSmaller];
    [popOverView addSubview:fontBigger];
    
    // a little trick
    [self.view bringSubviewToFront:_hud];
    
    if (_xmlData.articleElem != nil) {
        [self showArticle];
    }
}

- (BOOL)canBecomeFirstResponder {
    return YES;
}

- (void)viewDidAppear:(BOOL)animated {
    [self becomeFirstResponder];
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

- (void)changeFontSizeWithMultiplier:(int)multiplier {
    NSString *increaseScript = [NSString stringWithFormat:@"resizeText(%d)", multiplier];
    [_webView stringByEvaluatingJavaScriptFromString:increaseScript];
    //NSLog(@"excuted");
}

- (void)changeFontSizeButtonTouchUpInside:(UIButton *)sender {
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


#pragma mark - LAXMLDataDelegate

- (void)listWillStartLoading:(LAXMLData *)list {
    self.hud = [[MBProgressHUD alloc] initWithView:self.view];
    [self.view addSubview:_hud];
    
    [_hud setLabelText:@"加载中"];
    
    [_hud show:YES];
    UIAccessibilityPostNotification(UIAccessibilityAnnouncementNotification, @"加载中");
}

- (void)listDidFinishLoading:(LAXMLData *)list {
    // load page
    [self showArticle];
    UIAccessibilityPostNotification(UIAccessibilityAnnouncementNotification, @"加载完成");
    [_hud hide:YES];
}

- (void)list:(LAXMLData *)list failWithError:(NSError *)error {
    [_hud hide:YES];
    self.hud = [[MBProgressHUD alloc] initWithView:self.view];
    [_hud setLabelText:@"加载出错"];
    [self.view addSubview:_hud];
    [_hud show:YES];
    [_hud hide:YES afterDelay:2];
    UIAccessibilityPostNotification(UIAccessibilityAnnouncementNotification, @"加载出错");
    NSLog(@"加载出错");
}

#pragma mark - Shake 

- (void)motionEnded:(UIEventSubtype)motion withEvent:(UIEvent *)event {
    if (event.subtype == UIEventSubtypeMotionShake) {
        NSLog(@"shake");
        [_webView stringByEvaluatingJavaScriptFromString:@"changeStyle()"];
    }
}

@end
