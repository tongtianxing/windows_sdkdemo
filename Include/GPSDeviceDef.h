#ifndef _NET_DEVICE_DEF_H_
#define _NET_DEVICE_DEF_H_

#include "ttxpttnettype.h"

#define GPS_FRM_TYPE_HEAD						1
#define GPS_FRM_TYPE_I							0x63643000
#define GPS_FRM_TYPE_P							0x63643100
#define GPS_FRM_TYPE_A							0x63643230
#define GPS_FRM_TYPE_INFO						0x63643939
#define GPS_FRM_TYPE_REC_HDR					2

#define GPS_RESOLUTION_QCIF				1	//分辨率
#define GPS_RESOLUTION_CIF				2	//分辨率
#define GPS_RESOLUTION_HD1				3	//分辨率
#define GPS_RESOLUTION_D1				4	//分辨率
#define GPS_RESOLUTION_720P				5	//分辨率
#define GPS_RESOLUTION_1080P			6	//分辨率

#define GPS_FILE_TYPE_NORMAL			0 //正常录像
#define GPS_FILE_TYPE_ALARM				1 //报警录像
#define GPS_FILE_TYPE_ALL				-1 //全部




#define GPS_CHANNEL_ALL							99

#define GPS_ALARM_TYPE_ALL								0		//所有报警

#define GPS_ALARM_TYPE_USEDEFINE						1		//自定义报警
#define GPS_ALARM_TYPE_URGENCY_BUTTON					2		//紧急按钮报警
#define GPS_ALARM_TYPE_SHAKE							3		//振动报警
#define GPS_ALARM_TYPE_VIDEO_LOST						4		//视频信号丢失报警,AlarmInfo(|)param[0]:通道位(按位解析1-32个通道)
#define GPS_ALARM_TYPE_VIDEO_MASK						5		//视频信号遮挡报警,AlarmInfo(|)param[0]:通道位(按位解析1-32个通道)
#define GPS_ALARM_TYPE_DOOR_OPEN_LAWLESS				6		//非法开门报警
#define GPS_ALARM_TYPE_WRONG_PWD						7		//三次密码错误报警
#define GPS_ALARM_TYPE_FIRE_LOWLESS						8		//非法点火报警
#define GPS_ALARM_TYPE_TEMPERATOR						9		//温度报警		AlarmInfo传感器编号（0表示传感器1，1表示传感器2）, param[0]温度类型（0表示超高温，1表示超低温）, param[1]当前温度10000=100度 
#define GPS_ALARM_TYPE_DISK_ERROR						10		//硬盘错误报警		参数 param[0] 存储器掩码 按位 BIT0-BIT11：1-12主存储器 BIT12-BIT15：1-4灾备存储， 相应为1表示故障
#define GPS_ALARM_TYPE_OVERSPEED						11		//超速报警
#define GPS_ALARM_TYPE_BEYOND_BOUNDS					12		//越界报警
#define GPS_ALARM_TYPE_DOOR_ABNORMAL					13		//异常开关车门
#define GPS_ALARM_TYPE_PARK_TOO_LONG					14		//超时停车报警
#define GPS_ALARM_TYPE_MOTION							15		//移动侦测报警
#define GPS_ALARM_TYPE_ACC_ON							16		//ACC报警
#define GPS_ALARM_TYPE_DEV_ONLINE						17		//上线
#define GPS_ALARM_TYPE_GPS_SIGNAL_LOSS					18      //GPS讯号丢失报警
#define GPS_ALARM_TYPE_IO_1								19      //IO_1
#define GPS_ALARM_TYPE_IO_2								20      //IO_2
#define GPS_ALARM_TYPE_IO_3								21      //IO_3
#define GPS_ALARM_TYPE_IO_4								22      //IO_4
#define GPS_ALARM_TYPE_IO_5								23      //IO_5
#define GPS_ALARM_TYPE_IO_6								24      //IO_6
#define GPS_ALARM_TYPE_IO_7								25		//IO_7
#define GPS_ALARM_TYPE_IO_8								26      //IO_8
#define GPS_ALARM_TYPE_IN_FENCE							27      //进入电子围栏报警
#define GPS_ALARM_TYPE_OUT_FENCE						28      //出电子围栏报警
#define GPS_ALARM_TYPE_IN_FENCE_OVER_SPEED				29      //电子围栏内高速报警
#define GPS_ALARM_TYPE_OUT_FENCE_OVER_SPEED				30      //电子围栏外高速报警
#define GPS_ALARM_TYPE_IN_FENCE_LOW_SPEED				31      //电子围栏内低速报警
#define GPS_ALARM_TYPE_OUT_FENCE_LOW_SPEED				32      //电子围栏外低速报警
#define GPS_ALARM_TYPE_IN_FENCE_STOP					33      //电子围栏内停车报警
#define GPS_ALARM_TYPE_OUT_FENCE_STOP					34      //电子围栏外停车报警
#define GPS_ALARM_TYPE_FIRE								35      //火警
#define GPS_ALARM_TYPE_PANIC							36      //劫警
#define GPS_ALARM_TYPE_TASK_FINISHED					37		//调度任务完成
#define GPS_ALARM_TYPE_IMAGE_UPLOAD						38		//图片上传完成
#define GPS_ALARM_TYPE_DISK1_NO_EXIST					39		//硬盘1不存在
#define GPS_ALARM_TYPE_DISK2_NO_EXIST					40		//硬盘2不存在
#define GPS_ALARM_TYPE_IO_9								41      //IO_9
#define GPS_ALARM_TYPE_IO_10							42      //IO_10
#define GPS_ALARM_TYPE_IO_11							43      //IO_11
#define GPS_ALARM_TYPE_IO_12							44      //IO_12
#define GPS_ALARM_TYPE_GPS_UNENABLE						45		//GPS定位无效
#define GPS_ALARM_TYPE_REFUEL							46		//加油报警	AlarmInfo为加油的油量(9999=99.99升)，Param[0]为加油前油耗
#define GPS_ALARM_TYPE_STILL_FUEL						47		//油量减少报警	AlarmInfo为偷油的油量(9999=99.99升)，Param[0]为偷油前油耗
#define GPS_ALARM_TYPE_URGENCY_BUTTON_5					48		//紧急按钮报警(5秒)
#define GPS_ALARM_TYPE_FATIGUE							49		//疲劳驾驶	AlarmInfo表示报警级别	0 , 没有， 1  一级报警 2 二级报警, 3 三级报警, 4 关注度报警 param[0] 疲劳程度 



#define GPS_ALARM_TYPE_END_USEDEFINE					51		//自定义报警
#define GPS_ALARM_TYPE_END_URGENCY_BUTTON				52		//紧急按钮报警
#define GPS_ALARM_TYPE_END_SHAKE						53		//振动报警
#define GPS_ALARM_TYPE_END_VIDEO_LOST					54		//视频信号丢失报警
#define GPS_ALARM_TYPE_END_VIDEO_MASK					55		//视频信号遮挡报警
#define GPS_ALARM_TYPE_END_DOOR_OPEN_LAWLESS			56		//非法开门报警
#define GPS_ALARM_TYPE_END_WRONG_PWD					57		//三次密码错误报警
#define GPS_ALARM_TYPE_END_FIRE_LOWLESS					58		//非法点火报警
#define GPS_ALARM_TYPE_END_TEMPERATOR					59		//温度报警
#define GPS_ALARM_TYPE_END_DISK_ERROR					60		//硬盘错误报警
#define GPS_ALARM_TYPE_END_OVERSPEED					61		//超速报警
#define GPS_ALARM_TYPE_END_BEYOND_BOUNDS				62		//越界报警
#define GPS_ALARM_TYPE_END_DOOR_ABNORMAL				63		//异常开关车门
#define GPS_ALARM_TYPE_END_PARK_TOO_LONG				64		//超时停车报警
#define GPS_ALARM_TYPE_END_MOTION						65		//移动侦测报警
#define GPS_ALARM_TYPE_ACC_OFF							66		//ACC报警
#define GPS_ALARM_TYPE_DEV_DISONLINE					67		//离线
#define GPS_ALARM_TYPE_END_GPS_SIGNAL_LOSS				68      //GPS讯号丢失报警
#define GPS_ALARM_TYPE_END_IO_1							69      //IO_1
#define GPS_ALARM_TYPE_END_IO_2							70      //IO_2
#define GPS_ALARM_TYPE_END_IO_3							71      //IO_3
#define GPS_ALARM_TYPE_END_IO_4							72      //IO_4
#define GPS_ALARM_TYPE_END_IO_5							73      //IO_5
#define GPS_ALARM_TYPE_END_IO_6							74      //IO_6
#define GPS_ALARM_TYPE_END_IO_7							75      //IO_7
#define GPS_ALARM_TYPE_END_IO_8							76      //IO_8
#define GPS_ALARM_TYPE_END_IN_FENCE						77      //进入电子围栏报警
#define GPS_ALARM_TYPE_END_OUT_FENCE					78      //出电子围栏报警
#define GPS_ALARM_TYPE_END_IN_FENCE_OVER_SPEED			79      //电子围栏内高速报警
#define GPS_ALARM_TYPE_END_OUT_FENCE_OVER_SPEED			80      //电子围栏外高速报警
#define GPS_ALARM_TYPE_END_IN_FENCE_LOW_SPEED			81      //电子围栏内低速报警
#define GPS_ALARM_TYPE_END_OUT_FENCE_LOW_SPEED			82      //电子围栏外低速报警
#define GPS_ALARM_TYPE_END_IN_FENCE_STOP				83      //电子围栏内停车报警
#define GPS_ALARM_TYPE_END_OUT_FENCE_STOP				84      //电子围栏外停车报警
#define GPS_ALARM_TYPE_END_GPS_UNENABLE					85		//GPS定位无效
//加油和偷油没有结束
#define GPS_ALARM_TYPE_END_REFUEL						86		//加油报警	AlarmInfo为加油的油量(9999=99.99升)，Param[0]为加油前油耗
#define GPS_ALARM_TYPE_END_STILL_FUEL					87		//油量减少报警	AlarmInfo为偷油的油量(9999=99.99升)，Param[0]为偷油前油耗

#define GPS_ALARM_TYPE_END_IO_9							91      //IO_9
#define GPS_ALARM_TYPE_END_IO_10						92      //IO_10
#define GPS_ALARM_TYPE_END_IO_11						93      //IO_11
#define GPS_ALARM_TYPE_END_IO_12						94      //IO_12

#define GPS_ALARM_TYPE_END_FATIGUE						99		//疲劳驾驶	AlarmInfo表示报警级别	0 , 没有， 1  一级报警 2 二级报警, 3 三级报警, 4 关注度报警


#define GPS_EVENT_TYPE_PARK								101		//停车事件			Param[0]为停车秒数，Param[1]为停车前油耗(9999=99.99升)，Param[2]为停车后油耗
#define GPS_EVENT_TYPE_PARK_ACCON						102		//停车未熄火事件	Param[0]为停车秒数，Param[1]为停车前油耗(9999=99.99升)，Param[2]为停车后油耗
																//停车未熄火事件一般处于停车事件里面的一段时间内，11:00 - 11:20处于停车，11:00 - 11:05 处于停车未熄火
#define GPS_EVENT_TYPE_NET_FLOW							103		//流量	Param[0]为当前时间（单位秒，如：7206 = 当天02:06时 ），Param[1]为上行流量，Param[2]为下行流量
#define GPS_EVENT_TYPE_REFUEL							104		//加油	AlarmInfo为加油的油量(9999=99.99升)，Param[0]为加油前油耗
#define GPS_EVENT_TYPE_STILL_FUEL						105		//偷油	AlarmInfo为偷油的油量(9999=99.99升)，Param[0]为偷油前油耗
#define GPS_EVENT_TYPE_OVERSPEED						106		//超速事件	AlarmInfo为速度(999=99.9KM/H)，Param[0]超速的时间，Param[1]为超速类型（超高速或者超低速、暂时无效）
#define GPS_EVENT_TYPE_FENCE_ACCESS						107		//进出区域事件	 Param[0]区域编号，Param[1]出区域经度，Param[2]出区域纬度，Param[3]区域停留时间(秒）
#define GPS_EVENT_TYPE_FENCE_PARK						108		//区域停车事件	 Param[0]区域编号，Param[3]区域停车时间（秒）
#define GPS_EVENT_TYPE_FILE_UPLOAD						109		//图片文件或者录像文件上传通知
#define GPS_EVENT_TYPE_STATION_INFO						110		//报站信息
#define GPS_EVENT_TYPE_SEA_STATUS						111		//海船状态报警 1：出海 2：进港 3：外海滞留报警 4：外海滞留报警结束
//#define GPS_EVENT_TYPE_LOCK_STATUS				112		//电子锁状态					
#define GPS_ALARM_TYPE_CUSTOM							113		//自定义报警, AlarmInfo表示类型
										// param[0]表示参数1，param[1]表示参数2，param[2]表示参数3, param[3]表示参数4, 
										//szDesc表示内容，为字符串格式，中间不允许出现'\0'，最长为256个字节
#define GPS_EVENT_TYPE_OVERSPEED_WARNING				114		//超速预警
#define GPS_EVENT_TYPE_LOWSPEED_WARNING					115		//低速预警
#define GPS_EVENT_TYPE_DRIVER							116		//驾驶员身份信息采集 AlarmInfo：1表示登录，0表示退签，p0:协议(6=808协议),参考MDVR_PROTOCOL_TYPE_JT808
																//p1:是否为扩展协议(1=808协议,2=北斗协议,3=1078协议),参考MDVR_JT808_BD
																//p3:北斗协议时有效,(0=未知,1=签到,2=签退)
																//szReserve 表示司机名称，szDesc 表示发证机关，szImgFile：用 ';' 分隔 ，身体证号;从业资格证编码
#define GPS_EVENT_TYPE_OVER_STATION						117		//过站报警 
#define GPS_EVENT_TYPE_EXCEED_STATION					118		//越站报警，param[0],param[1]前一个报站时间和站点
#define GPS_EVENT_TYPE_FACE_DETECTION					119		//人脸检测 param[0]通道  param[1]结果 1成功  param[2]原因

#define GPS_EVENT_TYPE_TASK_READ						121		//guid为对应的任务guid,人员已经查看了调度任务
#define GPS_EVENT_TYPE_TASK_REPLY						122		//guid为对应的任务guid,人员对调度任务进行了回复，szDesc，为回复内容
#define GPS_ALARM_TYPE_MOBILE_USEDEFINE					123		//自定义报警
#define GPS_ALARM_TYPE_PTT								124		//集群对讲相关报警
#define GPS_EVENT_TYPE_FATIGUE_84220					125		//疲劳84220报警

#define GPS_ALARM_TYPE_TALK_BACK_REQ					127		//车辆主动对讲请求，以报警方式发送
#define GPS_ALARM_TYPE_DEVICE_INFO_CHANGE				128		//车辆信息发生变化，如用户修改设备信息
#define GPS_ALARM_TYPE_SNAPSHOT_FINISH					129		//存储服务器抓拍完成，以报警方式发送给客户端
#define GPS_ALARM_TYPE_DOWN_FINISH						130		//文件上传完成  存储服务器文件任务下载完成，以报警方式发送给客户端
#define GPS_ALARM_TYPE_DEVICE_INFO_CHANGE_EX			131		//车辆信息发生变化，如用户修改设备信息
#define GPS_ALARM_TYPE_TRANS_PORT						132		//透传数据
#define GPS_ALARM_TYPE_SWIPE_CARD						133		//刷卡记录 不同于司机考勤 alarminfo：-1表示无上下车表示， 0-上车， 1-下车 desc:卡号
#define GPS_EVENT_TYPE_FTP_TASK_NOTIFY					134	    //FTP任务完成通知 paramp[0]流水号 parma[1]0-成功, 1-失败
#define	GPS_EVENT_TYPE_808_PEOPLE_COUNT					135		//808客流统计 param[0]上车人数, param[1]下车人数
#define GPS_EVENT_TYPE_ABNORMAL_GPS						136		//定位异常 param[0] 间隔时间(秒) param[1]间隔距离 米
#define GPS_EVENT_TYPE_SVR_DISK_FULL_WARN				137    //服务器磁盘空间预警 alarminfo:服务器ID param[0]:剩余空间(MB) desc:服务器名称
#define GPS_EVENT_TYPE_UNLAWFUL_AREA_UNLOAD				138    //违规卸载
#define GPS_EVENT_TYPE_TRAVEL_COVER_OPEN				139    //重车行驶厢盖未关闭
#define GPS_EVENT_TYPE_OFFLINE_EARLYWARNING				140		//离线预警 Param[0]:0-预警 1-结束预警 2-预警(新) 3-结束预警(新)(设备上线) 4-结束预警(新)(预警已处理)
																//Param[1]:Param[0]=0时,参数无效; Param[0]=1时,1-设备上线,2-预警已处理; Param[0]=其他值时,表示离线时间
																//Param[2]:Param[0]=0或2时,表示判断阀值,单位:秒

#define GPS_ALARM_TYPE_NIGHT_NO_ROAD_LIST_NO_DRIVING 	141		//夜间无路单禁止行车(平台)
#define GPS_ALARM_TYPE_END_NIGHT_NO_ROAD_LIST_NO_DRIVING 142

#define GPS_EVENT_TYPE_DRIVER_8HOUR						145		//超时驾驶 param[0]:司机ID param[1]:驾驶时长,单位:秒 param[2]:超时阀值,单位:秒
#define GPS_EVENT_TYPE_DRIVER_OFFLINE					146		//在途不在线报警
#define GPS_EVENT_TYPE_UNKONW_VEL					    147		//未知车辆事件报警
#define GPS_EVENT_TYPE_VERMAN_REMINDER					148		//超员提醒	//(客户端)
#define GPS_EVENT_TYPE_ROAD_LIST_ALARM					149		//路单报警(中石油)	param[0]:0位 时间超时 1位:距离超时 2位:表示报警结束 szDesc:开始时间|规则名称|统计时间,时间阀值;里程,距离阀值
#define GPS_EVENT_TYPE_CONTROL_FACE_ALARM				150		//布控人脸识别报警  p0:匹配度  p1:匹配阙值  p2:布控名单ID  img:抓拍文件;比对文件(web)

#define GPS_ALARM_TYPE_NIGHT_DRIVING 					151		//夜间禁止行车报警(平台)
#define GPS_ALARM_TYPE_END_NIGHT_DRIVING				152
#define GPS_ALARM_TYPE_GATHERING						153		//聚众报警
#define GPS_ALARM_TYPE_END_GATHERING					154
#define GPS_ALARM_TYPE_USP_CUT		 					155		//UPS 剪线报警
#define GPS_ALARM_TYPE_END_USP_CUT						156
#define GPS_ALARM_TYPE_HDD_HIGH_TEMPERATURE				157		//硬盘超温报警
#define GPS_ALARM_TYPE_END_HDD_HIGH_TEMPERATURE			158
#define GPS_ALARM_TYPE_BEFORE_BOARD_OPENED				159		//前面板被撬开
#define GPS_ALARM_TYPE_END_BEFORE_BOARD_OPENED			160		
#define GPS_ALARM_TYPE_TURN_OFF							161		//关机上报	alarmInfo为原因: 1 ACC 无效关机,2定时关机,3软件重启, 4软件异常关机,5掉电关机,6硬盘锁打开关机
#define GPS_ALARM_TYPE_DISK_SPACE_WARNING				162		//硬盘空间不足		硬盘空间警告,alarmInfo为硬盘号,param[0]表示硬盘类型TTX_DISK_TYPE_SD, param[1]总空间, param[2]剩余空间,  16000表示空间为16000MB
#define GPS_ALARM_TYPE_END_DISK_SPACE_WARNING			163		//
#define GPS_ALARM_TYPE_GSENSOR							164		//GSENSOR报警
#define GPS_ALARM_TYPE_END_GSENSOR						165
#define GPS_ALARM_TYPE_SIM_LOST							166		//SIM卡丢失报警
#define GPS_ALARM_TYPE_END_SIM_LOST						167
#define GPS_ALARM_TYPE_TPMS								168		//胎压报警			//	胎压报警, alarmInfo  TPMS报警类型（1表示电池电压警告，2表示胎压异常报警，3表示温度异常）,
//			param[0] 当前温度 如: 200 = 20度
//			param[1] 当前胎压 如: 25 = 2.5P
//			param[2] 当前电压 如: 102=10.2V
//			param[3] 传感器编号（01表示TPMS左1，02表示TPMS左2，03表示TPMS左3，04表示TPMS左4，11表示TPMS右1，12表示TPMS右2，13表示TPMS右3，14表示TPMS右4）
#define GPS_ALARM_TYPE_END_TPMS							169		//胎压报警结束

