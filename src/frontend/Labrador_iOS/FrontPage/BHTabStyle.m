#import "BHTabStyle.h"

@implementation BHTabStyle

@synthesize tabHeight;
@synthesize tabsViewHeight;
@synthesize tabBarHeight;
@synthesize overlapAsPercentageOfTabWidth;
@synthesize shadowRadius;
@synthesize selectedTabColor;
@synthesize selectedTitleTextColor;
@synthesize selectedTitleFont;
@synthesize selectedTitleShadowColor;
@synthesize selectedTitleShadowOffset;
@synthesize unselectedTabColor;
@synthesize unselectedTitleTextColor;
@synthesize unselectedTitleFont;
@synthesize unselectedTitleShadowColor;
@synthesize unselectedTitleShadowOffset;

- (id)init {
  if ((self = [super init])) {
    self.tabsViewHeight = 45;
    self.tabHeight = 40;
    self.tabBarHeight = 5;
    self.overlapAsPercentageOfTabWidth = 0.20;
    self.shadowRadius = 3;

    self.selectedTabColor = [UIColor colorWithWhite:255/255.0 alpha:1];
    self.selectedTitleFont = [UIFont boldSystemFontOfSize:14];
    self.selectedTitleTextColor = [UIColor colorWithWhite:0/255.0 alpha:1];
    self.selectedTitleShadowOffset = CGSizeMake(0, 0.5);
    self.selectedTitleShadowColor = [UIColor colorWithWhite:1 alpha:1];

    CGFloat unselectedAlpha = 0.7;
    self.unselectedTabColor = [self.selectedTabColor colorWithAlphaComponent:1];
    self.unselectedTitleFont = [UIFont boldSystemFontOfSize:14];
    self.unselectedTitleTextColor = [self.selectedTitleTextColor colorWithAlphaComponent:unselectedAlpha];
    self.unselectedTitleShadowOffset = CGSizeMake(0, 0.5);
    self.unselectedTitleShadowColor = [UIColor colorWithWhite:1 alpha:1];
  }

  return self;
}

- (void)setTabHeight:(NSUInteger)newTabHeight {
  tabHeight = MIN(tabsViewHeight, newTabHeight);
}

+ (BHTabStyle *)defaultStyle {
  return [[[BHTabStyle alloc] init] autorelease];
}

@end
