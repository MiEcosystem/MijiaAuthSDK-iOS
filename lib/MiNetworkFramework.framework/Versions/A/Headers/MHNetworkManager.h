//
//  MHNetworkManager.h
//  MSmartHomeFramework
//
//  Created by zhangyinze on 16/8/15.
//  Copyright © 2016年 zhangyinze. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MHRequestSerializer.h"

@class MHBaseRequest;
@class MHMiotBaseRequest;
@interface MHNetworkManager : NSObject

//自定义时需要的一些额外数据,这些暂时包括帐号系统的一些数据
@property (nonatomic, strong) id<MHRequestConfig> requestSerilizer;

-(void)postRequest:(MHBaseRequest*)request sucess:(void(^)(MHBaseRequest* quest,id responseObject))sucess failure:(void(^)(NSError* error))failure;


-(void)getRequest:(MHBaseRequest*)request sucess:(void(^)(MHBaseRequest* quest,id responseObject))sucess failure:(void(^)(NSError* error))failure;

/**
 POST请求(未加密)
 */
- (void)sendNormalRequest:(MHMiotBaseRequest *)request sucess:(void(^)(MHMiotBaseRequest *request,id responseObject))sucess failure:(void(^)(NSError* error))failure;

/**
 GET请求(未加密)
 */
- (void)sendNormalGETRequest:(MHMiotBaseRequest *)request sucess:(void(^)(MHMiotBaseRequest *request,id responseObject))sucess failure:(void(^)(NSError* error))failure;

/**
 PUT请求(未加密)
 */
- (void)sendNormalPUTRequest:(MHMiotBaseRequest *)request sucess:(void(^)(MHMiotBaseRequest *request,id responseObject))sucess failure:(void(^)(NSError* error))failure;


- (void)sendDataRequest:(MHMiotBaseRequest *)request sucess:(void(^)(MHMiotBaseRequest *request,id responseObject))sucess failure:(void(^)(NSError* error))failure;
@end
