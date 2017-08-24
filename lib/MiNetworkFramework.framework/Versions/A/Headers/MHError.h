//
//  MHError.h
//  MSmartHomeFramework
//
//  Created by zhangyinze on 16/8/18.
//  Copyright © 2016年 zhangyinze. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger,kMHErrorTypes){
    kMHErrorOK                      =  0,
    kMHErrorCustom,
    kMHErrorAccountLoginFailure,
    kMHErrorNetWorkFailure,
    kMHErrorBluetoothFailure,
};

typedef NS_ENUM(NSInteger,kMHNetErrorTypes){
    MHErrorCodePermissionDenied = -1,
    MHErrorCodeDeviceOffline = -2,
    MHErrorCodeTimeout = -3,
    MHErrorCodeServerException = -4,
    MHErrorCodeDeviceException = -5,
    MHErrorCodeInvalidRequest = -6,
    MHErrorCodeUnknownDeviceId = -7,
    MHErrorCodeInvalidParam = -8,
    MHErrorCodeUnknownError = -9,
    MHErrorCodeRepeatedRequest = -11,
    MHErrorCodeFrequentRequest = -12,
    MHErrorCodeOAuthIdentifyFailed = -13,
    MHErrorCodeMsgTooLong = -101,
    MHErrorCodeMsgFormatError = -102,
    MHErrorCodeUnknowMethod = -103
};


@interface MHError : NSError

@property(nonatomic, assign) NSInteger subCode;

/**
 *  结果正确
 *
 *  @return
 */
+(instancetype)errorOK;


/**
 *  登录时的异常
 *
 *  @param error 由第三方的 sdk 返回的错误,再次封装一层
 *
 *  @return
 */

+(instancetype)errorLoginFailure:(NSError*) error;


/**
 *  网络异常
 *
 *  @param error 有第三方 sdk 返回的错误,再次封装一层
 *
 *  @return 
 */
+(instancetype)errorNetworkFailure:(NSError*) error;



/**
 *  网络异常
 *
 *  @param errCode Mi 后台返回的网络错误
 *
 *  @return 
 */
+(instancetype)errorNetWorkFailure:(NSInteger)errCode andMsg:(NSString*)msg;


/**
 *  用户自己定义的 error
 *
 *  @param description 错误描述
 *
 *  @return 
 */
+(instancetype)errorCustomFailure:(NSString*)description;


+(instancetype)errorBluetoothFailure:(NSInteger)errCode andMsg:(NSString*)msg;

@end