#define GPS_ALARM_TYPE_FACE_WARNING						170		//面向警示
#define GPS_ALARM_TYPE_END_FACE_WARNING					171		//
#define GPS_ALARM_TYPE_CLOSE_EYE_WARNING				172		//闭眼警示
#define GPS_ALARM_TYPE_END_CLOSE_EYE_WARNING			173		//
#define GPS_ALARM_TYPE_PHONE_WARNING					174		//手机警示
#define GPS_ALARM_TYPE_END_PHONE_WARNING				175		//
#define GPS_ALARM_TYPE_SMOKE_WARNING					176		//抽烟警示
#define GPS_ALARM_TYPE_END_SMOKE_WARNING				177		//


#define GPS_ALARM_TYPE_OVERSPEED_BEND					178		//弯道超速
#define GPS_ALARM_TYPE_END_OVERSPEED_BEND				179		//
#define GPS_ALARM_TYPE_OVERSPEED_STRAIGHT				180		//直道超速
#define GPS_ALARM_TYPE_END_OVERSPEED_STRAIGHT			181		//
#define GPS_ALARM_TYPE_DEVICE_UNLOCKED					182		//设备开锁
#define GPS_ALARM_TYPE_DEVICE_LOCKED					183		//设备上锁
#define GPS_ALARM_TYPE_WATER_LEVEL_ABNORMAL_INCREASE	184  //水位异常增加
#define GPS_ALARM_TYPE_WATER_LEVEL_ABNORMAL_DECREASE	185  //水位异常减少

#define GPS_ALARM_TYPE_OUT_WORK							186	 //离岗
#define GPS_ALARM_TYPE_END_OUT_WORK						187	 //
#define GPS_ALARM_TYPE_GLANCE_RIGHT_LEFT				188  //左顾右盼
#define GPS_ALARM_TYPE_END_GLANCE_RIGHT_LEFT			189  //
#define GPS_ALARM_TYPE_YAWN								190  //打哈欠
#define GPS_ALARM_TYPE_END_YAWN							191  //
#define GPS_ALARM_TYPE_OXYGEN_DENSITY_LOW				192  //氧气浓度低
#define GPS_ALARM_TYPE_END_OXYGEN_DENSITY_LOW			193  //
#define GPS_ALARM_TYPE_SMOKE_SENSOR						194  //烟感报警
#define GPS_ALARM_TYPE_END_SMOKE_SENSOR					195  //
#define GPS_ALARM_TYPE_DRIVER_ON						196  //司机开车验证通过事件 Param[0]:按位表示，0位：指纹，1位：酒精，2位：人脸
#define GPS_ALARM_TYPE_END_DRIVER_ON					197  //
#define GPS_ALARM_TYPE_OPEN_CLOSE_COVER					198	 //开合盖报警 alarminfo:1=开盖 0=合盖
#define GPS_ALARM_TYPE_LIFTING_ALARM					199	 //举升报警 alarminfo:1=开始举升 0=结束举升

//808部分报警
#define GPS_ALARM_TYPE_AREA_OVERSPEED					200		//区域超速报警
#define GPS_ALARM_TYPE_WARNING							201		//危险驾驶行为报警
#define GPS_ALARM_TYPE_GNSS_MOD_ERR						202		//GNSS模块发送故障报警
#define GPS_ALARM_TYPE_GNSS_WIRE_MISS					203		//GNSS天线未接或被剪断报警
#define GPS_ALARM_TYPE_GNSS_WIRE_SHORTAGE				204		//GNSS天线短路报警
#define GPS_ALARM_TYPE_VOLTAGE_LOW						205		//终端主电源欠压报警
#define GPS_ALARM_TYPE_POWER_OFF						206		//终端主电源掉电报警
#define GPS_ALARM_TYPE_LCD_ERR							207		//LCD或者显示器故障
#define GPS_ALARM_TYPE_TTS_MOD_ERR						208		//TTS模块故障
#define GPS_ALARM_TYPE_CAMERA_MOD_ERR					209		//摄像头故障
#define GPS_ALARM_TYPE_DIRVE_TIMEOUT					210		//当天累计驾驶超时
#define GPS_ALARM_TYPE_AREA_INOUT						211		//进出区域
#define GPS_ALARM_TYPE_LINE_INOUT						212		//进出线路
#define GPS_ALARM_TYPE_LINE_DRIVE_TIME					213		//线路行驶时间不足或过长  路段行驶时间过长/过短
#define GPS_ALARM_TYPE_LINE_DEVIATE						214		//线路偏离
#define GPS_ALARM_TYPE_VSS_ERR							215		//VSS故障
#define GPS_ALARM_TYPE_OIL_ABNORMAL						216		//油量异常
#define GPS_ALARM_TYPE_STOLEN							217		//车辆被盗
#define GPS_ALARM_TYPE_MOVE_LAWLESS						218		//非法位移报警
#define GPS_ALARM_TYPE_COLLISION						219		//碰撞侧翻报警
#define GPS_ALARM_TYPE_PASSENGER_FORBID					220		//客运车辆禁止  param[0]当前超速限速值
#define GPS_ALARM_TYPE_MOUNTAIN_FORBID					221		//山区公路禁止  param[0]-位置类型 param[1]-区域或者线路ID param[2]当前超速限速值 
#define GPS_ALARM_TYPE_OVERSPEED_L1_FIVE_LESS		    222		//超速20%  5分钟内	param[0]-最大速度 param[1]-限制速度 param[2]当前超速限速值 
#define GPS_ALARM_TYPE_OVERSPEED_L1_FIVE_TO_TEN			223		//超速20%  5(含)-10分钟
#define GPS_ALARM_TYPE_OVERSPEED_L1_TEN_MORE			224		//超速20%  10(含)分钟以上
#define GPS_ALARM_TYPE_OVERSPEED_L2_FIVE_LESS			225		//超速20-50%  5分钟内
#define GPS_ALARM_TYPE_OVERSPEED_L2_FIVE_TO_TEN			226		//超速20-50%  5(含)-10分钟
#define GPS_ALARM_TYPE_OVERSPEED_L2_TEN_MORE			227		//超速20-50%  10(含)分钟以上
#define GPS_ALARM_TYPE_OVERSPEED_L3_FIVE_LESS			228		//超速50%  5分钟内
#define GPS_ALARM_TYPE_OVERSPEED_L3_FIVE_TO_TEN			229		//超速50%  5(含)-10分钟
#define GPS_ALARM_TYPE_OVERSPEED_L3_TEN_MORE			230		//超速50%  10(含)分钟以上
#define GPS_ALARM_TYPE_OVERLAOD							231		//超载
#define GPS_ALARM_TYPE_FORBID_AREA						232		//禁行区 alarmInfo 区域ID    szdesc 车牌号;所属行政区域名称
#define GPS_ALARM_TYPE_FORBID_LINE						233		//禁行线路 alarmInfo 线路ID szdesc 车牌号;所属行政区域名称
#define GPS_ALARM_TYPE_OUTLAND_VEHI_ENTERY				234		//异地车辆入境 alarmInfo 区域ID szdesc 车牌号;所属行政区域名称
#define GPS_ALARM_TYPE_TT_ABNORMAL						235		//胎温报警 //参数 param[0] 当前温度 如: 200 = 20度param[1] 当前胎压 如: 25 = 2.5P param[2] 当前电压 如: 102=10.2V param[3]:0-7位为组, 8-15为排， 16-23为类型
#define GPS_ALARM_TYPE_TC_ABNORMAL						236		//配置错误报警 //参数见胎压 GPS_ALARM_TYPE_TT_ABNORMAL
#define GPS_ALARM_TYPE_TS_NOSIGNAL						237		//传感器无信号报警 //参数见胎压 GPS_ALARM_TYPE_TT_ABNORMAL
#define GPS_ALARM_TYPE_TS_LOWVOLTAGE					238		//低电压报警 //参数见胎压 GPS_ALARM_TYPE_TT_ABNORMAL
#define GPS_ALARM_TYPE_TP_ABNORMAL						239		//胎压报警(方皓) GPS_ALARM_TYPE_TT_ABNORMAL
#define GPS_ALARM_TYPE_1078_OTHER_DEVICE_ERROR			244		//其他视频设备故障报警
#define GPS_ALARM_TYPE_1078_RECORD_THRESHOLD			245		//录像阀值
#define GPS_ALARM_TYPE_RAPID_ACCELERATION				246		//急加速
#define GPS_ALARM_TYPE_RAPID_DECELERATION				247		//急减速
#define GPS_ALARM_TYPE_1078_ABNORMAL_DRIVE				248		//异常驾驶	 	param[0]:异常驾驶标志位 bit0：疲劳; bit1：打电话  bit2：抽烟 ；	param[1]: //疲劳程度 0-100
#define GPS_ALARM_TYPE_FACE_FATIGUE						249		//面部疲劳      param[1]: //疲劳程度 0-100  设备通过视频画面去判断

#define GPS_ALARM_TYPE_END_AREA_OVERSPEED				250		//区域超速报警
#define GPS_ALARM_TYPE_END_WARNING						251		//危险驾驶行为报警
#define GPS_ALARM_TYPE_END_GNSS_MOD_ERR					252		//GNSS模块发送故障报警
#define GPS_ALARM_TYPE_END_GNSS_WIRE_MISS				253		//GNSS天线未接或被剪断报警
#define GPS_ALARM_TYPE_END_GNSS_WIRE_SHORTAGE			254		//GNSS天线短路报警
#define GPS_ALARM_TYPE_END_VOLTAGE_LOW					255		//终端主电源欠压报警
#define GPS_ALARM_TYPE_END_POWER_OFF					256		//终端主电源掉电报警
#define GPS_ALARM_TYPE_END_LCD_ERR						257		//LCD或者显示器故障
#define GPS_ALARM_TYPE_END_TTS_MOD_ERR					258		//TTS模块故障
#define GPS_ALARM_TYPE_END_CAMERA_MOD_ERR				259		//摄像头故障
#define GPS_ALARM_TYPE_END_DIRVE_TIMEOUT				260		//当天累计驾驶超时
#define GPS_ALARM_TYPE_END_AREA_INOUT					261		//进出区域
#define GPS_ALARM_TYPE_END_LINE_INOUT					262		//进出线路
#define GPS_ALARM_TYPE_END_LINE_DRIVE_TIME				263		//线路行驶时间不足或过长 路段行驶时间过长/过短
#define GPS_ALARM_TYPE_END_LINE_DEVIATE					264		//线路偏离
#define GPS_ALARM_TYPE_END_VSS_ERR						265		//VSS故障
#define GPS_ALARM_TYPE_END_OIL_ABNORMAL					266		//油量异常
#define GPS_ALARM_TYPE_END_STOLEN						267		//车辆被盗
#define GPS_ALARM_TYPE_END_MOVE_LAWLESS					268		//非法位移报警
#define GPS_ALARM_TYPE_END_COLLISION					269		//碰撞侧翻报警
#define GPS_ALARM_TYPE_END_PASSENGER_FORBID				270		//客运车辆禁止  param[0]当前超速限速值
#define GPS_ALARM_TYPE_END_MOUNTAIN_FORBID				271		//山区公路禁止  param[0]-位置类型 param[1]-区域或者线路ID param[2]当前超速限速值 
#define GPS_ALARM_TYPE_END_OVERSPEED_L1_FIVE_LESS		272		//超速20%  5分钟内
#define GPS_ALARM_TYPE_END_OVERSPEED_L1_FIVE_TO_TEN		273		//超速20%  5(含)-10分钟
#define GPS_ALARM_TYPE_END_OVERSPEED_L1_TEN_MORE		274		//超速20%  10(含)分钟以上
#define GPS_ALARM_TYPE_END_OVERSPEED_L2_FIVE_LESS		275		//超速20-50%  5分钟内
#define GPS_ALARM_TYPE_END_OVERSPEED_L2_FIVE_TO_TEN		276		//超速20-50%  5(含)-10分钟
#define GPS_ALARM_TYPE_END_OVERSPEED_L2_TEN_MORE		277		//超速20-50%  10(含)分钟以上
#define GPS_ALARM_TYPE_END_OVERSPEED_L3_FIVE_LESS		278		//超速50%  5分钟内
#define GPS_ALARM_TYPE_END_OVERSPEED_L3_FIVE_TO_TEN		279		//超速50%  5(含)-10分钟
#define GPS_ALARM_TYPE_END_OVERSPEED_L3_TEN_MORE		280		//超速50%  10(含)分钟以上
#define GPS_ALARM_TYPE_END_OVERLAOD						281		//超载
#define GPS_ALARM_TYPE_END_FORBID_AREA					282		//禁行区 alarmInfo 区域ID	 szdesc 车牌号;所属行政区域名称
#define GPS_ALARM_TYPE_END_FORBID_LINE					283		//禁行线路 alarmInfo 线路ID	 szdesc 车牌号;所属行政区域名称
#define GPS_ALARM_TYPE_END_OUTLAND_VEHI_ENTERY			284		//异地车辆入境 alarmInfo 区域ID szdesc 车牌号;所属行政区域名称
#define GPS_ALARM_TYPE_END_TT_ABNORMAL					285		//胎温报警 //参数  param[0] 当前温度 如: 200 = 20度param[1] 当前胎压 如: 25 = 2.5P param[2] 当前电压 如: 102=10.2V param[3]:0-7位为组, 8-15为排，16-23为类型
#define GPS_ALARM_TYPE_END_TC_ABNORMAL					286		//配置错误报警 //参数见 GPS_ALARM_TYPE_TT_ABNORMAL
#define GPS_ALARM_TYPE_END_TS_NOSIGNAL					287		//传感器无信号报警 //参数见 GPS_ALARM_TYPE_TT_ABNORMAL
#define GPS_ALARM_TYPE_END_TS_LOWVOLTAGE				288		//低电压报警 //参数见 GPS_ALARM_TYPE_TT_ABNORMAL
#define GPS_ALARM_TYPE_END_TP_ABNORMAL					289		//胎压报警(方皓) GPS_ALARM_TYPE_TT_ABNORMAL 
#define GPS_ALARM_TYPE_END_1078_OTHER_DEVICE_ERROR		294		//其他视频设备故障报警
#define GPS_ALARM_TYPE_END_1078_RECORD_THRESHOLD		295		//录像阀值
#define GPS_ALARM_TYPE_END_RAPID_ACCELERATION			296		//急加速
#define GPS_ALARM_TYPE_END_RAPID_DECELERATION			297		//急减速
#define GPS_ALARM_TYPE_END_1078_ABNORMAL_DRIVE			298		//异常驾驶
#define GPS_ALARM_TYPE_END_FACE_FATIGUE					299		//面部疲劳

#define GPS_ALARM_TYPE_CMS_AREA_OVERSPEED				300		//区域超速报警(平台) param[0]-位置类型 param[1]-区域或者线路ID param[2]-速度阀值
#define GPS_ALARM_TYPE_CMS_AREA_LOWSPEED				301		//区域低速报警(平台) param[0]-位置类型 param[1]-区域或者线路ID param[2]-速度阀值	
#define GPS_ALARM_TYPE_CMS_AREA_INOUT					302		//进出区域报警(平台)	 param[0]-位置类型 param[1]-区域或者线路ID param[2]-0:进1:出
#define GPS_ALARM_TYPE_CMS_LINE_INOUT					303		//线路偏移(平台)	 param[0]-位置类型 param[1]-区域或者线路ID param[2]-0:进1:出
#define GPS_ALARM_TYPE_CMS_OVERSPEED					304		//时间段超速报警(平台) param[0]速度阀值
#define GPS_ALARM_TYPE_CMS_LOWSPEED						305		//时间段低速报警(平台) param[0]速度阀值
#define GPS_ALARM_TYPE_CMS_FATIGUE						306		//疲劳驾驶(平台)
#define	GPS_ALARM_TYPE_CMS_PARK_TOO_LONG				307		//超时停车(平台)
#define GPS_ALARM_TYPE_CMS_AREA_POINT					308		//关键点监控报警(平台)	param[0]-位置类型 param[1]-区域或者线路ID param[2]-0:未到达1:未离开
#define GPS_ALARM_TYPE_CMS_LINE_OVERSPEED				309		//线路超速报警(平台) param[0]-位置类型 param[1]-线路ID param[2]-速度阀值
#define GPS_ALARM_TYPE_CMS_LINE_LOWSPEED				310		//线路低速报警(平台) param[0]-位置类型 param[1]-线路ID param[2]-速度阀值
#define GPS_ALARM_TYPE_CMS_ROAD_LVL_OVERSPEED			311		//道路等级超速报警(平台) param[0]-道路等级 param[1]-市标志 param[2]-速度阀值
#define GPS_ALARM_TYPE_CMS_GPS_DRIFT					312		//GPS漂移(平台) 
#define GPS_ALARM_TYPE_CMS_TRACK_DISCON					313		//轨迹不连续报警(平台) 
#define GPS_ALARM_TYPE_CMS_NIGHT_OVERSEPED 				314		//夜间超速(平台)  param[0]当嗯前超速限速值
#define GPS_ALARM_TYPE_CMS_TRACK_VOERSPEED_50			315		//轨迹超过限速50KM/S, alarmInfo:超速率（放大100倍数）  param[0]:超速时长(秒) param[1]：最大速度
#define GPS_ALARM_TYPE_CMS_TRACK_VOERSPEED_60			316		//轨迹超过限速60KM/S, alarmInfo:超速率 （放大100倍数） param[0]:超速时长(秒) param[1]：最大速度
#define GPS_ALARM_TYPE_CMS_TRACK_VOERSPEED_70			317		//轨迹超过限速70KM/S, alarmInfo:超速率（放大100倍数）  param[0]:超速时长(秒) param[1]：最大速度
#define GPS_ALARM_TYPE_CMS_TRACK_VOERSPEED_80			318		//轨迹超过限速80KM/S, alarmInfo:超速率 （放大100倍数） param[0]:超速时长(秒) param[1]：最大速度
#define GPS_ALARM_TYPE_CMS_TRACK_VOERSPEED_90			319		//轨迹超过限速90KM/S, alarmInfo:超速率 （放大100倍数） param[0]:超速时长(秒) param[1]：最大速度
#define GPS_ALARM_TYPE_CMS_TRACK_VOERSPEED_100			320		//轨迹超过限速100KM/S, alarmInfo:超速率（放大100倍数）  param[0]:超速时长(秒) param[1]：最大速度
#define GPS_ALARM_TYPE_CMS_TRACK_VOERSPEED_110			321		//轨迹超过限速110KM/S, alarmInfo:超速率 （放大100倍数） param[0]:超速时长(秒) param[1]：最大速度
#define GPS_ALARM_TYPE_CMS_TRACK_VOERSPEED_120			322		//轨迹超过限速120KM/S, alarmInfo:超速率 （放大100倍数） param[0]:超速时长(秒) param[1]：最大速度
#define GPS_ALARM_TYPE_CMS_TRACK_VOERSPEED_30			323		//轨迹超过限速30KM/S, alarmInfo:超速率 （放大100倍数） param[0]:超速时长(秒) param[1]：最大速度
#define GPS_ALARM_TYPE_CMS_TRACK_VOERSPEED_35			324		//轨迹超过限速35KM/S, alarmInfo:超速率 （放大100倍数） param[0]:超速时长(秒) param[1]：最大速度
#define GPS_ALARM_TYPE_CMS_TRACK_VOERSPEED_40			325		//轨迹超过限速40KM/S, alarmInfo:超速率 （放大100倍数） param[0]:超速时长(秒) param[1]：最大速度
#define GPS_ALARM_TYPE_CMS_ACC_SIGNAL_ABNORMAL			326		//ACC信号异常报警(平台)   param[0] 持续时间阈值  param[1]速度阈值
#define GPS_ALARM_TYPE_CMS_LOCATION_REPORT_ABNORMAL		327		//位置信息上报异常报警(平台)   param[0]持续时间阈值)
#define GPS_ALARM_TYPE_CMS_ABNORMAL_OFFLINE				328		//车辆长时异常离线提醒(平台)   param[0]持续时间阈值
#define GPS_ALARM_TYPE_CMS_809_DISCONNECT				329		//809连接断开报警(平台)
#define GPS_EVENT_TYPE_CMS_TACHOGRAPH_DATA				330		//行驶记录仪数据	alarmInfo:采集命令字 格式为年份(2位)+命令(位)  如:0302表示2003的命令02
#define GPS_EVENT_TYPE_CMS_OPERATIONAL_STATUS			331		//运营状态变化事件 alarmInfo:0=运营状态 1=停运状态

