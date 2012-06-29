//
//  LAXMLDownloader.h
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-27.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol LAXMLDownloaderDelegate;

@interface LAXMLDownloader : NSObject <NSURLConnectionDataDelegate>

@property (weak, nonatomic) id<LAXMLDownloaderDelegate> delegate;
@property (strong, nonatomic) NSURLConnection *connection;

@end

@protocol LAXMLDownloaderDelegate <NSObject>



@end
