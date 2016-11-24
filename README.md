# iOS--DownLoad
iOS 下载学习Demo
主要是网络编程的方法
区别是通过代理的方法可以实现比较好的人机交互(Ps：第三方好看的API)
```
//方式一
    //NSString *path = @"http://192.168.0.215/jereh2.zip";
       NSString * path=@"http://192.168.0.215/jereh.jpg";
    NSURL *url = [NSURL URLWithString:path];
    NSURLSession *session = [NSURLSession sharedSession];
    NSURLSessionTask *task = [session dataTaskWithURL:url completionHandler:^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error) {
        //将下载后的数据存入文件(firstObject 无数据返回nil，不会导致程序崩溃)
        NSString *destPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject];
        //destPath = [destPath stringByAppendingPathComponent:@"my.zip"];
        destPath = [destPath stringByAppendingPathComponent:@"jereh.jpg"];
        NSLog(@"%@",destPath);
        
        //将下载的二进制文件转成入文件
        NSFileManager *manager = [NSFileManager defaultManager];
        BOOL isDownLoad =  [manager createFileAtPath:destPath contents:data attributes:nil];
        if (isDownLoad) {
            NSLog(@"OK");
        }else{
            NSLog(@"Sorry");
        }
    }];
    
    [task resume];
    ```
    通过代理方式（推荐）
    ```
     //方式二  通过NSURLSessionDelegate 来实现下载，并且通过UIProgressView 来监测进度
    NSURL *url = [NSURL URLWithString:@"http://192.168.0.215/jereh2.zip"];
    //创建管理类NSURLSessionConfiguration
    NSURLSessionConfiguration *config =[NSURLSessionConfiguration defaultSessionConfiguration];
    //初始化session并制定代理
    NSURLSession *session = [NSURLSession sessionWithConfiguration:config delegate:self delegateQueue:[NSOperationQueue mainQueue]];
    NSURLSessionDataTask *task = [session dataTaskWithURL:url];
    [task resume];
    ```
    注意
    `@interface ViewController ()<NSURLSessionDelegate>`
    代理方法的使用如下
    ```
    #pragma mark - 代理方法
#pragma mark *下载完成调用
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task
didCompleteWithError:(nullable NSError *)error{
    NSLog(@"%@",[NSThread currentThread]);
    //将下载后的数据存入文件(firstObject 无数据返回nil，不会导致程序崩溃)
    NSString *destPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject];
    //destPath = [destPath stringByAppendingPathComponent:@"my.zip"];
    destPath = [destPath stringByAppendingPathComponent:@"jereh.zip"];
    NSLog(@"%@",destPath);
    //将下载的二进制文件转成入文件
    NSFileManager *manager = [NSFileManager defaultManager];
    BOOL isDownLoad =  [manager createFileAtPath:destPath contents:self.data attributes:nil];
    if (isDownLoad) {
        NSLog(@"OK");
    }else{
        NSLog(@"Sorry");
    }
    NSLog(@"下载完成");
}

#pragma mark *接收到数据调用
- (void)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask
didReceiveResponse:(NSURLResponse *)response
 completionHandler:(void (^)(NSURLSessionResponseDisposition disposition))completionHandler{
    //允许继续响应
    completionHandler(NSURLSessionResponseAllow);
    //获取文件的总大小
    self.totalLength = response.expectedContentLength;
}

#pragma mark * 接收到数据调用
- (void)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask
    didReceiveData:(NSData *)data{
    NSLog(@"%li",data.length);
    //将每次接受到的数据拼接起来
    [self.data appendData:data];
    //计算当前下载的长度
    NSInteger nowlength= self.data.length;
    CGFloat value = nowlength*1.0/self.totalLength;
    //打印一下线程
    //NSLog(@"%@",[NSThread currentThread]);
    //self.downProgress.progress = value; //系统自带的ProgressView
    self.HV.percent = value; //第三方的ProgressView  展示
}
    ```
    
