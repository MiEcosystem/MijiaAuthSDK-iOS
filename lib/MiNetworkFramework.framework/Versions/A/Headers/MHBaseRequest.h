//
//  MHBaseRequest.h
//  MSmartHomeFramework
//
//  Created by zhangyinze on 16/8/15.
//  Copyright © 2016年 zhangyinze. All rights reserved.
//

#import <Foundation/Foundation.h>

//#import "MHRequestModel.h"


NS_ASSUME_NONNULL_BEGIN



@interface MHBaseRequest : NSObject


/**
 设置请求的BaseURL

 @param url url
 */
+(void)setupBaseRequestUrl:(NSString*)url;


/**
 查询当前的BaseURL

 @return 当前的URL
 */
+(NSString*)currentBaseRequestUrl;

-(NSString*)baseHttpPath;

//返回数据的 ModelClass
@property (nonatomic, strong) Class modelClass;

/**
 *  每个请求的具体 path
 *  eg: /path/query
 *  @return
 */
-(NSString*)path;



/**
 *  一个完整的 URL
 *
 *  @return
 */
-(NSString*)absoluteURL;


/**
 *
 *  @return 每个 request 需要的参数
 */
-(NSDictionary*)requestParameters;


/**
 *  需要再 Head 中设置的参数
 *
 *  @return 
 */
-(NSDictionary*)headParameters;


@end
NS_ASSUME_NONNULL_END
