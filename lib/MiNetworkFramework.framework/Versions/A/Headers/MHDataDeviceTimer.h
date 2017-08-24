//
//  MHDataDeviceTimer.h
//  MiHomeSDK
//
//  Created by Wayne Qiao on 16/5/13.
//  Copyright © 2016年 xiaomi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MHCrontabTime.h"

@interface MHDataDeviceTimer : NSObject

+ (instancetype)dataWithJSONObject:(id)json;
- (NSDictionary *)jsonObject;

@property (nonatomic, strong) MHCrontabTime* onTimer;   //开启时间
@property (nonatomic, copy)   NSString* onMethod;
@property (nonatomic, retain) NSArray*  onParam;
@property (nonatomic, copy)   NSString* onDesc;         //开启描述
@property (nonatomic, assign) BOOL isOnOpen;            //“开启时间”是否打开

@property (nonatomic, strong) MHCrontabTime* offTimer;  //关闭时间
@property (nonatomic, copy)   NSString* offMethod;
@property (nonatomic, retain) NSArray*  offParam;
@property (nonatomic, copy)   NSString* offDesc;        //关闭描述
@property (nonatomic, assign) BOOL isOffOpen;           //“关闭时间”是否打开

@property (nonatomic, assign) BOOL isEnabled;           //定时器是否打开

@property (nonatomic, assign) NSInteger timerId;
@property (nonatomic, retain) NSString* name;
@property (nonatomic, retain) NSString* identify;
@property (nonatomic, retain) NSString* did;
@property (nonatomic, retain) NSArray* authed;
@property (nonatomic, assign) NSInteger status;  //用于处理定时数据是否同步成功

@end
