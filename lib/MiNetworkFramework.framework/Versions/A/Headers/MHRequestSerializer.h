//
//  MHRequestSerializer.h
//  MSmartHomeFramework
//
//  Created by zhangyinze on 16/8/15.
//  Copyright © 2016年 zhangyinze. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MHPassport.h"

@protocol MHRequestConfig <NSObject>

/**
 *  配置 http 发送请求时,所需要带的数据
 *  
 *  @param parameters 规则话的参数,通俗的讲就是需要 client 传入的.
 *                    可以自定义,例如:把传入的 parameters 加密,或者在原来的基础上增加参数等等
 *                    note:如果不需要任何操作,请把输入 parameters 返回
 *  @return 一个配置完成后的字典,需要一些通用的数据.比如说,token,appID 等用户属性数据
 */
-(NSDictionary*)configHttpRequest:(NSDictionary*)parameters;

@end



@interface MHRequestSerializer : NSObject<MHRequestConfig>

+(instancetype)serializer;

@end



/**
 *  当需要的数据是以 post 的方式传送,并且需要设置 httpBoady的时候
 */
@interface MHRequestBodySerializer: MHRequestSerializer

@end

/**
 *  当需要设置 cookie 的时候
 */
@interface MHRequestCookieSerializer : MHRequestSerializer

@end

/**
 auth 认证serializer
 */
@interface MHAuthRequestSerializer : MHRequestSerializer

@end

@interface MHAuthRequestBodySerializer : MHRequestSerializer

@end


@interface MHRequestLocalePassportSerializer : MHRequestSerializer

@property (nonatomic, copy) NSString *locale;

@end


