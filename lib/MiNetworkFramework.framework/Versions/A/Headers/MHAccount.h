//
//  MHAccount.h
//  MSmartHomeFramework
//
//  Created by zhangyinze on 16/8/12.
//  Copyright © 2016年 zhangyinze. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MHAccountProfile.h"
#import "MHPassport.h"
@interface MHAccount : NSObject
@property (nonatomic, copy) NSString *archivePath;  //持久化的地址,可以传入.如果不传将会使用默认的.
@property (nonatomic, copy, readonly) NSString* accessToken;
@property (nonatomic, copy, readonly) NSString* appId;
@property (nonatomic, strong, readonly) MHPassport<MHPassport>* passport;

/**
 *  初始化方法
 *
 *  @param appId       第三方应用的 appID,通过再小米官网注册而来
 *  @param redirectUrl 在注册应用的时候,注册的一个 URL
 *
 *  @return MHPassport 的实例
 */
-(instancetype)initWithAppId:(NSString*)appId redirectUrl:(NSString*)redirectUrl;




/**
 *  把账户信息持久化
 *
 *  @return YES,加载成功
            NO, 加载失败,需要调用 logIn 重新登录
 */
-(BOOL)save;


/**
 *  登录
 */
-(void)login:(NSArray<NSNumber*>*)permissions;


/**
 *  登出
 */
-(void)logOut;


/**
 *  是否已经登录
 *
 *  @return   YES, 已经登录
 *            NO, 未登录
 */
-(BOOL)isLogin;


/**
 *  获取用户的相关信息 异步
 *
 *  @param profileBlock 请求完成后返回的结果
 */
-(void)fetchAccountProfile:(void(^)(MHAccountProfile*,NSError*))profileBlock;


/**
 *  获取用户的关系列表 异步
 *
 *  @param relationBlock 请求完成后的结果
 */
-(void)fetchAccountRelation:(void(^)(NSArray<MHAccountProfile*>*,NSError*))relationBlock;


/**
 *  获取Authorization Code
 *
 *  @param openIDBlock
 */
-(void)fetchOpenId:(void(^)(NSString* openID,NSError* error))openIDBlock;

@end
