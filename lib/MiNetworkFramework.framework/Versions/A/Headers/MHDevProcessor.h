//
//  MHDevProcessor.h
//  MiNetworkFramework
//
//  Created by CoolKernel on 05/07/2017.
//  Copyright © 2017 zhangyinze. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MHDeviceProfile.h"

@class MHGetDevProfileRequest;
@interface MHDevProcessor : NSObject

+ (instancetype)shared;

- (void)pullDeviceProfileWithType:(NSString *)type
                       completion:(void (^)(MHDeviceProfile *, NSError *))completion;


- (void)getDeviceList:(void (^)(NSArray <MHMiotDevice *> *, NSError *))completion;


- (void)getDeviceProperties:(NSArray <NSString *> *)pids
                 completion:(void (^)(NSArray <MHDevPropertyValue *> *, NSError *error))completion;

- (void)setDeviceProperties:(NSArray <MHDevPropertyValue *> *)properties
                 completion:(void (^)(id response, NSError *error))completion;

@end
