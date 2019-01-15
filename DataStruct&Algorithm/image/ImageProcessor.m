//
//  ImageProcessor.m
//  image
//
//  Created by K K on 2018/12/25.
//  Copyright © 2018 K K. All rights reserved.
//

#import "ImageProcessor.h"

#define Mask8(x) ( (x) & 0xFF )
#define R(x) ( Mask8(x) )
#define G(x) ( Mask8(x >> 8 ) )
#define B(x) ( Mask8(x >> 16) )
#define A(x) ( Mask8(x >> 24) )
#define RGBAMake(r, g, b, a) ( Mask8(r) | Mask8(g) << 8 | Mask8(b) << 16 | Mask8(a) << 24 )

@implementation ImageProcessor

+ (instancetype)sharedImageProcessor {
    static ImageProcessor *sharedImageProcessor = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedImageProcessor = [[self alloc] init];
    });
    return sharedImageProcessor;
}

- (void)processorImage:(UIImage *)inputImage complete: (ImageProcessorCompleted)completed {
    UInt32 *inputPixels;
    CGImageRef inputCGImage = [inputImage CGImage];
    NSUInteger inputWidth = CGImageGetWidth(inputCGImage);
    NSUInteger inputHeight = CGImageGetHeight(inputCGImage);
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    NSUInteger bytePerPixels = 4;
    NSUInteger bitsPerCompent = 8;
    NSInteger inputBytesPerRow = bytePerPixels * inputWidth;
    inputPixels = (UInt32 *)calloc(inputWidth * inputHeight, sizeof(UInt32));
    
    CGContextRef context = CGBitmapContextCreate(inputPixels, inputWidth, inputHeight, bitsPerCompent, inputBytesPerRow, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    CGContextDrawImage(context, CGRectMake(0, 0, inputWidth, inputHeight), inputCGImage);
    
    // 绘制水印
    UIImage *logoImage = [UIImage imageNamed:@"logo"];
    CGImageRef logoCGImage = [logoImage CGImage];
    
    CGFloat logoImageAspectRatio = logoImage.size.width / logoImage.size.height;
    NSInteger targetLogoWidth = inputWidth * 0.20;
    CGSize logoSize = CGSizeMake(targetLogoWidth, targetLogoWidth / logoImageAspectRatio);
    CGPoint logoOrigin = CGPointMake(inputWidth-logoSize.width - 20, inputHeight-logoSize.height - 30);
    NSUInteger logoBytesPerRow = bytePerPixels * logoSize.width;
    UInt32 *logoPixels = malloc(sizeof(UInt32) * logoSize.width*logoSize.height);
    
    CGContextRef logoContext = CGBitmapContextCreate(logoPixels, logoSize.width, logoSize.height, bitsPerCompent, logoBytesPerRow, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    CGContextDrawImage(logoContext, CGRectMake(0, 0, logoSize.width, logoSize.height), logoCGImage);
    
    // 便宜位置的起始位置
    NSUInteger offsetPixelCountForInput = logoOrigin.y * inputWidth + logoOrigin.x;
    for (int j = 0; j < logoSize.height; j++) {
        for (int i = 0; i < logoSize.width ; i++) {
            // input的位置色值
            UInt32 *inputPixel = inputPixels + inputWidth*j + i + offsetPixelCountForInput;
            UInt32 inputColor = *inputPixel;
            
            // logo的位置色值
            UInt32 *logoPixel = logoPixels + (UInt32)logoSize.width * j + i;
            UInt32 logoColor = *logoPixel;
            
            // 计算新值
            CGFloat logoAlpha = 0.5f * (A(logoColor)/255);
            UInt32 newR = R(inputColor)*(1-logoAlpha) + R(logoColor)*logoAlpha;
            UInt32 newG = G(inputColor)*(1-logoAlpha) + G(logoColor)*logoAlpha;
            UInt32 newB = B(inputColor)*(1-logoAlpha) + B(logoColor)*logoAlpha;
            newR = MAX(0, MIN(255.0, newR));
            newG = MAX(0, MIN(255.0, newG));
            newB = MAX(0, MIN(255.0, newB));
            
            *inputPixel = RGBAMake(newR, newG, newB, A(inputColor));
        }
    }
    
    for(int j = 0; j < inputHeight; j ++) {
        for (int i = 0; i < inputWidth; i++) {
            UInt32 *currentPixels = inputPixels + j*inputWidth + i;
            UInt32 color = *currentPixels;

            UInt32 averageColor = (R(color) + G(color) + B(color))/3.0;
            *currentPixels = RGBAMake(averageColor, averageColor, averageColor, A(color));
        }
    }
    
    CGImageRef newCGImage = CGBitmapContextCreateImage(context);
    UIImage *newImage = [UIImage imageWithCGImage:newCGImage];
    
    CGColorSpaceRelease(colorSpace);
    CGContextRelease(context);
    CGContextRelease(logoContext);
    free(inputPixels);
    free(logoPixels);
    
    completed(newImage);
}

- (UIImage *)processorImageUsingCoreGraphics:(UIImage *)inputImage {
    double start = CFAbsoluteTimeGetCurrent();
    
    // 原始图片大小
    CGRect inputRect = {CGPointZero, inputImage.size};
    NSInteger inputWidth = inputRect.size.width;
    NSInteger inputHeight = inputRect.size.height;
    
    // 计算水印大小
    UIImage *logoImage = [UIImage imageNamed:@"logo"];
    CGFloat logoImageAspectRatio = logoImage.size.width / logoImage.size.height;
    NSInteger targetLogoWidth = inputWidth * 0.25;
    CGSize logoSize = CGSizeMake(targetLogoWidth, targetLogoWidth / logoImageAspectRatio);
    CGPoint logoOrigin = CGPointMake(inputWidth * 0.5, inputHeight * 0.2);
    CGRect logoRect = {logoOrigin, logoSize};
    
    //绘制上下文
    UIGraphicsBeginImageContext(inputImage.size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    // 转换原点，坐标系-----core graphics 是以左下角为原点，image是以左上角为原点
    CGAffineTransform flip = CGAffineTransformMakeScale(1.0, -1.0);
    CGAffineTransform flipThenShift = CGAffineTransformTranslate(flip,0,-inputHeight);
    CGContextConcatCTM(context, flipThenShift);
    
    CGContextDrawImage(context, inputRect, [inputImage CGImage]);
    
    // 将后面绘制进去的透明度设置为0.5
    CGContextSetBlendMode(context, kCGBlendModeSourceAtop);
    CGContextSetAlpha(context,0.5);
    
    // 将logo的位置转换
    CGRect transformedLogoRect = CGRectApplyAffineTransform(logoRect, flipThenShift);
    CGContextDrawImage(context, transformedLogoRect, [logoImage CGImage]);
    
    UIImage * imageWithLogo = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    // 如果要灰白效果：
//    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceGray();
//    context = CGBitmapContextCreate(nil, inputWidth, inputHeight,
//                                    8, 0, colorSpace, (CGBitmapInfo)kCGImageAlphaNone);
//    CGContextDrawImage(context, inputRect, [imageWithLogo CGImage]);
//    CGImageRef imageRef = CGBitmapContextCreateImage(context);
//    imageWithLogo = [UIImage imageWithCGImage:imageRef];
//
//
//    CGColorSpaceRelease(colorSpace);
//    CGContextRelease(context);
//    CFRelease(imageRef);
    double end = CFAbsoluteTimeGetCurrent();
    NSLog(@"%f", end - start);
    return imageWithLogo;
}



- (UIImage *)processorImageUsingCoreImage:(UIImage *)inputImage {
    double start = CFAbsoluteTimeGetCurrent();
    CIImage *inputCIImage = [[CIImage alloc] initWithImage:inputImage];
    
    // 1、创建grayscale filter
    CIFilter *grayFilter = [CIFilter filterWithName:@"CIColorControls"];
    [grayFilter setValue:@(0) forKeyPath:@"inputSaturation"];
    
    // 2、创建logo和logo filter
    UIImage *logoImage = [self createPaddedGhostImageWithSize:inputImage.size];
//    UIImage *logoImage = [UIImage imageNamed:@"logo"];
    CIImage *logoCIImage = [[CIImage alloc] initWithImage:logoImage];
    
    // logo透明度滤镜设置参数
    CIFilter *alphaFilter = [CIFilter filterWithName:@"CIColorMatrix"];
    CIVector *alphaVector = [CIVector vectorWithX:0 Y:0 Z:0.5 W:0];
    [alphaFilter setValue:alphaVector forKey:@"inputAVector"];
    
    // 3、混合滤镜
    CIFilter * blendFilter = [CIFilter filterWithName:@"CISourceAtopCompositing"];
    
    // 给滤镜设置透明度
    // 透明度
    [alphaFilter setValue:logoCIImage forKeyPath:@"inputImage"];
    logoCIImage = [alphaFilter outputImage];
    
    // 混合透明度
    [blendFilter setValue:inputCIImage forKeyPath:@"inputBackgroundImage"];
    [blendFilter setValue:logoCIImage forKeyPath:@"inputImage"];
    
    CIImage *blendOutput = [blendFilter outputImage];
    
    // 灰白
    [grayFilter setValue:blendOutput forKeyPath:@"inputImage"];
    CIImage * outputCIImage = [grayFilter outputImage];
//    CIImage * outputCIImage = blendOutput;
    
    // 6. Render your output image
    CIContext * context = [CIContext contextWithOptions:nil];
    CGImageRef outputCGImage = [context createCGImage:outputCIImage fromRect:[outputCIImage extent]];
    UIImage * outputImage = [UIImage imageWithCGImage:outputCGImage];
    CGImageRelease(outputCGImage);
    double end = CFAbsoluteTimeGetCurrent();
    NSLog(@"%f", end - start);
    return outputImage;
}


- (UIImage *)createPaddedGhostImageWithSize:(CGSize)inputSize {
    UIImage * ghostImage = [UIImage imageNamed:@"logo"];
    CGFloat ghostImageAspectRatio = ghostImage.size.width / ghostImage.size.height;
    NSInteger targetGhostWidth = inputSize.width * 0.25;
    CGSize ghostSize = CGSizeMake(targetGhostWidth, targetGhostWidth / ghostImageAspectRatio);
    CGPoint ghostOrigin = CGPointMake(inputSize.width * 0.5, inputSize.height * 0.2);
    CGRect ghostRect = {ghostOrigin, ghostSize};
    UIGraphicsBeginImageContext(inputSize);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGRect inputRect = {CGPointZero, inputSize};
    CGContextClearRect(context, inputRect);
    CGAffineTransform flip = CGAffineTransformMakeScale(1.0, -1.0);
    CGAffineTransform flipThenShift = CGAffineTransformTranslate(flip,0,-inputSize.height);
    CGContextConcatCTM(context, flipThenShift);
    CGRect transformedGhostRect = CGRectApplyAffineTransform(ghostRect, flipThenShift);
    CGContextDrawImage(context, transformedGhostRect, [ghostImage CGImage]);
    UIImage * paddedGhost = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return paddedGhost;
}

// 将图片黑白画
- (void)toBlackAndWhite:(UIImage *)image complete:(ImageProcessorCompleted)completed {
    
    UInt32 *inputPixels;
    
    CGImageRef inputCGImage = [image CGImage];
    NSUInteger inputWidth = CGImageGetWidth(inputCGImage);
    NSUInteger inputHeigh = CGImageGetHeight(inputCGImage);
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    
    NSUInteger bytePerPixels = 4;
    NSUInteger bitsPerCompent = 8;
    NSInteger inputBytesPerRow = bytePerPixels * inputWidth;
    inputPixels = (UInt32 *)calloc(inputWidth * inputHeigh, sizeof(UInt32));
    
    CGContextRef context = CGBitmapContextCreate(inputPixels, inputWidth, inputHeigh, bitsPerCompent, inputBytesPerRow, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    CGContextDrawImage(context, CGRectMake(0, 0, inputWidth, inputHeigh), inputCGImage);
    for(int j = 0; j < inputHeigh; j ++) {
        for (int i = 0; i < inputWidth; i++) {
            UInt32 *currentPixels = inputPixels + j*inputWidth + i;
            UInt32 color = *currentPixels;
            
            UInt32 averageColor = (R(color) + G(color) + B(color))/3.0;
            *currentPixels = RGBAMake(averageColor, averageColor, averageColor, A(color));
        }
    }
    CGImageRef newCGImage = CGBitmapContextCreateImage(context);
    UIImage *newImage = [UIImage imageWithCGImage:newCGImage];
    
    CGColorSpaceRelease(colorSpace);
    CGContextRelease(context);
    free(inputPixels);
    
    completed(newImage);
}

- (UIImage *)grayImage:(UIImage *)image {
    
    int width  = image.size.width;
    int height = image.size.height;
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceGray();
    
    CGContextRef context = CGBitmapContextCreate(nil,
                                                 width,
                                                 height,
                                                 8, // bits per component
                                                 0,
                                                 colorSpace,
                                                 kCGBitmapByteOrderDefault);
    
    CGColorSpaceRelease(colorSpace);
    
    if (context == NULL) {
        
        return nil;
    }
    
    CGContextDrawImage(context,
                       CGRectMake(0, 0, width, height), image.CGImage);
    CGImageRef imageRef   = CGBitmapContextCreateImage(context);
    UIImage *grayImage = [UIImage imageWithCGImage:imageRef];
    CFRelease(imageRef);
    CGContextRelease(context);
    
    return grayImage;
}

@end
