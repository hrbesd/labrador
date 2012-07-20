//
//  CycleScrollView.m
//  CycleScrollDemo
//
//  Created by Weever Lu on 12-6-14.
//  Copyright (c) 2012年 linkcity. All rights reserved.
//

#import "CycleScrollView.h"
#import "UIImageView+WebCache.h"
#import <QuartzCore/QuartzCore.h>

#define vLabelHeight 30.0f

@implementation CycleScrollView
@synthesize delegate;
@synthesize imagesArray;
@synthesize titlesArray;

- (id)initWithFrame:(CGRect)frame cycleDirection:(CycleDirection)direction pictures:(NSArray *)pictureArray titles:(NSArray *)titles;
{
    self = [super initWithFrame:frame];
    if(self)
    {
        scrollFrame = frame;
        scrollDirection = direction;
        totalPage = pictureArray.count;
        curPage = 1;                                    // 显示的是图片数组里的第一张图片
        curImages = [[NSMutableArray alloc] init];
        self.imagesArray = [[NSArray alloc] initWithArray:pictureArray];
        
        curTitles = [[NSMutableArray alloc] init];
        self.titlesArray = [[NSArray alloc] initWithArray:titles];
        
        scrollView = [[UIScrollView alloc] initWithFrame:frame];
        scrollView.backgroundColor = [UIColor whiteColor];
        scrollView.showsHorizontalScrollIndicator = NO;
        scrollView.showsVerticalScrollIndicator = NO;
        scrollView.pagingEnabled = YES;
        scrollView.delegate = self;
        [self addSubview:scrollView];
        
        // 在水平方向滚动
        if(scrollDirection == CycleDirectionLandscape) {
            scrollView.contentSize = CGSizeMake(scrollView.frame.size.width * 3,
                                                scrollView.frame.size.height);
        }
        // 在垂直方向滚动 
        if(scrollDirection == CycleDirectionPortait) {
            scrollView.contentSize = CGSizeMake(scrollView.frame.size.width,
                                                scrollView.frame.size.height * 3);
        }
        
        [self addSubview:scrollView];
        [self refreshScrollView];
    }
    
    return self;
}

- (void)reloadWithPictures:(NSArray *)pictureArray titles:(NSArray *)titles {
    self.imagesArray = pictureArray;
    self.titlesArray = titles;
    totalPage = pictureArray.count;
    curPage = 1;    
    [self refreshScrollView];
}

- (void)refreshScrollView {
    
    NSArray *subViews = [scrollView subviews];
    if([subViews count] != 0) {
        [subViews makeObjectsPerformSelector:@selector(removeFromSuperview)];
    }
    
    if (self.imagesArray != nil && [self.imagesArray count] != 0) {
        [self getDisplayImagesWithCurpage:curPage];
        
        for (int i = 0; i < 3; i++) {
            UIImageView *imageView = [[UIImageView alloc] initWithFrame:scrollFrame];
            imageView.userInteractionEnabled = YES;
            //imageView.image = [curImages objectAtIndex:i];
            [imageView setImageWithURL:[curImages objectAtIndex:i]];
            
            //[imageView.layer setBorderColor:[[UIColor greenColor] CGColor]];
            //[imageView.layer setBorderWidth:2.0f];
            
            UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0, CGRectGetMaxY(scrollFrame) - vLabelHeight, scrollFrame.size.width, vLabelHeight)];
            [label setText:[curTitles objectAtIndex:i]];
            
            UIColor *labelColor = [UIColor colorWithWhite:1 alpha:0.7];
            [label setBackgroundColor:labelColor];
            //[label setTextColor:[UIColor whiteColor]];
            [imageView addSubview:label];
            
            //[label.layer setBorderColor:[[UIColor greenColor] CGColor]];
            //[label.layer setBorderWidth:2.0f];
            
            [label release];
            
            UITapGestureRecognizer *singleTap = [[UITapGestureRecognizer alloc] initWithTarget:self
                                                                                        action:@selector(handleTap:)];
            [imageView addGestureRecognizer:singleTap];
            [singleTap release];
            
            // 水平滚动
            if(scrollDirection == CycleDirectionLandscape) {
                imageView.frame = CGRectOffset(imageView.frame, scrollFrame.size.width * i, 0);
            }
            // 垂直滚动
            if(scrollDirection == CycleDirectionPortait) {
                imageView.frame = CGRectOffset(imageView.frame, 0, scrollFrame.size.height * i);
            }
            
            
            [scrollView addSubview:imageView];
        }

    }
    
    if (scrollDirection == CycleDirectionLandscape) {
        [scrollView setContentOffset:CGPointMake(scrollFrame.size.width, 0)];
    }
    if (scrollDirection == CycleDirectionPortait) {
        [scrollView setContentOffset:CGPointMake(0, scrollFrame.size.height)];
    }
}


