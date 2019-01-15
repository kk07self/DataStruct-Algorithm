//
//  UIImage+OrientationFix.m
//  image
//
//  Created by K K on 2018/12/25.
//  Copyright © 2018 K K. All rights reserved.
//

#import "UIImage+OrientationFix.h"

@implementation UIImage (OrientationFix)

- (UIImage *)imageWithFixedOrientation {
    if (self.imageOrientation == UIImageOrientationUp) return self;
    
    UIGraphicsBeginImageContextWithOptions(self.size, NO, self.scale);
    [self drawInRect:(CGRect){0, 0, self.size}];
    UIImage *normalizedImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return normalizedImage;
}
@end