#define GPS_ALARM_TYPE_END_CMS_AREA_OVERSPEED			350		//区域超速报警(平台) param[0]-位置类型 param[1]-区域或者线路ID param[2]-速度阀值	
#define GPS_ALARM_TYPE_END_CMS_AREA_LOWSPEED			351		//区域低速报警(平台) param[0]-位置类型 param[1]-区域或者线路ID param[2]-速度阀值
#define GPS_ALARM_TYPE_END_CMS_AREA_INOUT				352		//进出区域报警(平台)	 param[0]-位置类型 param[1]-区域或者线路ID param[2]-0:进1:出	
#define GPS_ALARM_TYPE_END_CMS_LINE_INOUT				353		//线路偏移(平台)	 param[0]-位置类型 param[1]-区域或者线路ID param[2]-0:进1:出
#define GPS_ALARM_TYPE_END_CMS_OVERSPEED				354		//时间段超速报警(平台)
#define GPS_ALARM_TYPE_END_CMS_LOWSPEED					355		//时间段低速报警(平台)
#define GPS_ALARM_TYPE_END_CMS_FATIGUE					356		//疲劳驾驶(平台)
#define	GPS_ALARM_TYPE_END_CMS_PARK_TOO_LONG			357		//超时停车(平台)
#define GPS_ALARM_TYPE_END_CMS_AREA_POINT				358		//关键点监控报警(平台)	param[0]-位置类型 param[1]-区域或者线路ID param[2]-0:未到达1:未离开
#define GPS_ALARM_TYPE_END_CMS_LINE_OVERSPEED			359		//线路超速报警(平台) param[0]-位置类型 param[1]-线路ID param[2]-速度阀值
#define GPS_ALARM_TYPE_END_CMS_LINE_LOWSPEED			360		//线路低速报警(平台) param[0]-位置类型 param[1]-线路ID param[2]-速度阀值
#define GPS_ALARM_TYPE_END_CMS_ROAD_LVL_OVERSPEED		361		//道路等级超速报警(平台) param[0]-道路等级 param[1]-市标志 param[2]-速度阀值
#define GPS_ALARM_TYPE_END_CMS_GPS_DRIFT				362		//GPS漂移(平台) 
#define GPS_ALARM_TYPE_END_CMS_TRACK_DISCON				363		//轨迹不连续报警(平台) 
#define GPS_ALARM_TYPE_END_CMS_NIGHT_OVERSEPED 			364	    //夜间超速 (平台)  param[0]当前超速限速值
#define GPS_ALARM_TYPE_END_CMS_TRACK_VOERSPEED_50		365		//轨迹超过限速50KM/S, alarmInfo:超速率（放大100倍数）   param[0]:超速时长(秒) param[1]：最大速度
#define GPS_ALARM_TYPE_END_CMS_TRACK_VOERSPEED_60		366		//轨迹超过限速60KM/S, alarmInfo:超速率 （放大100倍数）  param[0]:超速时长(秒)	param[1]：最大速度
#define GPS_ALARM_TYPE_END_CMS_TRACK_VOERSPEED_70		367		//轨迹超过限速70KM/S, alarmInfo:超速率（放大100倍数）   param[0]:超速时长(秒)	param[1]：最大速度
#define GPS_ALARM_TYPE_END_CMS_TRACK_VOERSPEED_80		368		//轨迹超过限速80KM/S, alarmInfo:超速率 （放大100倍数）  param[0]:超速时长(秒)	param[1]：最大速度
#define GPS_ALARM_TYPE_END_CMS_TRACK_VOERSPEED_90		369		//轨迹超过限速90KM/S, alarmInfo:超速率 （放大100倍数）  param[0]:超速时长(秒)	param[1]：最大速度
#define GPS_ALARM_TYPE_END_CMS_TRACK_VOERSPEED_100		370		//轨迹超过限速100KM/S, alarmInfo:超速率（放大100倍数）   param[0]:超速时长(秒) param[1]：最大速度
#define GPS_ALARM_TYPE_END_CMS_TRACK_VOERSPEED_110		371		//轨迹超过限速110KM/S, alarmInfo:超速率 （放大100倍数）  param[0]:超速时长(秒) param[1]：最大速度
#define GPS_ALARM_TYPE_END_CMS_TRACK_VOERSPEED_120		372		//轨迹超过限速120KM/S, alarmInfo:超速率 （放大100倍数）  param[0]:超速时长(秒) param[1]：最大速度
#define GPS_ALARM_TYPE_END_CMS_TRACK_VOERSPEED_30		373		//轨迹超过限速30KM/S, alarmInfo:超速率 （放大100倍数） param[0]:超速时长(秒) param[1]：最大速度
#define GPS_ALARM_TYPE_END_CMS_TRACK_VOERSPEED_35		374		//轨迹超过限速35KM/S, alarmInfo:超速率 （放大100倍数） param[0]:超速时长(秒) param[1]：最大速度
#define GPS_ALARM_TYPE_END_CMS_TRACK_VOERSPEED_40		375		//轨迹超过限速40KM/S, alarmInfo:超速率 （放大100倍数） param[0]:超速时长(秒) param[1]：最大速度
#define GPS_ALARM_TYPE_END_CMS_ACC_SIGNAL_ABNORMAL		376		//ACC信号异常报警(平台)    param[0] 持续时间阈值  param[1]速度阈值   
#define GPS_ALARM_TYPE_END_CMS_LOCATION_REPORT_ABNORMAL	377		//位置信息上报异常报警(平台)  param[0]持续时间阈值
#define GPS_ALARM_TYPE_END_CMS_ABNORMAL_OFFLINE			378		//车辆长时异常离线提醒(平台)   param[0]持续时间阈值
	
#define GPS_ALARM_TYPE_END_CMS_809_DISCONNECT			379		//809连接断开报警(平台)



#define GPS_ALARM_TYPE_FCW								400		//前车碰撞预警
#define GPS_ALARM_TYPE_LDW								401		//道路偏离预警
#define GPS_ALARM_TYPE_PCW								402		//行人检测预警
#define GPS_ALARM_TYPE_DRIVER_MASK						403		//驾驶员遮挡或镜头偏离位置
#define GPS_ALARM_TYPE_NO_ELR							404		//不系安全带
#define GPS_ALARM_TYPE_ADS_DEV_ERR						405		//设备故障
#define	GPS_ALARM_TYPE_NEAR_CAR							406		//车距近
#define GPS_ALARM_TYPE_BRAK								407		//急刹车
#define GPS_ALARM_TYPE_RAPID_TURNLEFT					408		//急左转弯
#define GPS_ALARM_TYPE_RAPID_TURNRIGHT					409		//急右转弯
#define GPS_ALARM_TYPE_HEAD_DOWN						410		//低头
#define GPS_ALARM_TYPE_NO_CARD							411		//未插卡
#define GPS_ALARM_TYPE_UNRECOGNIZED_CARD				412		//无法识别卡
#define GPS_ALARM_TYPE_NOT_REST_DRIVE					413		//未复位行车
#define GPS_ALARM_TYPE_WROKTIME							414		//工作时长
#define GPS_ALARM_TYPE_SIMCARD_ABNORMAL					415		//SIM卡异常
#define GPS_ALARM_TYPE_HOST_FORCIBLY_REMOVE				416		//主机强制拆除
#define GPS_ALARM_TYPE_CTRL_FORCIBLY_REMOVE				417		//管制器强制拆除
#define GPS_ALARM_TYPE_FACE_CAPTURE_ABNORMAL			418		//人脸抓拍摄像头异常
#define GPS_ALARM_TYPE_ILLEGAL_STARTUP					419		//非法启动
#define GPS_ALARM_TYPE_OFTEN_NOT_TURN_LIGHT				420		//频繁不打转向灯
#define GPS_ALARM_TYPE_HIT_PEDESTRIAN					421		//撞击行人
#define GPS_ALARM_TYPE_HIT_VEHICLE						422		//撞击车辆
#define GPS_ALARM_TYPE_HIT_PURPOSELY					423		//有意撞击
#define GPS_ALARM_TYPE_HIT_ACCIDENTAL					424		//无意撞击
#define GPS_ALARM_TYPE_KEY_CTRL							425		//管制
#define GPS_ALARM_TYPE_NORMAL_MODE						426		//固定模式
#define GPS_ALARM_TYPE_SHAKE_MODE						427		//振动模式
#define GPS_ALARM_TYPE_OVERSPEED_WARNING				428		//超速预警
#define GPS_ALARM_TYPE_FATIGUE_WARNING					429		//疲劳驾驶预警
#define GPS_ALARM_TYPE_FORWARD_COLLISION_WARNING		430		//前撞预警
#define GPS_ALARM_TYPE_LANE_OFFSET_WARNING				431		//车道偏移预警
#define GPS_ALARM_TYPE_TIRE_WARNING						432		//胎压预警
#define GPS_ALARM_TYPE_ROLLOVER_WARNING					433		//侧翻预警
#define GPS_ALARM_TYPE_ENGINE_WORK_TIME					434		//发动机工作时长
#define GPS_ALARM_TYPE_GSENSOR_INFO						435		//G-Sensor报警数据(定制,不用解析)
#define GPS_ALARM_TYPE_HARD_DISK_ERROR					436		//磁盘坏道故障报警 param[0] 当前故障磁盘 1=磁盘1 ,2=磁盘2
#define GPS_ALARM_TYPE_UPGRADE_SUCCESS					437		//升级成功报警
#define GPS_ALARM_TYPE_FORMAT_SUCCESS					438		//格式化成功报警 param[0] 当前格式化成功磁盘 1=磁盘1 ,2=磁盘2
#define GPS_ALARM_TYPE_GSENSOR_START					439		//GSensor启动
#define GPS_ALARM_TYPE_GSENSOR_STOP						440		//GSensor停止
#define GPS_ALARM_TYPE_GSENSOR_ROLLOVER					441		//GSensor侧翻
#define GPS_ALARM_TYPE_DRIVER_SIGN						442		//司机刷卡		szDesc: 司机名称;发证机关;身份证号;从业资格证编码		param4为司机id
#define GPS_ALARM_TYPE_STUDENT_SIGN						443		//学生刷卡		szDesc: 姓名;班级;学号;卡号
#define GPS_ALARM_TYPE_GSENSOR_SHARPTURN				444		//GSensor急转弯


#define GPS_ALARM_TYPE_END_FCW							450		//前车碰撞预警
#define GPS_ALARM_TYPE_END_LDW							451		//道路偏离预警
#define GPS_ALARM_TYPE_END_PCW							452		//行人检测预警
#define GPS_ALARM_TYPE_END_DRIVER_MASK					453		//驾驶员遮挡或镜头偏离位置
#define GPS_ALARM_TYPE_END_NO_ELR						454		//不系安全带
#define GPS_ALARM_TYPE_END_ADS_DEV_ERR					455		//设备故障
#define	GPS_ALARM_TYPE_END_NEAR_CAR						456		//车距近
#define GPS_ALARM_TYPE_END_BRAK							457		//急刹车
#define GPS_ALARM_TYPE_END_RAPID_TURNLEFT				458		//急左转弯
#define GPS_ALARM_TYPE_END_RAPID_TURNRIGHT				459		//急右转弯
#define GPS_ALARM_TYPE_END_HEAD_DOWN					460		//低头
#define GPS_ALARM_TYPE_END_NO_CARD						461		//未插卡
#define GPS_ALARM_TYPE_END_UNRECOGNIZED_CARD			462		//无法识别卡
#define GPS_ALARM_TYPE_END_NOT_REST_DRIVE				463		//未复位行车
#define GPS_ALARM_TYPE_END_WROKTIME						464		//工作时长
#define GPS_ALARM_TYPE_END_SIMCARD_ABNORMAL				465		//SIM卡异常
#define GPS_ALARM_TYPE_END_HOST_FORCIBLY_REMOVE			466		//主机强制拆除
#define GPS_ALARM_TYPE_END_CTRL_FORCIBLY_REMOVE			467		//管制器强制拆除
#define GPS_ALARM_TYPE_END_FACE_CAPTURE_ABNORMAL		468		//人脸抓拍摄像头异常
#define GPS_ALARM_TYPE_END_ILLEGAL_STARTUP				469		//非法启动
#define GPS_ALARM_TYPE_END_OFTEN_NOT_TURN_LIGHT			470		//频繁不打转向灯
#define GPS_ALARM_TYPE_END_HIT_PEDESTRIAN				471		//撞击行人
#define GPS_ALARM_TYPE_END_HIT_VEHICLE					472		//撞击车辆
#define GPS_ALARM_TYPE_END_HIT_PURPOSELY				473		//有意撞击
#define GPS_ALARM_TYPE_END_HIT_ACCIDENTAL				474		//无意撞击
#define GPS_ALARM_TYPE_END_KEY_CTRL						475		//管制
#define GPS_ALARM_TYPE_END_NORMAL_MODE					476		//固定模式
#define GPS_ALARM_TYPE_END_SHAKE_MODE					477		//振动模式
#define GPS_ALARM_TYPE_END_OVERSPEED_WARNING			478		//超速预警
#define GPS_ALARM_TYPE_END_FATIGUE_WARNING				479		//疲劳驾驶预警
#define GPS_ALARM_TYPE_END_FORWARD_COLLISION_WARNING	480		//前撞预警
#define GPS_ALARM_TYPE_END_LANE_OFFSET_WARNING			481		//车道偏移预警
#define GPS_ALARM_TYPE_END_TIRE_WARNING					482		//胎压预警
#define GPS_ALARM_TYPE_END_ROLLOVER_WARNING				483		//侧翻预警
#define GPS_ALARM_TYPE_END_ENGINE_WORK_TIME				484		//发动机工作时长
#define GPS_ALARM_TYPE_END_GSENSOR_INFO					485		//G-Sensor报警数据(定制,不用解析)
#define GPS_ALARM_TYPE_END_HARD_DISK_ERROR				486		//磁盘坏道故障报警
#define GPS_ALARM_TYPE_END_GSENSOR_START				489		//GSensor启动
#define GPS_ALARM_TYPE_END_GSENSOR_STOP					490		//GSensor停止
#define GPS_ALARM_TYPE_END_GSENSOR_ROLLOVER				491		//GSensor侧翻
#define GPS_ALARM_TYPE_END_DRIVER_SIGN					492		//司机刷卡		szDesc: 司机名称;发证机关;身份证号;从业资格证编码
#define GPS_ALARM_TYPE_END_STUDENT_SIGN					493		//学生刷卡		szDesc: 学生姓名;班级;学号
#define GPS_ALARM_TYPE_END_GSENSOR_SHARPTURN			494		//GSensor急转弯

// 苏标部分报警(600-649)
// 统一说明:设备上报报警desc存储报警标识号(SBAC=...),Param[3]:司机ID,其他参数如下定义
// ADAS(高级驾驶辅助系统)
#define GPS_ALARM_TYPE_SB_L1_FCW							600		//前向碰撞报警1级 //Param[0]:道路标志识别数据,Param[1]:前车车速,Param[2]:前车/行人距离
#define GPS_ALARM_TYPE_SB_L2_FCW							601		//前向碰撞报警2级 //
#define GPS_ALARM_TYPE_SB_L1_LDW							602		//车道偏离报警1级 //Param[0]:道路标志识别数据,Param[1](低16位):前车车速,Param[1](高16位):前车/行人距离,Param[2]:偏离类型
#define GPS_ALARM_TYPE_SB_L2_LDW							603		//车道偏离报警2级 //
#define GPS_ALARM_TYPE_SB_L1_NEAR_CAR						604		//车距过近报警1级 //Param[0]:道路标志识别数据
#define GPS_ALARM_TYPE_SB_L2_NEAR_CAR						605		//车距过近报警2级 //
#define GPS_ALARM_TYPE_SB_L1_HIT_PEDESTRIAN					606		//行人碰撞报警1级 //Param[0]:道路标志识别数据,Param[1]:前车/行人距离
#define GPS_ALARM_TYPE_SB_L2_HIT_PEDESTRIAN					607		//行人碰撞报警2级 //
#define GPS_ALARM_TYPE_SB_L1_FREQUENT_LANE_CHANGE			608     //频繁变道 1级 //Param[0]:道路标志识别数据
#define GPS_ALARM_TYPE_SB_L2_FREQUENT_LANE_CHANGE			609     //频繁变道 2级 //
#define GPS_ALARM_TYPE_SB_L1_ROAD_MARKING_OVER_LIMIT		610     //道路标识超限报警 1级 //Param[0]:道路标志识别数据,Param[1]:道路标志识别类型
#define GPS_ALARM_TYPE_SB_L2_ROAD_MARKING_OVER_LIMIT		611     //道路标识超限报警 2级 //
#define GPS_ALARM_TYPE_SB_L1_OBSTACLE						612     //障碍物报警 1级 //Param[0]:道路标志识别数据
#define GPS_ALARM_TYPE_SB_L2_OBSTACLE						613     //障碍物报警 2级 //
#define GPS_EVENT_TYPE_SB_L1_ROAD_SIGN_RECOGNITION    		614     //道路标志识别事件 1级 //Param[0]:道路标志识别数据,Param[1]:道路标志识别类型
#define GPS_EVENT_TYPE_SB_L2_ROAD_SIGN_RECOGNITION    		615     //道路标志识别事件 2级 //
#define GPS_EVENT_TYPE_SB_L1_ACTIVE_CAPTURE           		616     //主动抓拍事件 1级 //Param[0]:道路标志识别数据
#define GPS_EVENT_TYPE_SB_L2_ACTIVE_CAPTURE           		617     //主动抓拍事件 2级 //
// DSM(驾驶员状态监控系统)
#define GPS_ALARM_TYPE_SB_L1_FATIGUE_DRIVING 				618		//疲劳驾驶报警 1级 //param[0]:疲劳程度 0-10
#define GPS_ALARM_TYPE_SB_L2_FATIGUE_DRIVING 				619		//疲劳驾驶报警 2级 //
#define GPS_ALARM_TYPE_SB_L1_ANSWER_THE_CALL                620     //接打电话报警 1级 //
#define GPS_ALARM_TYPE_SB_L2_ANSWER_THE_CALL                621		//接打电话报警 2级 //
#define GPS_ALARM_TYPE_SB_L1_SMOKING                        622     //抽烟报警 1级 //
#define GPS_ALARM_TYPE_SB_L2_SMOKING                        623     //抽烟报警 2级 //
#define GPS_ALARM_TYPE_SB_L1_DISTRACTED_DRIVING             624     //分神驾驶报警 1级 //
#define GPS_ALARM_TYPE_SB_L2_DISTRACTED_DRIVING             625     //分神驾驶报警 2级 //
#define GPS_ALARM_TYPE_SB_L1_DRIVER_ABNORMAL                626     //驾驶员异常报警 1级 //
#define GPS_ALARM_TYPE_SB_L2_DRIVER_ABNORMAL                627     //驾驶员异常报警 2级 //
#define GPS_EVENT_TYPE_SB_L1_AUTO_CAPTURE                   628     //自动抓拍事件 1级 //
#define GPS_EVENT_TYPE_SB_L2_AUTO_CAPTURE                   629     //自动抓拍事件 2级 //
#define GPS_EVENT_TYPE_SB_L1_DRIVER_CHANGE                  630     //驾驶员变更事件 1级 //
#define GPS_EVENT_TYPE_SB_L2_DRIVER_CHANGE                  631     //驾驶员变更事件 2级 //
// TPMS(轮胎气压监测系统)
#define GPS_ALARM_TYPE_SB_TPMS								632		//胎压报警(苏标) AlarmInfo:bit0：胎压（定时上报） bit1：胎压过高报警 bit2：胎压过低报警 
																	//bit3：胎温过高报警 bit4：传感器异常报警 bit5：胎压不平衡报警 bit6：慢漏气报警
																	//bit7：电池电量低报警 bit8~bit15：自定义 
																	//Param[0]:胎压(单位 Kpa)
																	//Param[1](低16位):胎温(单位 ℃),Param[1](高16位):电池电量(单位 %)
																	//Param[2]:传感器编号（01表示TPMS左1，02表示TPMS左2，03表示TPMS左3，04表示TPMS左4，11表示TPMS右1，12表示TPMS右2，13表示TPMS右3，14表示TPMS右4）
