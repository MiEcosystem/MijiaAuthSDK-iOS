//
//  MHAuthListViewController.m
//  OpenMiHome
//
//  Created by huchundong on 2017/5/12.
//  Copyright © 2017年 CoolKernel. All rights reserved.
//

#import "MHAuthListViewController.h"

@implementation MHAuthListViewController{
    NSMutableArray<NSDictionary*>*     _datas;
    UITableView*        _tableView;
}
- (void)viewDidLoad{
    [super viewDidLoad];
    [self initDatas];
    [self buildTableView];
    self.title = @"授权demo";
}
- (void)buildTableView{
    _tableView = [[UITableView alloc] initWithFrame:CGRectMake(0, 0, CGRectGetWidth(self.view.frame), CGRectGetHeight(self.view.frame)) style:UITableViewStylePlain];
    _tableView.dataSource = self;
    _tableView.delegate = self;
    [self.view addSubview:_tableView];
}
- (void)initDatas{
    _datas = [[NSMutableArray alloc] initWithCapacity:10];
    [_datas addObject:@{
                        @"title": @"设备授权",
                        @"ctl":@"MHDeviceAuthRequestViewController",
                        
                        }];
    
    [_datas addObject:@{
                        @"title":@"App授权",
                        @"ctl":@"MHDeviceListTableViewController",
                        }];
    
    [_datas addObject:@{
                        @"title":@"账户绑定并且授权设备（只能用于未绑定账户)",
                        @"ctl":@"MHDeviceAuthAndBindRequestViewController",
                        }];
}
#pragma mark - datasource
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return [_datas count];
}
- (UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    NSString* idt = @"kAuthCellIdt";
    UITableViewCell* cell = [tableView dequeueReusableCellWithIdentifier:idt];
    
    if(cell == nil){
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:idt];
        
    }
    NSDictionary* dict = _datas[indexPath.row];
    cell.textLabel.text = dict[@"title"] ;
    
    return cell;
}
#pragma mark - delegate
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    NSDictionary* dict = _datas[indexPath.row];
    Class cls = NSClassFromString(dict[@"ctl"]);
    UIViewController* ctl = [cls new];
    [self.navigationController pushViewController:ctl animated: YES];
}
@end
