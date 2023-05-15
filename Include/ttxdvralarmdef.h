#ifndef _TTX_DVR_ALARM_DEF_H_
#define _TTX_DVR_ALARM_DEF_H_

/******************************************************************************
  Author        : afu
  Created       : 2012/11/30
  Last Modified :
  Description   : 报警信息定义，每个报警由一个开始事件和一个结束事件组成
  History       :
	  1.	Date        : 2012/11/30
		Author      : leeafu
		Modification: Created file
******************************************************************************/

#define TTX_ALARM_TYPE_USEDEFINE				1		//自定义报警AlarmInfo为报警源，0位表示io1，第1位表示io2，以此类推
#define TTX_ALARM_TYPE_URGENCY_BUTTON			2		//紧急按钮报警AlarmInfo为按钮编号
#define TTX_ALARM_TYPE_SHAKE					3		//振动报警AlarmInfo（加速度报警，bit0：X方向,bit1：Y方向,bit2：Z方向，bit3：碰撞,bit4：侧翻）
#define TTX_ALARM_TYPE_VIDEO_LOST				4		//摄像头无信号报警alarmInfo为通道号，按位表示，第0位表示通道1
#define TTX_ALARM_TYPE_VIDEO_MASK				5		//摄像头遮挡报警alarmInfo为通道号，按位表示，第0位表示通道1
#define TTX_ALARM_TYPE_DOOR_OPEN_LAWLESS		6		//非法开门报警
#define TTX_ALARM_TYPE_WRONG_PWD				7		//三次密码错误报警
#define TTX_ALARM_TYPE_FIRE_LOWLESS				8		//非法点火报警
#define TTX_ALARM_TYPE_TEMPERATOR				9		//温度报警, AlarmInfo传感器编号（0表示传感器1，1表示传感器2）, param[0]温度类型（0表示超高温，1表示超低温）, param[1]当前温度10000=100度 
#define TTX_ALARM_TYPE_DISK_ERROR				10		//硬盘错误报警, alarmInfo为硬盘类型(TTX_DISK_TYPE_SD等) param[1]为磁盘序号，1表示磁盘1，2表示磁盘2
#define TTX_ALARM_TYPE_OVERSPEED				11		//超速报警,  param[0]当前速度9900=99公里, param[1]速度最低值, param[2]速度最高值, param[3]持续时间, alarmInfo: 1低速,2超速,3紧急加速,4紧急减速
#define TTX_ALARM_TYPE_BEYOND_BOUNDS			12		//越界报警
#define TTX_ALARM_TYPE_DOOR_ABNORMAL			13		////异常开关车门报警，alarmInfo为门标志
#define TTX_ALARM_TYPE_PARK_TOO_LONG			14		//停车时间过长报警，alarmInfo为停车时长，param[0]为设定的时间间隔(单位秒)
#define TTX_ALARM_TYPE_MOTION					15		//移动侦测报警，按位表示，第0位表示通道1
#define TTX_ALARM_TYPE_ACC_ON					16		//ACC开启报警
#define TTX_ALARM_TYPE_DEV_ONLINE				17		//设备在线
#define TTX_ALARM_TYPE_GPS_SIGNAL_LOSS          18      //GPS讯号丢失开始
//#define TTX_ALARM_TYPE_IO_1                     19      //IO_1报警
//#define TTX_ALARM_TYPE_IO_2                     20      //IO_2报警
//#define TTX_ALARM_TYPE_IO_3                     21      //IO_3报警
//#define TTX_ALARM_TYPE_IO_4                     22      //IO_4报警
//#define TTX_ALARM_TYPE_IO_5                     23      //IO_5报警
//#define TTX_ALARM_TYPE_IO_6                     24      //IO_6报警
//#define TTX_ALARM_TYPE_IO_7                     25		//IO_7报警
//#define TTX_ALARM_TYPE_IO_8                     26      //IO_8报警

//27-34 为电子围栏报警
#define TTX_ALARM_TYPE_IN_FENCE				27	 //进入区域(	 param[0]-位置类型 param[1]-区域或者线路ID
#define TTX_ALARM_TYPE_OUT_FENCE	 		28	//出区域 param[0]-位置类型 param[1]-区域或者线路ID
//param[0]暂时不使用
//param[1]对应设置里面的    //aid: (area id)区域id 当产生报警后要把区域id返回给服务器

//以下4个报警不争对车载项目
#define TTX_ALARM_TYPE_FIRE                     35      //火警
#define TTX_ALARM_TYPE_PANIC                    36      //劫警
#define TTX_ALARM_TYPE_TASK_FINISHED			37		//调度任务完成
#define TTX_ALARM_TYPE_IMAGE_UPLOAD				38		//图片上传完成