// BSD(盲点监测系统)
#define GPS_ALARM_TYPE_SB_REAR_PROXIMITY               		633     //后方接近报警
#define GPS_ALARM_TYPE_SB_REAR_LEFT_CLOSE              		634     //左侧后方接近报警
#define GPS_ALARM_TYPE_SB_REAR_RIGHT_CLOSE             		635     //右侧后方接近报警
//其他
#define GPS_EVENT_TYPE_SB_DRIVER_IDENTIFICATION				636		//驾驶员识别事件 AlarmInfo:0:识别失败 1:识别成功 2:无法识别 3:比对失败
#define GPS_ALARM_TYPE_CMS_SB_L2_DISTRACTED_DRIVING			637		//分神驾驶报警 2级(平台)
#define GPS_EVENT_TYPE_SB_UPLOAD_FINISH						638		//苏标附件上传完成事件 desc:报警guid srcAlarmType:苏标报警类型  srcType:苏标报警时间

// DSM(中天定制)
#define GPS_ALARM_TYPE_L1_SUNGLASSES_FAILURE				639		//墨镜失效一级报警
#define GPS_ALARM_TYPE_L2_SUNGLASSES_FAILURE				640		//墨镜失效二级报警

//DSM(陕标增加)
#define GPS_ALARM_TYPE_SB_L1_DRIVER_IC_ABNORMAL             641     //驾驶员 IC 卡异常报警 1级 //
#define GPS_ALARM_TYPE_SB_L2_DRIVER_IC_ABNORMAL             642     //驾驶员 IC 卡异常报警 2级 //
#define GPS_EVENT_TYPE_SB_L1_DRIVER_IDENT                   643     //驾驶员身份识别事件


// ADAS
#define GPS_ALARM_TYPE_END_SB_L1_FCW						650		//前向碰撞报警1级
#define GPS_ALARM_TYPE_END_SB_L2_FCW						651		//前向碰撞报警2级
#define GPS_ALARM_TYPE_END_SB_L1_LDW						652		//车道偏离报警1级
#define GPS_ALARM_TYPE_END_SB_L2_LDW						653		//车道偏离报警2级
#define GPS_ALARM_TYPE_END_SB_L1_NEAR_CAR					654		//车距过近报警1级
#define GPS_ALARM_TYPE_END_SB_L2_NEAR_CAR					655		//车距过近报警2级
#define GPS_ALARM_TYPE_END_SB_L1_HIT_PEDESTRIAN				656		//行人碰撞报警1级
#define GPS_ALARM_TYPE_END_SB_L2_HIT_PEDESTRIAN				657		//行人碰撞报警2级
#define GPS_ALARM_TYPE_END_SB_L1_FREQUENT_LANE_CHANGE		658     //频繁变道 1级
#define GPS_ALARM_TYPE_END_SB_L2_FREQUENT_LANE_CHANGE		659     //频繁变道 2级
#define GPS_ALARM_TYPE_END_SB_L1_ROAD_MARKING_OVER_LIMIT	660     //道路标识超限报警 1级
#define GPS_ALARM_TYPE_END_SB_L2_ROAD_MARKING_OVER_LIMIT	661     //道路标识超限报警 2级
#define GPS_ALARM_TYPE_END_SB_L1_OBSTACLE					662     //障碍物报警 1级
#define GPS_ALARM_TYPE_END_SB_L2_OBSTACLE					663     //障碍物报警 2级
// DSM
#define GPS_ALARM_TYPE_END_SB_L1_FATIGUE_DRIVING 			668		//疲劳驾驶报警 1级
#define GPS_ALARM_TYPE_END_SB_L2_FATIGUE_DRIVING 			669		//疲劳驾驶报警 2级
#define GPS_ALARM_TYPE_END_SB_L1_ANSWER_THE_CALL            670     //接打电话报警 1级
#define GPS_ALARM_TYPE_END_SB_L2_ANSWER_THE_CALL            671		//接打电话报警 2级
#define GPS_ALARM_TYPE_END_SB_L1_SMOKING                    672     //抽烟报警 1级
#define GPS_ALARM_TYPE_END_SB_L2_SMOKING                    673     //抽烟报警 2级
#define GPS_ALARM_TYPE_END_SB_L1_DISTRACTED_DRIVING         674     //分神驾驶报警 1级
#define GPS_ALARM_TYPE_END_SB_L2_DISTRACTED_DRIVING         675     //分神驾驶报警 2级
#define GPS_ALARM_TYPE_END_SB_L1_DRIVER_ABNORMAL            676     //驾驶员异常报警 1级
#define GPS_ALARM_TYPE_END_SB_L2_DRIVER_ABNORMAL            677     //驾驶员异常报警 2级
// TPMS
#define GPS_ALARM_TYPE_END_SB_TPMS							682		//胎压报警(苏标)
// BSD
#define GPS_ALARM_TYPE_END_SB_REAR_PROXIMITY               	683     //后方接近报警,desc(非苏标为空):报警标识号
#define GPS_ALARM_TYPE_END_SB_REAR_LEFT_CLOSE              	684     //左侧后方接近报警,desc(非苏标为空):报警标识号
#define GPS_ALARM_TYPE_END_SB_REAR_RIGHT_CLOSE             	685     //右侧后方接近报警,desc(非苏标为空):报警标识号
//其他
#define GPS_ALARM_TYPE_END_CMS_SB_L2_DISTRACTED_DRIVING		687		//分神驾驶报警 2级(平台)
// DSM(中天定制)
#define GPS_ALARM_TYPE_END_L1_SUNGLASSES_FAILURE			689		//墨镜失效一级报警
#define GPS_ALARM_TYPE_END_L2_SUNGLASSES_FAILURE			690		//墨镜失效二级报警

//DSM(陕标增加)
#define GPS_ALARM_TYPE_END_SB_L1_DRIVER_IC_ABNORMAL             691     //驾驶员 IC 卡异常报警 1级 //
#define GPS_ALARM_TYPE_END_SB_L2_DRIVER_IC_ABNORMAL             692     //驾驶员 IC 卡异常报警 2级 //
#define GPS_EVENT_TYPE_END_SB_L1_DRIVER_IDENT                   693     //驾驶员身份识别事件


//ADAS(交通部)
#define GPS_ALARM_TYPE_SB_L1_CURVE_SPEED_WARNING			700		//弯道车速预警1级
#define GPS_ALARM_TYPE_SB_L2_CURVE_SPEED_WARNING			701		//弯道车速预警2级
//DSM(交通部)
#define GPS_ALARM_TYPE_SB_L1_NOT_LOOK_AHEAD_LONG_TIME		702		//长时间不目视前方报警1级
#define GPS_ALARM_TYPE_SB_L2_NOT_LOOK_AHEAD_LONG_TIME		703		//长时间不目视前方报警2级
#define GPS_ALARM_TYPE_SB_L1_SYSTEM_NOT_WORKING_PROPERLY	704		//系统不能正常工作报警1级
#define GPS_ALARM_TYPE_SB_L2_SYSTEM_NOT_WORKING_PROPERLY	705		//系统不能正常工作报警2级
#define GPS_ALARM_TYPE_SB_L1_DRIVER_NOT_WEARING_ASEATBELT	706		//驾驶员未系安全带报警1级
#define GPS_ALARM_TYPE_SB_L2_DRIVER_NOT_WEARING_ASEATBELT	707		//驾驶员未系安全带报警2级
#define GPS_ALARM_TYPE_SB_L1_DRIVER_NOT_SEAT				708		//驾驶员不在驾驶位报警1级
#define GPS_ALARM_TYPE_SB_L2_DRIVER_NOT_SEAT				709		//驾驶员不在驾驶位报警2级
#define GPS_ALARM_TYPE_SB_L1_DRIVER_HANDS_OFF_WHEEL			710		//驾驶员双手脱离方向盘报警1级
#define GPS_ALARM_TYPE_SB_L2_DRIVER_HANDS_OFF_WHEEL			711		//驾驶员双手脱离方向盘报警2级
#define GPS_ALARM_TYPE_IC_MODULE_FAILURE					712		//道路运输证IC卡模块故障
#define GPS_ALARM_TYPE_DRIVING_VIOLATIONS					713		//违规行驶
#define GPS_ALARM_TYPE_RIGHT_TURN_BLIND_ZONE_ANOMALY		714		//右转盲区异常报警


//ADAS(交通部)
#define GPS_ALARM_TYPE_END_SB_L1_CURVE_SPEED_WARNING			750		//弯道车速预警1级
#define GPS_ALARM_TYPE_END_SB_L2_CURVE_SPEED_WARNING			751		//弯道车速预警2级
//DSM(交通部)
#define GPS_ALARM_TYPE_END_SB_L1_NOT_LOOK_AHEAD_LONG_TIME		752		//长时间不目视前方报警1级
#define GPS_ALARM_TYPE_END_SB_L2_NOT_LOOK_AHEAD_LONG_TIME		753		//长时间不目视前方报警2级
#define GPS_ALARM_TYPE_END_SB_L1_SYSTEM_NOT_WORKING_PROPERLY	754		//系统不能正常工作报警1级
#define GPS_ALARM_TYPE_END_SB_L2_SYSTEM_NOT_WORKING_PROPERLY	755		//系统不能正常工作报警2级
#define GPS_ALARM_TYPE_END_SB_L1_DRIVER_NOT_WEARING_ASEATBELT	756		//驾驶员未系安全带报警1级
#define GPS_ALARM_TYPE_END_SB_L2_DRIVER_NOT_WEARING_ASEATBELT	757		//驾驶员未系安全带报警2级
#define GPS_ALARM_TYPE_END_SB_L1_DRIVER_NOT_SEAT				758		//驾驶员不在驾驶位报警1级
#define GPS_ALARM_TYPE_END_SB_L2_DRIVER_NOT_SEAT				759		//驾驶员不在驾驶位报警2级
#define GPS_ALARM_TYPE_END_SB_L1_DRIVER_HANDS_OFF_WHEEL			760		//驾驶员双手脱离方向盘报警1级
#define GPS_ALARM_TYPE_END_SB_L2_DRIVER_HANDS_OFF_WHEEL			761		//驾驶员双手脱离方向盘报警2级
#define GPS_ALARM_TYPE_END_IC_MODULE_FAILURE					762		//道路运输证IC卡模块故障
#define GPS_ALARM_TYPE_END_DRIVING_VIOLATIONS					763		//违规行驶
#define GPS_ALARM_TYPE_END_RIGHT_TURN_BLIND_ZONE_ANOMALY		764		//右转盲区异常报警


//自定义报警类型子类型定义 GPS_ALARM_TYPE_CUSTOM(113)
#define CUSTOM_ALARM_TYPE_PLATE					1	//车牌识别
#define CUSTOM_ALARM_TYPE_PRESON				2	//人脸识别
#define CUSTOM_ALARM_TYPE_EMPTY_PASSENGER		3	//空载
#define CUSTOM_ALARM_TYPE_LOAD_PASSENGER		4	//负载
#define CUSTOM_ALARM_TYPE_FENCE_ACC_SPPED		5	//电子围栏外,AAC开,速度0,报警
#define CUSTOM_ALARM_TYPE_TTS_REPLY				6	//tts回复
#define CUSTOM_ALARM_TYPE_OFF_ROUTE				7	//偏离线路,PAD上传报警
#define CUSTOM_ALARM_TYPE_TASK_FAILED			8	//任务失败,PAD上传报警
#define CUSTOM_ALARM_TYPE_TASK_FINISHED			9	//任务完成,PAD上传报警
#define CUSTOM_ALARM_TYPE_ALARM_ACTION			10	//报警联动
#define CUSTOM_ALARM_TYPE_START_ACC_SPEED5		11	//ACC信号有效、车速低于5公里/小时 报警开始
#define CUSTOM_ALARM_TYPE_END_ACC_SPEED5		12	//ACC信号有效、车速低于5公里/小时 报警结束
#define CUSTOM_ALARM_TYPE_START_SPPED0_IO3		13	//ACC信号有效、车速为0时、搅拌车的滚筒状态反转(IO_3) 报警开始
#define CUSTOM_ALARM_TYPE_END_SPPED0_IO3		14	//ACC信号有效、车速为0时、搅拌车的滚筒状态反转(IO_3) 报警结束

#define CUSTOM_ALARM_TYPE_EVENT_REPORT			15	//事件报告
#define CUSTOM_ALARM_TYPE_INFO_DEMAND			16	//信息点播
#define CUSTOM_ALARM_TYPE_ELECTRONIC_WAYBILL	17	//电子运单
#define CUSTOM_ALARM_TYPE_COMPRESS_DATA			18	//数据压缩上报
#define CUSTOM_ALARM_TYPE_OFL_TASK				19	//离线任务通知
#define CUSTOM_ALARM_TYPE_MEDIA_EVETN			20	//多媒体事件信息

//809查岗消息需要在客户端弹框显示，收到用户反馈后，再返回到上级平台
//回复时需要将查岗消息ID回复到客户端
// 	GPSVehicleAlarm_S VehiAlarm = {0};
// 	STRINGGenerateGUID(VehiAlarm.Alarm.guid);
//	strncpy(VehiAlarm.szDevIDNO, NETLOGIN_GetIDNO(), sizeof(VehiAlarm.szDevIDNO) - 1);
//	VehiAlarm.Alarm.AlarmType = GPS_ALARM_TYPE_CUSTOM;
//	VehiAlarm.Alarm.AlarmInfo = nAlarmInfo;
//	VehiAlarm.Alarm.Param[0] = pInfo->nObjType;
//	VehiAlarm.Alarm.Param[1] = pInfo->nMsgID;
//	VehiAlarm.Alarm.Param[2] = strlen(pInfo->szContent);
//	strncpy(VehiAlarm.Alarm.szDesc, pInfo->szObjID, sizeof(VehiAlarm.Alarm.szDesc) - 1);
//	strncpy(VehiAlarm.Alarm.szImgFile, pInfo->szContent, sizeof(VehiAlarm.Alarm.szImgFile) - 1);
#define CUSTOM_ALARM_TYPE_809_PLATFORM_POST_QUERY	21	//809查岗信息
//		上级平台 ---》下级平台	平台查岗消息
//szDevIDNO：网关服务器编号
//Param1：查岗对象类型
//Param2：查岗消息ID
//szDesc：对象ID|平台名称;服务器ID;报警时间
//szImgFile：查询信息内容
// 对象类型		
// 0x00  下级平台所属单一平台
// 0X01  当前连接的下级平台，由平台行政区划代码和平台唯一编码组成；
// 0X02  下级平台所属单一业户；为业户经营许可证号  
// 0X03  下级平台所属所有业户
// 0X04  下级平台所有平台
// 0X05  下级平台所有平台和业户
// 0X06  下级平台所有政府监管平台（含监控端）
// 0X07  下级平台所有企业监控平台
// 0X08  下级平台所有经营性企业监控平台
// 0X09  下级平台所有非经营性企业监控平台

// 平台 --->> 平台
// Param1：查岗对象类型
// Param2：未使用
// Param3：未使用
// Param4：未使用
// szImgFile：查询信息内容
// 对象类型	
// 0xFE  通天星平台查岗,此查岗类型保证与标准定义不重复即可,宏定义GPS_CHECK_POST_TYPE_TTX


//以下为809相关的事件，需要在客户端上显示
// 	GPSVehicleAlarm_S VehiAlarm = {0};
// 	STRINGGenerateGUID(VehiAlarm.Alarm.guid);
// 	strncpy(VehiAlarm.szDevIDNO, szDevIDNO, sizeof(VehiAlarm.szDevIDNO) - 1);		//设备编号
// 	VehiAlarm.Alarm.AlarmType = GPS_ALARM_TYPE_CUSTOM;				
// 	VehiAlarm.Alarm.AlarmInfo = nAlarmType;		对应 为  CUSTOM_ALARM_TYPE_809_EVENT_MONITOR_START_UP 等			
// 	VehiAlarm.Alarm.Param[0] = nColor;			对应的车牌颜色		
// 	VehiAlarm.Alarm.Param[1] = nParam2;
// 	VehiAlarm.Alarm.bSendOnly = 1;
// 	strncpy(VehiAlarm.Alarm.szDesc, NETLOGIN_GetIDNO(), sizeof(VehiAlarm.Alarm.szDesc) - 1);		//网关服务器的编号
// 	strncpy(VehiAlarm.Alarm.szImgFile, szContent, sizeof(VehiAlarm.Alarm.szImgFile) - 1);			//
#define CUSTOM_ALARM_TYPE_809_EVENT_RETURN_START_UP					22	
//		上级平台 ---》下级平台	启动车辆定位数据交换
//		事件内容：	上级平台启动车辆定位信息交换请求消息:车牌=%s, 颜色=%d,交换原因：%s
//		参数：		nParam2：	交换原因		0：车辆进入指定区域		1：人工指定交换		2：应急状态下的车辆定位数据回传，3：其它原因
#define CUSTOM_ALARM_TYPE_809_EVENT_RETURN_END						23	
//		上级平台 ---》下级平台	停止车辆定位数据交换
//		事件内容：	上级平台停止车辆定位信息交换请求消息:车牌=%s, 颜色=%d,结束原因：%s
//		参数：		nParam2：	停止原因		//0：车辆离开指定区域		1：人工停止交换		2：紧急监控完成		3：其它原因		4：其它原因
#define CUSTOM_ALARM_TYPE_809_EVENT_MONITOR_START_UP_ASK			24	
//		上级平台 ---》下级平台	启动车辆定位数据交换应答
//		事件内容：	申请交换制定车辆定位消息应答消息:车牌=%s, 颜色=%d,结果：%s
//		参数：		nParam2：	结果	0：申请成功，1：上级没有该车的信息，2：申请时间段错误，3：其它
#define CUSTOM_ALARM_TYPE_809_EVENT_MONITOR_END_ASK					25	
//		上级平台 ---》下级平台	取消车辆定位数据交换应答
//		事件内容：	取消申请交换制定车辆定位信息应答消息:车牌=%s, 颜色=%d,结果：%s
//		参数：		nParam2：	0：取消申请成功，1：之前没有对应的该车的信息，2：其它
#define CUSTOM_ALARM_TYPE_809_EVENT_APPLY_HISGNSSDATA_ASK			26
//		上级平台 ---》下级平台	下级平台请求补传车辆静态数据应答
//		事件内容：	补发车辆定位信息应答消息:车牌=%s, 颜色=%d,结果：%s
//		参数：		nParam2：	//0：成功，上级平台立刻补发，1：成功，上级平台择机补发，2：失败，上级平台无对应申请定位数据，3：失败，申请内容不正确，4：其它原因
#define CUSTOM_ALARM_TYPE_809_EVENT_CAR_INFO						27
//		上级平台 ---》下级平台	车辆静态数据
//		事件内容：	交换车辆静态信息消息:车牌=%s,颜色=%d, 车辆静态信息:%s
//		参数：		szContent为车辆静态信息
#define CUSTOM_ALARM_TYPE_809_PLATFORM_INFO							28	//平台报文
//		上级平台 ---》下级平台	平台报文
//		和 CUSTOM_ALARM_TYPE_809_PLATFORM  数据内容定义一样
//		事件内容：	下发平台报文, 报文类型=%d, 信息ID=%d, 营运证号=%s, 信息内容=%s
#define CUSTOM_ALARM_TYPE_809_WARN_URGE_TODO						29	//报警督办
//		上级平台 ---》下级平台	报警督办，客户端需要弹框进行回复
//		事件内容：	报警督办请求消息 车辆=%s, 信息ID=%d, 信息源=%s, 督办级别=%s， 报警类型=%s,报警时间=%s, 督办期限=%s  督办人=%s,督办电话=%s, 督办Email=%s
//		参数：		param1：	中心ID
//					param2：	uiSuporVisionID		督办ID
//					param3：	低16位为  nWarnSrc报警源	1车载终端，2企业平台，3政府平台，9其它  
//							高16位为  usWarnType报警类型		
//								1  超速报警，2 疲劳驾驶报警，3 紧急报警，4 进入指定区域报警，5  离开指定区域报警	6  路段阻塞报警   7  危险路段报警	
//								8  越界		9 盗警		10  劫警	11   偏移路线    12  车辆移动    13  超时驾驶   FF  其它报警
//					param4：	uiSuporVisionLeve	报警督办级别		0紧急，1一般
//					szDesc		督办人;督办电话;督办Email|平台名称;服务器ID;报警时间
//					srcTime		报警时间
//					Gps.Time	报警督办截止时间
#define CUSTOM_ALARM_TYPE_809_WARN_INFORMTIPS						30	//报警预警消息
//		上级平台 ---》下级平台	报警预警消息
//		事件内容：	报警预警消息 车辆=%s, 颜色=%d, 信息来源=%s, 报警时间=%s, 报信信息=%s:%s
//		参数：		param1：	车牌颜色
//					param2：	低16位为  nWarnSrc报警源	1车载终端，2企业平台，3政府平台，9其它  
//							高16位为  usWarnType报警类型	
//					srcTime		报警时间
//					szDesc		报警信息内容
#define CUSTOM_ALARM_TYPE_809_WARN_EXG_INFO							31	//报警交换消息
//		上级平台 ---》下级平台	报警交换消息
//		和 CUSTOM_ALARM_TYPE_809_WARN_INFORMTIPS  数据内容定义一样
//		事件内容：	实时交换报警信息 车辆=%s, 信息来源=%s, 报警时间=%s, 报信信息=%s:%s
#define CUSTOM_ALARM_TYPE_809_CONN_MSG_INFO							32	//与上级平台的连接信息
//		上级平台 《---》下级平台	连接信息
//		参数：		szImgFile		连接信息内容，直接做显示即可以

