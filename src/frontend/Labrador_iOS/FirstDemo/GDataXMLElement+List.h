//
//  GDataXMLElement+Labrador.h
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-22.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "GDataXMLNode.h"

@interface GDataXMLElement (List)

@property (readonly, nonatomic) NSString *nodeName;
@property (readonly, nonatomic) NSString *url;
@property (readonly, nonatomic) NSString *pageURL;
@property (readonly, nonatomic) NSString *refreshRate;
@property (readonly, nonatomic) NSString *hashName;
@property (readonly, nonatomic) NSArray *nodeList;
@property (readonly, nonatomic) NSString *imageUrl;
@property (readonly, nonatomic) NSString *title;

@end
