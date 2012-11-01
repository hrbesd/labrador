//
//  LAList.h
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-27.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GDataXMLNode.h"

typedef enum {
    XMLDataType_List,
    XMLDataType_Article
}XMLDataType;

@protocol LAXMLDataDelegate;

/**
 * LAXMLData
 * Get XML data from server or local storage
 * Basically parse the xml file
 */

@interface LAXMLData : NSObject <NSURLConnectionDataDelegate>

@property (weak, nonatomic) id<LAXMLDataDelegate> delegate;

@property (strong, nonatomic) NSMutableArray *listData;
@property (strong, nonatomic) GDataXMLElement *articleElem;

@property (readonly, nonatomic) XMLDataType type;

- (id)initWithURL:(NSString *)urlStr type:(XMLDataType)type;
- (id)initWithURL:(NSString *)urlStr type:(XMLDataType)type delegate:(id<LAXMLDataDelegate>)delegate;
- (void)forceUpdate;
//- (void)requestWithURL:(NSString *)urlStr;
- (void)cancleConnection;

@end

@protocol LAXMLDataDelegate <NSObject>

@optional

- (void)listDidFinishLoading:(LAXMLData *)list;
- (void)listWillStartLoading:(LAXMLData *)list;
- (void)listAlreadyLoading:(LAXMLData *)list;
- (void)list:(LAXMLData *)list failWithError:(NSError *)error;

@end
