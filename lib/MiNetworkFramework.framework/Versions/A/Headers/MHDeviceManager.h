//
//  MHDeviceManager.h
//  MiDeviceFramework
//
//  Created by zhangyinze on 16/8/26.
//  Copyright © 2016年 zhangyinze. All rights reserved.
//

#import <Foundation/Foundation.h>
//#import "MHRequestSerializer.h"
@class MHDevice;
@class MHDevices;
@class MHVersion;
@class MHDataDeviceTimer;
@class MHDeleteUser;
@class MHShareUser;
@class MHSharedDevice;
@class MHFirmwareInfo;
@protocol MHRequestConfig;

@interface MHDeviceManager : NSObject  

//网络请求需要额外配置的的参数
//note : 如果集成了 MHAccount,这个属性可以忽略.
//note : 如果用了别的帐号系统,网络请求时需要传入一些帐号信息,需要自己设置这个属性.
//note : 如果后台不需要额外的信息,这个属性也可以忽略
@property (nonatomic, strong) id<MHRequestConfig> serializer;
@property (nonatomic, copy) NSString *locale;
/**
 *  获取设备列表
 *
 *  @param dids       需要过滤的列表.
 nil,拉取说有设别
 dids,要拉取的设备信息.
 *  @param deviceList 返回一个
 */
-(void)fetchDeviceListWithFilters:(NSArray<NSString*>*)dids DeviceListBlock:(void(^)(MHDevices* deviceList))deviceList failure:(void(^)(NSError* error))failure;



/**
 *  获取新连入的设备
 *
 *  @param ssid       路由器的 ssid
 *  @param bssid      路由器的 mac 地址
 *  @param deviceList 返回的结果
 */
-(void)fetchNewDeviceWith:(NSString*)ssid withBssid:(NSString*)bssid  withDeviceMac:(NSString*)deviceMac channel:(NSString*)channel DeviceListBlock:(void(^)(MHDevices* deviceList))deviceList failure:(void(^)(NSError* error))failure;



/**
 *  绑定设备
 *
 *  @param device 设备
 */
-(void)bindDeviceWith:(MHDevice*)device  token:(NSString*)token sucess:(void(^)(NSError* error))sucessBlock failure:(void(^)(NSError* error))failureBlock;


/**
 *  解除绑定设备
 *
 *  @param device       设备
 *  @param sucessBlock  成功后的回调
 *  @param failureBlock 失败后的回调
 */
-(void)unbindDeviceWith:(MHDevice*)device sucess:(void(^)(NSError* error))sucessBlock failure:(void(^)(NSError* error))failureBlock;



/**
 *  删除设备
 *
 *  @param devices      所要删除设备的列表
 *  @param sucessBlock
 *  @param failureBlock
 */
-(void)deleteDevices:(NSArray<MHDevice*>*)devices sucess:(void(^)(NSError* error))sucessBlock failure:(void(^)(NSError* error))failureBlock;



/**
 *  修改设备的名称
 *
 *  @param name         设备的新名称
 *  @param device       所要修改名字的设备
 *  @param sucessBlock
 *  @param failureBlock
 */
-(void)modifyDeviceName:(NSString*)name forDevice:(MHDevice*)device sucess:(void(^)(NSError* error))sucessBlock failure:(void(^)(NSError* error))failureBlock;


/**
 *  分享设备
 *
 *  @param device       分享的设备
 *  @param userId       分享给的用户
 *  @param type         分享类型:@""为可控制 @"readonly"为只读
 *  @param sucessBlock
 *  @param failureBlock
 */
-(void)shareDevice:(NSArray<MHDevice*>*)devices toUser:(NSString*)userId withType:(NSString*)type sucess:(void(^)(NSError* error))sucessBlock failure:(void(^)(NSError* error))failureBlock;


/**
 获取设备分享给那些人

 @param device 分享的设备
 @param successBlock 成功
 @param failureBlock 失败
 */
-(void)fetchSharedUsersOfDevice:(MHDevice*)device success:(void(^)(NSArray<MHShareUser*>*))successBlock failure:(void(^)(NSError* error))failureBlock;


/**
 取消把设备分享给用户

 @param device 被分享的设备
 @param userIds 已经分享的用户id
 @param successBlock 成功
 @param failureBlock 失败
 */
