//
//  MiApiObject.h
//  OpenMiHome
//
//  Created by CoolKernel on 1/17/17.
//  Copyright © 2017 CoolKernel. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum MijiaAuthCode {
    kMijiaAuthSuccess = 100,//授权成功
    kMijiaAuthBindSuccess = 101,//绑定成功
    kMijiaAuthPackageError = -100,//包名错误
    kMijiaAuthLackParamsError = -101,//缺少参数
    kMijiaAuthGetTokenError = -102,//获取token失败
    kMijiaAuthAuthError = -103,//授权失败
    kMijiaAuthAppIdError = -104,//appid有问题
    kMijiaAuthAppSignError = -105,//签名错误
    kMijiaAuthAuthCancel = -106,///取消授权
    kMijiaAuthRequestAuthError = -107,//请求授权失败
    kMijiaAuthRequestCodeError = -108,//请求的code错误
    kMijiaAuthRequestDidError = -109,///缺少did
    kMijiaAuthRequestAuthNoCapability = -110,///该设备不支持语音授权，或者该设备不属于你的名下
    kMijiaAuthRequestAuthNoPermisson = -111,///该账号不支持该类型授权，请到开放平台申请
    kMijiaAuthRequestMissParams = -112,//缺少参数
    kMijiaAuthRequestBindError = -113,//绑定失败
    kMijiaAuthRequestAPILevelErr = -114,///版本号不匹配
    kMijiaAuthRequestNotSupportForInternal = -115,//暂时不支持海外版
    kMijiaAuthRequestNetworkError = -116, //网络错误
    kMijiaAuthRequestServiceDisconnect = -901,//service已经断开
    kMijiaAuthRequestMijiaVersionErr = -902,//可能没有安装米家，或者米家版本太低
    kMijiaAuthRequestNoResponse = -903,///IAuthResponse 为空
    
    kMijiaAuthNoSupportCountry = -1000, //不支持当前国家
    kMijiaAuthAccountNotMatch = -1001, //与当前米家账户不一致，请切换账户后重试
    kMijiaAuthNetworkingError = -1001, //网络错误
    
    kRequestCodeCallAuthForApp = 4,//给应用授权
    kRequestCodeCallAuthForDevice = 2,//给设备授权
    kRequestCodeCallAUthForBindDevice = 6,//给需要绑定的设备授权
    
//    kMijiaAuthNetworkingNotResponseCode = -99999,
}MijiaAuthCode;


typedef enum : NSUInteger {
    MiAuth = 1,
    MiNormal,
    MiDeviceAuth,
    MiAccountBind,
    MiAccountBindKey,
} MiServiceType;

@interface MiBaseReq : NSObject
@property (nonatomic, assign) MiServiceType type;

@end

@interface MiBaseResp : NSObject
@property (nonatomic, assign) MiServiceType type;
/*
 1.0版本的sdk是没有sdkversion的，errCode的返回只有0，或者-1.
 2.0以后的版本(包括2.0） response 添加新的属性respCode，这个属性
 返回更多的错误，
 3.0 MiDeviceAuth 添加userid 字段。注意userid是必须填的字段。不填授权出错
 4.0 添加bindkey的授权方式
 */
@property (nonatomic, assign) CGFloat sdkVersion;
/** 错误码 */
@property (nonatomic, assign) int errCode;
/** 错误提示字符串 */
@property (nonatomic, retain) NSString *errStr;
/** 返回的状态码，是用来代替errCode的，errCode兼容第一版，第二版新加respCode */
@property (nonatomic, assign) int respCode;
@end

@interface MiSendAuthReq : MiBaseReq

@end


@interface MiSendAuthResp : MiBaseResp

@end

@interface MiSendDeviceAuthReq : MiSendAuthReq
@property (nonatomic, strong) NSString* did;
@property (nonatomic, strong) NSString* userId;
@property (nonatomic, assign) BOOL ignoreUserId;
@end



typedef enum MiDeviceAuthRespCode {
    MiDeviceAuthRespCodeSuccess = 0,
    MiDeviceAuthRespCodeNotOwner = -1, //当前用户不是设备所有者
    MiDeviceAuthRespCodeServiceException = -4,//服务异常，如存储服务访问异常
    MiDeviceAuthRespCodeNotVoiceDevice = -7,// 语音设备不存在
    MiDeviceAuthRespCodeNotSupportVoiceCtl = -24,//该设备不支持语音控制
}MiDeviceAuthRespCode;

@interface MiSendDeviceAuthResp : MiSendAuthResp
//json 字符串。可能是NSDictionary 可能是NSArray<NSDictionary*> 里面的code对象是MiDeviceAuthRespCode
@property (nonatomic, strong) NSString* result;
@end


@interface MiSendAccountBindReq : MiSendAuthReq
@property (nonatomic, strong) NSString* did;
@property (nonatomic, strong) NSString* token;
@property (nonatomic, strong) NSString* sn;
@property (nonatomic, strong) NSString* model;
@property (nonatomic, strong) NSString* timeStamp;
@end

@interface MiSendAccountBindResp : MiSendAuthResp
//json 字符串。可能是NSDictionary 可能是NSArray<NSDictionary*> 里面的code对象是MiDeviceAuthRespCode
@property (nonatomic, strong) NSString* result;
@end


@interface MiSendBindKeyReq : MiSendAuthReq
@property (nonatomic, strong) NSString* bindKey;
@property (nonatomic, strong) NSString* model;
@end

@interface MiSendBindKeyResp : MiSendAuthResp
@property (nonatomic, strong) NSString* result;
@end