#define CUSTOM_ALARM_TYPE_809_TORAL_RECV_BACK						 33	//定位信息数量通知
//		上级平台 《---》下级平台	定位信息数量通知
//		参数：		param1：	平台ID
//					param2：	接收到的GPS总数
//					srcTime:    开始时间
//					time:       结束时间


#define CUSTOM_ALARM_TYPE_MEDIA_INFO								40
//通知媒体信息(通知到下载服务器)


#define CUSTOM_ALARM_TYPE_QUESTION_ANSWER							41	//提问应答 param[0] 回复流水号 param[1]回复答案ID

#define CUSTOM_ALARM_TYPE_BARCODE_SCAN								42	//条形码扫描报警

#define CUSTOM_ALARM_TYPE_PLATFORM_TEXT								43  //平台互通，发送文本消息  param[0]发送方用户ID， param[1]接受方用户ID szDesc:发送内容

#define CUSTOM_ALARM_TYPE_REPORT_VIDEO								44	//上报实时视频（客户端做主动视频弹出）	param1  表示 通道号，param2表示码流类型
#define CUSTOM_ALARM_TYPE_STOP_REPORT_VIDEO							45	//停止上报实时视频（客户端把主动弹出的视频关闭掉）	param1  表示 通道号，param2表示码流类型
#define CUSTOM_ALARM_TYPE_EVENT_VIDEO								46	//录像事件(客户端观看视频时存储服务器录像), Param[0] 0-停止 1-开始
#define	CUSTOM_ALARM_TYPE_PEOPLE_COUNT								47	//客流统计 描述内容(通道号,上车人数,下车人数,变化人数)
#define	CUSTOM_ALARM_TYPE_XC_SWIPE_CARD								54	//wkp协议刷卡自定义报警 param[0]：-1表示无上下车表示， 0-上车， 1-下车 desc:卡号
#define CUSTOM_ALARM_TYPE_XC_SMOKE									55	//烟感报警
#define CUSTOM_ALARM_TYPE_XC_DRIVER_ON								56  //司机开车验证通过事件
#define CUSTOM_ALARM_TYPE_1078_VIDEO_CTRL							58  //1078视频控制
#define CUSTOM_ALARM_TYPE_UPDATE_RESULT								59	//终端升级结果通知 param[0]:升级类型 param[1]:升级结果
#define CUSTOM_ALARM_TYPE_809TASK_FINISH							60	//809插件的任务完成,仅用于通知到插件  p[0]:下载结果 p[1]:流水号 p[2]:中心ID 
																			//Desc:插件名称 DevIDNO:设备号 ImgFile:文件路径

#define CUSTOM_ALARM_TYPE_DEV_REPORED_TEXT							99	//设备上报文字信息	


#define CUSTOM_ALARM_TYPE_PF_PLATFORM_LOGIN				101		//平台登录  param[0]:平台ID,  param[1] 验证结果	0、成功，1、IP地址不正确,  2、接入码不正确， 3、用户没有注册,  4、密码错误，5、资源紧张，6、其它的
#define CUSTOM_ALARM_TYPE_PF_PLATFORM_LOGOUT			102		//平台掉线  param[0]:平台ID, 
#define CUSTOM_ALARM_TYPE_PF_PLATFORM_POST_QUERY_ACK	103		//查岗应答  Param[0]：对象类型 Param[1]：查岗消息ID Param[2]：平台ID  Param[3]：公司ID //szDesc：查岗对象ID  //szImgFile：应答内容
#define CUSTOM_ALARM_TYPE_PF_PLATFORM_INFO_ACK			104		//报文应答  Param[0]：对象类型 Param[1]：查岗消息ID Param[2]：平台ID  Param[3]：公司ID //szDesc：查岗对象ID  //szImgFile：应答内容
#define CUSTOM_ALARM_TYPE_PF_VEHICLE_REGISTER			105		//车辆注册  szdec:  车载终端厂商唯一编;车载终端型号;车载终端编号;车载终端 SIM 卡电话号码 
#define CUSTOM_ALARM_TYPE_PF_VEHICLE_TTS				106		//车辆TTS  szdec: 文本信息

#define CUSTOM_ALARM_TYPE_DRIVER_SWIPE_CAR							279	//司机刷卡	Param[0]: 1表示登录，0表示退签		desc:卡号

//银星:自定义报警
#define GPS_ALARM_TYPE_SIMUL_INFRARED_HILLFIRE      400     //同步银星：红外火源检测报警
#define GPS_ALARM_TYPE_SIMUL_ULTRAVIOLET_PHOTON     401     //同步银星：紫外线路电晕放电报警
#define GPS_ALARM_TYPE_SIMUL_IO                     402     //同步银星：IO报警
#define GPS_ALARM_TYPE_SIMUL_TEMPERATURE_OVERRUN    403     //同步银星：温度超限报警
#define GPS_ALARM_TYPE_SIMUL_WIND_SPEED_DIRECTION   404     //同步银星：风速风向报警
#define GPS_ALARM_TYPE_SIMUL_RAINFALL_OVERRUN       405     //同步银星：雨量超限报警

//PTT
#define GPS_ALARM_TYPE_PPT_TALK_EVENT				501	//通知某个用户讲话事件，nParam1表示群组ID，nParam2表示终端ID，nParam3=0表示停止，1表示开始讲话, outParam无内容
#define GPS_ALARM_TYPE_PPT_SWITCH_GROUP				502	//切换群组, nParam1表示群组ID, nParam2表示终端ID, nParam3表示进入或者离开 
#define GPS_ALARM_TYPE_PPT_UPDATE_GROUP_INFO		504	//协同小组信息（如名称）发生变化，inParam：nParam1为群组ID，szParam1为utf8群组名称，szParam2为ansi群组名称, outParam无内容
#define GPS_ALARM_TYPE_PPT_GROUP_MEMBER				505	//协同成员变化（增加、删除成员），nParam1为群组ID, outParam无内容
#define GPS_ALARM_TYPE_PPT_FORCE_CONTROL			506	//强拉，强拆, nParam1表示群组ID, nParam2表示终端ID, nParam3表示1强拉，2强拆

// 客户端模拟报警类型,无报警信息,仅供报警屏蔽使用
#define CLIENT_ALARM_TYPE_NO_RECORD					-100	//状态:不录像


//道路等级定义
#define ROAD_LEVEL_UNKOWN				0	//未知
#define ROAD_LEVEL_HIGH_ROAD			1	//高速路
#define ROAD_LEVEL_CITYHIGH_ROAD		2	//都市高速路
#define ROAD_LEVEL_NATIONAL_ROAD		3	//国道
#define ROAD_LEVEL_PROVINICIAL_ROAD		4	//省道
#define ROAD_LEVEL_PREFECTURA_ROAD		5	//县道
#define ROAD_LEVEL_CONUTY_ROAD			6	//乡镇村道
#define ROAD_LEVEL_OTHER_ROAD			7	//其它道路
#define ROAD_LEVEL_NINE_ROAD			8	//九级路
#define ROAD_LEVEL_FERRY_ROAD			9	//轮渡
#define ROAD_LEVEL_PEDESTRIAN_ROAD		10	//行人道路


#define GPS_CNT_MSG_SUCCESS				0
#define GPS_CNT_MSG_FAILED				-1
#define GPS_CNT_MSG_DISCONNECT			-2
#define GPS_CNT_MSG_FINISHED			-3
#define GPS_CNT_MSG_USR_FULL_ERROR		-4
#define GPS_CNT_MSG_USR_ERROR			-5

#define GPS_NOTIFY_TYPE_AUDIO_COM		1

#define GPS_AUDIO_TYPE_HEAD				1
#define GPS_AUDIO_TYPE_DATA				2

#define GPS_SETUP_MODE_SEND_ONLY		1	//只发送指令，不等待反馈
#define GPS_SETUP_MODE_WAIT_RET			2	//发送指令，并等待反馈
#define GPS_SETUP_MODE_WAIT_ASYN		3	//发送指令，上层检查返回

#define GPS_GPS_VALID					1

#define GPS_DEV_TYPE_MDVR				1 //车载终端
#define GPS_DEV_TYPE_MOBILE				2 //手机终端
#define GPS_DEV_TYPE_DVR				3 //普通DVR
#define GPS_DEV_TYPE_PAD				4 //PAD类型

#define GPS_MOBILE_TYPE_ANDROID			1 //手机终端-Android
#define GPS_MOBILE_TYPE_IPHONE			2 //手机终端-Iphone

#define GPS_MDVR_TYPE_HI3512_4			1 //车载终端-3512
#define GPS_MDVR_TYPE_HI3515_4			2 //车载终端-3515-4
#define GPS_MDVR_TYPE_HI3515_8			3 //车载终端-3515-8

#define GPS_MOBILE_USER_POST_TEAM_MEMBER	1	//队员
#define GPS_MOBILE_USER_POST_TEAM_LEADER	2	//队长

#define GPS_MOBILE_USER_SEX_MAN				1	//男
#define GPS_MOBLIE_USER_SEX_WOMAN			2	//女

#define GPS_PTZ_MOVE_LEFT				0	//左
#define GPS_PTZ_MOVE_RIGHT				1	//右
#define GPS_PTZ_MOVE_TOP				2	//上
#define GPS_PTZ_MOVE_BOTTOM				3	//下
#define GPS_PTZ_MOVE_LEFT_TOP			4	//左上
#define GPS_PTZ_MOVE_RIGHT_TOP			5	//右上
#define GPS_PTZ_MOVE_LEFT_BOTTOM		6	//左下
#define GPS_PTZ_MOVE_RIGHT_BOTTOM		7	//右下

#define GPS_PTZ_FOCUS_DEL				8	//焦距变小
#define GPS_PTZ_FOCUS_ADD				9	//焦距变大
#define GPS_PTZ_LIGHT_DEL				10	//光圈变小
#define GPS_PTZ_LIGHT_ADD				11	//光圈变大
#define GPS_PTZ_ZOOM_DEL				12	//焦点后调(倍数)
#define GPS_PTZ_ZOOM_ADD				13	//焦点前调
#define GPS_PTZ_LIGHT_OPEN				14	//灯光
#define GPS_PTZ_LIGHT_CLOSE				15
#define GPS_PTZ_WIPER_OPEN				16	//雨刷
#define GPS_PTZ_WIPER_CLOSE				17
#define GPS_PTZ_CRUISE					18	//自动巡航
#define GPS_PTZ_MOVE_STOP				19	//停止

#define GPS_PTZ_PRESET_MOVE				21	//调用
#define GPS_PTZ_PRESET_SET				22	//设置
#define GPS_PTZ_PRESET_DEL				23	//删除

#define GPS_PTZ_SPEED_MIN				0
#define GPS_PTZ_SPEED_MAX				255

#define GPS_GPSINTERVAL_TYPE_DISTANCE	1	//按距离上报
#define GPS_GPSINTERVAL_TYPE_TIME		2	//按时间上报

//客户端查询车辆轨迹的选项
#define GPS_QUERY_TRACK_TYPE_GPS		1  //查询GPS数据
#define GPS_QUERY_TRACK_TYPE_GPSARLMR	2  //查询GPS和报警
#define GPS_QUERY_TRACK_TYPE_ALARM		3  //查询报警数据

//返回
#define GPS_TRACK_DATA_TYPE_GPS			1  //GPS数据
#define GPS_TRACK_DATA_TYPE_ALARM		2  //报警数据

//网络类型
#define GPS_NETWOKR_TYPE_3G				0	//3G类型
#define GPS_NETWORK_TYPE_3G				0	//3G类型
#define GPS_NETWOKR_TYPE_WIFI			1	//WIFI类型
#define GPS_NETWORK_TYPE_WIFI			1	//WIFI类型
#define GPS_NETWORK_TYPE_NET			2	//有线网络登录
#define GPS_NETWORK_TYPE_4G				3	//4G网络登录

//磁盘类型
#define GPS_DISK_TYPE_UNKOWN			0	//SD卡
#define GPS_DISK_TYPE_SD				1	//SD卡
#define GPS_DISK_TYPE_HDD				2	//硬盘
#define GPS_DISK_TYPE_SSD				3	//SSD


#define GPS_DISK_STATUS_UNKONW			0	
#define GPS_DISK_STATUS_NORMAL			1	//正常
#define GPS_DISK_STATUS_BAD				2	//坏了

//文件下载类型
#define GPS_DOWN_TYPE_OFFSET			1		//按文件偏移下载
#define GPS_DOWN_TYPE_TIME				2		//按时间偏移下载
#define GPS_DOWN_TYPE_SOURCE_SERVER		3		//从服务器主动下载，下载完成后，机器可以删除相应的文件
#define GPS_DOWN_TYPE_SB_ALARM_TIME		4		//苏标设备主动上报文件

//协议类型cProtocol，1-15是通用版本
#define MDVR_PROTOCOL_TYPE_WKP			1
#define MDVR_PROTOCOL_TYPE_TTX			2
#define MDVR_PROTOCOL_TYPE_TQ			3
#define MDVR_PROTOCOL_TYPE_HANV			4
#define MDVR_PROTOCOL_TYPE_GOOME		5
#define MDVR_PROTOCOL_TYPE_JT808		6
#define MDVR_PROTOCOL_TYPE_RM			7
#define MDVR_PROTOCOL_TYPE_YD			8
#define MDVR_PROTOCOL_TYPE_UNIMV		9
#define MDVR_PROTOCOL_TYPE_BSJ			10
#define MDVR_PROTOCOL_TYPE_LHXY			11	//联合欣业
#define MDVR_PROTOCOL_TYPE_ND			12	//牛斗
#define MDVR_PROTOCOL_TYPE_JT809		14	//809协议
#define MDVR_PROTOCOL_TYPE_GB28181		15  //28181协议

//厂家设备类型(WKP协议下的子类型)cFactoryType
#define WKP_FACTORY_TYPE_UNKOWN			0
#define WKP_FACTORY_TYPE_WKP			1		
#define WKP_FACTORY_TYPE_AUDS			2
#define WKP_FACTORY_TYPE_KX				3
#define WKP_FACTORY_TYPE_EST			4
#define WKP_FACTORY_TYPE_YXHD			5
#define WKP_FACTORY_TYPE_COOINT			6
#define WKP_FACTORY_TYPE_7				7
#define WKP_FACTORY_TYPE_8				8
#define WKP_FACTORY_TYPE_9				9
#define WKP_FACTORY_TYPE_10				10
#define WKP_FACTORY_TYPE_11				11
#define WKP_FACTORY_TYPE_12				12
#define WKP_FACTORY_TYPE_13				13
#define WKP_FACTORY_TYPE_14				14
#define WKP_FACTORY_TYPE_15				15
#define WKP_FACTORY_TYPE_16				16
#define WKP_FACTORY_TYPE_17				17
#define WKP_FACTORY_TYPE_18				18	
#define WKP_FACTORY_TYPE_19				19	
#define WKP_FACTORY_TYPE_20				20	
#define WKP_FACTORY_TYPE_21				21	
#define WKP_FACTORY_TYPE_22				22	
#define WKP_FACTORY_TYPE_23				23  
#define WKP_FACTORY_TYPE_24				24
#define WKP_FACTORY_TYPE_25				25
#define WKP_FACTORY_TYPE_26				26
#define WKP_FACTORY_TYPE_27				27
#define WKP_FACTORY_TYPE_28				28
#define WKP_FACTORY_TYPE_29				29
#define WKP_FACTORY_TYPE_30				30
#define WKP_FACTORY_TYPE_31				31
#define WKP_FACTORY_TYPE_32				32				//未使用
#define WKP_FACTORY_TYPE_33				33				//UAE
#define WKP_FACTORY_TYPE_34				34				//TJSX_ZFY
#define WKP_FACTORY_TYPE_35				35				//ZJX_ANDROID
#define WKP_FACTORY_TYPE_36				36				//ZBKJ_ZFY
#define WKP_FACTORY_TYPE_37				37				//MC_ZFY
#define WKP_FACTORY_TYPE_38				38				//CWAF_ZFY
#define WKP_FACTORY_TYPE_39				39				//MRDZ_MDVR
#define WKP_FACTORY_TYPE_40				40				//TW_MDVR
#define WKP_FACTORY_TYPE_41				41				
#define WKP_FACTORY_TYPE_42				42				//RTP	1078
#define WKP_FACTORY_TYPE_43_ANDROID				43				//cmscruise对接用，43为后视镜
#define WKP_FACTORY_TYPE_44_ANDROID				44				//cmscruise对接用，44为执法仪
#define WKP_FACTORY_TYPE_45_ANDROID				45				//cmscruise对接用，45为ptt客户端
#define WKP_FACTORY_TYPE_46_ANDROID				46				//cmscruise对接用，友浩车联网（后视镜）
#define WKP_FACTORY_TYPE_47_ANDROID				47				//cmscruise对接用，普通客户端（带查看组织列表位置视频功能）
#define WKP_FACTORY_TYPE_48_ANDROID				48				//cmscruise对接用，瑞特安
#define WKP_FACTORY_TYPE_49_ANDROID				49				//cmscruise对接用，执法仪版本（POLICE）
#define WKP_FACTORY_TYPE_50_ANDROID				50				//cmscruise对接用
#define WKP_FACTORY_TYPE_51_ANDROID				51				//cmscruise对接用
#define WKP_FACTORY_TYPE_52_ANDROID				52				//cmscruise对接用
#define WKP_FACTORY_TYPE_53_ANDROID				53				//cmscruise对接用
#define WKP_FACTORY_TYPE_54_ANDROID				54				//cmscruise对接用
#define WKP_FACTORY_TYPE_55_ANDROID				55				//cmscruise对接用
#define WKP_FACTORY_TYPE_56_ANDROID				56				//cmscruise对接用
#define WKP_FACTORY_TYPE_57_ANDROID				57				//cmscruise对接用
#define WKP_FACTORY_TYPE_58_ANDROID				58				//cmscruise对接用
#define WKP_FACTORY_TYPE_59_ANDROID				59				//cmscruise对接用
#define WKP_FACTORY_TYPE_60_ANDROID				60				//cmscruise对接用

//报警中用来区分协议数据
#define MDVR_JT808_NORMAL				1	//2011版本部标协议
#define MDVR_JT808_BD					2	//2013版本北斗协议
#define MDVR_JT808_1078					3	//JT1078 2016 视频部标

