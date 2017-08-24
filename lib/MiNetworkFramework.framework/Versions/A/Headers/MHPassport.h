//
//  MHPassport.h
//  MSmartHomeFramework
//
//  Created by zhangyinze on 16/8/12.
//  Copyright © 2016年 zhangyinze. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MHError.h"
#import <MiPassport/MiPassport.h>
typedef void(^completion)(NSDictionary* jsonResult,NSError* error);


@protocol MHUserConfig <NSObject>

@optional
/**
 *  获取用户登录后的一些用户信息，根据 SDK 提供的不同，返回值有所不同。
 *  例如:网络请求需要一些登录后的数据,让后台做校验,就从这个接口中来.
 *  @return
 */
+(NSDictionary*)accountLoginParameters;


@end


@protocol MHPassport <NSObject>

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
 *  登录是否已经过期
 *
 *  @return YES,过期
 *          NO, 未过期
 */
-(BOOL)isExpire;

@end


@interface MHPassport : NSObject<MHPassport,MHUserConfig>
@property(nonatomic, copy, readonly) NSString* accessToken;
@property(nonatomic, copy, readonly) NSString* appId;

@property(nonatomic, strong, readonly) MiPassport* miPassport;
   
/**
 *  初始化方法
 *
 *  @param appId       第三方应用的 appID,通过在小米官网注册而来
 *  @param redirectUrl 在注册应用的时候,注册的一个 URL
 *
 *  @return MHPassport 的实例
 */
-(instancetype)initWithAppId:(NSString*)appId redirectUrl:(NSString*)redirectUrl;


/**
 *  调用远程服务,获取相应的数据
 *
 *  @param process    @"user/profile" 获取用户简介
                      @"user/relation" 获取用户的关系链
 
 *  @param method     http 的调用方式  GET,POST
 *  @param completion 数据返回成功后的回调
 */
-(void)callProcess:(NSString*)process httpMethod:(NSString*)method completion:(completion)completion;


/**
 *  获取Authorization code
 *
 *  @param openIDBlock 
 */
-(void)fetchOpenID:(void(^)(NSString* openId,NSError* error))openIDBlock;

- (void)getExtToken:(void (^)(NSString* token))sucessBlock fail:(void (^)(NSError* err))failBlock;
@end


