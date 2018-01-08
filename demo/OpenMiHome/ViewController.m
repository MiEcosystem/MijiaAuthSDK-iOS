//
//  ViewController.m
//  OpenMiHome
//
//  Created by CoolKernel on 1/16/17.
//  Copyright © 2017 CoolKernel. All rights reserved.
//

#import "ViewController.h"
#import <MiNetworkFramework/MiApi.h>
#import <MiNetworkFramework/MHAuthDeviceManager.h>
#import <MiNetworkFramework/MHDevices.h>

@interface ViewController ()<MiApiDelegate>
@property (weak, nonatomic) IBOutlet UILabel *resultLabel;
@property (nonatomic, strong) MHAuthDeviceManager *manager;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.manager = [[MHAuthDeviceManager alloc] init];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
- (IBAction)openMiHome:(id)sender {
    [self clearDashboard];
    MiSendAuthReq *request = [[MiSendAuthReq alloc] init];
    [MiApi sendAuthReq:request viewController:self delegate:self];
}

- (void)onReq:(MiBaseReq *)req
{
    
}

- (void)onResp:(MiBaseResp *)resp
{
//    if ([MHKeychainManager getAccesstoken]) {
//        self.resultLabel.text = [NSString stringWithFormat:@"授权成功\naccessToken:%@", [MHKeychainManager getAccesstoken]];
//    }
}

- (IBAction)getDeviceList:(id)sender {
    [self clearDashboard];
    __weak typeof(self) weakself = self;
    [self.manager fetchAuthDeviceListWithFilters:@[] DeviceListBlock:^(MHDevices *deviceList) {
        NSMutableString *deviceInfo = [@"" mutableCopy];
        if (deviceList) {
            [deviceList.devices enumerateObjectsUsingBlock:^(MHDevice * _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
                [deviceInfo appendFormat:@"DeviceName:%@, deviceId:%@, pdid:%ld\n", obj.name, obj.did, (long)obj.pid];
            }];
        }
        weakself.resultLabel.text = [NSString stringWithFormat:@"获取设备列表:\n %@", deviceInfo];
    } failure:^(NSError *error) {
        weakself.resultLabel.text = [NSString stringWithFormat:@"获取设备列表失败:%@", error];
    }];
}
- (IBAction)sendRPC:(id)sender {
    [self clearDashboard];
//    __weak typeof(self) weakself = self;
    self.resultLabel.text = @"设备RPC未实现";
}

- (void)clearDashboard
{
    self.resultLabel.text = @"";
}

@end