- (NSArray *)getDisplayImagesWithCurpage:(int)page {
    
    int pre = [self validPageValue:curPage-1];
    int last = [self validPageValue:curPage+1];
    
    if([curImages count] != 0) [curImages removeAllObjects];
    
    [curImages addObject:[imagesArray objectAtIndex:pre-1]];
    [curImages addObject:[imagesArray objectAtIndex:curPage-1]];
    [curImages addObject:[imagesArray objectAtIndex:last-1]];
    
    if ([curTitles count] != 0) [curTitles removeAllObjects];
    
    [curTitles addObject:[titlesArray objectAtIndex:pre-1]];
    [curTitles addObject:[titlesArray objectAtIndex:curPage-1]];
    [curTitles addObject:[titlesArray objectAtIndex:last-1]];
    
    return curImages;
}

- (int)validPageValue:(NSInteger)value {
    
    if(value == 0) value = totalPage;                   // value＝1为第一张，value = 0为前面一张
    if(value == totalPage + 1) value = 1;
    
    return value;
}

- (void)scrollViewDidScroll:(UIScrollView *)aScrollView {
    
    int x = aScrollView.contentOffset.x;
    int y = aScrollView.contentOffset.y;
    //NSLog(@"did  x=%d  y=%d", x, y);
    
    // 水平滚动
    if(scrollDirection == CycleDirectionLandscape) {
        // 往下翻一张
        if(x >= (2*scrollFrame.size.width)) { 
            curPage = [self validPageValue:curPage+1];
            [self refreshScrollView];
        }
        if(x <= 0) {
            curPage = [self validPageValue:curPage-1];
            [self refreshScrollView];
        }
    }
    
    // 垂直滚动
    if(scrollDirection == CycleDirectionPortait) {
        // 往下翻一张
        if(y >= 2 * (scrollFrame.size.height)) { 
            curPage = [self validPageValue:curPage+1];
            [self refreshScrollView];
        }
        if(y <= 0) {
            curPage = [self validPageValue:curPage-1];
            [self refreshScrollView];
        }
    }
    
    if ([delegate respondsToSelector:@selector(cycleScrollViewDelegate:didScrollImageView:)]) {
        [delegate cycleScrollViewDelegate:self didScrollImageView:curPage];
    }
}

- (void)scrollViewDidEndDecelerating:(UIScrollView *)aScrollView {
    
    //int x = aScrollView.contentOffset.x;
    //int y = aScrollView.contentOffset.y;
    
    //NSLog(@"--end  x=%d  y=%d", x, y);
    
    if (scrollDirection == CycleDirectionLandscape) {
            [scrollView setContentOffset:CGPointMake(scrollFrame.size.width, 0) animated:YES];
    }
    if (scrollDirection == CycleDirectionPortait) {
        [scrollView setContentOffset:CGPointMake(0, scrollFrame.size.height) animated:YES];
    }
}

- (void)handleTap:(UITapGestureRecognizer *)tap {
    
    if ([delegate respondsToSelector:@selector(cycleScrollViewDelegate:didSelectImageView:)]) {
        [delegate cycleScrollViewDelegate:self didSelectImageView:curPage];
    }
}


- (void)dealloc
{
    [imagesArray release];
    [curImages release];
    
    [titlesArray release];
    [curTitles release];
    
    [super dealloc];
}

@end
