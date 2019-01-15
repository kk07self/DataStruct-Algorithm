//
//  main.m
//  OC
//
//  Created by K K on 2018/12/5.
//  Copyright © 2018 K K. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <objc/runtime.h>
#import <malloc/malloc.h>

int main(int argc, const char * argv[]) {
    @autoreleasepool {
    
        NSLog(@"%zu", class_getInstanceSize([NSObject class]));
        
        NSObject *obj = [[NSObject alloc] init];
        NSLog(@"%zu", malloc_size((__bridge const void *)obj));
    }
    return 0;
}