//扩展协议
#define GPS_EXTENDED_PROTOCOL_UNKOWN			0	//未知
#define GPS_EXTENDED_PROTOCOL_JIANGSU			1	//苏标
#define GPS_EXTENDED_PROTOCOL_SHANXI			2	//陕标
#define GPS_EXTENDED_PROTOCOL_JIAOTONG			3	//交通部

//GPS坐标类型定义
#define	GPS_COOR_TYPE_WSG84		0		//WSG84类型坐标
#define	GPS_COOR_TYPE_GCJ02		1		//火星坐标，高德地图使用
#define	GPS_COOR_TYPE_BD09		2		//百度坐标

//GPS定位类型定义
#define	GPS_LOC_TYPE_GPS			0		//GPS定位
#define	GPS_LOC_TYPE_WIFI			1		//WIFI定位

//客户端和设备数据透传类型
#define GPS_TPD_TYPE_DJWL_SET_TASK_FAIL_TIME	1	//大件物流设置任务失败时间
#define GPS_TPD_TYPE_DJWL_TASK_FAIL_CONFIRM		2	//大件物流任务失败确认
#define GPS_TPD_TYPE_DJWL_TASK_STOP				3	//大件物流手动点击任务完成或失败

#define GPS_JT808_UNKNOWN				0	//未知版本的部标协议
#define GPS_JT808_NORMAL				1	//2011版本部标协议
#define GPS_JT808_BD					2	//2013版本北斗协议
#define GPS_JT808_1078					3	//JT1078 2016 视频部标

#define GPS_CHECK_POST_TYPE_TTX			0xFF	//通天星查岗(企业平台)

#define GPS_RESOURCE_TYPE_AV			0		//音视频
#define GPS_RESOURCE_TYPE_AUDIO			1		//音频
#define GPS_RESOURCE_TYPE_VIDEO			2		//视频
#define GPS_RESOURCE_TYPE_LOG			80		//日志

#define MEDIA_LISTEN_REALPALY_MAIN		0
#define MEDIA_LISTEN_REALPALY_SUB		1
#define MEDIA_LISTEN_TALKBACK			2
#define MEDIA_LISTEN_AUDIOLISTEN		3
#define MEDIA_LISTEN_PALYBACK			4
#define MEDIA_LISTEN_TRANSPORT			5

#pragma pack(4)

typedef struct _tagGPSDeviceInfo
{
	char sVersion[62];///
	char cProtocolVersion;	//协议版本
	char cLoginType;			//0:LINUX 0	 1:WINDOW	2:WEB 	3:ANdroid   4:IOS
	char sSerialNumber[32];  		
	char szDevIDNO[32];			///车辆编号  		
	short sDevType;				///设备类型
	char cFactoryType;			//厂家类型	
	char cFactoryDevType;		//厂家设备类型
	char cDiskNum;///硬盘数目	
	char cChanNum;///通道数目
	char cProtocol;				//协议类型
	unsigned char cAudioCodec:5;//音频解码器类型
	unsigned char cDiskType:3;	//0：SD，1：硬盘，2：SSD
	char cPlateNumber[34];		//车牌号
	char cPlateUnicode:1;		//0表示非unicode，1表示unicode
	char cPlateColor:7;			//车牌颜色 1-蓝2-黄3-黑4-白9-其他
	char bTimeZoneValid:1;		//时区是否有效
	char cTimeZone:7;			//时区
}GPSDeviceInfo_S, *LPGPSDeviceInfo_S;

typedef struct _tagGPSDeviceIDNO
{
	char szDevIDNO[32];
}GPSDeviceIDNO_S, *LPGPSDeviceIDNO_S;

typedef struct _tagGPSSvrAddr
{
	char	IPAddr[80];
	unsigned short usPort;
	unsigned short Reserve;
}GPSSvrAddr_S;

typedef struct _tagGPSFile
{
	char	szFile[227]; 	/*带路径的文件名*/	
	// 2019-03-22  230变为227，	ttx协议增加是否可以同时支持多路回放
	char 	bMulPlay;			//是否支持多路同时回放
	unsigned short usMulChn;	//可以多路回放的通道，按位表示
	// 2017-3-6 	242变为234，  增加1078协议上需求的资源类型,码流类型,存储类型,报警标志
	// 2017-4-25 	234变为230， 增加1078报警标志 以前的nAlarmInfo不共用
	char cStoreType;			//1：主存储器， 2：灾备存储器
	char cReserve;		
	int nAlarmFlag1;
	int nAlarmFlag2;
	char cResourceType;			//0：音视频， 1：音频， 2：视频
	char cStreamType;			//0：主码流， 1：子码流
	// 2016-3-16	243变为242， 增加流标识
	char	bStream;		//是否为流式文件，当为流式文件时，客户端会使用回放的方式进行文件下载
	// 2015-8-17	244变为243， 增加录像标识
	char	bRecording;		//是否正在录像的文件，0表示没有，1表示正在录像
	// 2015-4-30	248变为244， 增加文件偏移量
	unsigned int nFileOffset;	//文件偏移量
	//2015-04-08 原来是252，变为248，增加 nChnMask
	int		nChnMask;		//通道掩码，每个文件存在多个通道
	//2015-03-14 原来是256，变为252，增加 nAlarmInfo
	int		nAlarmInfo;		//报警信息，每个文件可能会有多个报警
	int		nYear;
	int		nMonth;
	int		nDay;
	unsigned int uiBegintime;
	unsigned int uiEndtime;
	char	szDevIDNO[32];			//设备ID
	int		nChn;
	unsigned int nFileLen;
	int		nFileType;
	int		nLocation;		//位置，设备上的录像文件，还是存储服务上的录像文件
	int		nSvrID;			//存储服务器ID，在为存储服务器上的文件时有效
}GPSFile_S, *LPGPSFile_S;

typedef struct _tagGPSRecFile
{
	char	szFile[227]; 		/*带路径的文件名*/		
								//原来是230，取3字节来用，afu：20190322
	char 	bMulPlay;			//是否支持多路同时回放
	unsigned short usMulChn;	//可以多路回放的通道，按位表示
	// 2016-3-16	231变为230， 增加流标识
	char	bStream;		//是否为流式文件，当为流式文件时，客户端会使用回放的方式进行文件下载
	//原来是232，取1个字节来用，afu：20150817
	char	bRecording;		//是否正在录像的文件，0表示没有，1表示正在录像
	//原来是236，取4个字节来用，afu：20150410
	int nChnMask;			//通道掩码
	//原来是240，取4个字节来用，afu：20150305
	int nAlarmInfo;	//每个文件可能会有多个报警
	//原来是256，取16个字节来用，afu：20140815
	unsigned char ucYear;		//跨天搜索用
	unsigned char ucMonth;		//跨天搜索用
	unsigned char ucDay;		//跨天搜索用
	char cResourceType;			//0：音视频， 1：音频， 2：视频, 3.图片
	int nAlarmFlag1;			//报警标志1 1078
	int nAlarmFlag2;			//报警标志2 1078
	char cStreamType;			//0：主码流， 1：子码流
	char cStoreType;			//1：主存储器， 2：灾备存储器
	char cReserve[2];	
	//char	szFile[256]; 	/*带路径的文件名*/

	unsigned int uiBegintime;
	unsigned int uiEndtime;
	int		nChn;
	unsigned int nFileLen;
	int		nRecType;
}GPSRecFile_S, *LPGPSRecFile_S;

//时间
typedef struct _tagGPSTime
{
	unsigned int ucYear:6;		//年(2000+ucYear) 范围(0-64)
	unsigned int ucMonth:4;		//月(1-12)	范围(0-16)
	unsigned int ucDay:5;		//日(1-31)  范围(0-32)
	unsigned int ucHour:5;		//时(0-23)	范围(0-32)
	unsigned int ucMinute:6;	//分(0-59)  范围(0-64)
	unsigned int ucSecond:6;	//秒(0-59)  范围(0-64)
}GPSTime_S;

//车辆状态,每位表示车辆的相关状态
//uiStatus[0]共有32位
//0位表示GPS定位状态		0无效1有效
//1位表示ACC状态		0表示ACC关闭1表示ACC开启
//2位表示左转状态		0无效1左转
//3位表示右转状态		0无效1右转
//4位表示刹车状态		0无效1刹车
//5位表示正转状态		0无效1正转
//6位表示反转状态		0无效1反转
//7位表示GPS天线状态		0不存在1存在
//8,9位为表示硬盘状态		0不存在，1存在，2断电
//10,11,12位表示3G模块状态  0模块不存在，1无信号，2信号差，3信号一般，4信号好，5信号优
//13位表示静止状态		1表示静止
//14位表示超速状态		1表示超速
//15位表示补传状态		1表示GPS补传
//16位低速状态
//17位表示夜间			0-表示日间 1-表示夜间 先判断超速才有效
//18位表示超载状态		0-正常 1-超载
//19位
//关于停车未熄火，如果处理静止状态，并且处于ACC开启状态，则表示停车未熄火
//20位表示IO1状态	1表示报警
//21位表示IO2状态	1表示报警
//22位表示IO3状态	1表示报警
//23位表示IO4状态	1表示报警
//24位表示IO5状态	1表示报警
//25位表示IO6状态	1表示报警
//26位表示IO7状态	1表示报警
//27位表示IO8状态	1表示报警
/* 新国标才有效(1,12-13)
26=车道偏移预警(431)
27=胎压预警(432)
*/
//28位表示盘符2状态	1表示有效
//29、30位表示，硬盘2的状态		0不存在，1存在，2断电
//31位硬盘状态（GPS设备时使用）	1、无效		0、有效，要再判断1，2的状态
//uiStatus[1]
/* --- 删除 zjt2017-03-10 v6版本的电子围栏
//0位表示出区域报警	 （终端产生）
//1位表示出线路报警	 （终端产生）	

//2位表示区域内高速报警	
//3位表示区域内低速报警	

//4位表示区域外高速报警
//5位表示区域外低速报警	

//6位表示区域内停车报警	
//7位表示区域外停车报警	
*/

//第0位	视频信号丢失报警 （视频部标）
//第1位	视频信号遮挡报警  视频部标）	
//第2位	存储单元故障报警 （视频部标）
//第3位	其他视频设备故障报警（视频部标）
//第4位	异常驾驶行为报警 （视频部标）
//第5位	特殊报警录像达到存储阈值报警 （视频部标）
//第6位: 急加速: 1-急加速
//第7位：急减速  1-急减速


//8位表示日流量预警
//9位表示日流量超过
//10位表示月流量预警
//11位表示月流量超过

/*  --- 删除 hw2016-8-18
//12位--主机掉电由后备电池供电
//13位--车门开
//14位--车辆设防
*/
/* --- 删除 ydl 2019-4-2
//12: 作业状态: 1-作业中 0-空闲  平台产生(环卫车)
//13: 高峰作业: 1-高峰作业			 平台产生(环卫车)
*/
//12-13 0表示旧协议 0x01表示新协议有效(以下状态位需要增加/修改解析) 0x10和0x11预留
//14: 通道录像状态状态位有效 1,有效 0 无效
//15位--电池电压过低 (808电池欠压)		ttx协议: 为人员时，解析为  电池低压报警
//16位--电池坏	(808主电源掉电)
//17位--发动机
//18位--为最后一个有效的GPS信息，状态显示成定位无效，但GPS可以在地图上定位
//19位--0-空载状态 1-重载状态

//20：运营状态；1：停运状态(808)
//21：经纬度未加密；1：已加密(808)
//22：油路正常，1：油路断开(808)
//23：电路正常，1：电路断开(808)
//24：车门解锁，1：车门加锁(808)
//25：区域超速报警(平台产生)
//26：区域低速报警(平台产生)
//27：进区域报警(平台产生)	 
//28：线路偏移(平台产生)
//29：时间段超速报警(平台产生) 
//30：时间段低速报警(平台产生) 
//31：疲劳驾驶(平台产生)   

//uiStatus[2]
//0-7表示通道视频丢失状态
//8-15表示通道录像状态
//16-23表示IO输入9-16 状态
//24-27表示IO输出1-4 状态
//28-29 0表示GPS定位，1表示基站定位，2表示Wifi定位，  手机定位要显示这个定位信息
/* 新国标才有效(1,12-13)
2,16=侧翻预警(433)
2,17=道路运输证IC卡模块故障(712)
2,18=违规行驶(713)
2,19=右转盲区异常报警(714)
2,20=需要和1,19合并判断   1,19:0表示空载 1表示满载  2,20:1表示半载
2,21=0：门 1 关；1：门 1 开（前门）
2,22=0：门 2 关；1：门 2 开（中门）
2,23=0：门 3 关；1：门 3 开（后门）
2,24=0：门 4 关；1：门 4 开（驾驶席门）
2,25=0：门 5 关；1：门 5 开（自定义）
2,26=0：未使用 GPS 卫星进行定位；1：使用 GPS 卫星进行定位
2,27=0：未使用北斗卫星进行定位；1：使用北斗卫星进行定位
2,28=0：未使用 GLONASS 卫星进行定位；1：使用 GLONASS 卫星进行定位
2,29=0：未使用 Galileo 卫星进行定位；1：使用 Galileo 卫星进行定位 
*/
//30:异常行驶状态 客运车禁止行驶 0表示正常1表示报警
//31:异常行驶状态 山区禁行 0表示正常1表示报警

//uiStatus[3]
//0-2表示定位类型	0表示WSG_84（标准的GPS坐标体系），1表示GCJ-02（火星坐标），2表示BD09（百度坐标）
/* 新国标才有效(1,12-13)
0=超速预警(428) 新国标协议时有效
1=疲劳驾驶预警(429) 新国标协议时有效
2=前撞预警(430) 新国标协议时有效
*/
//3：紧急报警
//4：区域超速报警
//5：疲劳驾驶报警
//6：预警
//7：GNSS模块故障
//8：GNSS天线未接或者剪断
//9：GNSS天线短路
//10：终端LCD或者显示器故障
//11：TTS模块故障
//12：摄像头故障
//13：当天累计驾驶超时
//14：超时停车
//15：进区域
//16：进路线
//17：路段行驶时间不足或过长
//18：路线偏离报警
//19：车辆VSS故障
//20：车辆油量异常
//21：车辆被盗
//22：车辆非法点火
//23：车辆非法位移
//24：碰撞侧翻报警
//25：超时停车(平台产生)
//26：关键点未到达报警(平台产生)
//27：线路超速报警(平台产生) 
//28：线路低速报警(平台产生) 
//29: 道路超速报警(平台产生)
//30: 表示出区域报警	 （平台产生）
//31: 表示关键点未离开报警	  （平台产生）	

//usReserve：	0位表示  	司机卡未插卡报警
//		1位表示 	司机识别错误报警
//		2位表示 	未复位行车报警
//		3位表示 	nParkTime是否为工作时长
typedef struct _tagGPSVehicleGps
{
	GPSTime_S Time;
	unsigned int uiSpeed:14;	//速度值 KM/S	9999 = 999.9 	范围(0-16384)
	unsigned int uiYouLiang:18;	//油量   升	9999 = 99.99 	范围(0-262100)
	unsigned int uiLiCheng;		//里程   公里	9999 = 9.999 	
	unsigned int uiHangXiang:9;	//地面航向，(0-360) 范围(0-512)
	unsigned int uiMapType:3;	//地图类型		1表示GOOGLE，2表示百度，0表示无效
	unsigned int uiNetWorkType:4;	//网络类型(3G类,WIFI,有线,4G)
	unsigned int uiTachographSpeed:14;  //速度值 KM/S	9999 = 999.9 	范围(0-16384) 行驶记录仪速度
	//unsigned int uiReserve:2;  //保留位1
	unsigned int uiLongGps:2;		//长GPS,表示此结构体后面还有72个字节的数据  0位有效表示libmdvrnet数据有效  1位有效表示Gateway/数据库数据有效
	unsigned int uiStatus[4];		//目前只使用，每1个状态	0位表示GPS定位状态（0无效，1有效）
	short sTempSensor[4];	//温度传感器的状态
	int	nJingDu;		//经度	4字节 整数部分	9999999 = 9.999999 
	int nWeiDu;			//纬度	4字节 整数部分	9999999 = 9.999999
	short nGaoDu;			//高度，暂时未使用
	unsigned short usSatellites:4;		//卫星数，大于0时显示，范围0-12
	unsigned short uiStatusEx:8;		//保留字段	定义使用20180103 AFU,数据库存储在usExtraFlag字段的高位
	unsigned short usExtraFlag:4;	//附加信息标志， 默认为0
	int	nParkTime;		//停车时长 秒	在静止(或川标超速)状态时有效
	unsigned int uiLineID:29;			//线路号(数据库中关联)
	unsigned int uiDirection:1;			//方向 0-上行， 1-下行
	unsigned int uiStationFlag:1;		//（0-站点 1-站场）
	unsigned int uiStationStatus:1;		//0-本站 1-下一站

	unsigned int uiODBVotage:9;		//OBD电池电压			123   = 12.3V		0-512			
	unsigned int uiODBJQTemp:7;		//燃油进气温度			33 = 33度			0 - 127			
	unsigned int uiODBStatus:6;		//第0位表示ACC 開關	1 離合器開關  2	煞車開關  3	PTO 開關	4  緊急剎車	
	unsigned int uiODBJQMPos:10;	//节气门位置			102 = 10.2 %		0-1024			

	unsigned int uiOBDRpm:14;		//发动机转速			1000 = 1000转		0-16384			
	unsigned int uiOBDSpeed:8;		//ODB速度				99 = 99公里			(0-256)			
	unsigned int uiODBReserve:2;	//保留字段		
	unsigned int uiPeopleCur:8;		//当前车上人数		范围(0-256)

	unsigned int uiPeopleUp:12;		//上车人数		范围(0-4096)
	unsigned int uiPeopleDown:12;	//下车人数		范围(0-4096)
	unsigned int uiStationIndex:8;	//站点索引
}GPSVehicleGps_S;
//注意目前总长度为72个字节，每次改变结构体变量时，必须都sizeof(GPSVehicleGps_S)判断下，避免更改出错的问题
const int GPSVehicleGps_LEN = sizeof(GPSVehicleGps_S);

typedef struct _tagGPSVehicleLongGps : public GPSVehicleGps_S
{
	GPSTime_S RecvTime;					//接收GPS的系统时间
	unsigned int uiLongStatus;			//状态位  0位:车厢温度  1位:IO状态位  2位:扩展车辆信号状态  3位:模拟量  4位:胎压
										//		5位:主动安全ADAS  6位:主动安全DSM  7位:主动安全BSD
	short usCompartmentTemp;			//车厢温度(0x06)
	unsigned short usIOStatus;			//IO状态位(0x2A)
	unsigned int uiExtraStatus;			//扩展车辆信号状态位(0x25)
	unsigned int uiAnalogQuantity;		//模拟量(0x2B)

	unsigned short usADASAlarmL1;			//主动安全adas报警状态位 一级
	unsigned short usADASAlarmL2;			//主动安全adas报警状态位 二级
	/* 	0：前向碰撞报警 	1：车道偏离报警 	2：车距过近报警 	3：行人碰撞报警 	4：频繁变道报警 	5：道路标识超限报警 	6：障碍物报警
	7：弯道车速预警
	*/

	unsigned short usDSMAlarmL1;			//主动安全dsm报警状态位 一级
	unsigned short usDSMAlarmL2;			//主动安全dsm报警状态位 二级
	/* 	0:疲劳驾驶报警 	1:接打电话报警 	2:抽烟报警 	3:长时间不目视前方报警 	4:系统不能正常工作报警  5:驾驶员未系安全带报警
	6:驾驶员不在驾驶位报警 	7:驾驶员双手脱离方向盘报警  8:分神驾驶报警(苏) 9:驾驶员异常报警(苏)

	*/
	unsigned char ucBSDAlarmL1;			//主动安全bsd报警状态位 一级
	unsigned char ucBSDAlarmL2;			//主动安全bsd报警状态位 二级
	/* 	0：左侧盲区报警 	1：右侧盲区报警 	2：后方接近报警
	*/

	// ADAS
	unsigned char ucFrontVehiSpeed;		//前车车速	单位 Km/h。范围 0~250，仅报警类型为 0x01 和 0x02 时	有效
	unsigned char ucDistinceTime;		//前车/行人距离	单位 100ms，范围 0~100仅报警类型为 0x01、0x02 和 0x04 时有效
	unsigned char ucRoadFlagData;		//道路标志识别数据
	unsigned char ucDeviationType : 1;	//偏离类型(0:左侧 1:右侧)仅报警类型为 0x02 时有效 
	unsigned char ucRoadFlagType : 2;	//道路标志识别类型(0：限速标志 1：限高标志 2：限重标志)仅报警类型为 0x06 时有效 
	unsigned char ucDistractedDriving : 1;	//分神驾驶报警 2级(平台)
	unsigned char ucReserve : 4;		//预留

	// DSM
	unsigned char ucFatigueLv : 4;		//疲劳程度(1-10)
	unsigned char ucYawningNum : 4;		//打哈欠次数 范围1~10。报警结束上报 仅在报警类型为0x01时有效
	unsigned char ucClosedEyeTime;		//闭眼持续时长 单位100ms  报警结束上报 仅在报警类型为0x01时有效
	unsigned char ucWinkCount;			//连续眨眼次数 范围1~100。报警结束上报 仅在报警类型为0x01时有效
	unsigned char ucReserve2;			//预留

	unsigned char ucTirePressure[30];	//胎压(0x05)
	int nDriverID;						//司机ID
}GPSVehicleLongGps_S;
const int GPSVehicleLongGps_LEN = sizeof(GPSVehicleLongGps_S);
static_assert(144 == GPSVehicleLongGps_LEN, "GPSVehicleLongState_S Length error");

