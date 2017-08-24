//
//  MHNetworkEngine.h
//  MSmartHomeFramework
//
//  Created by zhangyinze on 16/8/17.
//  Copyright © 2016年 zhangyinze. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MHRequestSerializer.h"

@class MHDevice;
@class MHBaseRequest;



@interface MHNetworkEngine : NSObject

/**
 *  设置网络请求时的可配参数,SDK 中带有符合小米后台协议的 serializer(MHRequestBodySerializer)
 *  如果 client 自己去封装了 Mipassport,那么他需要实现 MHRequestConfig,在里面把 clientId,accessToken传入.
 *  @param serializer
 */
+(void)setRequestSerializer:(id<MHRequestConfig>)serializer;

/**
 *  调用设备
 *
 *  @param did      设备ID
 *  @param method   调用方法
 *  @param params   调用参数
 *  @param finish   完成回调
 */
+(void)callDeviceMethod:(NSString*)did method:(NSString *)method params:(id)params sucess:(void(^)(id result))sucess failure:(void(^)(NSError* error))failure;

+(void)callAuthDeviceMethod:(NSString*)did method:(NSString *)method params:(id)params sucess:(void(^)(id result))sucess failure:(void(^)(NSError* error))failure;


/**
 *  通用调用 MiHome 的接口
 *
 *  @method POST or GET
 *  @param request 调用发起的 request
 *  @param result  接口返回的结果
 */
+(void)callRemoteApi:(MHBaseRequest*)request httpMethod:(NSString*)method sucess:(void(^)(MHBaseRequest* request,id result))sucess failure:(void(^)(NSError* error))failure;

@end


