//
//  ImageProcessor.h
//  image
//
//  Created by K K on 2018/12/25.
//  Copyright © 2018 K K. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef void(^ImageProcessorCompleted)(UIImage*);

@interface ImageProcessor : NSObject

+ (instancetype)sharedImageProcessor;

- (void)processorImage:(UIImage *)inputImage complete: (ImageProcessorCompleted)completed;
- (void)toBlackAndWhite:(UIImage *)image complete: (ImageProcessorCompleted)completed;
- (UIImage *)processorImageUsingCoreGraphics:(UIImage *)inputImage;
- (UIImage *)processorImageUsingCoreImage:(UIImage *)inputImage;
- (UIImage *)grayImage:(UIImage *)image;

@end

