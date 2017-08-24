//
//  MHTimeUtils.h
//  MiHome
//
//  Created by Woody on 14/12/30.
//  Copyright (c) 2014年 小米移动软件. All rights reserved.
//

#import <Foundation/Foundation.h>

#define kTimeIntervalOneDay (24*3600)

@interface MHTimeUtils : NSObject

+ (NSDate* )beijingDateWithHour:(NSInteger)hour minute:(NSInteger)min second:(NSInteger)sec refDate:(NSDate *)refDate;

#pragma mark - 转换时区

// 检查两个时区的时间早晚，Ex：北京（东八区）比日本（东九区）时间早
+ (BOOL)isTimeZone:(NSTimeZone *)timeZone1 earlierThanTimeZone:(NSTimeZone *)timeZone2;

// 把本地Hms转换成北京时间Hms
+ (void)changeLocalTimeOfHour:(NSInteger)hour minute:(NSInteger)min second:(NSInteger)sec toBeijingTimeHour:(NSInteger*)bjHour minute:(NSInteger*)bjMin second:(NSInteger*)bjSec;
// 把北京时间Hms转换成本地Hms
+ (void)changeBJTimeOfHour:(NSInteger)hour minute:(NSInteger)min second:(NSInteger)sec toLocalTimeHour:(NSInteger*)localHour minute:(NSInteger*)localMin second:(NSInteger*)localSec;

+ (NSString* )gatewayLogDateString:(NSDate* )date;

// 消息中心时间显示
+ (NSString* )shareMsgListDateString:(NSDate* )date;

#pragma mark - 解析日期
// 根据指定unit和timezone，获取日期的component
+ (NSDateComponents *)componentsWithUnits:(NSCalendarUnit)units inTimeZone:(NSTimeZone *)timeZone forDate:(NSDate *)date;
// 根据指定的unit获取日期的component
+ (NSDateComponents *)componentsWithUnits:(NSCalendarUnit)units forDate:(NSDate *)date;
// 获取日期的month
+ (NSInteger)monthForDate:(NSDate *)date;
// 获取日期的day of month
+ (NSInteger)dayOfMonthForDate:(NSDate *)date;
// 获取日期的weed of year
+ (NSInteger)weekOfYearForDate:(NSDate *)date;


// 获取日期的对应周的描述字符串
+ (NSString *)weekAgoForDate:(NSDate *)date;
// 生成本地时间字符串
+ (NSString *)localTimeStringForDate:(NSDate *)date;
// 生成本地时间格式化字符串
+ (NSString *)localFormattedStringForDate:(NSDate *)date dateFormat:(NSString *)format;

#pragma mark - 定义日期

// 基于某日期指定月日时分秒
+ (NSDate* )dateWithMonth:(NSInteger)month
                      day:(NSInteger)day
                     hour:(NSInteger)hour
                   minute:(NSInteger)min
                   second:(NSInteger)sec
                 timeZone:(NSTimeZone *)timeZone
                  refDate:(NSDate *)refDate;

//在某日期基础上指定了时分秒的日期
+ (NSDate* )dateWithHour:(NSInteger)hour
                  minute:(NSInteger)min
                  second:(NSInteger)sec
                timeZone:(NSTimeZone *)timeZone
                 refDate:(NSDate *)refDate;

// 昨天同一时间
+ (NSDate *)yesterdayForDate:(NSDate *)date;
// 明天同一时间
+ (NSDate *)tomorrowForDate:(NSDate *)date;
// 本周第一天（周日）
+ (NSDate *)firstDayOfWeekWhichContainsDate:(NSDate *)date;
// 本周最后一天（周六）
+ (NSDate *)lastDayOfWeekWhichContainsDate:(NSDate *)date;
// 本月第一天
+ (NSDate *)firstDayOfMonthWhichContainsDate:(NSDate *)date;
// 本月最后一天
+ (NSDate *)lastDayOfMonthWhichContainsDate:(NSDate *)date;

#pragma mark - 日期比较

// date1是否和date2是同一天
+ (BOOL)isDate1:(NSDate *)date1 inSameDayWithdate2:(NSDate *)date2;
// date是否是今天
+ (BOOL)isDateInToday:(NSDate *)date;
// date是否是昨天
+ (BOOL)isDateInYesterday:(NSDate *)date;
// date是否是明天
+ (BOOL)isDateInTomorrow:(NSDate *)date;

+ (BOOL)isToday:(NSDate*)date;
+ (BOOL)isYesterday:(NSDate*)date;
+ (BOOL)isDayBeforeYesterday:(NSDate*)date;
+(BOOL)isMonday:(NSDate* )refDate;
+(BOOL)isThisWeek:(NSDate* )refDate;
+(BOOL)isLastWeek:(NSDate* )refDate;
+ (NSString* )weekString:(NSDate*)refDate;
+(BOOL)isThisMonth:(NSDate* )refDate;
+(BOOL)isLastMonth:(NSDate* )refDate;

@end
