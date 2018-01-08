//
//  MHDeviceAuthRequestViewController.m
//  OpenMiHome
//
//  Created by huchundong on 2017/5/15.
//  Copyright © 2017年 CoolKernel. All rights reserved.
//

#import "MHDeviceAuthRequestViewController.h"
#import "MiNetworkFramework/MiApi.h"
#import "MiNetworkFramework/MHAuthDeviceManager.h"
#import "MiNetworkFramework/MHDevices.h"
#import <StoreKit/StoreKit.h>

@interface MHDeviceAuthRequestViewController ()<MiApiDelegate>
@property (nonatomic, strong) UILabel *hintLabel;
@end

@implementation MHDeviceAuthRequestViewController{
    UITextField*    _didField;
}

- (void)viewDidLoad {
    [super viewDidLoad];

    self.view.backgroundColor = [UIColor whiteColor];
    UIView *v = [[UIView alloc] initWithFrame:CGRectMake(0, 88,CGRectGetWidth(self.view.frame), 88)];
    UIButton *button = [UIButton buttonWithType:UIButtonTypeSystem];
    [button setTitle:@"点击授权" forState:UIControlStateNormal];
    [button setFrame:CGRectMake(0, 0, CGRectGetWidth(self.view.frame), 44)];
    [button addTarget:self action:@selector(sendDeviceAuthRequest) forControlEvents:UIControlEventTouchUpInside];
    [v addSubview:button];
    
    _didField = [[UITextField alloc] initWithFrame:CGRectMake(0, CGRectGetMaxY(button.frame), CGRectGetWidth(v.frame), 44)];
    _didField.placeholder = @"输入设备did";
    [v addSubview:_didField];
    
    UILabel *hintV = [[UILabel alloc] initWithFrame:CGRectMake(0, 30, CGRectGetMaxX(self.view.frame), 10)];
    hintV.textAlignment = NSTextAlignmentCenter;
    hintV.font = [UIFont systemFontOfSize:10];
    hintV.textColor = [UIColor redColor];
    [v addSubview:hintV];
    self.hintLabel = hintV;
    [self.view addSubview:v];
    
    self.title = @"设备授权";
}

- (void)onReq:(MiBaseReq *)req
{
    
}
- (void)handleResponseV1:(MiBaseResp *)resp{
    MiSendDeviceAuthResp* dResp = (MiSendDeviceAuthResp*)resp;
    if (resp.errCode != MiDeviceAuthRespCodeSuccess) {
        NSMutableString* ms = [[NSMutableString alloc] initWithCapacity:100];
        [ms appendString:@"授权失败，请查看result字段:"];
        dResp.result = @"{\"hello\":\"hellozzzz\"}";
        if(dResp.result != nil){
            ;
        
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
- (NSString*)getResponseCodeString:(MijiaAuthCode)authCode{
    NSString* msg = @"";
    switch (authCode) {
        case kMijiaAuthAuthError:{
            msg = @"授权问题。";
            break;
        }
        case kMijiaAuthAuthCancel:{
            msg = @"用户点击取消按钮";
            break;
        }
        case kMijiaAuthAppSignError:{
            msg = @"";
            break;
        }
            
        default:{
            msg = @"";
        }
            break;
    }
    return msg;
}
- (void)handleResponseV2:(MiBaseResp *)resp{
    if(resp.respCode != kMijiaAuthSuccess){
        self.hintLabel.text = [MiApi respCodeString:resp.respCode];//[self getResponseCodeString:resp.respCode];
    }else{
        self.hintLabel.text = @"授权成功";
    }
}
- (void)onResp:(MiBaseResp *)resp
{
//    MiSendDeviceAuthResp* dResp = (MiSendDeviceAuthResp*)resp;
    
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

}


- (void)sendDeviceAuthRequest{
    self.hintLabel.text = @"";
    
    MiSendDeviceAuthReq *request = [[MiSendDeviceAuthReq alloc] init];
    NSString* did = _didField.text ;
    if(did == nil || [did isEqualToString:@""]){
        self.hintLabel.text = @"did 为空";
        return;
    }
    request.userId = @"1080231669";
    request.did = did ;//@"58067462";
    request.ignoreUserId = YES;
    BOOL opt = [MiApi sendAuthReq:request viewController:self delegate:self];
    if(opt == NO){
        NSLog(@"米家 app 没有安装");
        [self downloadApp];
    }
}
- (void)downloadApp{
    SKStoreProductViewController *storeViewController =
    [[SKStoreProductViewController alloc] init];
    storeViewController.delegate = self;
    NSDictionary *parameters =
    @{SKStoreProductParameterITunesItemIdentifier:
          [NSNumber numberWithInteger:957323480]};
    [storeViewController loadProductWithParameters:parameters
                                   completionBlock:^(BOOL result, NSError *error) {
                                       if (result)
                                           [self presentViewController:storeViewController
                                                              animated:YES
                                                            completion:nil];
                                   }];
}
- (void)productViewControllerDidFinish:(SKStoreProductViewController *)viewController{
    
}
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
