                                                           
## AIO5对等电路dp点信息

- 房间温控器及风盘控制器

|DP地址 |DP名称                   |R/W| 长度 |详情                                        |     占用链路      |    备注                      |
|-------|-------------------------|---|------|--------------------------------------------|-------------------|------------------------------|
|       |                         |   |      |十六进制:  0x00 关机  0x01开机              |                   |末端<--->输配                 |  
|0x0000 | 开关机                  |R/W| 1byte|步进    :  1                                |7  +  1	= 8byte	  |风盘<--->显示                 | 
|       |                         |   |      |范围    :  0x00 - 0x01                      |                   |                              | 
|       |                         |   |      |十六进制:  0x00dc 代表22.0度                |                   |末端<--->输配                 |  
|0x0001 | 制冷设定温度            |R/W| 2byte|步进    :  0.5度                            |7  +  2	= 9byte	  |风盘<--->显示                 | 
|       |                         |   |      |范围    :  设定温度上下限控制               |                   |                              |
|       |                         |   |      |十六进制:  0x00dc 代表22.0度                |                   |末端<--->输配                 |  
|0x0002 | 制热设定温度            |R/W| 2byte|步进    :  0.5度                            |7  +  2	= 9byte	  |风盘<--->显示                 | 
|       |                         |   |      |范围    :  设定温度上下限控制               |                   |                              |
|       |                         |   |      |十六进制:  0x00 解锁  0x01加锁              |                   |末端<--->输配                 |  
|0x0003 | 童锁                    |R/W| 1byte|步进    :  1                                |7  +  1	= 8byte	  |风盘<--->显示                 | 
|       |                         |   |      |范围    :  0x00 - 0x01                      |                   |                              |
|       |                         |   |      |十六进制:  0x00 AI  0x01低风                |                   |末端<--->输配                 | 
|       |                         |   |      |           0x02 中风  0x03高风              |                   |风盘<--->显示                 |  
|0x0004 | 设定风速                |R/W| 1byte|步进    :  1                                |7  +  1	= 8byte	  |                              |
|       |                         |   |      |范围    :  0x00 - 0x04                      |                   |                              |
|       |                         |   |      |十六进制:  0x00 单辐射  0x01单风盘  0x02 AI |                   |末端<--->输配                 |  
|0x0005 | 双末端运行模式          |R/W| 1byte|步进    :  1                                |7  +  1	= 8byte	  |风盘<--->显示                 | 
|       |                         |   |      |范围    :  0x00 - 0x02                      |                   |                              | 


- 组合DP   

