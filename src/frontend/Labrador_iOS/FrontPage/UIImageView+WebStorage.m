//
//  UIImageView+WebStorage.m
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-29.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import "UIImageView+WebStorage.h"

@implementation UIImageView (WebStorage)

- (void)setStorageImageWithURL:(NSURL *)url
{
    [self setStorageImageWithURL:url placeholderImage:nil];
}

- (void)setStorageImageWithURL:(NSURL *)url placeholderImage:(UIImage *)placeholder
{
    [self setStorageImageWithURL:url placeholderImage:placeholder options:0];
}

- (void)setStorageImageWithURL:(NSURL *)url placeholderImage:(UIImage *)placeholder options:(SDWebImageOptions)options
{
    SDWebImageStorageManager *manager = [SDWebImageStorageManager sharedManager];
    
    // Remove in progress downloader from queue
    [manager cancelForDelegate:self];
    
    self.image = placeholder;
    
    if (url)
    {
        [manager downloadWithURL:url delegate:self options:options];
    }
}

#if NS_BLOCKS_AVAILABLE
- (void)setStorageImageWithURL:(NSURL *)url success:(void (^)(UIImage *image))success failure:(void (^)(NSError *error))failure;
{
    [self setStorageImageWithURL:url placeholderImage:nil success:success failure:failure];
}

- (void)setStorageImageWithURL:(NSURL *)url placeholderImage:(UIImage *)placeholder success:(void (^)(UIImage *image))success failure:(void (^)(NSError *error))failure;
{
    [self setStorageImageWithURL:url placeholderImage:placeholder options:0 success:success failure:failure];
}

- (void)setStorageImageWithURL:(NSURL *)url placeholderImage:(UIImage *)placeholder options:(SDWebImageOptions)options success:(void (^)(UIImage *image))success failure:(void (^)(NSError *error))failure;
{
    SDWebImageStorageManager *manager = [SDWebImageStorageManager sharedManager];
    
    // Remove in progress downloader from queue
    [manager cancelForDelegate:self];
    
    self.image = placeholder;
    
    if (url)
    {
        [manager downloadWithURL:url delegate:self options:options success:success failure:failure];
    }
}
#endif

- (void)cancelCurrentImageLoad
{
    [[SDWebImageStorageManager sharedManager] cancelForDelegate:self];
}

- (void)webImageManager:(SDWebImageStorageManager *)imageManager didProgressWithPartialImage:(UIImage *)image forURL:(NSURL *)url
{
    self.image = image;
    [self setNeedsLayout];
}

- (void)webImageManager:(SDWebImageStorageManager *)imageManager didFinishWithImage:(UIImage *)image
{
    self.image = image;
    [self setNeedsLayout];
}


@end
