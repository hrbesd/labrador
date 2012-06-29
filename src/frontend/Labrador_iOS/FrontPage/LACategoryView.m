//
//  LACategoryVieww.m
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-28.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "LACategoryView.h"
#import "LACategoryItemView.h"
#import "LogTools.h"
#import "StyledPageControl.h"
#import <QuartzCore/QuartzCore.h>

#define vPageControlHeight 20.0f

@interface LACategoryView ()

@property (strong, nonatomic) StyledPageControl *pageControl;
@property (strong, nonatomic) UIScrollView *scrollView;

@end

@implementation LACategoryView

@synthesize pageControl = _pageControl;
@synthesize scrollView = _scrollView;
@synthesize items = _items;
@synthesize numberOfRows = _numberOfRows;
@synthesize numberOfCols = _numberOfCols;

- (id)initWithItems:(NSArray *)items {
    self = [super initWithFrame:CGRectZero];
    if (self) {
        
        _numberOfRows = 2;
        _numberOfCols = 3;
        
        self.pageControl = [[StyledPageControl alloc] initWithFrame:CGRectZero];
        [_pageControl setPageControlStyle:PageControlStyleStrokedCircle];
        [_pageControl setUserInteractionEnabled:YES];
        [_pageControl addTarget:self action:@selector(pageControlValueChanged:) forControlEvents:UIControlEventValueChanged];

        self.items = items;
        
        self.scrollView = [[UIScrollView alloc] initWithFrame:CGRectZero];
        [_scrollView setPagingEnabled:YES];
        [_scrollView setShowsVerticalScrollIndicator:NO];
        [_scrollView setShowsHorizontalScrollIndicator:NO];
        [_scrollView setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];
        
        [_scrollView setDelegate:self];
        
        //[_scrollView.layer setBorderColor:[[UIColor redColor] CGColor]];
        //[_scrollView.layer setBorderWidth:2];
        
        
        [self addSubview:_scrollView];
        [self addSubview:_pageControl];
        
        
    }
    return self;
}

- (void)didMoveToSuperview {
    //DLog(@"%@", NSStringFromCGRect(self.frame));
    
    // layout pageControl
}

- (void)layoutSubviews {
    DLog(@"%@", NSStringFromCGRect(_scrollView.frame));
    
    // remove _scrollView's subviews
    
    for (UIView *view in _scrollView.subviews) {
        [view removeFromSuperview];
    }
    
    
    // relayout _scrollView's subviews
    CGFloat itemViewWidth = _scrollView.frame.size.width / _numberOfCols;
    CGFloat itemViewHeight = (_scrollView.frame.size.height - vPageControlHeight) / _numberOfRows;
    
    NSUInteger page;
    for (int i = 0; i < [_items count]; i += _numberOfCols * _numberOfRows) {
        page = i / 6;
        for (int row = 0; row < _numberOfRows; row++) {
            for (int col = 0; col < _numberOfCols; col++) {
                CGRect frame;
                frame.origin.x = page * _scrollView.frame.size.width + col * itemViewWidth;
                frame.origin.y = row * itemViewHeight;
                frame.size.width = itemViewWidth;
                frame.size.height = itemViewHeight;
                
                LACategoryItemView *itemView = [[LACategoryItemView alloc] initWithFrame:frame];
                [_scrollView addSubview:itemView];
            }
        }
    }
    
    NSUInteger numOfPages = page + 1;
    [_scrollView setContentSize:CGSizeMake(numOfPages * _scrollView.frame.size.width, _scrollView.frame.size.height)];
    
    // layout page control
    
    CGFloat middleX = _scrollView.frame.size.width / 2;

    CGFloat pageControlWidth = 44;
    CGFloat pageControlHeight = vPageControlHeight;
    CGFloat pageControlX = middleX - pageControlWidth / 2;
    CGFloat pageControlY = _scrollView.frame.size.height - vPageControlHeight;
    
    CGRect pageControlFrame = CGRectMake(pageControlX, pageControlY, pageControlWidth, pageControlHeight);
    
    [_pageControl setFrame:pageControlFrame];
    
    [_pageControl setNumberOfPages:numOfPages];
}

#pragma mark - PageControl Event

- (void)pageControlValueChanged:(UIPageControl *)pageControl {
    DLog(@"");
    
    NSUInteger page = pageControl.currentPage;
    CGPoint offset = CGPointMake(page * _scrollView.frame.size.width, 0);
    [_scrollView setContentOffset:offset animated:YES];
}

#pragma mark - ScrollView Delegate

- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView {
    //DLog(@"");
    
    CGPoint offset = scrollView.contentOffset;
    NSUInteger page = offset.x / scrollView.frame.size.width;
    
    [_pageControl setCurrentPage:page];
}

#pragma mark - public methods

- (void)updateWithItems:(NSArray *)items {
    self.items = items;
    [self setNeedsLayout];
}

@end
