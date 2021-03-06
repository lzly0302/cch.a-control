//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//AIO5功能层次图
//date：2021.09.13_V1.0
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
输配中心
       |
       |--温度测量
	   |         |--一次侧进水温度
       |         |--一次侧回水温度
       |         |--二次侧回水温度
       |         `--二次侧混水温度
       |
       |--故障保护
       |         |--混水传感器故障
       |         |               |
       |         |               |--故障指示
       |         |               `--三通阀关闭
       |         |--二次侧回水传感器故障
       |         |              |
       |         |              `--故障指示
       |         |
       |         |--一次侧进水传感器故障
       |         |              |
       |         |              `--故障指示
	   |         |--一次侧回水传感器故障
       |         |              |
       |         |              `--故障指示
       |         |
       |         `--末端(房间温控器或者风盘控制器)离线
       |                   |
       |                   |--故障指示
       |                   `--执行器关闭
	   |  
	   |--系统保护  
	   |        |--混水制冷设定温度最低16度。
	   |        |--制冷模式下二次侧混水或者回水温度低于(最高露点温度-2度)且持续1分钟
	   |        |                                              `--外机制冷出水温度设为35度
       |	    `--二次侧混水或者回水温度高于(最高露点温度+1度)且持续1分钟
	   |                                                       `--外机制冷出水温度设为7度
	   | 
       |--空调外机参数设定范围
	   |                     |--制冷出水设定温度5-36度
	   |                     `--制热出水设定温度30-60度
	   |
	   |--水泵自动调节频率及流量反馈
	   |                         |--根据辐射能需数量自动调节水泵频率
	   |                         `--根据水泵反馈计算出当前流量
	   |
	   |-主控策略
	   |       `--根据不同工况设计对应的控制策略，具体策略不断累加。
	   |
	   |
	   |
	   |
       |-- 混水温度计算
       |          |
       |          |--制冷模式
       |          |         |--开机有辐射能需的末端
       |          |         |--获取末端最大露点温度
	   |          |         |--最大露点温度低于16度时，混水设定温度固定为16度。
       |          |         `--最大露点温度不低于16度时，调整混水设定温度为最大露点温度。   
       |          |
       |          `--制热模式
       |                    |--周期30分钟
       |                    `--根据末端的设定、测量温差值、末端的升温系数，计算供水温度，达到合理的热负荷匹配。
       |--运行逻辑
       |         |
       |         |--关机
       |         |     |
       |         |     |--防冻保护
       |         |     |         |
       |         |     |         |--回水温度 < 5 度
       |         |     |         |                |--防冻请求
       |         |     |         |                |--水泵运转
       |         |     |         |                |--三通阀开启，调整混水温度到制热的'设定温度'
       |         |     |         |                `--打开全部执行器
       |         |     |         `--回水温度 > 10 度
       |         |     |                          |--解除防冻需求
       |         |     |                          `--水泵、阀门、执行器重新处于待机状态
       |         |     |
       |         |     |--水泵停止运转
       |         |     |--三通阀关闭
       |         |     `--执行器关闭
       |         |     
       |         |
       |         `--开机
       |               |
       |               |--新风
       |               |     |--防冻保护
       |               |     |         |
       |               |     |         |--回水温度 < 5 度
       |               |     |         |                |--防冻请求
       |               |     |         |                |--水泵运转
       |               |     |         |                |--三通阀开启，调整混水温度到制热的'设定温度'
       |               |     |         |                `--打开全部执行器
       |               |     |         `--回水温度 > 10 度
       |               |     |                          |--解除防冻需求
       |               |     |                          `--水泵、阀门、执行器重新处于待机状态
       |               |     |
       |               |     |--水泵停止运转
       |               |     |--三通阀关闭
       |               |     `--执行器关闭
       |               |
	   |               |--除湿模式(是否单独存在？？)
	   |               |
       |               `--制冷、制热
       |                          |
       |                          |--初始能量需求
       |                          |            |--对应的执行开启
       |                          |            `--120s 后转入[重复能量需求]
       |                          |--重复能量需求
       |                          |            |
       |                          |            |--水泵运转
       |                          |            |--对应的执行开启
       |                          |            |--混水温度调整到'计算温度'，规则见混水温度计算。
       |                          |            `--末端能量需求全部解除，转入[无能量需求]
       |                          `--无能量需求  
       |                                      |
       |                                      |--执行器关闭
       |                                      |--三通阀关闭
       |                                      |--水泵停止运转
       |                                      `--末端有能量需求，转入[初始能量需求]
       |                                   
       |                
       |-- 数据同步
       |          |
       |          |
       |          |
       |          |--房间温控器/风盘控制器
       |          |           |--独立DP
       |          |           |      |
       |          |           |      |--开关机1byte
       |          |           |      |--制冷设定温度2byte
       |          |           |      |--制热设定温度2byte
       |          |           |      |--童锁1byte
       |          |           |      |--设定风速1byte
       |          |           |      `--双末端运行模式1byte
       |          |           |         
       |          |           `--组合DP
       |          |                  |
       |          |                  |--末端绑定信息4byte
	   |          |                  |             |--辐射绑定列表2byte
	   |          |                  |             `--风盘绑定列表2byte
	   |          |                  |
       |          |                  |--末端状态信息10byte
	   |          |                  |             |--辐射能需2byte
	   |          |                  |             |--风盘能需2byte
	   |          |                  |             |--露点保护状态1byte
	   |          |                  |             |--风机输出状态1byte  
	   |          |                  |             |--系统运行模式1byte
	   |          |                  |             |--EC风机PWM值1byte
	   |          |                  |             `--设备故障字2byte 
	   |          |                  |
	   |          |                  |--末端测量数据5byte
	   |          |                  |             |--测量温度2byte
	   |          |                  |             |--露点温度2byte
	   |          |                  |             `--测量湿度1byte
	   |          |                  |
       |          |                  |--末端高级设置32byte
	   |          |                  |             |--防冻保护1byte
	   |          |                  |             |--防冻温度2byte
	   |          |                  |             |--上电关机1byte
	   |          |                  |             |--最大设定温度2byte  
	   |          |                  |             |--最小设定温度2byte
	   |          |                  |             |--制冷舒适温度2byte
	   |          |                  |             |--制热舒适温度2byte
	   |          |                  |             |--控温带宽2byte
	   |          |                  |             |--露点带宽2byte
	   |          |                  |             |--AI制冷协同使能1byte
	   |          |                  |             |--AI制冷协同带宽2byte  
	   |          |                  |             |--AI制热协同使能1byte
	   |          |                  |             |--AI制热协同带宽2byte
	   |          |                  |             |--风机受控1byte
	   |          |                  |             |--低风量PWM值1byte
	   |          |                  |             |--中风量PWM值1byte
	   |          |                  |             |--高风量PWM值1byte
	   |          |                  |             |--双末端选择1byte
	   |          |                  |             |--校温2byte  
	   |          |                  |             |--校湿1byte
	   |          |                  |             |--辐射类型1byte
	   |          |                  |             `--房间面积1byte
	   |          |                  |--系统数据14byte
	   |          |                  |         |--辐射未绑定列表2byte
	   |          |                  |         |--风盘未绑定列表2byte
	   |          |                  |         |--系统开关机 1byte
	   |          |                  |         |--系统运行模式 1byte  
	   |          |                  |         |--系统故障 2byte
	   |          |                  |         |--绑定故障2byte
	   |          |                  |         |--混水测量温度2byte
	   |          |                  |         `--露点状态2byte
	   |          |                  |--系统时钟数据7byte
	   |          |                  |         |--RTC_秒1byte
	   |          |                  |         |--RTC_分1byte
	   |          |                  |         |--RTC_时1byte
	   |          |                  |         |--RTC_星期1byte  
	   |          |                  |         |--RTC_天1byte
	   |          |                  |         |--RTC_月1byte
	   |          |                  |         `--RTC_年1byte
	   |          |                  |--特殊DP4byte
	   |          |                  |         |--运行类型1byte
	   |          |                  |         |--风盘软件版本2byte
	   |          |                  |         `--风盘信息1byte
	   |          |                  |--设备类型4byte
	   |          |                  |         |--类型2byte
	   |          |                  |         `--软件版本2byte
	   |          |                  |--辐射类型6byte
	   |          |                  |         |--地辐射列表2byte
	   |          |                  |         |--墙辐射列表2byte
	   |          |                  |         `--顶辐射列表2byte
	   |          |                  `--RS485参数4byte
	   |          |                            |--地址1byte
	   |          |                            |--波特率2byte
	   |          |                            `--校验位1byte
       |          `--除湿模块
       |                    |--独立DP
       |                    |      |
       |                    |      |--系统开关机1byte
       |                    |      |--设定相对湿度 1byte
       |                    |      |--系统运行模式1byte
       |                    |      `--设定风速 1byte
       |                    |         
       |                    `--组合DP
       |                           |
       |                           |--系统状态5byte
	   |                           |             |--系统除湿需求1byte
	   |                           |             |--除湿带宽2byte
	   |                           |             `--PTC再热带宽2byte
	   |                           |--系统信息11byte
	   |                           |             |--PTC测量温度2byte
	   |                           |             |--房间温度2byte
	   |                           |             |--房间湿度1byte
	   |                           |             |--输出状态2byte
	   |                           |             |--软件版本号2byte
	   |                           |             `--硬件标识号2byte
	   |                           |--新风PWM值3byte
	   |                           |             |--新风低风PWM值1byte
	   |                           |             |--新风中风PWM值1byte
	   |                           |             `--新风高风PWM值1byte
	   |                           |--回风PWM值3byte
	   |                           |             |--回风低风PWM值1byte
	   |                           |             |--回风中风PWM值1byte
	   |                           |             `--回风高风PWM值1byte
	   |                           |--户外温湿度7byte
	   |                           |             |--户外进风口温度2byte
	   |                           |             |--户外进风口湿度1byte
	   |                           |             |--户外进风口湿度值修正系数2byte
	   |                           |             `--户外进风口温度值修正系数2byte
	   |                           |--氟盘前温湿度7byte
	   |                           |             |--氟盘前温度2byte
	   |                           |             |--氟盘前湿度1byte
	   |                           |             |--氟盘前湿度值修正系数2byte
	   |                           |             `--氟盘前温度值修正系数2byte
	   |                           |--氟盘后温湿度7byte
	   |                           |             |--氟盘后温度2byte
	   |                           |             |--氟盘后湿度1byte
	   |                           |             |--氟盘前湿度值修正系数2byte
	   |                           |             `--氟盘前温度值修正系数2byte
	   |                           |--回风口综合传感器15byte
	   |                           |             |--回风口温度2byte
	   |                           |             |--回风口湿度1byte
	   |                           |             |--回风口CO2浓度2byte
	   |                           |             |--回风口PM25浓度2byte
	   |                           |             |--回风口湿度值修正系数2byte
	   |                           |             |--回风口温度值修正系数2byte
	   |                           |             |--回风口CO2值修正系数2byte
	   |                           |             `--回风口PM25值修正系数2byte
	   |                           |--排风口温湿度7byte
	   |                           |             |--排风口温度2byte
	   |                           |             |--排风口湿度1byte
	   |                           |             |--排风口湿度值修正系数2byte
	   |                           |             `--排风口温度值修正系数2byte
	   |                           |--系统时钟数据7byte
	   |                           |             |--RTC_秒1byte
	   |                           |             |--RTC_分1byte
	   |                           |             |--RTC_时1byte
	   |                           |             |--RTC_星期1byte  
	   |                           |             |--RTC_天1byte
	   |                           |             |--RTC_月1byte
	   |                           |             `--RTC_年1byte
	   |                           `--RS485参数4byte
	   |                                     |--地址1byte
	   |                                     |--波特率2byte
	   |                                     `--校验位1byte
       |                 
       `-- 通讯接口
                  |
                  |--末端控制器(风盘、辐射、除湿模块)
                  |             |
                  |             |--最大末端数 11 个
				  |             |--除湿模块仅支持两路
                  |             |--波特率9600(1S8N1)
                  |             `--数据同步
                  |
                  `--mibee智能
                          |
                          |--modbus slave
                          |             |--地址:01
                          |             |--波特率:9600
                          |             `--1S8N1
                          |
                          |--固件更新
                          |         |--本级更新(输配中心)
                          |         |
                          |         `--下级更新(除湿模块、风盘、辐射)
                          |
                          `--远程控制
                                    |--主机(输配中心)
                                    |
                                    `--末端设备(除湿模块、风盘、辐射)
                                    
				  
				  
         






//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++end++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