//扩展状态结构体
const int GPS_VEHICLE_EXTRA_FALG_BUSODB = 0;			//默认版本
const int GPS_VEHICLE_EXTRA_FALG_VIDEO_ALARM = 1;		//视频部标
const int GPS_VEHICLE_EXTRA_FALG_UAE = 2;				//UAE
const int GPS_VEHICLE_EXTRA_FLAG_SUBIAO_ALARM = 3;		//视频部标(苏标)

#define GPS_VEHICLE_EXTRA_FLAG_BUSODB	GPS_VEHICLE_EXTRA_FALG_BUSODB
#define	GPS_VEHICLE_EXTRA_FLAG_VIDEO_ALARM	GPS_VEHICLE_EXTRA_FALG_VIDEO_ALARM
#define GPS_VEHICLE_EXTRA_FLAG_UAE	GPS_VEHICLE_EXTRA_FALG_UAE
#define IS_GPS_EXTRA_FLAG	//定义此宏用来判断扩展标志位
#define IS_GPS_EXTRA_FLAG_BUSODB(Flag)		(GPS_VEHICLE_EXTRA_FLAG_BUSODB == (Flag))
#define IS_GPS_EXTRA_FLAG_VIDEO(Flag)		(GPS_VEHICLE_EXTRA_FLAG_VIDEO_ALARM == (Flag))
#define IS_GPS_EXTRA_FLAG_UAE(Flag)		(GPS_VEHICLE_EXTRA_FLAG_UAE == (Flag))
#define IS_GPS_EXTRA_FLAG_SUBIAO(Flag)		(GPS_VEHICLE_EXTRA_FLAG_SUBIAO_ALARM == (Flag))
typedef struct GPSVehicleExtraBusObd
{
	unsigned int uiLineID:29;			//线路号(数据库中关联)
	unsigned int uiDirection:1;			//方向 0-上行， 1-下行
	unsigned int uiStationFlag:1;		//（0-站点 1-站场）
	unsigned int uiStationStatus:1;		//0-本站 1-下一站
	unsigned int uiODBVotage:9;		//OBD电池电压			123   = 12.3V		0-512			
	unsigned int uiODBJQTemp:7;		//燃油进气温度			33 = 33度			0 - 127			
	unsigned int uiODBStatus:6;		//第0位表示ACC 開關	1 離合器開關  2	煞車開關  3	PTO 開關	4  緊急剎車	
	unsigned int uiODBJQMPos:10;	//节气门位置			102 = 10.2 %		0-1024			

	unsigned int uiOBDRpm:14;		//发动机转速			1000 = 1000转		0-16384			
	unsigned int uiOBDSpeed:8;		//ODB速度				99 = 99公里			(0-256)			
	unsigned int uiODBReserve:2;	//保留字段		
	unsigned int uiPeopleCur:8;		//当前车上人数		范围(0-256)

	unsigned int uiPeopleUp:12;		//上车人数		范围(0-4096)
	unsigned int uiPeopleDown:12;	//下车人数		范围(0-4096)
	unsigned int uiStationIndex:8;	//站点索引
}GPSVehicleExtraBusObd_S;

typedef struct GPSVehicleExtraVideoAlarm
{
	int nVideoLostFlag;				//bit0～bit31分别表示第 1～32 个通道
	int nVideoMaskFlag;				//bit0～bit31分别表示第 1～32 个通道
	short sDiskErrFalg ;			//bit0～bit11分别表示第 1～12 个主存储 器， bit12～bit15分别表示 第 1～4个灾备存储装置
	short sAbnormaDrivelFlag;		//异常驾驶标志位 bit0：疲劳； 	 bit1：打电话?	 bit2：抽烟 ；
	unsigned char ucFatigueLv;		//疲劳程度 0-100
	char cReserve[1];
	short sAbnormaDrivelFlagEx;		//异常驾驶标志扩展位
}GPSVehicleExtraVideoAlarm_S;

typedef struct MDVRVehicleExtraUAE
{
	unsigned short cDisk3Status:3;		////硬盘3状态, 0不存在，1存在，2断电，3无效
	unsigned short cDisk3Type:3;			//TTX_DISK_TYPE_SD=1, TTX_DISK_TYPE_HDD=2, TTX_DISK_TYPE_SSD=3
	unsigned short cDisk4Status:3;		////硬盘4状态, 0不存在，1存在，2断电，3无效
	unsigned short cDisk4Type:3;			//TTX_DISK_TYPE_SD, TTX_DISK_TYPE_HDD, TTX_DISK_TYPE_SSD
	unsigned short sReserve:4;			//保留字段
	unsigned short sSensor1;			//传感器1，值范围 (0 - 65535)，如果后期字段不够，建议改sSensor为char，正常湿度范围是 0-100， 25表示温度为25%

	//Obd和当前人数与之前的状态保持一致
	unsigned int uiODBVotage:9;		//OBD电池电压			123   = 12.3V		0-512			
	unsigned int uiODBJQTemp:7;		//燃油进气温度			33 = 33度			0 - 127			
	unsigned int uiODBStatus:6;		//第0位表示ACC 開關	1 離合器開關  2	煞車開關  3	PTO 開關	4  緊急剎車	
	unsigned int uiODBJQMPos:10;	//节气门位置			102 = 10.2 %		0-1024			

	unsigned int uiOBDRpm:14;		//发动机转速			1000 = 1000转		0-16384			
	unsigned int uiOBDSpeed:8;		//ODB速度				99 = 99公里			(0-256)			
	unsigned int uiODBReserve:2;	//保留字段		
	unsigned int uiPeopleCur:8;		//当前车上人数		范围(0-256)

	unsigned short sSensor2;			//传感器2
	unsigned short sSensor3;			//传感器3
}MDVRVehicleExtraUAE_S;

// 注:以下注释中的报警类型对应标志位应减一
typedef struct GPSVehicleExtraSBAlarm
{
	unsigned short usVideoLostFlag;		//bit0～bit15分别表示第 1～15 个通道
	unsigned char ucFrontVehiSpeed;		//前车车速	单位 Km/h。范围 0~250，仅报警类型为 0x01 和 0x02 时	有效
	unsigned char ucDistinceTime:7;		//前车/行人距离	单位 100ms，范围 0~100仅报警类型为 0x01、0x02 和 0x04 时有效
	unsigned char ucDeviationType:1;	//偏离类型(0:左侧 1:右侧)仅报警类型为 0x02 时有效 

	unsigned short usVideoMaskFlag;		//bit0～bit15分别表示第 1～15 个通道
	unsigned char ucRoadFlagData;		//道路标志识别数据
	unsigned char ucReserve1;			//预留:8位

	unsigned short usDiskErrFalg;		//bit0～bit11分别表示第 1～12 个主存储 器， bit12～bit15分别表示 第 1～4个灾备存储装置

	unsigned short usADASAlarmL1:7;		//苏标ADAS报警位(一级)
	unsigned short usADASAlarmL2:7;		//苏标ADAS报警位(二级)
	unsigned short usRoadFlagType:2;	//道路标志识别类型(0：限速标志 1：限高标志 2：限重标志)仅报警类型为 0x06 时有效 

	unsigned short usDSMAlarmL1:5;		//苏标DSM报警位(一级)
	unsigned short usDSMAlarmL2:5;		//苏标DSM报警位(二级)
	unsigned short usDistractedDriving:1;		//分神驾驶报警 2级(平台)
	unsigned short usFatigueLv:4;		//疲劳程度(1-10)
	unsigned short usReserve:1;			//预留:1位

	//unsigned char ucReserve2;			//预留:8位
	unsigned char ucAlarmEx;			//苏标报警扩展状态位,0位:(陕标)驾驶员IC 1级 1位:(陕标)驾驶员IC 2级
	unsigned char ucBSDAlarm:3;			//苏标盲区报警位
	unsigned char ucReserve3:5;			//预留:5位

}GPSVehicleExtraSBAlarm_S;

typedef union GPSVehicleExtra
{
	GPSVehicleExtraBusObd_S BusObd;
	GPSVehicleExtraVideoAlarm_S VideoAlarm;
	MDVRVehicleExtraUAE_S Uae;
	GPSVehicleExtraSBAlarm_S SBAlarm;
}GPSVehicleExtra_S;
static_assert(16 == sizeof(GPSVehicleExtraBusObd_S), "GPSVehicleExtraBusObd_S Length error");
static_assert(16 == sizeof(GPSVehicleExtraVideoAlarm_S), "GPSVehicleExtraVideoAlarm_S Length error");
static_assert(16 == sizeof(MDVRVehicleExtraUAE_S), "MDVRVehicleExtraUAE_S Length error");
static_assert(16 == sizeof(GPSVehicleExtraSBAlarm_S), "GPSVehicleExtraVideoAlarmSB_S Length error");

//确保GPSVehicleGpsNew_S长度为72字节
typedef struct _tagGPSVehicleGpsNew
{
	GPSTime_S Time;
	unsigned int uiSpeed:14;	//速度值 KM/S	9999 = 999.9 	范围(0-16384)
	unsigned int uiYouLiang:18;	//油量   升	9999 = 99.99 	范围(0-262100)
	unsigned int uiLiCheng;		//里程   公里	9999 = 9.999 	
	unsigned int uiHangXiang:9;	//地面航向，(0-360) 范围(0-512)
	unsigned int uiMapType:3;	//地图类型		1表示GOOGLE，2表示百度，0表示无效
	unsigned int uiNetWorkType:4;	//网络类型(3G类,WIFI,有线,4G)
	unsigned int uiTachographSpeed:14;  //速度值 KM/S	9999 = 999.9 	范围(0-16384) 行驶记录仪速度		
										//ttx协议: 为人员时，解析为  电池电量  0-100，  90 = 90%
	//unsigned int uiReserve:2;  //保留位1
	unsigned int uiLongGps : 2;		//长GPS,表示此结构体后面还有72个字节的数据  0位有效表示libmdvrnet数据有效  1位有效表示Gateway/数据库数据有效
	unsigned int uiStatus[4];		//目前只使用，每1个状态	0位表示GPS定位状态（0无效，1有效）
	short sTempSensor[4];	//温度传感器的状态
	int	nJingDu;		//经度	4字节 整数部分	9999999 = 9.999999 
	int nWeiDu;			//纬度	4字节 整数部分	9999999 = 9.999999
	short nGaoDu;			//高度，暂时未使用
	unsigned short usSatellites:4;	//卫星数，大于0时显示，范围0-12
	unsigned short usReserve:8;		//保留字段
	unsigned short usExtraFlag:4;	//附加信息标志， 默认为0
	int	nParkTime;		//停车时长 秒	在静止状态时有效
	GPSVehicleExtra_S  Extra;		//联合体
}GPSVehicleGpsNew_S;
const int GPSVehicleGpsNew_LEN = sizeof(GPSVehicleGpsNew_S);
static_assert(72 == GPSVehicleGpsNew_LEN, "GPSVehicleGpsNew_S Length error");

typedef struct _GPSVehicleState
{
	char	szDevIDNO[32];
	GPSVehicleGps_S	Gps;
}GPSVehicleState_S;

typedef struct _GPSVehicleLongState
{
	char	szDevIDNO[32];
	GPSVehicleLongGps_S	Gps;
}GPSVehicleLongState_S;

typedef struct _GPSVehicleStatus
{
	char	szDevIDNO[32];
	BOOL	bOnline;
	int		nNetworkType;
	char	szNetworkName[32];
}GPSVehicleStatus_S;

typedef struct _tagGPSAlarmInfo
{
	char	guid[36];			//标识唯一的报警信息
	GPSVehicleGps_S Gps;		//报警时候的GPS信息
	GPSTime_S Time;				//报警时间
	short 	AlarmType;			//报警类型
	short 	AlarmInfo;			//报警信息
	int	Param[4];				//报警参数
	char szDesc[256];			//报警描述
	//说明srcAlarmType和srcTime，当报警类型为报警图片上传完成时有效，表示对应的报警参数信息，图片上传完成报警类型
	//报警类型为图片上传报警时，只使用AlarmType和szImgFile参数，其它参数表示对应报警参数
	short srcAlarmType;			//源报警类型
	short sReserve;				//保留参数 (V6版本报警联动用到)
	GPSTime_S srcTime;			//源报警时间
	char szImgFile[256];		//图片文件信息，用;分隔，为http地址路径，可以为多个图片信息
	//报警开始类型
	short AlarmStartType;
	char bSendOnly;				//1表示只发送，用在报警回掉中，防止再次把报警放入插件中处理
	char cHandleStatus;			//处理标志位，0位：0表示未处理， 1表示已处理； 1位：0表示未确认， 1表示已确认
	char cUtf8Text;				//Utf8编码,表示本报警的描述和图片信息,仅用于服务器保存数据使用 0位:0表示szDesc使用ASCII,1表示使用Utf8 1位:szImgFile
	char szReserve[59];			//保留字段
}GPSAlarmInfo_S, *LPGPSAlarmInfo_S;

typedef struct _GPSVehicleAlarm
{
	char	szDevIDNO[32];
	GPSAlarmInfo_S	Alarm;
}GPSVehicleAlarm_S;

//hw 2014/1/23 
//-- begin
typedef struct _tagGPSAlarmInfoEx
{
	char	guid[36];			//标识唯一的报警信息
	GPSVehicleGps_S Gps;		//报警时候的GPS信息
	GPSTime_S Time;				//报警时间
	short 	AlarmType;			//报警类型
}GPSAlarmInfoEx_S, *LPGPSAlarmInfoEx_S;

typedef struct _tagGPSConfigData
{
	int nLength;		//数据缓存长度
	char cBuffer[1024];	//数据内容
}GPSConfigData_S, *LPGPSConfigData_S;

typedef struct _tagGPSConfigDataEx
{
	int nLength;		//数据缓存长度
	char cBuffer[2048];	//数据内容
}GPSConfigDataEx_S, *LPGPSConfigDataEx_S;

typedef struct _tagGPSTransPortData
{
	int nType;					//类型
	GPSConfigData_S	Data;		//透传数据
}GPSTransPortData_S, *LPGPSTransPortData_S;

//透传转换报警
typedef struct tagGPSAlarmTPD 
{
	char	szDevIDNO[32];
	GPSAlarmInfoEx_S VehiAlarm;
	GPSTransPortData_S TPD;	
}GPSAlarmTPD_S, *LPGPSAlarmTPD_S;
//-- end

//报警日志数目
typedef struct _tagGPSAlarmCount
{
	int nCount;
	char szReserve[8];
}GPSAlarmCount_S, *LPGPSAlarmCount_S;

//车辆轨迹(包含GPS和报警)
typedef struct _tagGPSVehicleTrack
{
	int nType;					//标识该数据类型(GPS数据或者报警数据)
	GPSVehicleAlarm_S Alarm;	//报警数据(如果类型为GPS数据 则只有GPS字段数据有效)
}GPSVehicleTrack_S, *LPGPSVehicleTrack_S;

//轨迹点数目
typedef struct _tagGPSTrackCount
{
	int nCount;
	char szReserve[8];
}GPSTrackCount_S, *LPGPSTrackCount_S;

//设备轨迹点信息
typedef struct _tagGPSDevTrackCountInfo
{
	char szDevIDNO[32];	//设备编号
	int nGPSValid;		//GPS有效(0-无效 1-有效)
	int nCount;			//数目
	char szReserve[8];
}GPSDevTrackCountInfo_S, *LPGPSDevTrackCountInfo_S;

//设备轨迹点数目
typedef struct _tagGPSTrackDevCount
{
	int nDevCount;					//设备数目
	GPSDevTrackCountInfo_S Info[8];	//最大8个设备轨迹信息
}GPSTrackDevCount_S, *LPGPSTrackDevCount_S;


typedef struct _tagGPSTrackInFenceInfo
{
	int		nVehiID;				//车辆ID
	GPSTime_S BeginTime;		//开始时间
	GPSTime_S EndTime;			//结束时间
	int		nStartJingDu;		//进入区域经度	4字节 整数部分	9999999 = 9.999999 
	int		nStartWeiDu;		//进入区域纬度	4字节 整数部分	9999999 = 9.999999
	int		nEndJingDu;			//离开区域经度	4字节 整数部分	9999999 = 9.999999 
	int		nEndWeiDu;			//离开区域纬度	4字节 整数部分	9999999 = 9.999999
	char szRes[32];				//保留32
}GPSTrackInFenceInfo_S, *LPGPSTrackInFenceInfo_S;

const int GPS_VEHICLE_ALARM_LENGTH = sizeof(GPSVehicleAlarm_S);
const int GPS_ALARM_INFO_LENGTH = sizeof(GPSAlarmInfo_S);
const int GPS_VEHICLE_GPS_LENGTH = sizeof(GPSVehicleGps_S);
const int GPS_VEHICLE_RUN_LENGTH = sizeof(GPSVehicleState_S);
const int GPS_VEHICLE_STATUS_LENGTH = sizeof(GPSVehicleStatus_S);
const int GPS_VEHICLE_TRACK_LENGTH = sizeof(GPSVehicleTrack_S);
const int GPS_VEHICLE_RUN_LONG_LENGTH = sizeof(GPSVehicleLongState_S);

//透明串口数据
typedef struct _tagGPSTranPortData
{
	int nID;
	char szDevIDNO[32];	//车机编号
	int nType;			//类型
	SYSTEMTIME Time;		//时间
	int	nLength;		//长度
	char cData[1280];	//数据长度
}GPSTranPortData_S, *LPGPSTranPortData_S;

//透明串口数据数目
typedef struct _tagGPSTranPortDataCount
{
	int nCount;
	char szReserve[8];
}GPSTranPortDataCount_S, *LPGPSTranPortDataCount_S;

const int GPS_TRAN_PORT_DATA_LENGTH = sizeof(GPSTranPortData_S);

#define GPS_WLAN_TYPE_2G					0
#define GPS_WLAN_TYPE_3G_EVDO				1
#define GPS_WLAN_TYPE_3G_WCDMA				2
#define GPS_WLAN_TYPE_TD_WCDMA				3
#define GPS_WLAN_TYPE_TD_LED				4
#define GPS_WLAN_TYPE_FDD					5

typedef struct _tagGPSWLanStatus
{
	int nWLanActive;	//
	int	nWLanType;		////0：表示2G;1：表示3G-EVDO; 2：表示3G-WCDMA 
	int nWLanQuantity;	//信号值	不显示
	char szWLanAddr[32];//网络地址
}GPSWLanStatus_S, *LPGPSWLanStatus_S;

typedef struct _tagGPSWifiStatus
{
	int nWifiActive;
	char szWifiAP[32];	//hide
	int nWifiQuantity;	//hide
	char szWifiAddr[32];//
}GPSWifiStatus_S, *LPGPSWifiStatus_S;

