//
//  MHDevice.h
//  MSmartHomeFramework
//
//  Created by zhangyinze on 16/8/17.
//  Copyright © 2016年 zhangyinze. All rights reserved.
//

#import <Foundation/Foundation.h>
@interface MHDevice : NSObject
@property (nonatomic, copy) NSString* did;          //设备的ID
@property (nonatomic, copy) NSString* token;        //设备的Token，每次快连后，设备的token会发生变化
@property (nonatomic, assign) double longitude;     //上次绑定时的经度
@property (nonatomic, assign) double latitude;      //上次绑定时的纬度
@property (nonatomic, copy) NSString* name;         //设备名称，用户可以修改
@property (nonatomic, copy) NSString* model;        //设备类别标识，如插座、摄像头
@property (nonatomic, copy) NSString* parent_id;    //父设备的ID
@property (nonatomic, copy) NSString* parent_model; //父设备的Model
@property (nonatomic, assign) NSInteger pid;        //设备id
@property (nonatomic, assign) BOOL isOnline;        //设备是否在线（是否通电）
@property (nonatomic, assign) BOOL adminFlag;       //是否被绑定
@property (nonatomic, assign) BOOL shareFlag;       //是否已分享
@property (nonatomic, assign) BOOL resetFlag;       //本地设备才会返回该字段，为1时表示设备刚刚reset过
@property (nonatomic, retain) id prop;  //可选字段，当该类型设备有默认属性时，这里为默认属性的值，否则无此字段；//并且，不同的设备类型，prop中包含的属性不同，prop实际是个dictionary
@property (nonatomic, copy) NSString* localip;      //设备的Ip，局域网内的Ip
@property (nonatomic, strong) NSDictionary* extra;
@property (nonatomic, copy) NSString* mac;       //设备的mac
@property (nonatomic, strong) NSDictionary* owner; //设备的拥有者

/*
@property (nonatomic, assign) NSInteger showMode;   //仅对子设备有效，用来标明子设备是否显示在设备列表页，1：显示 0：不显示
@property (nonatomic, copy) NSString* desc;      //设备在设备列表展示的副标题
@property (nonatomic, copy) NSString* ssid;      //设备的ssid
@property (nonatomic, copy) NSString* bssid;     //设备的bssid
@property (nonatomic, retain) NSArray* method;
@property (nonatomic, assign) NSInteger rssi;    //信号强度
@property (nonatomic, assign) NSInteger permitLevel;   //只读分享过来的设备 4:普通分享 36:只读分享
 */
@end