//39-40为硬盘1, 硬盘2不存在

//#define TTX_ALARM_TYPE_IO_9                     41      //IO_9报警
//#define TTX_ALARM_TYPE_IO_10                    42      //IO_10报警
//#define TTX_ALARM_TYPE_IO_11                    43      //IO_11报警
//#define TTX_ALARM_TYPE_IO_12                    44      //IO_12报警

//45为GPS无效

#define TTX_ALARM_TYPE_REFUEL					46		//加油	AlarmInfo为加油的油量(9999=99.99升)，Param[0]为加油前油耗
#define TTX_ALARM_TYPE_STILL_FUEL				47		//偷油	AlarmInfo为偷油的油量(9999=99.99升)，Param[0]为偷油前油耗

#define TTX_ALARM_TYPE_TRANSPARENT				48		//串口透传数据
#define TTX_ALARM_TYPE_FATIGUE					49		//疲劳驾驶	AlarmInfo表示报警级别	0 , 没有， 1  一级报警 2 二级报警, 3 三级报警, 4 关注度报警

#define TTX_ALARM_TYPE_END_USEDEFINE			51		//自定义报警
#define TTX_ALARM_TYPE_END_URGENCY_BUTTON		52		//紧急按钮报警
#define TTX_ALARM_TYPE_END_SHAKE				53		//振动报警
#define TTX_ALARM_TYPE_END_VIDEO_LOST			54		//摄像头无信号报警
#define TTX_ALARM_TYPE_END_VIDEO_MASK			55		//摄像头遮挡报警
#define TTX_ALARM_TYPE_END_DOOR_OPEN_LAWLESS	56		//非法开门报警
#define TTX_ALARM_TYPE_END_WRONG_PWD			57		//三次密码错误报警
#define TTX_ALARM_TYPE_END_FIRE_LOWLESS			58		//非法点火报警
#define TTX_ALARM_TYPE_END_TEMPERATOR			59		//温度报警
#define TTX_ALARM_TYPE_END_DISK_ERROR			60		//硬盘错误报警
#define TTX_ALARM_TYPE_END_OVERSPEED			61		//超速报警
#define TTX_ALARM_TYPE_END_BEYOND_BOUNDS		62		//越界报警
#define TTX_ALARM_TYPE_END_DOOR_ABNORMAL		63		//异常开关车门报警
#define TTX_ALARM_TYPE_END_PARK_TOO_LONG		64		//停车时间过长报警
#define TTX_ALARM_TYPE_END_MOTION				65		//移动侦测报警
#define TTX_ALARM_TYPE_ACC_OFF					66		//ACC关闭报警
#define TTX_ALARM_TYPE_DEV_DISONLINE			67		//设备断线
#define TTX_ALARM_TYPE_END_GPS_SIGNAL_LOSS      68      //GPS讯号丢失结束
//#define TTX_ALARM_TYPE_END_IO_1                 69      //IO_1报警
//#define TTX_ALARM_TYPE_END_IO_2                 70      //IO_2报警
//#define TTX_ALARM_TYPE_END_IO_3                 71      //IO_3报警
//#define TTX_ALARM_TYPE_END_IO_4                 72      //IO_4报警
//#define TTX_ALARM_TYPE_END_IO_5                 73      //IO_5报警
//#define TTX_ALARM_TYPE_END_IO_6                 74      //IO_6报警
//#define TTX_ALARM_TYPE_END_IO_7                 75      //IO_7报警
//#define TTX_ALARM_TYPE_END_IO_8                 76      //IO_8报警

//77-84 为电子围栏报警
#define TTX_ALARM_TYPE_END_IN_FENCE	             	77      //进入区域报警     param[0]-位置类型 param[1]-区域或者线路ID
#define TTX_ALARM_TYPE_END_OUT_FENCE	        78      //出区域报警   param[0]-位置类型 param[1]-区域或者线路ID

//#define TTX_ALARM_TYPE_END_IO_9                 91      //IO_9报警
//#define TTX_ALARM_TYPE_END_IO_10                92      //IO_10报警
//#define TTX_ALARM_TYPE_END_IO_11                93      //IO_11报警
//#define TTX_ALARM_TYPE_END_IO_12                94      //IO_12报警

#define TTX_ALARM_TYPE_END_FATIGUE				99		//疲劳驾驶	AlarmInfo表示报警级别	0 , 没有， 1  一级报警 2 二级报警, 3 三级报警, 4 关注度报警

