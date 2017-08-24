//
//  MHDeviceListTableViewController.m
//  OpenMiHome
//
//  Created by CoolKernel on 28/02/2017.
//  Copyright © 2017 CoolKernel. All rights reserved.
//

#import "MHDeviceListTableViewController.h"
#import "MiNetworkFramework/MiApi.h"
#import "MiNetworkFramework/MHAuthDeviceManager.h"
#import "MiNetworkFramework/MHDevices.h"



@interface MHDeviceListTableViewController ()<MiApiDelegate>
@property (nonatomic, strong) MHAuthDeviceManager *manager;
@property (nonatomic, strong) NSArray<MHDevice*> *deviceList;
@property (nonatomic, strong) UILabel *hintLabel;

@end

@implementation MHDeviceListTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.manager = [[MHAuthDeviceManager alloc] init];
    
    UIView *v = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 100, 44)];
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeSystem];
    [button setTitle:@"点击授权" forState:UIControlStateNormal];
    [button setFrame:CGRectMake(0, 0, 100, 34)];
    [button addTarget:self action:@selector(openMiHomeAction) forControlEvents:UIControlEventTouchUpInside];
    [v addSubview:button];
    
    UILabel *hintV = [[UILabel alloc] initWithFrame:CGRectMake(0, 30, 100, 10)];
    hintV.textAlignment = NSTextAlignmentCenter;
    hintV.font = [UIFont systemFontOfSize:10];
    hintV.textColor = [UIColor redColor];
    [v addSubview:hintV];
    self.hintLabel = hintV;
    
    self.navigationItem.titleView = v;
    
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Retry" style:UIBarButtonItemStylePlain target:self action:@selector(getDeviceList)];
    
    self.deviceList = @[];
    
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:@"reuseIdentifier"];
}

- (void)onReq:(MiBaseReq *)req
{
    
}

- (void)onResp:(MiBaseResp *)resp
{
    if (resp.errStr) {
        self.hintLabel.text = resp.errStr;
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

- (void)openMiHomeAction
{
    self.deviceList = @[];
    self.hintLabel.text = @"";
    [self.tableView reloadData];
    
    MiSendAuthReq *request = [[MiSendAuthReq alloc] init];
    [MiApi sendAuthReq:request viewController:self delegate:self];
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
 // Override to support conditional editing of the table view.
 - (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
 // Return NO if you do not want the specified item to be editable.
 return YES;
 }
 */

/*
 // Override to support editing the table view.
 - (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
 if (editingStyle == UITableViewCellEditingStyleDelete) {
 // Delete the row from the data source
 [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
 } else if (editingStyle == UITableViewCellEditingStyleInsert) {
 // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
 }
 }
 */

/*
 // Override to support rearranging the table view.
 - (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath {
 }
 */

/*
 // Override to support conditional rearranging of the table view.
 - (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
 // Return NO if you do not want the item to be re-orderable.
 return YES;
 }
 */

/*
 #pragma mark - Navigation
 
 // In a storyboard-based application, you will often want to do a little preparation before navigation
 - (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
 // Get the new view controller using [segue destinationViewController].
 // Pass the selected object to the new view controller.
 }
 */

@end
