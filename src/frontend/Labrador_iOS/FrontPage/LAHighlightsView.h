//
//  LAHighlightsView.h
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-28.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef enum {
    LAScrollDirection_Portait,
    LAScrollDirection_Landscape
}LAScrollDirection;

@protocol LAHighlightsViewDelegate;

@interface LAHighlightsView : UIScrollView <UIScrollViewDelegate>

@property (weak, nonatomic) id<LAHighlightsViewDelegate> highlightsViewDelegate;

@end


@protocol LAHighlightsViewDelegate <NSObject>



@end