//有文件需要上传
#define TTX_ALARM_TYPE_UPLOAD_FILE              109     //录像文件需要上传AlarmInfo类型1表示JPG图片，2表示录像文件,  szDesc为文件绝对路径
														//param[0] = 文件长度，param[1] = 文件类型(常规或者报警)，param[2] = 文件时长, param[3] = 通道
														//param[4] = 对应的报警类型alarmtype，param[5]对应的alarmInfo
														//szReserve = 文件开始时间，如: 2013-06-13 100001
														//当为JPG图片时，文件时长无效
#define TTX_ALARM_TYPE_CUSTOM					113		//自定义报警, AlarmInfo表示类型
														// param[0]表示参数1，param[1]表示参数2，param[2]表示参数3, param[3]表示参数4, 
														//szDesc表示内容，为字符串格式，中间不允许出现'\0'，最长为256个字节
#define TTX_ALARM_TYPE_UPLOAD_COMPLETE          114		//通知文件下载完成, param[0]表示文件ID，param[1]表示文件类型


#define TTX_ALARM_TYPE_USP_CUT		 			155		//UPS 剪线报警
#define TTX_ALARM_TYPE_END_USP_CUT				156
#define TTX_ALARM_TYPE_HDD_HIGH_TEMPERATURE		157		//硬盘超温报警, alarmInfo为硬盘号0表示1,param[0]表示硬盘类型TTX_DISK_TYPE_SD, param[1]当前温度100=100度
#define TTX_ALARM_TYPE_END_HDD_HIGH_TEMPERATURE	158
#define TTX_ALARM_TYPE_BEFORE_BOARD_OPENED		159		//前面板被撬开
#define TTX_ALARM_TYPE_END_BEFORE_BOARD_OPENED	160		
#define TTX_ALARM_TYPE_TURN_OFF					161		//关机上报	,	alarmInfo为原因: 1ACC 无效关机,2定时关机,3软件重启, 4软件异常关机,5掉电关机,6硬盘锁打开关机
#define TTX_ALARM_TYPE_DISK_SPACE_WARNING		162		//硬盘空间警告,alarmInfo为硬盘号,param[0]表示硬盘类型TTX_DISK_TYPE_SD, param[1]总空间, param[2]剩余空间,  16000表示空间为16000MB
#define TTX_ALARM_TYPE_END_DISK_SPACE_WARNING	163		//硬盘空间警告,alarmInfo为硬盘号,param[0]表示硬盘类型TTX_DISK_TYPE_SD, param[1]总空间, param[2]剩余空间,  16000表示空间为16000MB
#define TTX_ALARM_TYPE_SIMCARD_LOST				164		//SIMCARD丢失报警
#define TTX_ALARM_TYPE_END_SIMCARD_LOST			165		//SIMCARD丢失报警
#define TTX_ALARM_TYPE_TPMS				166		//	胎压报警, alarmInfo  TPMS报警类型（1表示电池电压警告，2-胎压过高，3-胎压过低 4-漏气 5-温度异常（只有过高））,
												//			param[0] 当前温度 如: 200 = 20度
												//			param[1] 当前胎压 如: 25 = 2.5P
												//			param[2] 当前电压 如: 102=10.2V
												//			param[3] 传感器编号（01表示TPMS左1，02表示TPMS左2，03表示TPMS左3，04表示TPMS左4，11表示TPMS右1，12表示TPMS右2，13表示TPMS右3，14表示TPMS右4）

#define TTX_ALARM_TYPE_END_TPMS			167		//TPMS报警

#define TTX_ALARM_TYPE_DEVICE_UNLOCKED		182		//设备开锁
#define TTX_ALARM_TYPE_DEVICE_LOCKED		183		//设备上锁

#define TTX_ALARM_TYPE_SWITCH_VIEW				301		//切换视频，alarminfo表示通道号，param[0]: 0表示还原，1表示最大化

//进出区域的自定义报警
#define TTX_ALARM_CUSTOM_INOUT_AREA		 351		//param2为区域id，param3为类型（0为进入，1为离开）
#define TTX_ALARM_CUSTOM_END_INOUT_AREA	 352	 	//param2为区域id，param3为类型（0为进入，1为离开）

#pragma pack(4)

typedef struct _tagTTXAlarmInfo
{
	unsigned int AlarmType;			//报警类型
	unsigned int AlarmInfo;			//报警信息
	int		Param[8];			//报警参数
	char	szDesc[256];		//报警描述
	char	szReserve[64];		//保留字段
}TTXAlarmInfo_S, *LPTTXAlarmInfo_S;

#pragma pack()

#endif

