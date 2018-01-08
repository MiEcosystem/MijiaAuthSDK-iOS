//
//  MHVersion.h
//  MiDeviceFramework
//
//  Created by yinze zhang on 16/9/12.
//  Copyright © 2016年 zhangyinze. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MHVersion : NSObject

@property (nonatomic, copy) NSString *curr;
@property (nonatomic, assign) NSInteger force;
@property (nonatomic, assign) BOOL isLatest;
@property (nonatomic, copy) NSString *latest;
@property (nonatomic, copy) NSString *ota_failed_code;
@property (nonatomic, copy) NSString *ota_failed_reason;
@property (nonatomic, copy) NSString *ota_progress;
@property (nonatomic, copy) NSString *ota_status;
@property (nonatomic, copy) NSString *timeout_time;
@property (nonatomic, assign) NSInteger updating;
@property (nonatomic, copy) NSString* desp;

@end