typedef struct _tagGPSDiskInfo
{
//	int nAllVolume;		//15923	表示159.23	G //总容量
	int nAllVolume:24;	//15923	表示159.23	G //总容量
	int nDiskType:8;	//硬盘类型
	int nLeftVolume;	//同上  ///剩余容量
}GPSDiskInfo_S, *LPGPSDiskInfo_S;

const int GPS_DISK_INFO_COUNT			= 8;	//最多硬盘数目为8个

typedef struct _tagGPSDeviceStatus
{
	//硬盘序列号, 以 | 分隔，共有硬盘数目序列号			
		//DevInfo.sSerialNumber、DevInfo.szDevID用于存储硬盘序列号
	GPSDeviceInfo_S	DevInfo;	//设备信息
	GPSWLanStatus_S	WLanInfo;	//3G状态
	GPSWifiStatus_S	WifiInfo;	//WIFI信息
	GPSDiskInfo_S	DiskInfo[GPS_DISK_INFO_COUNT];	//硬盘信息
	int	nVideoLost;		//视频丢失状态  1表示该视频丢失
	int nRecord;		//录像状态 0：没有录像，1录像
	int nVideoTran;		//视频传输数目
	long l3GFlow;		//KB为单位，从月结日开始算，累加
	long l4GFlow;		//KB为单位，从月结日开始算，累加
	char cDiskNum;		//硬盘数目
	char cNetType;		//网络类型	0,3g,1 wifi, 2 net, 3 4g
	char cVersion;		//为1时，cNetType有效  devinfo里面的cPlateNumber为imei信息
	char cReserve;	//保留参数
	int nReserve;	//保留参数
}GPSDeviceStatus_S, *LPGPSDeviceStatus_S;

const int GPS_MOTION_MASK = 9;

typedef struct _tagGPSMotionParam
{
	int	nMask[GPS_MOTION_MASK];	//低11位表示移动侦测
	BOOL bEnable;	//是否启用
	int	nSensitive;	//灵敏度
}GPSMotionParam_S, *LPGPSMotionParam_S;

typedef struct _tagGPSVideoColor
{
	int nExposure;		//爆光度
	int	nBrightness;	//亮度
	int	nConstract;		//对比度
	int	nHue;			//色调	
	int	nSaturate;		//饱合度
}GPSVideoColor_S, *LPGPSVideoColor_S;

//向车辆发送FTP文件上传指令
typedef struct _tagGPSFtpUploadFileTask
{
	int nTaskType;					//0:暂停,1:继续,2:取消,3:新建任务
	char szFtpSvrIp[32];			//服务器
	unsigned short usSvrPort;		//服务端口
	unsigned short usSequence;		//流水号 当类型为0,1,2时有效
	char szAccount[32];				//用户名
	char szPassword[32];			//密码
	char szFilePath[MAX_PATH];		//上传路径
	int nChnMask;					//逻辑通道号
	SYSTEMTIME BegTime;				//开始时间
	SYSTEMTIME EndTime;				//结束时间
	int nAlarmFlag1;				//报警标志位1
	int nAlarmFlag2;				//报警标志位2
	char cResourceType;				//0：音视频， 1：音频， 2：视频, 3.音视频或者音频
	char cStreamType;				//-1:主码流或者子码流,0：主码流,1：子码流
	char cStoreType;				//0:主存储器或者灾备存储器, 1：主存储器， 2：灾备存储器
	char cNetworkMask;				//任务执行网络 bit0:WFIF,bit1:LAN,bit2:3G/4G
	char szReserve[32];
}GPSFtpUploadFileTask_S, *LPGPSFtpUploadFileTask_S;

//获取FTP信息
typedef struct _tagGPSFtpUpLoadInfo
{
	char szFtpSvrIp[32];			//服务器
	unsigned short usSvrPort;		//服务端口
	unsigned short usSequence;		//流水号 当类型为0,1,2时有效
	char szAccount[32];				//用户名
	char szPassword[32];			//密码
	char szFilePath[MAX_PATH];		//上传目录
}GPSFtpUpLoadInfo_S, *LPGPSFtpUpLoadInfo_S;


//////////////////////////////////////////////////////////////////////////
//hw 2012-11-07
//网络流量参数
typedef struct _tagGPSNetFlowParam
{
	int nIsOpenFlowCount;		//流量统计开关 0-关闭，1-开启
	int nIsOpenDayFlowRemind;	//日流量提醒 0-不提醒 1-提醒
	int nIsOpenMonthFlwRemind;	//月流量提醒 0-不提醒 1-提醒
	float fDayLimit;			//日流量限制(MB)
	float fMonthLimit;			//月流量限制(MB)
	int nDayRemind;				//每天流量提醒（百分比），20%即20
	int nMonthRemind;			//每月流量提醒（百分比），20%即20
	int nMonthTotleDay;			//月结日
	unsigned char ucFlowLimitType;	//0表示参数无效,1表示不开启,2表示开启
	char szRes[31];				//保留32
}GPSNetFlowParam_S, *LPGPSNetFlowParam_S;

//网络流量统计
typedef struct _tagGPSNetFlowStatistics
{
	GPSNetFlowParam_S	FlowParam;	//流量参数
	float fFlowUsedToday;			//今日流量
	float fFlowUsedMonth;			//本月已使用流量
	SYSTEMTIME StatisticsTime;
	char szRes[20];					//保留32
}GPSNetFlowStatistics_S, *LPGPSNetFlowStatistics_S;	

//end
//////////////////////////////////////////////////////////////////////////

//调度指令
typedef struct _tabGPSDispatchCommand
{
	char szGuid[40];		//指令GUID
	int nMapType;			//目的地，地图类型，1表示GOOGLE，2表示百度
	int nJingDu;			//经度
	int nWeiDu;				//纬度
	char szCommand[256];	//命令字
}GPSDispatchCommand_S, *LPGPSDispatchCommand_S;


typedef union _tagUNCfg
{
// 	HI_S_Video cfgVideo;				/* 视频参数 */
// 	HI_S_Audio cfgAudio;				/* 音频参数 */
// 	HI_E_AudioInput cfgAudioInput;		/* 音频输入参数 */
// 	HI_S_PTZ cfgPTZ;					/* 云台参数 */
}GPSCfg, *LPGPSCfg;

//文件信息
typedef struct _tagGPSRecHead_S
{
	int	nYear;			//年	2013
	int	nMonth;			//月	5
	int nDay;			//日	29
	int nBegHour;		//开始时间
	int nBegMinute;		
	int nBegSecond;
	unsigned __int64 u64BegPts;	//文件起始的时间戳
	unsigned int uiTotalMinSecond;	//文件总时长，毫秒
	unsigned int uiAudioCodec;		//音频解码器类型	TTX_AUDIO_CODEC_G726_40KBPS
	unsigned int uiAudioChannel;		//音频通道
	unsigned int uiAudioSamplesPerSec;	//音频采样率
	unsigned int uiAudioBitPerSamples;	//音频每个取样所需的位元数
	unsigned int uiInfoCodec;		//信息帧解码器	TTX_INFO_CODEC_WKP
	unsigned int uiVideoCodec;		//视频帧解码器	TTX_VIDEO_CODEC_H264
	unsigned char ucResolution;		//分辨率		TTX_RESOLUTION_720P
	char szReserve[59];		//保留字段
} GPSRecHead_S, *LPGPSRecHead_S;

typedef struct _tagGPSUsrLog
{
	int nUsrID;
	int nMainType;
	int nSubType;
	char szDevIDNO[40];
	char szParam1[256];
	char szParam2[256];
	char szParam3[256];
	char szParam4[256];
	GPSTime_S time;
	char szReserve[64];
}GPSUsrLog_S, *LPGPSUsrLog_S;

//用户基本信息
typedef struct _tagUserBasicInfo
{
	int nUserID;				//用户ID		
	char szUserName[32];		//用户名称
	int nGroupID;				//分组ID
	char cOnline;				//在线状态
	char szReserve[27];			//保留32
}UserBasicInfo_S, *LPUserBasicInfo_S;


//用户日志数目
typedef struct _tagGPSUsrLogCount
{
	int nCount;
	char szReserve[8];
}GPSUsrLogCount_S, *LPGPSUsrLogCount_S;


//联系人
typedef struct _tagContactInfo
{
	char szName[32];			//姓名
	char szPhone[16];			//手机
	char szTel[16];				//电话
	char szReserve[16];			//保留16
}ContactInfo_S, *LPContactInfo_S;

//学生信息
typedef struct _tagStudentInfo
{
	char szCarNum[32];			//卡号
	char szName[32];			//学生姓名
	int nStudySection;			//0-未知 1-幼儿园 2-小学 3-初中 4-高中 5-大学
	int nGrade;					//0-未知，1-1年级，2-2年级
	int nClass;					//0-未知，1-1班 2-2班
	ContactInfo_S Contact1;		//联系人1
	ContactInfo_S Contact2;		//联系人2
	char szEmail[64];			//email
	char szAddress[256];		//地址
	char szRemark[256];			//备注
	char szReserve[256];		//保留256
}StudentInfo_S, *LPStudentInfo_S;


typedef struct _tagDeviceDevIPInfo
{
	GPSDeviceIDNO_S DevIDNO;
	int nPort;
	char szIP[16];
	char szReserve[16];
}DeviceDevIPInfo_S, *LPDeviceDevIPInfo_S;


typedef struct _tagGPSPictureDataInfo
{
	unsigned char cDataPackIndex;		//图像数据是第N个包
	unsigned char cChannel;				//通道号0 开始
	unsigned char cPictureIndex;		//表示图片序号,范围：0~8
	unsigned char cStatus;				//主机状态:0x01 表示劫警，0x02表示自定义高，0x03表示自定义低，0x04表示定时回传图像，0x05表示捕捉图像回传
	unsigned char cCountPack;			//总包数
	char nResult;						//结果 0：成功/确认；1：失败；2：消息有误；3：不支持；4：报警确认处理
	char bMediaFinished;				//是否完成
	char cReserve;						//保留
}GPSPictureDataInfo_S, *LPGPSPictureDataInfo_S;

//设备要下载的文件信息
typedef struct _tagGPSDownFileInfo
{
	int nFileType;		//文件类型，1图片文件，2表示升级文件
	char szParam[256];	//中间使用逗号(,)分隔
	int nFileID;		//文件ID
	char szFile[256];	//文件路径
	char szIP[64];		//服务器IP
	unsigned short usPort;	//端口
	unsigned short usReserve;
	char szMd5[40];		//MD5校验
	char szReserve[32];	//保留参数
}GPSDownFileInfo_S;

//JT808媒体数据
typedef struct _tagGPSMediaDataInfo
{
	unsigned int uiMediaID;				//媒体ID
	unsigned char ucMediaType;			//媒体类型 0-图片;1-音频;2-视频
	unsigned char ucCodeFormat;			//编码格式 0-JPEG;1-TIF;2-MP3;3-WAV;4-WMV	
	unsigned char ucEventType;			//事件项 0-平台下发指令;1-定时动作;2-抢劫报警触发;4-碰撞侧翻报警触发;其他保留
	unsigned char ucChannel;			//通道ID
	unsigned short usTotal;				//总包数
	unsigned short usIndex;				//包序号，从1开始
	char nReserve[32];					//保留
}GPSMediaDataInfo_S, *LPGPSMediaDataInfo_S;

typedef struct _tagGPS808TerminalInfo
{
	unsigned short	usProvince;		//省际ID
	unsigned short  usCity;			//市际ID
	char szFactory[12];				//制造商编码
	char szTerminalType[24];		//终端型号
	char szTerminalID[24];			//终端ID
	unsigned char  ucPlateColor;	//车牌颜色
	char szPlate[31];				//车牌号
	char cRegisterFlag;				//注册标志位
	char szFactoryAsc[11];			//制造商ASC
	char szIMEI[16];				//无线模块IMEI号
	char szICCID[24];				//终端SIM卡号的ICCID号
	char cExtraFlag;				//扩展标志
	char szReserve[11];				//保留参数
	// 160 字节
	// if (cExtraFlag >= 1) 时有效
	char szFactory2[20];
	char szTerminalType2[12];
	char szTerminalID2[12];
	char szFactoryAsc2[20];
	char szSoftVer[24];				//软件版本号
	// 248字节
}GPS808TerminalInfo_S, *LPGPS808TerminalInfo_S;

const int GPS808TerminalInfo0_LEN = 160;
const int GPS808TerminalInfo1_LEN = 248;
const int GPS808TerminalInfo_LEN = sizeof(GPS808TerminalInfo_S);


//设备报警录像报警类型定义
typedef enum
{
	FILE_ALARM_INFO_URGENCY_BUTTON  =0 ,		//紧急按钮报警
	FILE_ALARM_INFO_OVERSPEED 		=1 ,		//超速报警
	FILE_ALARM_INFO_LOWSPEED 		=2 ,		//低速报警
	FILE_ALARM_INFO_SHARK			=3 ,		//振动报警
	FILE_ALARM_INFO_TEMPERATOR 		=4 ,		//温度报警
	FILE_ALARM_INFO_TMOTION			=5 ,		//移动侦测报警
	FILE_ALARM_INFO_UPS_CUT			=6 ,		//UPS剪断报警
	FILE_ALARM_INFO_COLLISION		=7 ,		//碰撞侧翻
	FILE_ALARM_INFO_FATIGUE			=8 ,		//疲劳驾驶
	FILE_ALARM_INFO_IO1				=9 ,		//IO1报警
	FILE_ALARM_INFO_IO2				=10, 		//IO2报警
	FILE_ALARM_INFO_IO3				=11,		//IO3报警
	FILE_ALARM_INFO_IO4				=12, 		//IO4报警
	FILE_ALARM_INFO_IO5				=13, 		//IO5报警
	FILE_ALARM_INFO_IO6				=14, 		//IO6报警
	FILE_ALARM_INFO_IO7				=15, 		//IO7报警
	FILE_ALARM_INFO_IO8				=16, 		//IO8报警
	FILE_ALARM_INFO_RAPID_ACCELERATION =17,		//急加速告警 华宝定制
	FILE_ALARM_INFO_RAPID_DECELERATION =18,		//急减速告警 华宝定制
	FILE_ALARM_INFO_REVERSING		 =19,		//倒车告警 华宝定制
	FILE_ALARM_INFO_CUS_OVER_SPEED	 =20,		//超速告警 华宝定制
	FILE_ALARM_INFO_DISTRACTION		= 21,		//司机分神 华宝定制
	FILE_ALARM_INFO_NO_PORTRAIT		= 22,		//无人像 华宝定制
}GPS_ALARM_REC_TYPE_E;


//报站信息
const char REPORT_FALG_GPS = 0;			//GPS
const char REPORT_FALG_STATION = 1;		//站点
typedef struct _tagGPSStation_S
{
	GPSTime_S	Time;						//报站时间
	GPSVehicleGps_S	Gps;					//GPS位置
	char szJobNum[32];						//司机工号
	char szLineName[32];					//线路名称
	unsigned short usReportType;			//上报类型(0-GPS 1-过站)
// 	char szStationName[32];					//站点名称 最长20个字节的字符
	unsigned short uiLimitSpeed;			//限速 （为0则无效）
	char cSendOnly;							//只发送不存储
	unsigned char cReserve[31];				//保留字段
}GPSStation_S, *LPGPSStation_S;

typedef struct _tagGPSVehicleStation_S
{
	char szDevIDNO[32];
	GPSStation_S Station;
}GPSVehicleStation_S, *LPGPSVehicleStation_S;

//设备扩展数据
#define  GPS_EXDATA_TYPE_808_ALARM  1

typedef struct _tagGPSVehicleStateExData
{
	char szDevIDNO[32];
	GPSTime_S Time;
	int nDataType;
	char cData[512];
}GPSVehicleStateExData_S;

typedef struct _tagGPSVehicleStateAlarmParam
{
	int nParam[4];
}GPSVehicleStateAlarmParam_S;


//第0位 区域超速报警
//第1位 进出线路报警
//第2位 路段行驶时间不足/过长报警
//第3位 异常行驶报警:客运车禁止行驶
//第4位 异常行驶报警：山区禁行
//第5位 线路偏移
//第6位	设备升级状态和进度,0:状态(0：设备没有在升级 1：设备在升级，下载升级包中 2：设备在升级，写入固件中) 1:进度(0-100)
typedef struct _tagGPSVehicleStateExDataAlarm
{
	int nAlarmFlag;								//报警标志位
	GPSVehicleStateAlarmParam_S ArmParam[16];		//报警参数
}GPSVehicleStateExDataAlarm_S;


const int GPS_VEHICLE_STATE_EXDATA_LENGTH = sizeof(GPSVehicleStateExData_S);



//用户在线状态信息
typedef struct _tagUserOnlineStatusInfo_S
{
	int nUserID;				//用户ID
	char szAccount[32];			//登录账号
	char szName[32];			//用户名称

	int nGroupID;				//分组ID
	char szGroupName[32];		//分组名称

	int nOnlineStatus;			//在线状态
	GPSTime_S LoginTime;		//在线时表示上线时间,离线时代表上次上线时间

	char szIP[16];				//登录ip
	unsigned short usPort;		//登录端口
	unsigned short usClientType; //登录类型

	//int nCount;					//已登录的客户端数量

	GPSTime_S LogoutTime;		//登出时间
	char szReserve[24];			//保留
}UserOnlineStatusInfo_S, *LPUserOnlineStatusInfo_S;
const int USER_ONLINE_STATUS_INFO_LENGTH = sizeof(UserOnlineStatusInfo_S);
static_assert(USER_ONLINE_STATUS_INFO_LENGTH == 160, "USER_ONLINE_STATUS_INFO_LENGTH != 160");

typedef struct _tagUserOnlineStatusInfoEx_S 
{
	UserOnlineStatusInfo_S Info;
	char szAccountEx[64];
	char szNameEx[64];
	char szGroupNameEx[64];

}UserOnlineStatusInfoEx_S;


//SB相关结构体
typedef struct _tagGPSSBAlarmFileInfo
{
	unsigned char ucIndex;		//编号
	unsigned char ucType;		//类型 0x00：图片 0x01：音频 0x02：视频 0x03：文本 0x04：其它
	char szFileName[204];	//文件名称
	char szAlarmCode[20];	//报警标识 设备上报
	char szAlarmGUID[36];	//报警Guid 平台生成
	unsigned int uiLength;		//文件长度
}GPSSBAlarmFileInfo_S;

typedef struct _tagGPSSBAlarmFileListInfo
{
	char szAlarmCode[20];	//报警标识 设备上报
	char szAlarmGUID[36];	//报警Guid 平台生成
	unsigned char ucType;	//信息类型  0x00:正常报警文件   0x01：补传报警文件
	unsigned char ucCount;  //数目
	GPSSBAlarmFileInfo_S* pFileList;	//文件列表指针
}GPSSBAlarmFileListInfo_S;

typedef struct _tagGPSSBAlarmFileSupplement_S
{
	typedef struct _tagPack_S
	{
		unsigned int uiOffset;
		unsigned int uiLength;
	}Pack_S;
	char szFileName[MAX_PATH];		//文件名
	unsigned char ucType;			//文件类型 0x00：图片 	0x01：音频 	0x02：视频 	0x03：文本 	0x04：其它
	unsigned char ucResult;			//上传结果 0x00：完成 0x01：需要补传 
	unsigned char ucCount;			//补传数据包数量 需要补传的数据包数量，无补传时该值为 0 
	Pack_S PackData[10];			//补传数据包列表
}GPSSBAlarmFileSupplement_S;

//北斗808和国标升级文件
typedef struct _tagGPSUpgradeFileInfo
{
	char szFileName[256];
	int nFileLength;
	int nFileType;
	char szVersion[64];
	char szParam[256]; 
}GPSUpgradeFileInfo_S, *LPGPSUpgradeFileInfo_S;

//1078  设备对应的视频服务器地址
typedef struct _tagGPSDevVideoSvrReq
{
	unsigned char ucChn;		//通道号
	unsigned char ucResType;	//音视频类型
	char cReserve[18];			//保留字段
}GPSDevVideoSvrReq_S, *LPGPSDevVideoSvrReq_S;

typedef struct _tagGPSDevVideoServer
{
	char szServerIP[64];
	unsigned short usServerPort;
	unsigned short usReserve;
	char szReserve[32];
}GPSDevVideoServer_S, *LPGPSDevVideoServer_S;


#pragma pack()

#endif	
