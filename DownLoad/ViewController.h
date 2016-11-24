//
//  ViewController.h
//  DownLoad
//
//  Created by MasterChen on 16/11/24.
//  Copyright © 2016年 MasterChen. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController
@property (weak, nonatomic) IBOutlet UIButton *downBtn;
/**通过连线声明的进度条 */
@property (weak, nonatomic) IBOutlet UIProgressView *downProgress;

@end

