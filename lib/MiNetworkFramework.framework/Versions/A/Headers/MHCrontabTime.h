//
//  MHCrontabTime.h
//  MiHome
//
//  Created by Wayne Qiao on 15/10/19.
//  Copyright © 2015年 小米移动软件. All rights reserved.
//

#import <Foundation/Foundation.h>

// 周日定义
typedef enum : NSUInteger {
    MHCrontabDayOfWeekNone = 0,
    MHCrontabSunday     = 1,
    MHCrontabMonday     = 1<<1,
    MHCrontabTuesday    = 1<<2,
    MHCrontabWednesday  = 1<<3,
    MHCrontabThursday   = 1<<4,
    MHCrontabFriday     = 1<<5,
    MHCrontabSaturday   = 1<<6,
} MHCrontabDayOfWeek;

// 工作日
static const NSUInteger MHCrontabWeekday = (MHCrontabMonday | MHCrontabTuesday | MHCrontabWednesday | MHCrontabThursday | MHCrontabFriday);
// 周末
static const NSUInteger MHCrontabWeekend = (MHCrontabSaturday | MHCrontabSunday);
// 每天
static const NSUInteger MHCrontabEveryday = (MHCrontabWeekday | MHCrontabWeekend);

@interface MHCrontabTime : NSObject <NSCopying>

@property (nonatomic, assign) NSUInteger minute;     //分
@property (nonatomic, assign) NSUInteger hour;       //时
@property (nonatomic, assign) NSUInteger dayOfMonth; //日
@property (nonatomic, assign) NSUInteger month;      //月
@property (nonatomic, assign) NSUInteger daysOfWeek; //周日（crontab规则：可以指定多个周日）

// 使用crontab字符串初始化CrontabTime对象
- (instancetype)initWithCrontabString:(NSString *)cs;

// 使用北京时间crontab字符串初始化CrontabTime对象
+ (instancetype)timeFromBeijingCrontabString:(NSString *)beijingCrontabString;

// 转换成crontab字符串
- (NSString *)crontabString;

// 北京时间crontab字符串
- (NSString *)beijingTimeCrontabString;

// 重复描述
- (NSString *)repeatDescription;

// 定时描述
- (NSString *)timerDescription;

// 检查两个time是否equal
- (BOOL)isEqualToTime:(MHCrontabTime *)time;

@end
