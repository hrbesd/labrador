//
//  LAHighlightsView.m
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-28.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "LAHighlightsView.h"

@interface LAHighlightsView ()

@property (strong, nonatomic) UIView *currentView;
@property (strong, nonatomic) NSMutableArray *views;
@property (assign, nonatomic) NSInteger numOfPages;
@property (assign, nonatomic) NSInteger curPage;

@property (assign, nonatomic) LAScrollDirection scrollDirection;

@end

@implementation LAHighlightsView

@synthesize highlightsViewDelegate = _highlightsViewDelegate;
@synthesize currentView = _currentView;
@synthesize views = _views;
@synthesize numOfPages = _numOfPages;
@synthesize curPage = _curPage;
@synthesize scrollDirection = _scrollDirection;

- (id)initWithFrame:(CGRect)frame scrollDirection:(LAScrollDirection)direction numOfPages:(NSInteger) numOfPages;
{
    self = [super initWithFrame:frame];
    if (self) {
        [self setBackgroundColor:[UIColor whiteColor]];
        
        self.scrollDirection = direction;
        self.numOfPages = numOfPages;
        
        self.curPage = 1;
        
        self.views = [NSMutableArray array];
        
        self.showsVerticalScrollIndicator = NO;
        self.showsHorizontalScrollIndicator = NO;
        self.pagingEnabled = YES;
        super.delegate = self;
        
        if (_scrollDirection == LAScrollDirection_Landscape) {
            self.contentSize = CGSizeMake(self.frame.size.width * 3, self.frame.size.height);
        }
        else {
            self.contentSize = CGSizeMake(self.frame.size.width, self.frame.size.height * 3);
        }
        
    }
    return self;
}

#pragma mark - Accessory

- (void)setDelegate:(id<UIScrollViewDelegate>)delegate {
    NSLog(@"Cannot set Delegate");
}

#pragma mark - Layout

- (void)layoutSubviews {
    [super layoutSubviews];
    
    
}

@end
