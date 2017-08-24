//
//  MHAuthDeviceManager.h
//  MiNetworkFramework
//
//  Created by CoolKernel on 27/02/2017.
//  Copyright © 2017 zhangyinze. All rights reserved.
//

#import <Foundation/Foundation.h>

@class MHDevice;
@class MHDevices;
@protocol MHRequestConfig;

@interface MHAuthDeviceManager : NSObject
@property (nonatomic, strong) id<MHRequestConfig> serializer;

- (void)fetchAuthDeviceListWithFilters:(NSArray<NSString*>*)dids DeviceListBlock:(void(^)(MHDevices* deviceList))deviceList failure:(void(^)(NSError* error))failure;

@end
