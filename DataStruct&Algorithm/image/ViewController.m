//
//  ViewController.m
//  image
//
//  Created by K K on 2018/12/25.
//  Copyright © 2018 K K. All rights reserved.
//

#import "ViewController.h"
#import "UIImage+OrientationFix.h"
#import "ImageProcessor.h"

@interface ViewController ()<UIImagePickerControllerDelegate, UINavigationControllerDelegate>

@property (weak, nonatomic) IBOutlet UIImageView *imageView;
@property (strong, nonatomic) UIImagePickerController * imagePickerController;
@property (strong, nonatomic) UIImage * workingImage;

@property (strong, nonatomic) dispatch_queue_t queue;

@end

@implementation ViewController

- (void)invocationOpereation1 {
    for (int i = 0; i<10; i++) {
        NSLog(@"2---%@",[NSThread currentThread]);
    }
}

- (void)read {
    sleep(1);
    NSLog(@"read");
}

- (void)write
{
    sleep(1);
    NSLog(@"write");
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // 初始化队列
    self.queue = dispatch_queue_create("rw_queue", DISPATCH_QUEUE_CONCURRENT);
    // 使用
    for (int i = 0; i < 10; i++) {
        dispatch_async(self.queue, ^{
            [self read];
        });
        
        dispatch_async(self.queue, ^{
            [self read];
        });
        
        dispatch_async(self.queue, ^{
            [self read];
        });
        
        dispatch_barrier_async(self.queue, ^{
            [self write];
        });
    }
    // Do any additional setup after loading the view, typically from a nib.
//    NSOperationQueue *queue = [[NSOperationQueue alloc] init];
//    queue.maxConcurrentOperationCount = 1;
//    [queue addOperationWithBlock:^{
//        for (int i = 0; i<10; i++) {
//            NSLog(@"1---%@",[NSThread currentThread]);
//        }
//    }];
//    NSInvocationOperation *operation1 = [[NSInvocationOperation alloc] initWithTarget:self selector:@selector(invocationOpereation1) object:nil];
//    [queue addOperation:operation1];
//    [queue addOperationWithBlock:^{
//        for (int i = 0; i<10; i++) {
//            NSLog(@"2---%@",[NSThread currentThread]);
//        }
//    }];
//
           
    
////    // 创建串行
//    dispatch_queue_t queue1 = dispatch_queue_create("kirk1", DISPATCH_QUEUE_SERIAL);
////    // 创建并行队列
//    dispatch_queue_t queue2 = dispatch_queue_create("ckckck", DISPATCH_QUEUE_CONCURRENT);
//    // 获取主队列
//    dispatch_queue_t queue = dispatch_get_main_queue();
//    dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
//    dispatch_sync(queue, ^{
//        for (int i = 0; i<10; i++) {
//            NSLog(@"1---%@",[NSThread currentThread]);
//        }
//    });
//    // 在队列中添加线程，异步执行任务
//    dispatch_async(queue, ^{
//        for (int i = 0; i<10; i++) {
//            NSLog(@"1---%@",[NSThread currentThread]);
//            sleep(1);
//        }
//    });
    
//    dispatch_async(dispatch_get_main_queue(), ^{
//        for (int i = 0; i<10; i++) {
//            NSLog(@"3---%@",[NSThread currentThread]);
//        }
//    });
//    for (int i = 0; i<10; i++) {
//        NSLog(@"1---%@",[NSThread currentThread]);
//        sleep(1);
//    }
//    dispatch_async(queue, ^{
//        for (int i = 0; i<10; i++) {
//            NSLog(@"2---%@",[NSThread currentThread]);
//        }
//    });
////    NSLog(@"end");
//    dispatch_async(dispatch_get_main_queue(), ^{
//        for (int i = 0; i<10; i++) {
//            NSLog(@"4---%@",[NSThread currentThread]);
//        }
//    });
//    dispatch_block_t block1 = dispatch_block_create(DISPATCH_BLOCK_DETACHED, ^{
//        for (int i = 0; i<10; i++) {
//            NSLog(@"1---%@",[NSThread currentThread]);
//        }
//    });
    
    
    // 获取全局队列
//    dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    

}

- (UIImagePickerController *)imagePickerController {
    if (!_imagePickerController) { /* Lazy Loading */
        _imagePickerController = [[UIImagePickerController alloc] init];
        _imagePickerController.allowsEditing = NO;
        _imagePickerController.delegate = self;
    }
    return _imagePickerController;
}

- (IBAction)camera:(id)sender {
    self.imagePickerController.sourceType = UIImagePickerControllerSourceTypeCamera;
    [self presentViewController:self.imagePickerController animated:YES completion:nil];
}

- (IBAction)album:(id)sender {
    self.imagePickerController.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
    [self presentViewController:self.imagePickerController animated:YES completion:nil];
}

- (IBAction)save:(id)sender {
    if (!self.workingImage) {
        return;
    }
    UIImageWriteToSavedPhotosAlbum(self.workingImage, nil, nil, nil);
}


- (void)setupWithImage:(UIImage*)image {
    UIImage * fixedImage = [image imageWithFixedOrientation];
//    self.workingImage = fixedImage;
    
    // Commence with processing!
//    [ImageProcessor.sharedImageProcessor toBlackAndWhite:fixedImage complete:^(UIImage *new) {
//        self.workingImage = new;
//        self.imageView.image = new;
//    }];
    
//    UIImage *new = [ImageProcessor.sharedImageProcessor grayImage:fixedImage];
//    self.workingImage = new;
//    self.imageView.image = new;
//    [ImageProcessor.sharedImageProcessor processorImage:fixedImage complete:^(UIImage *new) {
//        self.workingImage = new;
//        self.imageView.image = new;
//    }];
//    UIImage *new = [ImageProcessor.sharedImageProcessor processorImageUsingCoreGraphics:fixedImage];
    UIImage *new = [ImageProcessor.sharedImageProcessor processorImageUsingCoreImage:fixedImage];
    self.workingImage = new;
    self.imageView.image = new;
}


#pragma mark - UIImagePickerDelegate
- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker {
    [[picker presentingViewController] dismissViewControllerAnimated:YES completion:nil];
}

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info {
    // Dismiss the imagepicker
    [[picker presentingViewController] dismissViewControllerAnimated:YES completion:nil];
    [self setupWithImage:info[UIImagePickerControllerOriginalImage]];
}


@end
