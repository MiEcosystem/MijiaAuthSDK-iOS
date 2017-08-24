//
//  MHShareUser.h
//  MiDeviceFramework
//
//  Created by yinze zhang on 2016/11/3.
//  Copyright © 2016年 zhangyinze. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger,kUserShareStatus){
    eUserShareStatusWaiting,
    eUserShareStatusAccepet,
    eUserShareStatusRefuses
};

@interface MHShareUser : NSObject

@property (nonatomic, copy) NSString* icon;
@property (nonatomic, copy) NSString* nickname;
@property (nonatomic, assign) NSInteger sharetime;
@property (nonatomic, assign) kUserShareStatus status;
@property (nonatomic, assign) NSInteger userid;

@end
