//
//  MHDeviceAuthRequestViewControllerTableViewController.m
//  OpenMiHome
//
//  Created by huchundong on 2017/6/26.
//  Copyright © 2017年 CoolKernel. All rights reserved.
//

#import "MHDeviceAuthAndBindRequestViewController.h"

#import <MiNetworkFramework/MiApi.h>
#import <MiNetworkFramework/MHAuthDeviceManager.h>
#import <MiNetworkFramework/MHDevices.h>

#import <StoreKit/StoreKit.h>

@interface MHDeviceAuthAndBindRequestViewController ()<MiApiDelegate>
@property (nonatomic, strong) MHAuthDeviceManager *manager;
@property (nonatomic, strong) NSArray<MHDevice*> *deviceList;
@property (nonatomic, strong) UILabel *hintLabel;

@end

@implementation MHDeviceAuthAndBindRequestViewController{
    UITextField*    _didField;
    UITextField*    _modelField;
    UITextField*    _timeStampField;
    UITextField*    _snField;
    UITextField*    _tokenField;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    self.manager = [[MHAuthDeviceManager alloc] init];
    
    UIView *v = [[UIView alloc] initWithFrame:CGRectMake(0, 0,CGRectGetWidth(self.view.frame), 280)];
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeSystem];
    [button setTitle:@"点击授权" forState:UIControlStateNormal];
    [button setFrame:CGRectMake(0, 0, CGRectGetWidth(self.view.frame), 44)];
    [button addTarget:self action:@selector(sendDeviceAuthRequest) forControlEvents:UIControlEventTouchUpInside];
    [v addSubview:button];
    
    _didField = [[UITextField alloc] initWithFrame:CGRectMake(0, CGRectGetMaxY(button.frame), CGRectGetWidth(v.frame), 44)];
    _didField.placeholder = @"输入设备did";
    [v addSubview:_didField];
    
    _modelField = [[UITextField alloc] initWithFrame:CGRectMake(0, CGRectGetMaxY(_didField.frame)+10, CGRectGetWidth(v.frame), 44)];
    _modelField.placeholder = @"输入设备Model";
    [v addSubview:_modelField];
    
    _timeStampField = [[UITextField alloc] initWithFrame:CGRectMake(0, CGRectGetMaxY(_modelField.frame)+10, CGRectGetWidth(v.frame), 44)];
    _timeStampField.placeholder = @"输入时间";
    [v addSubview:_timeStampField];
    
    _snField = [[UITextField alloc] initWithFrame:CGRectMake(0, CGRectGetMaxY(_timeStampField.frame)+10, CGRectGetWidth(v.frame), 44)];
    _snField.placeholder = @"输入设备sn";
    [v addSubview:_snField];
    
    _tokenField = [[UITextField alloc] initWithFrame:CGRectMake(0, CGRectGetMaxY(_snField.frame)+10, CGRectGetWidth(v.frame), 44)];
    _tokenField.placeholder = @"输入设备token";
    [v addSubview:_tokenField];
    
    UILabel *hintV = [[UILabel alloc] initWithFrame:CGRectMake(0, 30, 100, 10)];
    hintV.textAlignment = NSTextAlignmentCenter;
    hintV.font = [UIFont systemFontOfSize:10];
    hintV.textColor = [UIColor redColor];
    [v addSubview:hintV];
    self.hintLabel = hintV;
    
    
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Retry" style:UIBarButtonItemStylePlain target:self action:@selector(getDeviceList)];
    
    self.deviceList = @[];
    self.tableView.tableHeaderView = v;
    v.backgroundColor = [UIColor colorWithRed:0xf6/255.0 green:0xf6/255.0 blue:0xf6/255.0 alpha:1];
    
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:@"reuseIdentifier"];
    self.title = @"账户绑定并且授权设备";
}

- (void)onReq:(MiBaseReq *)req
{
    
}
- (void)handleResponseV1:(MiBaseResp *)resp{
    MiSendDeviceAuthResp* dResp = (MiSendDeviceAuthResp*)resp;
    
    if (resp.errCode != MiDeviceAuthRespCodeSuccess) {
        
        NSMutableString* ms = [[NSMutableString alloc] initWithCapacity:100];
        [ms appendString:@"授权失败，请查看result字段:"];
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
        self.hintLabel.text = @"绑定成功，但是语音设备授权失败";
    }else{
        self.hintLabel.text = [MiApi respCodeString:resp.respCode];
    }
}
- (void)onResp:(MiBaseResp *)resp
{
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

- (void)getDeviceList
{
    self.deviceList = @[];
    [self.tableView reloadData];
    
    __weak typeof(self) weakself = self;
    [self.manager fetchAuthDeviceListWithFilters:@[] DeviceListBlock:^(MHDevices *devs) {
        if (devs) {
            weakself.deviceList = devs.devices;
            [weakself.tableView reloadData];
        }
    } failure:^(NSError *error) {
        
    }];
}

- (void)sendDeviceAuthRequest{
    self.deviceList = @[];
    self.hintLabel.text = @"";
    [self.tableView reloadData];
    
    MiSendAccountBindReq *request = [[MiSendAccountBindReq alloc] init];
    NSString* did = _didField.text ;
    if(did == nil || [did isEqualToString:@""]){
        self.hintLabel.text = @"did 为空";
        return;
    }
    
    request.did = did ;//@"58067462";
    request.sn = _snField.text;
    request.token = _tokenField.text;
    request.model = _modelField.text;
    request.timeStamp = _timeStampField.text;// [NSString stringWithFormat:@"%lf",CFAbsoluteTimeGetCurrent()];
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

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return _deviceList.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"reuseIdentifier" forIndexPath:indexPath];
    MHDevice *dev = _deviceList[indexPath.row];
    cell.textLabel.numberOfLines = 2;
    cell.textLabel.text = [NSString stringWithFormat:@"%@\n did:%@, pid:%ld", dev.name, dev.did, dev.pid];
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    
}
/*
 #pragma mark - Navigation
 
 // In a storyboard-based application, you will often want to do a little preparation before navigation
 - (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
 // Get the new view controller using [segue destinationViewController].
 // Pass the selected object to the new view controller.
 }
 */

@end

