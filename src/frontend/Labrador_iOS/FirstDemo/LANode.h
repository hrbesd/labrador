//
//  LACategoryNode.h
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-22.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface LANode : NSObject

@property (copy, nonatomic) NSString *name;
@property (copy, nonatomic) NSString *url;
@property (copy, nonatomic) NSString *refreshRate;
@property (copy, nonatomic) NSString *hashName;
@property (strong, nonatomic) NSMutableArray *nodeList;

- (id)initWithName:(NSString *)name url:(NSString *)url refreshRate:(NSString *)refreshRate hashName:(NSString *)hashName nodeList:(NSArray *)nodeList;

@end
