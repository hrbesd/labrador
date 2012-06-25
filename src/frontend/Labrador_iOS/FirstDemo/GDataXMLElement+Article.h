//
//  GDataXMLElement+Article.h
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-23.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "GDataXMLNode.h"

@interface GDataXMLElement (Article)

@property (readonly, nonatomic) NSString *title;
@property (readonly, nonatomic) NSString *author;
@property (readonly, nonatomic) NSString *lastModified;
@property (readonly, nonatomic) NSString *bodyData;

@end
