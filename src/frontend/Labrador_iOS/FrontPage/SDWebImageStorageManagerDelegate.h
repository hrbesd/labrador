//
//  SDWebImageStorageManagerDelegate.h
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-29.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SDWebImageStorageManager;

@protocol SDWebImageStorageManagerDelegate <NSObject>
@optional

/**
 * Called while an image is downloading with an partial image object representing the currently downloaded portion of the image.
 * This delegate is called only if ImageIO is available and `SDWebImageProgressiveDownload` option has been used.
 *
 * @param imageManager The image manager
 * @param image The retrived image object
 * @param url The image URL used to retrive the image
 * @param info The user info dictionnary
 */
- (void)webImageManager:(SDWebImageStorageManager *)imageManager didProgressWithPartialImage:(UIImage *)image forURL:(NSURL *)url userInfo:(NSDictionary *)info;
- (void)webImageManager:(SDWebImageStorageManager *)imageManager didProgressWithPartialImage:(UIImage *)image forURL:(NSURL *)url;

/**
 * Called when image download is completed successfuly.
 *
 * @param imageManager The image manager
 * @param image The retrived image object
 * @param url The image URL used to retrive the image
 * @param info The user info dictionnary
 */
- (void)webImageManager:(SDWebImageStorageManager *)imageManager didFinishWithImage:(UIImage *)image forURL:(NSURL *)url userInfo:(NSDictionary *)info;
- (void)webImageManager:(SDWebImageStorageManager *)imageManager didFinishWithImage:(UIImage *)image forURL:(NSURL *)url;
- (void)webImageManager:(SDWebImageStorageManager *)imageManager didFinishWithImage:(UIImage *)image;

/**
 * Called when an error occurred.
 *
 * @param imageManager The image manager
 * @param error The error
 * @param url The image URL used to retrive the image
 * @param info The user info dictionnary
 */
- (void)webImageManager:(SDWebImageStorageManager *)imageManager didFailWithError:(NSError *)error forURL:(NSURL *)url userInfo:(NSDictionary *)info;
- (void)webImageManager:(SDWebImageStorageManager *)imageManager didFailWithError:(NSError *)error forURL:(NSURL *)url;
- (void)webImageManager:(SDWebImageStorageManager *)imageManager didFailWithError:(NSError *)error;

@end
