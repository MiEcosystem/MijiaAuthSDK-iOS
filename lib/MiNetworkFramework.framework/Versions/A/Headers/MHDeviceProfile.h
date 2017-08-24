//
//  MHDeviceProfile.h
//  MiNetworkFramework
//
//  Created by CoolKernel on 05/07/2017.
//  Copyright © 2017 zhangyinze. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MHDevPropertyValue : NSObject
@property (nonatomic, assign) NSInteger value;
@property (nonatomic, copy) NSString *des;
@property (nonatomic, copy) NSString *pid;
@property (nonatomic, assign) NSInteger status;
@property (nonatomic, copy) NSString *message;

@end

@interface MHDevProperty : NSObject
@property (nonatomic, assign) NSInteger iid;
@property (nonatomic, copy) NSString *type;
@property (nonatomic, copy) NSString *des;
@property (nonatomic, copy) NSString *format;
@property (nonatomic, strong) NSArray *access;
@property (nonatomic, strong) NSArray *valueRange;
@property (nonatomic, copy) NSString *unit;
@property (nonatomic, strong) NSArray <MHDevPropertyValue *> *valueList; 

@end

@interface MHDevService : NSObject
@property (nonatomic, assign) NSInteger iid;
@property (nonatomic, copy) NSString *type;
@property (nonatomic, copy) NSString *des;
@property (nonatomic, strong) NSArray <MHDevProperty *> *properties;

@end

@interface MHDeviceProfile : NSObject
@property (nonatomic, copy) NSString *type;
@property (nonatomic, copy) NSString *des;
@property (nonatomic, strong) NSArray <MHDevService *> *services;

@end

@interface MHMiotDevice : NSObject
@property (nonatomic, copy) NSString *pdid;
@property (nonatomic, copy) NSString *did;
@property (nonatomic, assign) NSInteger online;
@property (nonatomic, copy) NSString *type;
@property (nonatomic, copy) NSString *category;
@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *rid;


@end

