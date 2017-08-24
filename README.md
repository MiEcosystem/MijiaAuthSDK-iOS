#授权方式
目前授权方式分两种：
1、设备授权，
2、设备账户绑定+授权

#iOS 设备授权使用说明

1、注册授权app。 

在 [开放平台](https://open.home.mi.com/index.html) 注册账户并创建app

2、项目内置sdk。

在AppDelegate 的 
```objc
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions{
    //注册appid
	[MiApi registerApp:@"申请的app id"];
}
```


在info.plist 里面添加新的URL types
```xml
<key>CFBundleURLTypes</key>
<array>
    <dict>
        <key>CFBundleURLName</key>
        <string>OpenMiHome</string>
        <key>CFBundleURLSchemes</key>
        <array>
            <string>XM申请的appid</string>
        </array>
    </dict>
</array>
```

假如appid为1234567,AppDelegate 与info.plist里面的写法如下

```objc
[MiApi registerApp:@"1234567"];
```

info.plist写法如下
```xml
<key>CFBundleURLTypes</key>
<array>
    <dict>
        <key>CFBundleURLName</key>
            <string>OpenMiHome</string>
            <key>CFBundleURLSchemes</key>
            <array>
            <string>XM1234567</string>
        </array>
    </dict>
</array>
```


语音设备授权调用方式
```objc
MiSendDeviceAuthReq *request = [[MiSendDeviceAuthReq alloc] init];
request.did = did ;
BOOL opt = [MiApi sendAuthReq:request viewController:self delegate:self];
if(opt == NO){
    NSLog(@"米家 app 没有安装");
    [self downloadApp];
}
```
可参考Demo 中的 MHDeviceAuthRequestViewController.m  或者 MHDeviceAuthAndBindRequestViewController.m 的sendDeviceAuthRequest方法， 绑定绑定账户并授权调用方式
```objc
MiSendAccountBindReq *request = [[MiSendAccountBindReq alloc] init];
request.did = did ;
request.sn = sn; //sn
request.token = token;//设备token;
request.model = model;//设备model
request.timeStamp = timeStamp;//时间戳
BOOL opt = [MiApi sendAuthReq:request viewController:self delegate:self];
if(opt == NO){
    NSLog(@"米家 app 没有安装");
    [self downloadApp];
}
```
代码里面的delegate 需要实现 MiApiDelegate。当授权完成后，米家调起对应的app。 需要实现
```objc。
 - (void)onResp:(MiBaseResp *)resp
```
方法
    
可参考Demo 中的 MHDeviceAuthRequestViewController.m 和 MHDeviceAuthAndBindRequestViewController.m 的onResp代码
 ，具体代码如下
```objc
- (void)handleResponseV1:(MiBaseResp *)resp{
    MiSendDeviceAuthResp* dResp = (MiSendDeviceAuthResp*)resp;
    
    if (resp.errCode != MiDeviceAuthRespCodeSuccess) {
        //resp.result
        NSMutableString* ms = [[NSMutableString alloc] initWithCapacity:100];
        [ms appendString:@"授权失败，请查看result字段:"];
        //resp.errStr;
        if(dResp.result != nil){
            
            id obj = [NSJSONSerialization JSONObjectWithData:[dResp.result dataUsingEncoding:NSUTF8StringEncoding] options:NSJSONReadingAllowFragments error:nil];
            if([obj isKindOfClass:[NSArray class]]){
                NSArray* array = (NSArray*)obj;
                //每个设备成功失败都有一个单独的错误码。遍历数组查看
                for(id o in array){
                    if([o isKindOfClass:[NSDictionary class]]){
                        NSDictionary* d = (NSDictionary*)o;
                        NSNumber* n = [d objectForKey:@"code"];
                        if(n){
                            switch(n.integerValue){
                                case MiDeviceAuthRespCodeNotOwner:{
                                    [ms appendString:@"当前用户不是设备所有者"];
                                    break;
                                }
                                    
                                case MiDeviceAuthRespCodeServiceException:{
                                    [ms appendString:@"服务异常，如存储服务访问异常"];
                                    break;
                                }
                                case MiDeviceAuthRespCodeNotVoiceDevice:{
                                    [ms appendString:@"语音设备不存在"];
                                    break;
                                }
                                case MiDeviceAuthRespCodeNotSupportVoiceCtl:{
                                    [ms appendString:@"该设备不支持语音控制"];
                                    
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        self.hintLabel.text = ms;
    } else {
        self.hintLabel.text = @"授权成功";
    }
}

- (void)handleResponseV2:(MiBaseResp *)resp{
    if(resp.respCode == kMijiaAuthBindSuccess){
        self.hintLabel.text = @"授权成功";
    }else{
        self.hintLabel.text = [MiApi respCodeString:resp.respCode];
    }
}

- (void)onResp:(MiBaseResp *)resp{
    if (resp.errCode != MiDeviceAuthRespCodeSuccess) {
    /*
         得到具体的错误码，这里分sdk的版本，如果是2.0版本以后，可以查看resp对象的respCode
         的字段，这个字段的类型是MijiaAuthCode。
         如果是2.0之前的版本，还是通过resp的errCode的属性来判断，errCode的类型为MiDeviceAuthRespCode。
         errCode 与respCode 的区别在于respCode的信息更详细。它包括了errCode里面的所有错误类型。
         而且值的代表的意思是跟android一样的。
         errCode是最早的定义的，错误类型有限，如果只是简单的判断授权是否成功，可以使用errCode来判断，但是如果想給用户更详细的信息，请使用respCode的。
    */
        if(resp.sdkVersion < 2.0){
            [self handleResponseV1:resp];
        }else{
            [self handleResponseV2:resp];
        }
    } else {
        self.hintLabel.text = @"授权成功";
        
    }
    [self getDeviceList];
}
```


3、Demo 代码说明

设备授权
具体代码在 MHDeviceAuthRequestViewController.m 文件中 。sdk的framework为MiNetworkFramework.framework

如果是要给某个设备访问其他设备的权限，运行Demo后请选择“设备授权”

绑定账户并授权
具体代码在 MHDeviceAuthAndBindRequestViewController.m 里面。
这时要注意的是，如果使用2.0的以后的SDK。respCode的值的区别。
如果respCode 为 kMijiaAuthSuccess，就是说绑定和授权都成功了。
如果respCode 为kMijiaAuthBindSuccess，就是说绑定成功，但是授权没有成功，（授权没有成功可能是用户点击返回按钮，或者服务器在授权的时候错误）


