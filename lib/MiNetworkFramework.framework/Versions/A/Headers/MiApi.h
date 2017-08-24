//
//  MiApi.h
//  OpenMiHome
//
//  Created by CoolKernel on 1/17/17.
//  Copyright © 2017 CoolKernel. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MiApiObject.h"
#import <UIKit/UIKit.h>

@protocol MiApiDelegate <NSObject>
@optional

- (void)onReq:(MiBaseReq *)req;

- (void)onResp:(MiBaseResp *)resp;

@end

@interface MiApi : NSObject

/**
 向米家app注册第三方应用

 @param appid 米家开发ID,必须加前缀“XM”作为scheme
 @return 成功返回YES，失败返回NO
 */
+ (BOOL)registerApp:(NSString *)appid;

/**
 向米家发送请求，等待米家返回onResp
 函数调用后，会切换到米家的界面。第三方应用程序等待米家返回onResp。米家在异步处理完成后一定会调用onResp。
 @param req 具体的发送请求
 @return 成功返回YES，失败返回NO
 */
+ (BOOL)sendReq:(MiBaseReq *)req;

/**
 发送Auth请求到米家

 @param req 具体的发送请求
 @param viewController 当前界面对象
 @param delegate 用来接收米家消息
 @return 成功返回YES，失败返回NO
 */
+ (BOOL)sendAuthReq:(MiSendAuthReq *)req viewController:(UIViewController *)viewController delegate:(id<MiApiDelegate>)delegate;

/**
 发送 设备Auth请求到米家
 
 @param req 具体的发送请求
 @param viewController 当前界面对象
 @param delegate 用来接收米家消息
 @return 成功返回YES，失败返回NO
 */
+ (BOOL)sendDeviceAuthReq:(MiSendDeviceAuthReq *)req viewController:(UIViewController *)viewController delegate:(id<MiApiDelegate>)delegate;

/**
 收到米家onReq的请求，发送对应的应答给米家，并切换到米家界面
 函数调用后，会切换到米家的界面。第三方应用程序收到米家onReq的请求，异步处理该请求，完成后必须调用该函数
 @param resp 具体应答内容
 @return 成功返回YES，失败返回NO
 */
+ (BOOL)sendResp:(MiBaseResp *)resp;

/**
 处理米家通过URL启动App时传递的数据

 @param url 米家启动第三方应用传递过来的URL
 @param delegate 用来接收米家消息
 @return 成功返回YES，失败返回NO
 */
+ (BOOL)handleOpenURL:(NSURL *)url delegate:(id<MiApiDelegate>)delegate;

/**
 检查当前米家是否被用户安装

 @return 已经安装返回YES，未安装返回NO
 */
+ (BOOL)isMiAppInstalled;

/**
 获取当前米家SDK的版本号

 @return 返回当前米家SDK的版本号
 */
+ (NSString *)getApiVersion;

/**
 获取米家itunes安装地址

 @return 米家的安装地址字符串
 */
+ (NSString *)getMiAppInstallUrl;

+ (CGFloat)sdkVersion;

+ (NSString*)respCodeString:(MijiaAuthCode)authCode;
@end
