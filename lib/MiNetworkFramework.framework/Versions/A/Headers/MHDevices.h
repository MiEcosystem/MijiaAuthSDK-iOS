//
//  MHDevices.h
//  MSmartHomeFramework
//
//  Created by zhangyinze on 16/8/19.
//  Copyright © 2016年 zhangyinze. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MHDevice.h"

@interface MHDevices : NSObject
@property (nonatomic, strong) NSArray<MHDevice*> *devices;
@end