|DP地址 |DP名称          |   组合     | 长度 |详情                                        |     占用链路      |          备注                |
|-------|----------------|----------- |------|--------------------------------------------|-------------------|------------------------------|
|       |                |            |      |十六进制:  0x0003 第1和第2被绑定            |                   |      末端---->输配           |  
|       |                |辐射列表    | 2byte|步进    :  按bit处理                        |	                  |                              | 
|       |                |            |      |范围    :  0x0000 - 0x0FFF                  |                   |      风盘<--->显示           | 
|0x0006 | 末端绑定信息   |            |      |十六进制:  0x0003 第1和第2被绑定            |  7 + 2 + 2= 11byte|                              |  
|       |                | 辐射列表   | 2byte|步进    :  按bit处理                        |                   |                              | 
|       |                |            |      |范围    :  0x0000 - 0x0FFF                  |                   |                              | 
|       |                |            |      |十六进制:  0x0003 第1和第2路输出            | 	              |                              |
|       |                |辐射需求    | 2byte|步进    :  按bit处理                        |  7 +  2 =  9      |                              |
|       |                |            |      |范围    :  0x0000 - 0x0FFF                  | 	              |      末端---->输配           |  
|       |                |            |      |十六进制:  0x00C0 第7和第8路输出            | 	              |      风盘 --->显示           | 
|       |                |风盘需求    | 2byte|步进    :  按bit处理                        |  9 +  2 = 11      |                              |
|       |                |            |      |范围    :  0x0000 - 0x0FC0                  | 	              |                              | 
|       |                |            |      |十六进制:  0x00 无  0x01保护运行            | 	              |                              | 
|       |                |露点状态    | 1byte|步进    :  1                                | 11 +  1 = 12      | 20210525后无效               |
|       |                |            |      |范围    :  0x00 - 0x01                      | 	              |                              |
|       |                |            |      |十六进制:  0x00 无风  0x01低风              | 	              |                              |
|       |                |            |      |十六进制:  0x02 中风  0x03高风              | 	              |                              |
|       |                |风机状态    | 1byte|步进    :  1                                | 12 +  1 = 13      |                              |
|0x0007 |末端信息        |            |      |范围    :  0x00 - 0x03                      | 	              |                              |     
|       |                |            |      |十六进制:  0x00 未知  0x01制冷              | 	              |                              |
|       |                |            |      |十六进制:  0x02 制热  0x03待机              | 	              |                              |
|       |                |冷暖模式    | 1byte|步进    :  1                                | 13 +  1 = 14      |                              |
|       |                |            |      |范围    :  0x00 - 0x03                      | 	              |                              |
|       |                |            |      |十六进制:  0x01 EC风机PWM值                 | 	              |                              |
|       |                |EC风机      | 1byte|步进    :  1                                | 14 +  1 = 15      |                              |
|       |                |            |      |范围    :  0x00 - 0x64                      | 	              |                              |
|       |                |            |      |十六进制:  bit0  传感器错误                 | 	              |                              |
|       |                |            |      |           bit1  无输配信息                 | 	              |                              |
|       |                |            |      |           bit2  EC风机错误                 | 	              |                              |
|       |                |设备故障字  | 2byte|步进    :  1                                | 15 +  2 = 17      |                              |
|       |                |            |      |范围    :  0x00 - 0x64                      | 	              |                              |
|       |                |            |      |十六进制:  0x00DC 代表220  22.0度           | 	              |                              |
|       |                |测量温度    | 2byte|步进    :  0.1度                            |  7 +  2 =  9      |                              |
|       |                |            |      |范围    :  -9.9度 - 99.9度                  | 	              |      末端---->输配           | 
|       |                |            |      |十六进制:  0x00DC 代表220  22.0度           | 	              |      风盘<--- 显示           | 
|0x0008 |末端测量信息    |露点测量温度| 2byte|步进    :  0.1度                            |  9 +  2 = 11      |                              |
|       |                |            |      |范围    :  0.0度 - 99.9度                   | 	              |                              | 
|       |                |            |      |十六进制:  0x32   相对湿度50%               | 	              |                              | 
|       |                |测量湿度    | 1byte|步进    :  1                                | 11 +  1 = 12      |                              |
|       |                |            |      |范围    :  0x00 - 0x01                      | 	              |                              |
|       |                |            |      |十六进制:  0x00 关闭  0x01开启              | 	              |                              |
|       |                |防冻保护    | 1byte|步进    :  1                                |  7 +  1 =  8      |                              |
|       |                |            |      |范围    :  0x00 - 0x01                      | 	              |      末端<---->输配          | 
|       |                |            |      |十六进制:  0x0032 代表5.0度                 | 	              |      风盘<---->显示          | 
|       |                |防冻温度    | 2byte|步进    :  按bit处理                        |  8 +  2 = 10      |                              |
|       |                |            |      |范围    :  0x0032 - 0x0064                  | 	              |防冻保护关闭:防冻温度5.0度    | 
|       |                |            |      |十六进制:  0x00 恢复  0x01关机              | 	              |                              | 
|       |                |上电关机    | 1byte|步进    :  1                                | 10 +  1 = 11      |                              |
|       |                |            |      |范围    :  0x00 - 0x01                      | 	              |                              |
|       |                |            |      |十六进制:  0x015E 代表350  35.0度           | 	              |                              |
|       |                |设定最大值  | 2byte|步进    :  0.5度                            | 11 +  2 = 13      |                              |
|       |                |            |      |范围    :  0x00FA - 0x015E                  | 	              |                              |
|       |                |            |      |十六进制:  0x0064 代表100  10.0度           | 	              |                              |
|       |                |设定最小值  | 2byte|步进    :  0.5度                            | 13 +  2 = 15      |                              |
|       |                |            |      |范围    :  0x0032 - 0x0096                  | 	              |                              |
|       |                |            |      |十六进制:  0x0104 代表260  26.0度           | 	              |                              |
|       |                |制冷舒适设定| 2byte|步进    :  0.5度                            | 15 +  2 = 17      |                              |
|       |                |            |      |范围    :  最小值 - 最大值                  | 	              |                              |
|0x0009 |高级信息        |            |      |十六进制:  0x00C8 代表200  20.0度           | 	              |                              |
|       |                |制热舒适设定| 2byte|步进    :  0.5度                            | 17 +  2 = 19      |                              |
|       |                |            |      |范围    :  最小值 - 最大值                  | 	              |                              |
|       |                |            |      |十六进制:  0x0064 代表100  10.0度           | 	              |                              |
|       |                |控温带宽    | 2byte|步进    :  0.5度                            | 19 +  2 = 21      |                              |
|       |                |            |      |范围    :  0x0005 - 0x0064                  | 	              |                              |
|       |                |            |      |十六进制:  0x0064 代表100  10.0度           | 	              |                              |
|       |                |露点带宽    | 2byte|步进    :  0.5度                            | 21 +  2 = 23      |                              |
|       |                |            |      |范围    :  0x0014 - 0x0064                  | 	              |                              |
|       |                |            |      |十六进制:  0x00 关闭  0x01开启              | 	              |                              |
|       |                |制冷协同使能| 1byte|步进    :  1                                | 23 +  1 = 24      |                              |
|       |                |            |      |范围    :  0x00 - 0x01                      | 	              |                              | 
|       |                |            |      |十六进制:  0x0064 代表100  10.0度           | 	              |                              |
|       |                |制冷协同带宽| 2byte|步进    :  0.5度                            | 24 +  2 = 26      |                              |
|       |                |            |      |范围    :  0x0014 - 0x0064                  | 	              |                              |
|       |                |            |      |十六进制:  0x00 关闭  0x01开启              | 	              |                              |
|       |                |制热协同使能| 1byte|步进    :  1                                | 26 +  1 = 27      |                              |
|       |                |            |      |范围    :  0x00 - 0x01                      | 	              |                              | 
|       |                |            |      |十六进制:  0x0064 代表100  10.0度           | 	              |                              |
|       |                |制热协同带宽| 2byte|步进    :  0.5度                            | 27 +  2 = 29      |                              |
|       |                |            |      |范围    :  0x0014 - 0x0064                  | 	              |                              |
|       |                |            |      |十六进制:  0x00 非受控  0x01受控            | 	              |                              |
|       |                |风机受控    | 1byte|步进    :  1                                | 29 +  1 = 30      |                              |
|       |                |            |      |范围    :  0x00 - 0x01                      | 	              |                              | 
|       |                |            |      |十六进制:  0x1E 代表30 低风30%输出          |     	          |                              |
|       |                |低风pwm     | 1byte|步进    :  1                                | 30 +  1 = 31      |                              |
|       |                |            |      |范围    :  0x00 - 0x64                      | 	              |                              | 
|       |                |            |      |十六进制:  0x3C 代表60 中风60%输出          |     	          |                              |
|       |                |中风pwm     | 1byte|步进    :  1                                | 31 +  1 = 32      |                              |
|       |                |            |      |范围    :  0x00 - 0x64                      | 	              |                              | 
|       |                |            |      |十六进制:  0x5A 代表90 高风90%输出          |     	          |                              |
|       |                |高风pwm     | 1byte|步进    :  1                                | 32 +  1 = 33      |                              |
|       |                |            |      |范围    :  0x00 - 0x64                      | 	              |                              | 
|       |                |            |      |十六进制:  0x00 关闭  0x01开启              | 	              |                              |
|       |                |双末端使能  | 1byte|步进    :  1                                | 33 +  1 = 34      |                              |
|       |                |            |      |范围    :  0x00 - 0x01                      | 	              |                              | 
|       |                |            |      |十六进制:  0x0064 代表100  10.0度           | 	              |                              |
|       |                |校温        | 2byte|步进    :  0.1度                            | 34 +  2 = 36      |                              |
|       |                |            |      |范围    :  0xFF9D - 0xFFFF                  | 	              |                              |
|       |                |            |      |范围    :  0x0000 - 0x0064                  | 	              |                              |
|       |                |            |      |十六进制:  0x64 代表10                      |     	          |                              |
|       |                |校湿        | 1byte|步进    :  1                                | 36 +  1 = 37      |                              |
|       |                |            |      |范围    :  0xF7 - 0xFF                      | 	              |                              | 
|       |                |            |      |范围    :  0x00 - 0x0A                      | 	              |                              |
|       |                |            |      |十六进制:  0x00 地辐射                      |     	          |                              |
|       |                |            |      |十六进制:  0x01 墙辐射                      |     	          |                              |
|       |                |            |      |十六进制:  0x02 顶辐射                      |     	          |                              |
|       |                |            |      |十六进制:  0x03 地辐射 + 墙辐射             |     	          |                              |
|       |                | 辐射类型   | 1byte|十六进制:  0x04 地辐射 + 顶辐射             |     	          |                              |
|       |                |            |      |十六进制:  0x05 墙辐射 + 顶辐射             |     	          |                              |
|       |                |            |      |十六进制:  0x06 地辐射 + 墙辐射 + 顶辐射    |     	          |                              |
|       |                |            |      |步进    :  1                                | 37 +  1 = 38      |                              |
|       |                |            |      |范围    :  0x00 - 0x06                      | 	              |                              | 
|       |                |            |      |十六进制:  0x00 25平方米                    |     	          |                              |
|       |                |            |      |十六进制:  0x01 35平方米                    |     	          |                              |
|       |                |  房间面积  | 1byte|十六进制:  0x02 45平方米                    |     	          |                              |
|       |                |            |      |步进    :  1                                | 38 +  1 = 39      |                              |
|       |                |            |      |范围    :  0x00 - 0x02                      | 	              |                              | 
|       |                |            |      |十六进制:  0x0003 代表第1和第2路未绑定      | 	              |                              |
|       |                |辐射未绑定  | 2byte|步进    :  bit                              |  7 +  2 =  9      |                              |
|       |                |            |      |范围    :  BIT0 --- BIT11                   | 	              |      末端<-----输配          | 
|       |                |            |      |十六进制:  0x0003 代表第1和第2路未绑定      | 	              |      风盘----->显示          | 
|       |                |风盘未绑定  | 2byte|步进    :  按bit处理                        |  9 +  2 = 11      |                              |
|       |                |            |      |范围    :  BIT7 --- BIT11                   | 	              |                              | 
|       |                |            |      |十六进制:  0x00 关机  0x01开机              | 	              |                              | 
|       |                |系统开关机  | 1byte|步进    :  bit                              | 11 +  1 = 12      |                              |
|       |                |            |      |范围    :  0x00 - 0x01                      | 	              |                              |
|       |                |            |      |十六进制:  0x00 保留                        |     	          |                              |
|       |                |            |      |十六进制:  0x01 制冷                        |     	          |                              |
|       |                |            |      |十六进制:  0x02 制热                        |     	          |                              |
|       |                |            |      |十六进制:  0x03 除湿                        |     	          |                              |
|       |                |系统运行模式| 1byte|十六进制:  0x04 新风                        |     	          |                              |
|       |                |            |      |十六进制:  0x05 夏季自动                    |     	          |                              |
|       |                |            |      |十六进制:  0x06 冬季自动                    |     	          |                              |
|       |                |            |      |步进    :  1                                | 12 +  1 = 13      |                              |
|0x000A |系统信息        |            |      |范围    :  0x00 - 0x06                      | 	              |                              | 
|       |                |            |      |十六进制:  0x0000 无                        |                   |                              |
|       |                |            |      |十六进制:  0x0001 混水传感器故障            |                   |                              |
|       |                |            |      |十六进制:  0x0002 回水传感器故障            |                   |                              |
|       |                |            |      |十六进制:  0x0004 三通阀故障                |                   |                              |
|       |                |            |      |十六进制:  0x0008 空调外机                  |                   |                              |
|       |                |            |      |十六进制:  0x0010 进风风机故障              |                   |                              |
|       |                |            |      |十六进制:  0x0020 回风风机故障              |                   |                              |
|       |                |            |      |十六进制:  0x0040 户外进风传感器故障        |                   |                              |
|       |                |            |      |十六进制:  0x0080 氟盘前传感器故障          |                   |                              |
|       |                |            |      |十六进制:  0x0100 氟盘后传感器故障          |                   |                              |
|       |                |            |      |十六进制:  0x0200 回风传感器故障            |                   |                              |
|       |                |            |      |十六进制:  0x0400 排风传感器故障            |                   |                              |
|       |                |系统故障    | 2byte|步进    :  bit                              | 13 +  2 = 15      |                              |
|       |                |            |      |范围    :  bit0  - bit15                    | 	              |                              |
|       |                |            |      |十六进制:  0x0003 代表第1和第2路绑定故障    | 	              |                              | 
|       |                |绑定故障    | 2byte|步进    :  按bit处理                        | 15 +  2 = 17      |                              |
|       |                |            |      |范围    :  BIT0 --- BIT11                   | 	              |                              | 
|       |                |            |      |十六进制:  0x0032 代表5.0度                 | 	              |                              | 
|       |                |混水温度    | 2byte|步进    :  0.1度                            | 17 +  2 = 19      |                              |
|       |                |            |      |范围    :                                   | 	              |                              | 
|       |                |            |      |十六进制:  0x0003 代表第1和第2路露点状态    | 	              |                              | 
|       |                |绑定故障    | 2byte|步进    :  按bit处理                        | 19 +  2 = 21      |                              |
|       |                |            |      |范围    :  BIT0 --- BIT11                   | 	              |                              | 
|       |                |            |      |十六进制:  0x03 代表3秒                     | 	              |                              |
|       |                |RTC秒       | 1byte|步进    :  1                                |  7 +  1 =  8      |                              |
|       |                |            |      |范围    :  0x00 --- 0x3B                    | 	              |      末端<-----输配          | 
|       |                |            |      |十六进制:  0x03 代表3分                     | 	              |      风盘----->显示          |
|       |                |RTC分       | 1byte|步进    :  1                                |  8 +  1 =  9      |                              |
|       |                |            |      |范围    :  0x00 --- 0x3B                    | 	              |                              | 
|       |                |            |      |十六进制:  0x03 代表3时                     | 	              |                              |
|       |                |RTC时       | 1byte|步进    :  1                                |  9 +  1 =  10     |                              |
|       |                |            |      |范围    :  0x00 --- 0x17                    | 	              |                              | 
|       |                |            |      |十六进制:  0x00 代表星期天                  | 	              |                              |
|0x000B |系统RTC信息     |RTC星期     | 1byte|步进    :  1                                |  10 + 1 =  11     |                              |
|       |                |            |      |范围    :  0x00 --- 0x06                    | 	              |                              | 
|       |                |            |      |十六进制:  0x1F 代表31号                    | 	              |                              |
|       |                |RTC天       | 1byte|步进    :  1                                |  11 + 1 =  12     |                              |
|       |                |            |      |范围    :  0x01 --- 0x1F                    | 	              |                              | 
|       |                |            |      |十六进制:  0x0c  代表12月                   | 	              |                              |
|       |                |RTC月       | 1byte|步进    :  1                                |  12 +  1 =  13    |                              |
|       |                |            |      |范围    :  0x01 --- 0x0C                    | 	              |                              | 
|       |                |            |      |十六进制:  0x63  代表99年                   | 	              |                              |
|       |                |RTC年       | 1byte|步进    :  1                                |  13 +  1 =  14    |                              |
|       |                |            |      |范围    :  0x00 --- 0x63                    | 	              |                              | 
|       |                |            |      |十六进制:  0x00房间温控器 0x01键盘          | 	              |                              |
|       |                |模式        | 1byte|步进    :  1                                |  7 +  1 =  8      |                              |
|       |                |            |      |范围    :  0x00 --- 0x01                    | 	              |                              | 
|       |                |            |      |十六进制:  0x0101 代表第1个版本             | 	              |      风盘----->显示          | 
|0x000C |特殊DP          |风盘软件版本| 2byte|步进    :  1                                |  8 +  2 = 10      |                              |
|       |                |            |      |范围    :  BIT7 --- BIT11                   | 	              |                              | 
|       |                |            |      |十六进制:  0x00 常规  0x01直流              | 	              |  版本信息                    | 
|       |                |风盘信息    | 1byte|步进    :  bit                              | 10 +  1 = 11      |  0x0109下一个版本为0x0110    |
|       |                |            |      |范围    :  0x00 - 0x01                      | 	              |   全联供有两种类型风盘       |
|       |                |            |      |十六进制:  0x9522 房间温控器                | 	              |                              |
|       |                |            |      |十六进制:  0x9521 风盘控制器                | 	              |      末端----->输配          |
|       |                |            |      |十六进制:  0x8522 输配中心                  | 	              |                              |
|       |                |            |      |十六进制:  0x8521 环控中心                  | 	              |                              |
|0x000D |设备类型        |类型        | 2byte|步进    :  无                               |  7 +  2 =  9      |                              |
|       |                |            |      |范围    :  枚举                             | 	              |                              | 
|       |                |            |      |十六进制:  0x0003 代表第1和第2路绑定        | 	              |                              |
|       |                |地辐射列表  | 2byte|步进    :  bit                              |  7 +  2 =  9      |                              |
|       |                |            |      |范围    :  BIT0 --- BIT15                   | 	              |                              | 
|       |                |            |      |十六进制:  0x0101 代表第1个版本             | 	              |      风盘<---->显示          | 
|0x000E |辐射类型        |墙辐射列表  | 2byte|步进    :  bit                              |  9 +  2 = 11      |                              |
|       |                |            |      |范围    :  BIT0 --- BIT15                   | 	              |                              | 
|       |                |            |      |十六进制:  0x00 常规  0x01直流              | 	              |                              | 
|       |                |顶辐射列表  | 2byte|步进    :  bit                              | 11 +  2 = 13      |                              |
|       |                |            |      |范围    :  BIT0 --- BIT15                   | 	              |                              |
|       |                |            |      |十六进制:  0x01 代表地址为1                 | 	              |                              |
|       |                |地址        | 1byte|步进    :  bit                              |  7 +  1 =  8      |                              |
|       |                |            |      |范围    :  BIT0 --- BIT15                   | 	              |                              | 
|       |                |            |      |十六进制:  0x2580 代表9600                  | 	              |      风盘<---->显示          | 
|0x000F |rs485参数       |波特率      | 2byte|步进    :  特殊                             |  8 +  2 = 11      |                              |
|       |                |            |      |范围    :  2400 4800 9600                   | 	              |                              | 
|       |                |            |      |十六进制:  0x00 无                          | 	              |                              | 
|       |                |            |      |十六进制:  0x01 奇校验                      | 	              |                              | 
|       |                |            |      |十六进制:  0x02 偶校验                      | 	              |                              | 
|       |                |校验位      | 2byte|步进    :  bit                              | 11 +  1 = 12      |                              |
|       |                |            |      |范围    :  BIT0 --- BIT15                   | 	              |                              |
|       |                |            |      |十六进制:  0xFA3456AF                       | 	              |                              |
|       |                |安全字      | 4byte|步进    :  无                               |  7 +  4 =  11     |                              |
|       |                |            |      |范围    :  固定                             | 	              |                              | 
|       |                |            |      |十六进制:  0xF1 代表设备ID的第1位是F1(高)   | 	              |  上位设备----->全联供设备    | 
|       |                |ID_6        | 1byte|步进    :  无                               |  11 +  1 = 12     |                              |
|       |                |            |      |范围    :  无                               | 	              |                              | 
|       |                |            |      |十六进制:  0x21 代表设备ID的第2位是21       | 	              |                              | 
|       |                |ID_5        | 1byte|步进    :  无                               |  12 +  1 = 13     |                              |
|       |                |            |      |范围    :  无                               | 	              |                              |  
|       |                |            |      |十六进制:  0x05 代表设备ID的第3位是05       | 	              |                              | 
|       |                |ID_4        | 1byte|步进    :  无                               |  13 +  1 = 14     |                              |
|       |                |            |      |范围    :  无                               | 	              |                              | 
|       |                |            |      |十六进制:  0x11 代表设备ID的第4位是11       | 	              |                              | 
|0x1000 |ID_DP           |ID_3        | 1byte|步进    :  无                               |  14 +  1 = 15     |                              |
|       |                |            |      |范围    :  无                               | 	              |                              |  
|       |                |            |      |十六进制:  0x00 代表设备ID的第5位是00       | 	              |                              | 
|       |                |ID_2        | 1byte|步进    :  无                               |  15 +  1 = 16     |                              |
|       |                |            |      |范围    :  无                               | 	              |                              | 
|       |                |            |      |十六进制:  0x01 代表设备ID的第6位是01       | 	              |                              | 
|       |                |ID_1        | 1byte|步进    :  无                               |  16 +  1 = 17     |                              |
|       |                |            |      |范围    :  无                               | 	              |                              | 
| 55 AB |00 27 D0 21|  FF FF FF FF FF FF|   FA FA FA AF AF AF  | 01 01 00 01    |00 00 00 00 | 0C  10 00 FA 34 56 AF F2 21 05 10 00 5A 03 30 |
| 头    |长度  同步 |  待写入设备id     |   工具ID             | 写入1块需应答  |时间戳      |长度 地址  4bit秘钥        6bit——id   2bit校验 | 
- End


























