//
//  MHAccountRelation.h
//  MSmartHomeFramework
//
//  Created by zhangyinze on 16/8/12.
//  Copyright © 2016年 zhangyinze. All rights reserved.
//

#import <Foundation/Foundation.h>

@class MHAccountProfile;

NS_ASSUME_NONNULL_BEGIN
@interface MHAccountRelation : NSObject

@property (nonatomic, strong, readonly) NSArray<MHAccountProfile*> *relation;

/**
 *  添加好友
 *
 *  @param account 好友信息
 */
-(void)addFriend:(MHAccountProfile*)account;


@end

NS_ASSUME_NONNULL_END
