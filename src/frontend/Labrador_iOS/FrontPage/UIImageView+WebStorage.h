//
//  UIImageView+WebStorage.h
//  Labrador
//
//  Created by 鑫容 郭 on 12-6-29.
//  Copyright (c) 2012年 FoOTOo. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SDWebImageStorageManager.h"
#import "SDWebImageStorageManagerDelegate.h"
#import "SDWebImageCompat.h"

/**
 * Integrates SDWebImage async downloading and caching of remote images with UIImageView.
 *
 * Usage with a UITableViewCell sub-class:
 *
 * 	#import <SDWebImage/UIImageView+WebCache.h>
 * 	
 * 	...
 * 	
 * 	- (UITableViewCell *)tableView:(UITableView *)tableView
 * 	         cellForRowAtIndexPath:(NSIndexPath *)indexPath
 * 	{
 * 	    static NSString *MyIdentifier = @"MyIdentifier";
 * 	
 * 	    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:MyIdentifier];
 * 	
 * 	    if (cell == nil)
 * 	    {
 * 	        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault
 * 	                                       reuseIdentifier:MyIdentifier] autorelease];
 * 	    }
 * 	
 * 	    // Here we use the provided setImageWithURL: method to load the web image
 * 	    // Ensure you use a placeholder image otherwise cells will be initialized with no image
 * 	    [cell.imageView setImageWithURL:[NSURL URLWithString:@"http://example.com/image.jpg"]
 * 	                   placeholderImage:[UIImage imageNamed:@"placeholder"]];
 * 	
 * 	    cell.textLabel.text = @"My Text";
 * 	    return cell;
 * 	}
 * 	
 */

@interface UIImageView (WebStorage) <SDWebImageStorageManagerDelegate>

/**
 * Set the imageView `image` with an `url`.
 *
 * The downloand is asynchronous and cached.
 *
 * @param url The url for the image.
 */
- (void)setStorageImageWithURL:(NSURL *)url;

/**
 * Set the imageView `image` with an `url` and a placeholder.
 *
 * The downloand is asynchronous and cached.
 *
 * @param url The url for the image.
 * @param placeholder The image to be set initially, until the image request finishes.
 * @see setImageWithURL:placeholderImage:options:
 */
- (void)setStorageImageWithURL:(NSURL *)url placeholderImage:(UIImage *)placeholder;

/**
 * Set the imageView `image` with an `url`, placeholder and custom options.
 *
 * The downloand is asynchronous and cached.
 *
 * @param url The url for the image.
 * @param placeholder The image to be set initially, until the image request finishes.
 * @param options The options to use when downloading the image. @see SDWebImageOptions for the possible values.
 */
- (void)setStorageImageWithURL:(NSURL *)url placeholderImage:(UIImage *)placeholder options:(SDWebImageOptions)options;

#if NS_BLOCKS_AVAILABLE
/**
 * Set the imageView `image` with an `url`.
 *
 * The downloand is asynchronous and cached.
 *
 * @param url The url for the image.
 * @param success A block to be executed when the image request succeed This block has no return value and takes the retrieved image as argument.
 * @param failure A block object to be executed when the image request failed. This block has no return value and takes the error object describing the network or parsing error that occurred (may be nil).
 */
- (void)setStorageImageWithURL:(NSURL *)url success:(void (^)(UIImage *image))success failure:(void (^)(NSError *error))failure;

/**
 * Set the imageView `image` with an `url`, placeholder.
 *
 * The downloand is asynchronous and cached.
 *
 * @param url The url for the image.
 * @param placeholder The image to be set initially, until the image request finishes.
 * @param success A block to be executed when the image request succeed This block has no return value and takes the retrieved image as argument.
 * @param failure A block object to be executed when the image request failed. This block has no return value and takes the error object describing the network or parsing error that occurred (may be nil).
 */
- (void)setStorageImageWithURL:(NSURL *)url placeholderImage:(UIImage *)placeholder success:(void (^)(UIImage *image))success failure:(void (^)(NSError *error))failure;

/**
 * Set the imageView `image` with an `url`, placeholder and custom options.
 *
 * The downloand is asynchronous and cached.
 *
 * @param url The url for the image.
 * @param placeholder The image to be set initially, until the image request finishes.
 * @param options The options to use when downloading the image. @see SDWebImageOptions for the possible values.
 * @param success A block to be executed when the image request succeed This block has no return value and takes the retrieved image as argument.
 * @param failure A block object to be executed when the image request failed. This block has no return value and takes the error object describing the network or parsing error that occurred (may be nil).
 */
- (void)setStorageImageWithURL:(NSURL *)url placeholderImage:(UIImage *)placeholder options:(SDWebImageOptions)options success:(void (^)(UIImage *image))success failure:(void (^)(NSError *error))failure;
#endif

/**
 * Cancel the current download
 */
- (void)cancelCurrentImageLoad;

@end
