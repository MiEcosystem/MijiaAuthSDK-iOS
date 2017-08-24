//
//  MHSharedDevice.h
//  MiDeviceFramework
//
//  Created by yinze zhang on 2016/11/3.
//  Copyright © 2016年 zhangyinze. All rights reserved.
//

#import <Foundation/Foundation.h>
typedef NS_ENUM(NSInteger,kDeviceShareStatus){
    eShareStatusWaiting,
    eShareStatusAccepet,
    eShareStatusRefuses
};

@interface MHSharedDevice : NSObject

@property (nonatomic, assign) NSInteger ctime;
@property (nonatomic, copy) NSString* name;
@property (nonatomic, copy) NSString* did;
@property (nonatomic, assign) NSInteger expireTime;//过期时间,如果超过这个期限,就是放弃.在status为waiting的时候判断
@property (nonatomic, copy) NSString* invId;
@property (nonatomic, copy) NSString* model;
@property (nonatomic, copy) NSString* msgId;
@property (nonatomic, copy) NSString* sender;
@property (nonatomic, copy) NSString* senderName;
@property (nonatomic, assign) kDeviceShareStatus status;

@end