-(void)cancelShareDevice:(MHDevice *)device sharedUsers:(NSArray<NSString*>*)userIds success:(void(^)(NSArray<MHDeleteUser*>* deleteUsers))successBlock failure:(void(^)(NSError* error))failureBlock;



/**
 获取分享请求

 @param userId 被分享用户的id
 @param successBlock 成功
 @param failureBlock 失败
 */
-(void)fetchSharedDevices:(NSString*)userId success:(void(^)(NSArray<MHSharedDevice*>*))successBlock failure:(void(^)(NSError* error))failureBlock;



/**
 处理分享请求

 @param msgId   在MHShareDevice中的msgId
 @param action  accept / reject
 @param invid   在MHShareDevice中的ivid
 @param successBlock 成功
 @param failureBlock 失败
 */
-(void)replyShareRequest:(NSString*)msgId action:(NSString*)action invId:(NSInteger)invid success:(void(^)(NSError* error))successBlock failure:(void(^)(NSError* error))failureBlock;

/**
 *  升级设备的固件
 *
 *  @param device       设备
 *  @param sucessBlock
 *  @param failureBlock
 */
-(void)updateDeviceFirmware:(MHDevice*)device sucess:(void(^)(NSError* error))sucessBlock failure:(void(^)(NSError* error))failureBlock;


/**
 *  检查设备固件的版本号
 *
 *  @param device     设备
 *  @param sucessBlock
 *  @param failureBlock
 */
-(void)checkDeviceFirmwareVersion:(MHDevice*)device sucess:(void(^)(MHVersion* version))sucessBlock failure:(void(^)(NSError* error))failureBlock;

/**
 *  蓝牙设备固件升级 获取固件升级信息
 *
 *  @param model      设备的model
 *  @param sucessBlock
 *  @param failureBlock
 */
- (void)firmwareUpdateInfoWithDeviceModel:(NSString *)model sucess:(void(^)(MHFirmwareInfo* info))sucessBlock failure:(void(^)(NSError* error))failureBlock;


/**
 获取定时器列表

 @param did          设备id
 @param successBlock successBlock
 @param failureBlock failureBlock
 */
-(void)fetchTimerListWith:(NSString*)did success:(void(^)(NSArray<MHDataDeviceTimer*> *timerList))successBlock failure:(void(^)(NSError* error))failureBlock;


/**
 编辑定时

 @param timer        已有或者新创建的定时器
 @param sucessBlock  successBlock
 @param failureBlock failureBlock
 */
-(void)editTimer:(MHDataDeviceTimer*)timer success:(void(^)(NSError* error))sucessBlock failure:(void(^)(NSError* error))failureBlock;



/**
 删除定时器

 @param timerId      定时器id
 @param sucessBlock  sucessBlock
 @param failureBlock failureBlock
 */
-(void)deleteTimer:(NSString*)timerId success:(void(^)(NSError* error))sucessBlock failure:(void(^)(NSError* error))failureBlock;

/**
 *  操纵设备
 *
 *  @param device     设备
 *  @param method  操作设备的方法
 *  @param params  参数
 *  @param sucess  成功
 *  @param failure 失败
 */
-(void)callDeviceMethod:(MHDevice*) device method:(NSString *)method params:(id)params sucess:(void(^)(id result))sucess failure:(void(^)(NSError* error))failure;

/**
 *  得到用户的头像信息
 *  @param uid 用户id
 *  @param sucessBlock 成功的回调 obj 为 MHAvatarInfo 对象。
 *  @param failureBlock 失败的回调。
 */
-(void)getUserProfile:(NSString*)uid success:(void (^)(id obj))sucessBlock failure:(void (^)(NSError *))failureBlock;

/**
 *  @params rpcs : rpcs格式
 *    - rpcs(array)
        -did
        -method (可选)
        -params (array)
        -method (可选)

 *  @param sucess obj参数为 
 *      -code
 *      -message
 *      -result (array)
 *          -code
 *          -did
 */
-(void)batchRpc:(NSString*)method  rps:(NSArray*)rpcs sucess:(void(^)(id result))sucess failure:(void(^)(NSError* error))failure;

@end
