#ifndef _TTX_DVR_NET_DEF_H_
#define _TTX_DVR_NET_DEF_H_

/******************************************************************************
  Author        : afu
  Created       : 2012/11/30
  Last Modified :
  Description   : 网络库通用信息定义
  History       :
	  1.	Date        : 2012/11/30
		Author      : leeafu
		Modification: Created file
******************************************************************************/

#ifdef WIN32

	#ifdef LIBDVRNET_EXPORTS
	#define LIBDVRNET_API __declspec(dllexport)
	#else
	#define LIBDVRNET_API __declspec(dllimport)
	#endif

#else

	#define LIBDVRNET_API

#endif

#include "ttxtypedef.h"

#define TTX_NET_VERSION 		"V6.1.53 20191205"


#define TTX_MAX_CHANNEL			16		//最多通道数目
#define TTX_MAX_SESS			4		//最多会话数目
#define TTX_MAX_STREAM			4		//最多码流数目
//错误码定义
#define TTX_NET_OK				0		//成功
#define TTX_NET_FALSE			-1		//失败
#define TTX_NET_ERR_PARAM		-2		//参数错误
#define TTX_NET_ERR_EXIST		-3		//已经存在
#define TTX_NET_ERR_NETWORK		-4		//网络错误
#define TTX_NET_ERR_BUF_FULL	-5		//发生缓存满的情况
#define TTX_NET_ERR_NO_RUNNING	-6		//未启动网络服务

//客户端登录类型
#define TTX_LOGIN_TYPE_LINUX 	0		//默认为嵌入式
#define TTX_LOGIN_TYPE_WINDOW	1		//windowsPC电脑
#define TTX_LOGIN_TYPE_WEB		2		//IOS端
#define TTX_LOGIN_TYPE_ANDROID	3		//ANdroid端
#define TTX_LOGIN_TYPE_IOS		4		//IOS端

//GPS状态定义
#define TTX_GPS_VALID 			'A'		//GPS有效
#define TTX_GPS_UNVALID 		'V'		//GPS无效
#define TTX_GPS_LONGITUDE_EAST 	'E'		//东经
#define TTX_GPS_LONGITUDE_WEST  'W'		//西经
#define TTX_GPS_LATITUDE_NORTH  'N'		//北纬
#define TTX_GPS_LATITUDE_SOUTH  'S'		//南纬

//GPS坐标类型定义
#define	TTX_COOR_TYPE_WSG84		0		//WSG84类型坐标
#define	TTX_COOR_TYPE_GCJ02		1		//火星坐标，高德地图使用
#define	TTX_COOR_TYPE_BD09		2		//百度坐标

//GPS定位类型定义
#define	TTX_LOC_TYPE_GPS		0		//GPS定位
#define	TTX_LOC_TYPE_LBS		1		//基站
#define	TTX_LOC_TYPE_WIFI		2		//WIFI定位

//硬盘状态定义
#define TTX_DISK_NO_EXIST		0		//硬盘不存在
#define TTX_DISK_EXIST			1		//硬盘存在
#define TTX_DISK_NO_ELEC		2		//硬盘断电

//3G模块状态定义			
//			0、SIM卡不存在1、信号弱2、信号差3、信号一般4、信号好
//			5、信号 优6、3G模块不存在7、3G功能关闭
#define TTX_3G_SIM_NO_EXIST		0		//SIM卡不存在
#define TTX_3G_SIGNAL_WEAK		1		//模块信号弱
#define TTX_3G_SIGNAL_POOR		2		//模块信号差
#define TTX_3G_SIGNAL_NORMAL	3		//模块信号一般
#define TTX_3G_SIGNAL_GOOD		4		//模块信号好
#define TTX_3G_SIGNAL_EXCELLENT	5		//模块信号优
#define TTX_3G_NO_EXIST			6		//模块不存在
#define TTX_3G_CLOSE			7		//3G功能关闭

//媒体类型定义
#define TTX_MEDIA_TYPE_AV		0		//音视频客户(用于实时预览)
#define TTX_MEDIA_TYPE_AUDIO	1		//音频客户(用于音频监听)
#define TTX_MEDIA_TYPE_TALKBACK	2		//对讲客户(用于音频对讲)

//码流类型定义
#define TTX_STREAM_TYPE_MAIN	0		//主码流
#define TTX_STREAM_TYPE_SUB		1		//子码流
#define TTX_STREAM_TYPE_DIRECT_MAIN		2		//直连主码流
#define TTX_STREAM_TYPE_DIRECT_SUB		3		//直连子码流

//音频流定义
#define TTX_AUDIO_STREAM_MIC	0		//麦克
#define TTX_AUDIO_STREAM_CAM	1		//摄像头
#define TTX_AUDIO_STREAM_PTT	2		//集群对讲

//录像通道
#define TTX_CHANNEL_ALL			98		//所有通道
#define TTX_CHANNEL_ALL_EX		-1		//所有通道

//录像类型定义
#define TTX_RECTYPE_NORMAL		1		//常规录像
#define TTX_RECTYPE_ALARM		2		//报警录像
#define TTX_RECTYPE_ALL			3		//所有录像

//文件属性定义
#define TTX_FILE_JPEG		1		//图片文件
#define TTX_FILE_RECORD		2		//录像文件
#define TTX_FILE_LOG		3		//日志文件
#define TTX_FILE_AUDIO		4		//音频文件

//日志文件类型定义(日志文件搜索时使用)
#define TTX_LOGFILE_NETWORK		1		//网络日志信息
#define TTX_LOGFILE_SYSTEM		2		//系统日志信息


//不同厂家，使用不同的类型
#define TTX_FACTORY_TYPE_UNKOWN					0
#define TTX_FACTORY_TYPE_1						1	//
#define TTX_FACTORY_TYPE_2						2	//
#define TTX_FACTORY_TYPE_3						3	//
#define TTX_FACTORY_TYPE_4						4	//
#define TTX_FACTORY_TYPE_5						5	//
#define TTX_FACTORY_TYPE_6						6	//
#define TTX_FACTORY_TYPE_7						7	//
#define TTX_FACTORY_TYPE_8						8	//
#define TTX_FACTORY_TYPE_9						9	//
#define TTX_FACTORY_TYPE_10						10	//
#define TTX_FACTORY_TYPE_11						11	//
#define TTX_FACTORY_TYPE_12						12	//TTX
#define TTX_FACTORY_TYPE_13						13	//
#define TTX_FACTORY_TYPE_14						14	//
#define TTX_FACTORY_TYPE_15						15	//
#define TTX_FACTORY_TYPE_16						16	//
#define TTX_FACTORY_TYPE_17						17	//
#define TTX_FACTORY_TYPE_18						18	//
#define TTX_FACTORY_TYPE_19						19	//
#define TTX_FACTORY_TYPE_20						20	//
#define TTX_FACTORY_TYPE_21						21	//
#define TTX_FACTORY_TYPE_22						22	//
#define TTX_FACTORY_TYPE_23						23	//
#define TTX_FACTORY_TYPE_24						24	//
#define TTX_FACTORY_TYPE_25						25	//
#define TTX_FACTORY_TYPE_26						26	//
#define TTX_FACTORY_TYPE_27						27	//
#define TTX_FACTORY_TYPE_28						28	//
#define TTX_FACTORY_TYPE_29						29	//
#define TTX_FACTORY_TYPE_30						30	//
#define TTX_FACTORY_TYPE_31						31	//
#define TTX_FACTORY_TYPE_32						32	//
#define TTX_FACTORY_TYPE_33						33	//
#define TTX_FACTORY_TYPE_34						34				
#define TTX_FACTORY_TYPE_35						35				
#define TTX_FACTORY_TYPE_36						36				
#define TTX_FACTORY_TYPE_37						37				
#define TTX_FACTORY_TYPE_38						38				
#define TTX_FACTORY_TYPE_39						39				
#define TTX_FACTORY_TYPE_40						40				
#define TTX_FACTORY_TYPE_41						41	//
#define TTX_FACTORY_TYPE_42						42	//
#define TTX_FACTORY_TYPE_43						43	//
#define TTX_FACTORY_TYPE_44						44				
#define TTX_FACTORY_TYPE_45						45				
#define TTX_FACTORY_TYPE_46						46				
#define TTX_FACTORY_TYPE_47						47				
#define TTX_FACTORY_TYPE_48						48				
#define TTX_FACTORY_TYPE_49						49				
#define TTX_FACTORY_TYPE_50						50	

//文件类型定义
#define TTX_FILE_TYPE_JPEG						1//图片
#define TTX_FILE_TYPE_REC						2	//录像文件
#define TTX_FILE_TYPE_AUDIO						5	//音频文件

//云台类型定义
#define TTX_PTZ_MOVE_LEFT				1
#define TTX_PTZ_MOVE_RIGHT				2
#define TTX_PTZ_MOVE_TOP				3
#define TTX_PTZ_MOVE_BOTTOM				4
#define TTX_PTZ_MOVE_LEFT_TOP			5
#define TTX_PTZ_MOVE_RIGHT_TOP			6
#define TTX_PTZ_MOVE_LEFT_BOTTOM		7
#define TTX_PTZ_MOVE_RIGHT_BOTTOM		8

#define TTX_PTZ_FOCUS_DEL				9
#define TTX_PTZ_FOCUS_ADD				10
#define TTX_PTZ_LIGHT_DEL				11
#define TTX_PTZ_LIGHT_ADD				12
#define TTX_PTZ_ZOOM_DEL				13
#define TTX_PTZ_ZOOM_ADD				14
#define TTX_PTZ_LIGHT_OPEN				15
#define TTX_PTZ_LIGHT_CLOSE				16
#define TTX_PTZ_WIPER_OPEN				17
#define TTX_PTZ_WIPER_CLOSE				18
#define TTX_PTZ_CRUISE					19
#define TTX_PTZ_MOVE_STOP				99

#define TTX_PTZ_PRESET_MOVE				22
#define TTX_PTZ_PRESET_SET				23
#define TTX_PTZ_PRESET_DEL				24

#define TTX_PTZ_SPEED_MIN				0
#define TTX_PTZ_SPEED_MAX				255

//音频类型定义
#define TTX_AUDIO_TYPE_G726_40KBPS				1		//使用海思格式
#define TTX_AUDIO_TYPE_ADPCM					2		//使用海思格式
#define TTX_AUDIO_TYPE_G726_MEDIA_40KBPS		3		//使用海思格式
#define TTX_AUDIO_TYPE_G726_MEDIA_32KBPS		4		//使用海思格式
#define TTX_AUDIO_TYPE_G726_MEDIA_24KBPS		5		//使用海思格式
#define TTX_AUDIO_TYPE_G726_MEDIA_16KBPS		6		//使用海思格式
#define TTX_AUDIO_TYPE_G726_32KBPS				7		//使用海思格式
#define TTX_AUDIO_TYPE_G726_24KBPS				8		//使用海思格式
#define TTX_AUDIO_TYPE_G726_16KBPS				9		//使用海思格式
#define TTX_AUDIO_TYPE_G711A					10		//使用海思格式
#define TTX_AUDIO_TYPE_G711U					11		//使用海思格式
#define TTX_AUDIO_TYPE_AAC_8KBPS				12
#define TTX_AUDIO_TYPE_AAC_16KBPS				13
#define TTX_AUDIO_TYPE_ARM						14		//使用海思格式
#define TTX_AUDIO_TYPE_AAC_24KBPS				15
#define TTX_AUDIO_TYPE_ADPCM_IMA				16		//使用海思格式
#define TTX_AUDIO_TYPE_G711A_EX					17		//非海思格式
#define TTX_AUDIO_TYPE_G711U_EX					18		//非海思格式
#define TTX_AUDIO_TYPE_NELLY_8KBPS				19		//Nellymoser

//视频Coder 定义
#define TTX_VIDEO_CODEC_H264					0
#define TTX_VIDEO_CODEC_H264_HI					1	//视频解码器，海思芯片使用些类型	
#define TTX_VIDEO_CODEC_H264_PRI_1				2	//私有带加密信息，请不要使用些参数
#define TTX_VIDEO_CODEC_H265_HI					3	//
#define TTX_VIDEO_CODEC_H265					4	//


//网络类型定义
#define TTX_NETWORK_TYPE_3G				0	//3G网络登录
#define TTX_NETWORK_TYPE_WIFI			1	//WIFI网络登录
#define TTX_NETWORK_TYPE_NET			2	//有线网络登录
#define TTX_NETWORK_TYPE_4G				3	//4G网络
#define TTX_NETWORK_TYPE_5G				4	//5G网络

//磁盘类型(用于区分卡机和硬盘机)
#define TTX_DISK_TYPE_SD				1	//SD卡
#define TTX_DISK_TYPE_HDD				2	//硬盘
#define TTX_DISK_TYPE_SSD				3	//SSD

//设备控制类型定义
#define TTX_CTRL_TYPE_OIL_STOP			1	//断开油路
#define TTX_CTRL_TYPE_OIL_RESTORE		2	//恢复油路
#define TTX_CTRL_TYPE_ELEC_STOP			3	//断开电路
#define TTX_CTRL_TYPE_ELEC_RESTORE		4	//恢复电路
#define TTX_CTRL_TYPE_REBOOT			5	//重启机器 
#define TTX_CTRL_TYPE_RESET				6	//设备复位
//为了省电和节省磁盘空间，我们DVR会自动关掉摄像头电源并停止录像，处于休眠状态，
//但是一旦检测有报警输入或者远程唤醒指令，DVR就会启动摄像头电源并启动录像
#define TTX_CTRL_TYPE_SLEEP				7	//休眠
#define TTX_CTRL_TYPE_WAKE				8	//唤醒
//录像的通道号0表示通道1，1表示通道2     98表示所有通道(TTX_CHANNEL_ALL)
#define TTX_CTRL_TYPE_START_RECORD		9	//开始录像	//高两字节为录像的通道号，低两字节为指令
#define TTX_CTRL_TYPE_STOP_RECORD		10	//停止录像	//高两字节为录像的通道号，低两字节为指令
#define TTX_CTRL_TYPE_START_CRUISE		11	//客户端开始对此通道进行轮询，高两字节为通道号，低两字节为指令
#define TTX_CTRL_TYPE_STOP_CRUISE		12	//客户端停止对此通道进行轮询，高两字节为通道号，低两字节为指令
#define TTX_CTRL_TYPE_WRITE_LOG			13	//启动记录日志功能	高两个字节大于0表示写日志，0表示不写日志
#define TTX_CTRL_TYPE_FORMAT_HDD		14	//格式化硬盘(高位表示硬盘号,硬盘号从0开始,低位表示命令号)
#define TTX_CTRL_TYPE_MILEAGE_CLEARED 		15	//里程清零
#define TTX_CTRL_TYPE_FLIP_NORMAL 		16	//正转翻转	//高两字节为通道号，低两字节为指令
#define TTX_CTRL_TYPE_FLIP_REVERSE 	 	17	//发转翻转	//高两字节为通道号，低两字节为指令
#define TTX_CTRL_TYPE_CLEAR_ALARM		18		//清除报警
#define TTX_CTRL_TYPE_SWITCH_CAM		19		//切换摄像头
#define TTX_CTRL_TYPE_RECORD_SOUND		20		//开始录音    //高两字节为录音的通道号，低两字节为指令
#define TTX_CTRL_TYPE_STOP_REC_SOUND	21		//停止录音    //高两字节为录音的通道号，低两字节为指令
#define TTX_CTRL_TYPE_WIFI_DOWN_FINISH	22		//wifi下载结束

//上传的文件类型定义
#define TTX_UPLOAD_FILE_TYPE_PICTURE	1	//图片文件(可以是jpg, bmp, png等格式)
#define TTX_UPLOAD_FILE_TYPE_UPGRADE	2	//升级文件，参数为(版本号+ 版本名称)

#define TTX_MOTION_MASK 			9	//移动侦测
#define TTX_UPLOAD_STATES_INFO		0x11223344 //信息帧是否带gps,车辆状态等信息
//编码类型类型
#define TTX_TYPE_CODE_ANSI			0		//ANSI
#define TTX_TYPE_CODE_UTF8			1		//UTF8

#pragma pack(4)

typedef struct tagTTXGpsInfo
{
	char cGpsStatus; 			//gps是否有效标，A表示有效，V表示无效，默认为V
	char cReserve;				//保留参数
	unsigned short usSpeed;		//速度值，默认为0，9999 = 99.99公里
	unsigned char cLatDegree;			//纬度值的度
	unsigned char cLatCent; 				//纬度值的分
	unsigned char cLngDegree;			//经度值的度
	unsigned char cLngCent;				//经度值的分
	long lLatSec;				//纬度值的秒
	long lLngSec;				//经度值的秒
	char cLatDirection;			//纬度的方向，'N'表示北纬，'S'表示南纬 
	char cLngDirection;			//经度的方向，'E'表示东经，'W'表示西经
	unsigned short usGpsAngle; 	//gps夹角(车辆运动方向)，0 -  360，0表示正北，顺时针方向，90表示东
	short sGaoDu;	//高程，单位米
	unsigned short usReserved;		//保留字段
	//设备端的GPS信息的格式一般是按照DDFF.MMMM的方式保存的
	//所以此处对设备端如何取秒并转换成此处要求的形式加以示范
	//(*注意：具体的计算方式和GPS模块提供的数据格式有关) 
	//假如设备端采集到的GPS值是：12158.3416，则： 
	//		度是 121 
	//		分是 58 
	//		秒是 0.3416 分 (*注意：单位是分)
	// 			0.3416 * 60 = 20.496 秒 
	//		再扩大一千万倍，把它转换成此结构需要的精度： 
	//			20.496 * 10,000,000 = 204,960,000 (千万分之一秒)
	// 此时cLongitudeDegree = 121，cLongitudeCent = 58，lLongitudeSec = 204, 960, 000
}TTXGpsInfo_S, *LPNetGpsInfo_S;

typedef struct tagTTXVehiStatus
{
	bool bAccOpen;		//ACC状态，默认为true，true表示ACC开
	bool bLeft;			//左转状态，true表示左转状态,  默认为false
	bool bRight;		//右转状态,    true表示右转状态,  默认为false
	bool bBrake;		//刹车状态,    true表示刹车状态,  默认为false
	bool bZZhuang;		//正转状态 =  运混凝土的车,    true表示正转状态,  默认为false
	bool bFZhuang;		//反转状态 =  运混凝土的车,    true表示反转状态,  默认为false
	bool bOverSpeed;	//超速状态
	bool bLowSpeed;		//低速状态
	unsigned int nLiCheng;	//里程数据,  单位米
	float fYouLiang;		//油量99.99 = 99.99升
	unsigned int nParkTime;	//停车时长单位秒，大于0表示静止状态	
}TTXVehiStatus_S, *LPTTXVehiStatus_S;

typedef struct tagTTXDiskStatus
{
	char cDiskStatus;	//硬盘状态, 0不存在，1存在，2断电，默认为0
	bool bDisk2Valid;	//硬盘2是否有效, 默认为false，硬盘2有效时，硬盘2的状态才有效
	char cDisk2Status;	//硬件2状态, 0不存在，1存在，2断电
	char cReserve;		//保留字段
}TTXDiskStatus_S, *LPTTXDiskStatus_S;

typedef struct tagTTXModuleStatus
{
	bool bGpsExist;		//GPS模块是否存在，true表示存在,  默认为true
	char c3gState;		//3G模块状态, 	0、SIM卡不存在1、信号弱2、信号差3、信号一般4、信号好
						//			5、信号 优6、3G模块不存在7、3G功能关闭
	char cCoorType;		//GPS坐标类型TTX_COOR_TYPE_WSG84，TTX_COOR_TYPE_GCJ02, TTX_COOR_TYPE_BD09
	char cLocType; 		//GPS定位类型TTX_LOC_TYPE_GPS，TTX_LOC_TYPE_WIFI
	char cSatellites;		//卫星数
	char cSosButton;	//紧急报警的状态，1为true，0为false
	char cLowVoltage;	//低压报警状态，1为true, 0为false
	char cVoltage;		//电量, 0-100
	char cReserve[4];	//保留参数
}TTXModuleStatus_S, *LPTTXModuleStatus_S;

typedef struct tagTTXIOStatus
{
	unsigned short usIOInputStatus;//IO输入模块状态，0位表示IO_1，值为1表示IO输入处于报警状态，默认为0
						//最多16个
	unsigned short usIOOutStatus; 	//IO输出状态，最多4个有效
	char cReserve[8];	//保留参数
}TTXIOStatus_S, *LPTTXIOStatus_S;

typedef struct tagTTXChannelStatus
{
	unsigned short usLostStatus;	//视频丢失状态，最多8个有效，每位表示相应通道的状态	1表示视频丢失
	unsigned short usRecordStatus;	//视频录像状态，最多8个有效	1表示正在录像
	char cRecStaValid;	//录像状态是否有效,用于客户端的不录像报警功能
	char cReserve[7];	//保留参数
}TTXChannelStatus_S, *LPTTXChannelStatus_S;

//OBD状态
typedef struct tagTTXObdStatus
{
	unsigned int uiSpeed;		//通过OBD速度		9900 = 99公里			(0-256)			
	unsigned int uiRpm;		//发动机转速		3000转					0-16384			
	unsigned char ucStatus;		//第0位表示ACC 開關	1 離合器開關  2	煞車開關  3	PTO 開關	4  緊急剎車	
	char ucJQTemp;			//燃油进气温度	33-33度				-127 - 127		
	short ucJQMPos;			//节气门位置		102 = 10.2 %				0-1024			
	short ucBatteryVoltage;		//电池电压			123   = 12.3V				0-512			
	char cReserve[8];	//保留参数
}TTXObdStatus_S, *LPTTXObdStatus_S;

//人数统计的状态
typedef struct tagTTXPeopleStatus
{
	unsigned int uiUp;			//上车人数
	unsigned int uiDown;		//下车人数
	char cReserve[8];	//保留参数
}TTXPeopleStatus_S, *LPTTXPeopleStatus_S;

//渣土车的状态
typedef struct tagTTXSlagStatus
{
	unsigned int uiWeight;		//重量，可以为刻度、百分比，由后台进行换算。如果为真实的重量，则单位为千克
	unsigned char ucLift;		//举升
	unsigned char ucClose;		//闭合
	unsigned char ucLoadPersent;		//装载百分比，暂时无效
	unsigned char ucValid;		//渣土车是否为效，如果要上报状态必须填为1
	char cReserve[8];	//保留参数	
}TTXSlagStatus_S, *LPTTXSlagStatus_S;

typedef struct tagTTXTemperature
{
	float fTemperatue[4];		//温度，99.99 = 99.99度
}TTXTemperature_S, *LPTTXTemperature_S;

typedef struct _tagTTXRecFile
{
	unsigned char Year;		//年，11 = 2011年
	unsigned char Month;	//日，从1开始，1 - 12
	unsigned char Day;		//天，从1开始，1 - 31
	unsigned char Hour;		//小时，从0开始，0 - 23
	unsigned char Minute;	//分钟，从0开始，0 - 59
	unsigned char Second;	//秒，从0开始，0 - 59
	unsigned char Type;		//文件类型		TTX_RECTYPE_NORMAL, TTX_RECTYPE_ALARM, TTX_RECTYPE_ALL
	unsigned char Channel;	//通道号，从0开始
	unsigned int  uiFileTime;	//文件时长，秒为单位
	unsigned int  uiFileLen;	//文件长度
	char	szFileName[240];
	unsigned short usMulChn;	//可以多路回放的通道	，按位表示
	char 	bMulPlay;			//是否支持多路同时回放
	char	cReserve;			//保留参数
	char	cYJWNewFlag;		//新文件使用，请填0
	char	cCoointNewFlag;		//新文件使用，请填0
	char	bRecording;			//是否正在录像，0表示没有，1表示正在录像
	char	bStream;				//是否为流式文件，当为流式文件时，客户端会使用回放的方式进行文件下载
	unsigned int ChnMask;		//通道掩码，当一个文件存在多个通道的录像时，使用些参数
	int 	nAlarmInfo;			//一个文件允许有多个报警，当文件是报警文件时有效
}TTXRecFile_S, *LPTTXRecFile_S;

//TTXRecFile_S内的nAlarmInfo定义，按位表示，单个录像文件存在多个报警时使用
//设备报警录像报警类型定义
typedef enum
{
	TTX_FILE_ALARM_INFO_URGENCY_BUTTON  =0 ,		//紧急按钮报警
	TTX_FILE_ALARM_INFO_OVERSPEED 		=1 ,		//超速报警
	TTX_FILE_ALARM_INFO_LOWSPEED 		=2 ,		//低速报警
	TTX_FILE_ALARM_INFO_SHARK			=3 ,		//振动报警
	TTX_FILE_ALARM_INFO_TEMPERATOR 		=4 ,		//温度报警
	TTX_FILE_ALARM_INFO_TMOTION			=5 ,		//移动侦测报警
	TTX_FILE_ALARM_INFO_UPS_CUT			=6 ,		//UPS剪断报警
	TTX_FILE_ALARM_INFO_COLLISION		=7 ,		//碰撞侧翻
	TTX_FILE_ALARM_INFO_FATIGUE			=8 ,		//疲劳驾驶
	TTX_FILE_ALARM_INFO_IO1				=9 ,		//IO1报警
	TTX_FILE_ALARM_INFO_IO2				=10, 		//IO2报警
	TTX_FILE_ALARM_INFO_IO3				=11,		//IO3报警
	TTX_FILE_ALARM_INFO_IO4				=12, 		//IO4报警
	TTX_FILE_ALARM_INFO_IO5				=13, 		//IO5报警
	TTX_FILE_ALARM_INFO_IO6				=14, 		//IO6报警
	TTX_FILE_ALARM_INFO_IO7				=15, 		//IO7报警
	TTX_FILE_ALARM_INFO_IO8				=16, 		//IO8报警
	TTX_FILE_ALARM_INFO_RAPID_ACCELERATION =17,		//急加速告警 
	TTX_FILE_ALARM_INFO_RAPID_DECELERATION =18,		//急减速告警 
	TTX_FILE_ALARM_INFO_REVERSING		 =19,		//倒车告警 
	TTX_FILE_ALARM_INFO_CUS_OVER_SPEED	 =20,		//超速告警 
}TTX_ALARM_REC_TYPE_E;

//文件信息
typedef struct _tagTTXFILEInfo_S
{
	int	nYear;			//年	2013
	int	nMonth;			//月	5
	int nDay;			//日	29
	int nBegHour;		//开始时间
	int nBegMinute;		
	int nBegSecond;
	_u64long u64BegPts;	//文件起始的时间戳
	unsigned int uiTotalMinSecond;	//文件总时长，毫秒
	unsigned int uiAudioCodec;		//音频解码器类型	TTX_AUDIO_TYPE_G726_40KBPS
	unsigned int uiAudioChannel;		//音频通道
	unsigned int uiAudioSamplesPerSec;	//音频采样率
	unsigned int uiAudioBitPerSamples;	//音频每个取样所需的位元数
	unsigned int uiInfoCodec;		//信息帧解码器	TTX_INFO_CODEC_WKP
	unsigned int uiVideoCodec;		//视频帧解码器	TTX_VIDEO_CODEC_H264
	unsigned char ucResolution;		//分辨率		TTX_RESOLUTION_720P
	char szReserve[59];		//保留字段
} TTXFILEInfo_S, *LPTTXFILEInfo_S;

//说明海思参数为
//uiAudioChannel = 1
//uiAudioSamplesPerSec = 8000
//uiAudioBitPerSamples = 16;

//帧信息
typedef struct _tagTTXFILEFrame_S
{
    _u64long u64Pts;	//帧时间戳	单位微秒		1微秒等于一百万分之一秒
    unsigned char	*pU8Data;   //帧数据
    unsigned int	u32FrmSize; //帧长度
    unsigned int	u32Type;    //帧类型
    unsigned int	nChannel;	//对应的通道信息，信息帧和数据帧不需要返回
    							//文件如果对应多个通道的视频数据，则需要返回
} TTXFILEFrame_S, *LPTTXFILEFrame_S;

//参数配置数据
typedef struct _tagTTXConfigData_S
{
	int nLength;
	char cBuffer[2048];
} TTXConfigData_S, *LPTTXConfigData_S;

//网络参数
typedef struct _tagTTXNetParam_S
{
	unsigned char cMac[6];			//MAC地址
	unsigned char cLanIP[4];		//局域网地址
	unsigned char cLanMask[4];		//子网掩码
	unsigned char cLanGateway[4];	//网关地址
	int 	bAutoLogin;				//自动登录
	char	szServerIP[64];			//服务器地址
	unsigned short usServerPort;	//服务器端口
	unsigned short usConnType;		//连接类型，暂时无效
	unsigned short usWebPort;
	unsigned short usReserve;		//保留参数
	char szWebUrl[128];			//		ip:port/szWebUrl	
} TTXNetParam_S, *LPTTXNetParam_S;

//颜色参数
typedef struct _tagTTXVideoColor
{
	int nExposure;		//爆光度
	int	nBrightness;	
	int	nConstract;	
	int	nHue;				
	int	nSaturate;			 
}TTXVideoColor_S, *LPTTXVideoColor_S;

//会话本地端口配置
//使用: 		在服务器防火墙 双向管制时使用，服务器只接收设备指定端口上传的数据
//默认端口为0，为0表示不绑定
typedef struct _tagTTXSessPortBind
{
	unsigned short usRegister;	//注册端口
	unsigned short usUpgrade;	//升级端口
	unsigned short usMainStream[TTX_MAX_CHANNEL];	//主码流主端口配置
	unsigned short usSubStream[TTX_MAX_CHANNEL];	//子码流端口配置
	unsigned short usTalkback;	//双向对讲端口
	unsigned short usMikeListen;	//麦克监听端口
	unsigned short usAudioListen[TTX_MAX_CHANNEL];	//声音监听端口配置
	unsigned short usRecSearch[TTX_MAX_SESS];	//录像文件搜索
	unsigned short usFileDown[TTX_MAX_SESS];	//文件下载(录像和图片文件下载)
	unsigned short usPlayback[TTX_MAX_SESS];	//远程回放
	unsigned short usSnapshot[TTX_MAX_SESS];	//图片抓拍
}TTXSessPortBind_S, *LPTTXSessPortBind_S;

//透明查询数据，暂时不考虑数据包超出1400字节的情况
typedef struct _tagTTXTransQueryData_S
{
	int nLength;
	char cBuffer[1400];
} TTXTransQueryData_S, *LPTTXTransQueryData_S;

//设备要下载的文件信息，服务器向设备上传的文件
typedef struct _tagTTXUploadFileInfo
{
	int nFileType;		//文件类型，1表示升级文件TTX_DOWN_FILE_TYPE_UPGRADE
	char szParam[256];	//中间使用 _ 分隔
	int nFileID;		//文件ID
	char szFile[256];	//文件路径
	char szIP[64];		//服务器IP
	unsigned short usPort;	//端口
	unsigned short usReserve;
	char szMd5[40];		//MD5校验
	char szReserve[32];	//保留参数
}TTXUploadFileInfo_S;

typedef struct _tagTTXMotionParam
{
	int	nMask[TTX_MOTION_MASK];	//低11位表示移动侦测
	int	nSensitive;	//灵敏度
	unsigned char bEnable;	//是否启用
	char cReserve[3];
}TTXMotionParam_S, *LPTTXMotionParam_S;

typedef	struct _tagTTXStateInfoIndexHead
{
	unsigned int		unStateInfoflag; 			//状态发送标志位TTX_UPLOAD_STATES_INFO
	unsigned short usDataType;		//数据类型	第0位为1表示车辆状态信息TTXVehiStatus_S,
									//第1位为1GPS信息TTXGpsInfo_S,第2位为1IO状态TTXIOStatus_S,第3位为1gsensor状态TTXGsensorInfo_S	
	unsigned short usDataLen;		//数据长度
}TTXStateInfoIndexHead_S;

typedef struct _tagTTXGsensorInfo
{
	short sAccelerateX; 	//加速度x值 比如:1000 / Unit(基准值) =  1g
	short sAccelerateY; //加速度y值
	short sAccelerateZ; //加速度z值
	short sUnit;			//基准值 (0是无效)//单位,此值表示1G
	int	nReserve[4];
}TTXGsensorInfo_S,*LPTTXGsensorInfo_S;


#pragma pack()

//音视频数据回调函数
//@nType	帧类型
//@nLength	帧长度
//@u64Stamp	时间戳
//@pData	帧数据
//@pUsr		用户自定义数据
//返回值		TTX_NET_OK表示正常
//				TTX_NET_ERR_BUF_FULL表示发生丢弃缓存的情况
typedef int (* TTXPfnAVEncoderCB)(int nType, int nLength, _u64long u64Stamp, const char* pData, void* pUsr);

//文件查找回调函数
//@pFile		录像文件
//@pUsr		用户自定义数据
typedef void(* TTXPfnRecFindCB)(LPTTXRecFile_S pFile, void* pUsr);

//判断是否需要退出
//返回true表示退出
//文件查找过程中，需要不停调用此函数来判断是否需要退出
typedef bool (* TTXPfnGetExitCB)(void* pUsr);

//透明查询回调函数
//@pData	查询返回的数据
//@pUsr		用户自定义数据
typedef void(* TTXPfnTranQueryDataCB)(LPTTXTransQueryData_S pData, void* pUsr);

//808对接用的，将指令透传到服务器上
//@pData	查询返回的数据
//@pUsr		用户自定义数据
typedef void(* TTXPfnJT808UploadTransInstructionCB)(const char* pData, int nLength, void* pUsr);

//808对接用的，查询808信息链路是否在线
//@pUsr		用户自定义数据
//@返回true表示在线，false表示离线
typedef bool(* TTXPfnJT808CheckOnlineCB)(void* pUsr);


/**
 * @Description:网络服务基类
 * @Author: afu	2011-06-30
 */
class CTTXRecFile;
class CTTXFrameReader;
class LIBDVRNET_API CTTXNetWork
{
public:
	CTTXNetWork() 
	{
		memset(&m_GpsInfo, 0, sizeof(m_GpsInfo));
		m_GpsInfo.cGpsStatus = TTX_GPS_UNVALID;
		memset(&m_VehiState, 0, sizeof(m_VehiState));
		m_VehiState.bAccOpen = true;
		memset(&m_DiskStatus, 0, sizeof(m_DiskStatus));
		memset(&m_ModuleStatus, 0, sizeof(m_ModuleStatus));		
		m_ModuleStatus.bGpsExist = true;
		m_ModuleStatus.c3gState = TTX_3G_SIGNAL_NORMAL;
		memset(&m_Temperature, 0, sizeof(m_Temperature));
		memset(&m_IOStatus, 0, sizeof(m_IOStatus));
		memset(&m_ObdStatus, 0, sizeof(m_ObdStatus));
		memset(&m_PeopleStatus, 0, sizeof(m_PeopleStatus));
		memset(&m_SlagStatus, 0, sizeof(m_SlagStatus));
		memset(&m_ChannelStaus, 0, sizeof(m_ChannelStaus));
		memset(&m_Gsensorinfo, 0, sizeof(m_Gsensorinfo)); //Gsensor
		
		m_nGpsInterval = 10;		//默认GPS发送间隔为10秒钟
		m_nHeartInterval = 60;
		m_nTtsFlag = 0;
		m_nTtsParam = 0;
	}
	virtual ~CTTXNetWork(){}
	
public:
	/*****************************************************************************
	* @ 状态两种方式
	*		方案A，调用SetGpsInfo接口主动更新
	*		方案B，重载GetGpsInfo接口，在获取时进行更新
	******************************************************************************/
	//更新GPS 信息，设备在变化时可以及时进行更新
	//终端在GPS信息发生变化时及时调用此接口进行更新
	void	SetGpsInfo(const TTXGpsInfo_S& gps) {	m_GpsInfo = gps;	}
	//更新车辆状态
	void	SetVehiStatus(const TTXVehiStatus_S& vehi) {	m_VehiState = vehi;}
	//更新硬盘状态
	void	SetDiskStatus(const TTXDiskStatus_S& disk) {	m_DiskStatus = disk;}
	//更新模块状态
	void	SetModuleStatus(const TTXModuleStatus_S& module) {	m_ModuleStatus = module;}
	//更新温度状态
	void	SetTemperature(const TTXTemperature_S& temperature) {	m_Temperature = temperature;}
	//获取配置GPS间隔，单位秒
	int		GetGpsInterval() {	return m_nGpsInterval;	}
	//设置GPS间隔
	void	SetGpsInterval(int nInterval) {	m_nGpsInterval = nInterval;	}
	//获取心跳间隔(秒)
	int		GetHeartInterval() {	return m_nHeartInterval;	}
	//设置心跳间隔
	void	SetHeartInterval(int nSecond) {	m_nHeartInterval = nSecond;	}	
	void	SetIOStatus(const TTXIOStatus_S& io) {	m_IOStatus = io;}
	void	SetObdStatus(const TTXObdStatus_S& obd) {	m_ObdStatus = obd;}
	void	SetPeopleStatus(const TTXPeopleStatus_S& people) {	m_PeopleStatus = people;}
	void	SetSlagStatus(const TTXSlagStatus_S& slag) {	m_SlagStatus = slag;}
	//更新通道状态信息
	void	SetChannelStatus(const TTXChannelStatus_S& channel) {	m_ChannelStaus = channel;}

	//更新gsensor状态
	void	SetGsensorStatus(const TTXGsensorInfo_S& Gsensor) {	m_Gsensorinfo = Gsensor;}
	
public:
	//判断状态是否初始化了，只有加载成功后，才会与服务器建立通信链路
	//避免gps数据没生成时，上报状态到服务器上
	//设备上可以简单做个策略，从gps模块存在时，可以从gps模块获取到数据（不管gps是否有效）
	//存在油量模块时，可以从油量模块获取到数据
	//如果2分钟后，条件还是不满足，则也配置成初始化状态成功
	virtual bool IsInitStatus() {	return true;	}
	//如果状态变化时调用SetGpsInfo 及时进行更新，则不需要重载此接口
	//也在可以重载此接口，网络库在需要时，会主动调用此接口获取GPS信息
	virtual TTXGpsInfo_S GetGpsInfo() { return m_GpsInfo;};
	//获取车辆状态
	virtual TTXVehiStatus_S GetVehiStatus() { return m_VehiState;};
	//获取硬盘状态
	virtual TTXDiskStatus_S GetDiskStatus() { return m_DiskStatus;};
	//获取模块状态
	virtual TTXModuleStatus_S GetModuleStatus() { return m_ModuleStatus;};
	//获取温度状态
	virtual TTXTemperature_S GetTemperature() {	return m_Temperature;}	
	//更新IO状态信息
	virtual	TTXIOStatus_S GetIOStatus() {	return m_IOStatus;}
	//获取Obd状态
	virtual	TTXObdStatus_S GetObdStatus() {	return m_ObdStatus;}
	//获取人数统计状态
	virtual	TTXPeopleStatus_S GetPeopleStatus() {	return m_PeopleStatus;}
	//获取渣土车状态
	virtual	TTXSlagStatus_S GetSlagStatus() {	return m_SlagStatus;}
	//更新通道状态信息
	virtual TTXChannelStatus_S GetChannelStatus() {	return m_ChannelStaus;}
	//获取软件版本信息
	//@szVersion: 版本信息
	//@nVerLen: szVersion缓存的长度, 上层拷贝长度不得超过此长度
	virtual void GetSoftwareVersion(char* szVersion, int nVerLen) {}
	//获取视频状态(视频丢失和录像状态)
	//@nVideoLost: 第0位表示通道1,  值为1表示视频丢失
	//@nVideoRecord: 第0位表示通道1,  值为1表示正在录像
	virtual void GetVideoStatus(int& nVideoLost, int& nVideoRecord) {}
	//获取磁盘信息
	//@nDiskCount: 磁盘数目
	//@szDiskValue: 16000_8000_32000_8000 格式, 单位MB, 16000表示所有空间为16000MB, 8000表示剩余空间为8000MB
	//          如果0_0  则表示硬盘出错
	//		中间使用_   分隔
	//@nDiskValLen: szDiskValue缓存的长度, 上层拷贝长度不得超过此长度
	virtual void GetDiskInfo(int& nDiskCount, char* szDiskValue, int nDiskValLen) {}
	//获取3G状态
	//@n3GStatus: 0表示无效，1表示有效
	//@n3GType: 网络类型0表示2G,  1表示EVDO,  2表示WCDMA, 3表示TD-WCDMA, 4 TD_LED , 5 FDD
	//@sz3GAddress: 3G拔号后的地址
	virtual void Get3GStatus(int &n3GStatus, int& n3GType, char* sz3GAddress, int n3GAddrLen) {}
	//获取WIFI状态
	//@nWifiStatus: 0表示无效，1表示有效
	//@szWifiAddress: WIFI  的网络地址
	//@nWifiAddrLen: WIFI  的网络地址
	virtual void GetWifiStatus(int &nWifiStatus, char* szWifiAddress, int nWifiAddrLen) {}
	//获取IO状态
	//@nIOOutCount: IO输出个数
	//@nIOInCount: IO输入个数
	virtual void GetIOInfo(int& nIOOutCount, int& nIOInCount) {}
	////3g和4g流量，已经使用的网络流量信息，单位KB
	virtual void GetNetFlowInfo(unsigned int& ui3GFlow, unsigned int& ui4GFlow) {}

	//获取gsensor状态
	virtual TTXGsensorInfo_S GetGsensorStatus() { return m_Gsensorinfo;};

public:
	//登录消息通知
	//@bSuc: true表示与服务器通信成功 false表示通信中断或不成功
	//@bExistDevice: 当bSuc为true时有效，如果为true表示服务器已经添加了相应的设备，如果为flase表示服务器未添加相关的设备
	virtual void DoLoginMsg(bool bSuc, bool bExistDevice) {}
	
	//鉴权处理
	//@szSvrAuthKey服务器下发的鉴权码，可以判断此鉴权码是否满足一定的规则
	//		如果是则表示服务器版本是对的，如果不对，则设备主动中断链接
	//		然后再对szSvrAuthKey进行加密返回串数据给服务器
	//		服务器对szDevAuthKey数据进行解密匹配，如果不满足规则，则会中断连接
	//@szDevAuthKey设备对szSvrAuthKey进行加密后，返回给服务器的数据
	//@nDevAuthKeyLen，表示szDevAuthKey的长度(这个长度不超过260个字节)
	//如果返回失败，则会中断链接
	virtual bool DoAuthentication(const char* szSvrAuthKey, char* szDevAuthKey, int nDevAuthKeyLen) {	return true;	}
	
	/*****************************************************************************e
	* @ 控制指令业务
	******************************************************************************/
	//指令处理
	//TTS语音处理
	//情况1：上层先调用SetTtsParam再调用DoTtsVoice
	//情况2：上层直接调用DoTtsVoice
	//nFlag：按位表示
	//		0 紧急
	//		1 保留
	//		2 1：终端显示器显示
	//		3 1：终端TTS 播读
	//		4 1：广告屏显示
	//		5 0：中心导航信息，1：CAN 故障码信息
	//nParam：当 终端显示屏显示时，nParam表示显示的秒数
	virtual void SetTtsParam(int nFlag, int nParam) {	m_nTtsFlag = nFlag;	m_nTtsParam = nParam;	}
	virtual bool DoTtsVoice(const char* szText) {		return false;	}
	//发送控制指令
	//@nCtrlType: 控制类型
	virtual bool DoControl(int nCtrlType) {	return false;}
	//设置GPS 发送间隔，可以在此接口中存储GPS间隔参数信息
	//@nSecond: 秒数
	virtual void DoSetGpsInterval(int nSecond) {}
	//PTZ控制
	//@nChannel: 通道号从0开始
	//@nCommand: 控制指令
	//@nSpeed: 速度
	//@nParam: 参数
	virtual bool DoPtzContrl(int nChannel, int nCommand, int nSpeed, int nParam) {	return false;	}
	//获取空闲预置位
	//@nChannel: 通道号从0开始
	//@nPresetNo: 最小空闲预置号
	virtual bool DoFreePresetGet(int nChannel, int& nPresetNO) {	return false;	}
	//获取移动侦测参数
	//@nChannel: 通道号从0开始
	virtual bool DoReadMotionParam(int nChannel,  TTXMotionParam_S* pMotion) {	return false;	}
	//设置移动侦测参数
	virtual bool DoSetMotionParam(int nChannel, const TTXMotionParam_S* pMotion) {		return false;	}
	//接收到透明串口数据
	virtual void DoRecvTransparentSerial(int nType, const unsigned char* pBuffer, int nLength) {	}
	//获取参数数据
	//@nType: 参数类型
	//@pConfigData: 参数缓存
	virtual bool DoGetConfig(int nType, LPTTXConfigData_S pConfigData) {	return false; 	}
	//设置参数数据
	virtual bool DoSetConfig(int nType, const LPTTXConfigData_S pConfigData) {	return false;	}
	//参数处理透传
	//@nType: 参数类型
	//@pInConfig: PC传入的参数信息
	//@pOutConfig: 设备返回的参数信息
	virtual bool DoTransparentConfig(int nType, const LPTTXConfigData_S pInConfig, LPTTXConfigData_S pOutConfig) {	return false;	}
	//文件开始上传
	//@szFile: 文件名绝对路径
	//@isServer: 如果为true表示服务器执行下载，如果为false表示客户端进行下载
	virtual void DoFileUploadBegin(const char* szFile, bool isServer) {	}
	//文件上传完成
	//@szFile: 文件名绝对路径
	//@isServer: 如果为true表示服务器执行下载，如果为false表示客户端进行下载
	virtual void DoFileUploadFinishEx(const char* szFile, bool isServer) {	}
	//文件上传完成
	//@szFile: 文件名绝对路径
	virtual void DoFileUploadFinish(const char* szFile) {	}
	//获取网络参数，搜索设备时使用
	//@netParam: 网络参数
	virtual bool DoGetNetParam(TTXNetParam_S& netParam) {	return false;	}
	//在直连时实时视频时，可以显示通道名称到界面上
	virtual bool DoGetChannelName(char* szChannelName, int nChnNameLen) {	return false;	}
	//设置网络参数(使用广播的方式进行配置)
	//@Mac: 上层需要判断mac是否与设备的mac地址一致
	//@szIDNO: 终端编号, 上层需要判断下，是否发生变化
	//@netParam: 网络参数
	virtual bool DoSetNetParam(unsigned char Mac[6], const char* szIDNO, const TTXNetParam_S& netParam) {	return false;	}
	//获取颜色参数
	virtual bool DoGetVideoColor(int nChannel, LPTTXVideoColor_S pColor) {	return false;	}
	//设置颜色参数
	virtual bool DoSetVideoColor(int nChannel, LPTTXVideoColor_S pColor) {	return false;	}
	//WIFI参数配置
	//@szUser: 用户名信息，暂时无效
	//@szPwd: 密码信息，暂时无效
	//@szWifiSsid: Wifi SSID信息
	//@szWifiPwd: Wifi密码信息
	virtual bool DoSetWifiParam(const char* szUser, const char* szPwd, const char* szWifiSsid, const char* szWifiPwd) {	return false;	}

public:
	/*****************************************************************************
	* @ 媒体业务
	******************************************************************************/

	/*****************************************************************************
	//获取视频参数
	//@nChannel: 通道号从0开始
	//@nStreamType: TTX_STREAM_TYPE_MAIN 或 TTX_STREAM_TYPE_SUB
	//@nVideoCoder: 音频类型TTX_VIDEO_CODEC_H264 等TTX_VIDEO_CODEC_H265
	//如果不同通道的视频格式不一样时，请重载此接口，例如通道1是264，通道2是265
	//如果是同一个视频格式，则不需要重载GetVideoParam接口
	******************************************************************************/
	virtual bool GetVideoParam(int nChannel, int nStreamType, int& nVideoCoder) {	return false;	}
	
	/*****************************************************************************
	//取得视频通道的分辨率
	//@nChannel: 通道号从0开始
	//@nStreamType: 码流类型，媒体类型为视频时有效TTX_STREAM_TYPE_MAIN
	//@nResolution: 默认分辨率TTX_RESOLUTION_CIF
	//@nFrameBufLen: 帧长度返回0时，则由SDK决定缓存大小
	//	 QCIF和CIF为300K缓存
	//    HD1和D1为1200K 缓存
	//    720P为4800K缓存
	//	1080P为19200K 缓存
	******************************************************************************/
	virtual bool GetVideoResolution(int nChannel, int nStreamType, int& nResolution, int& nFrameBufLen) {	nResolution = TTX_RESOLUTION_CIF; nFrameBufLen = 0;	return true;	}

	//视频有两种方式
	//方式1  重载InitFrameReader和FreeFrameReader接口，sdk直接使用上层的帧缓存
	//方式2  重载StartAVEnc和StopAVEnc接口，上层将帧数据通过回调送到sdk, sdk内有个帧缓存
	//先调用InitFrameReader如果成功了，则不会再调用StartAVEnc接口,如果失败，则会调用StartAVEnc接口
	//如果InitFrameReader成功，在停止的时候，会调用FreeFrameReader
	
	/*****************************************************************************
	//启动音视频编码，服务器请求实时视频和声音监听时将调用此接口
	//@nMediaType: 媒体类型，TTX_MEDIA_TYPE_AV 或者TTX_MEDIA_TYPE_AUDIO
	//@nChannel: 通道号从0开始，如果为音频时，nChannel还可以为麦克通道
	//@nStreamType: 码流类型，媒体类型为视频时有效
	//@ppReader: 返回一个CTTXFrameReader对象，用于获取帧数据
	//如果此接口返回true，则不会再调用StartAVEnc和StopAVEnc两个接口
	//SDK不会再开启帧缓存，由上层进行缓存，主要用于提高的效率
	******************************************************************************/
	virtual bool InitFrameReader(int nMediaType, int nChannel, int nStreamType, bool bDirectConnect, CTTXFrameReader** ppReader) {	return false;	}
		
	/*****************************************************************************
	//停止音视频编码，服务器停止实时视频和声音监听时将调用此接口
	//@nMediaType: 媒体类型，TTX_MEDIA_TYPE_AV 或者TTX_MEDIA_TYPE_AUDIO
	//@nChannel: 通道号从0开始
	//@nStreamType: 码流类型
	//@pReader: 帧缓存读取对象
	******************************************************************************/
	virtual void FreeFrameReader(int nMediaType, int nChannel, int nStreamType, bool bDirectConnect, CTTXFrameReader* pReader) {	/*delete pReader; pReader = NULL;*/		}
	
	/*****************************************************************************
	//启动音视频编码，服务器请求实时视频和声音监听时将调用此接口
	//也需要知道音频的格式参数
	//@nMediaType: 媒体类型，TTX_MEDIA_TYPE_AV 或者TTX_MEDIA_TYPE_AUDIO
	//@nChannel: 通道号从0开始，如果为音频时，nChannel还可以为麦克通道
	//@nStreamType: 码流类型，媒体类型为视频时有效
	//@pfnEncoderCB: 数据回调函数
	//@pEncUsr: 编码回调函数用户自定义数据
	//@ppAVUsr: 编码对象用户自定义数据，返回给网络库，在StopAVEnc，将此参数传回
	//上层保存pfnEncoderCB和pUsr，在编码产生数据时，通过此接口告诉网络层
	//上层将音视频数据按顺序传送给网络库
	//网络库模块不发送音频数据，但客户端请求音频后，才发送音频
	******************************************************************************/
	virtual bool StartAVEnc(int nMediaType, int nChannel, int nStreamType, TTXPfnAVEncoderCB pfnEncoderCB, void* pEncUsr, void** ppAVUsr) {	return false;	}
		
	/*****************************************************************************
	//停止音视频编码，服务器停止实时视频和声音监听时将调用此接口
	//@nMediaType: 媒体类型，TTX_MEDIA_TYPE_AV 或者TTX_MEDIA_TYPE_AUDIO
	//@nChannel: 通道号从0开始
	//@nStreamType: 码流类型
	//@pAVUsr: 在StartAVEnc里面输入的pAVUsr参数
	//调用此接口后，上层必须停止调用数据回调函数
	******************************************************************************/
	virtual bool StopAVEnc(int nMediaType, int nChannel, int nStreamType, void* pAVUsr) {	return false;	}

	/*****************************************************************************
	//改变码流类型，直连设备使用，一般不需要重载此接口
	//@nMediaType: 媒体类型，TTX_MEDIA_TYPE_AV 或者TTX_MEDIA_TYPE_AUDIO
	//@nChannel: 通道号从0开始
	//@nStreamType: 码流类型
	//@nNewStreamType: 新的码流类型
	//@pAVUsr: 在StartAVEnc里面输入的pAVUsr参数
	******************************************************************************/
	virtual void ChangeStreamType(int nMediaType, int nChannel, int nStreamType, int nNewStreamType, void* pAVUsr) {}

	/*****************************************************************************
	//请求I帧
	//@nChannel: 通道号从0开始
	//@nStreamType: 码流类型
	//当一个新的客户端连接到媒体服务器时，服务器要求设备立刻产生一个I帧数据
	//由于3G网络传送I帧间隔一般都比较长，及时产生I帧，可以让客户端及时看到视频
	******************************************************************************/
	virtual bool AVEncIFrame(int nChannel, int nStreamType) { return false;	}

	/*****************************************************************************
	//获取音频编码的格式
	//@nChannel: 通道号从0开始
	//@nAudioStreamType: TTX_AUDIO_STREAM_MIC 或 TTX_AUDIO_STREAM_CAM,  TTX_AUDIO_STREAM_MIC为对讲时使用
	//@nAudioCoder: 音频类型TTX_AUDIO_TYPE_G726 等
	//如果不同通道的音频格式不一样，比如对讲使用g711，视频使用aac，请重载些接口
	//TTXNET_SetMediaInfo 接口配置的是平台对讲使用的音频格式
	//如果是同一个音频格式，则不需要重载GetAudioParam接口
	******************************************************************************/
	virtual bool GetAudioParam(int nChannel, int nAudioStreamType, int& nAudioCoder) {	return false;	}

	/*****************************************************************************
	//启动双向对讲
	//@nChannel: 通道号从0开始，表示麦克通道，从0开始
	//@pfnEncoderCB: 编码回调
	//@pEncUsr: 编码回调用户自定义数据
	//@ppDecUsr: 用户解码回调自字义函数，在
	//双向对讲时，将编码数据不停通过pfnEncoderCB，通知给网络层
	//设备启动音频解码器
	******************************************************************************/
	virtual bool StartTalkback(int nChannel, TTXPfnAVEncoderCB pfnEncoderCB, void* pEncUsr, void** ppTalkUsr) { 	return false;	}

	/*****************************************************************************
	//停止双向对讲
	//@nChannel: 通道号从0开始，表示麦克通道，从0开始
	//@pTalkUsr: 在StartTalkback里面输入的ppTalkUsr参数
	//设备可以关闭音频解码器
	******************************************************************************/
	virtual bool StopTalkback(int nChannel, void* pTalkUsr) 	{		return false;	}
	
	/*****************************************************************************
	//设置解码的音频参数,此接口无效,上层可以不做处理
	//@nChannel: 麦克通道
	//@nAudioType: 音频类型TTX_AUDIO_TYPE_G726_40KBPS 等
	//@nFrmLength: 每个音频帧的数据长度
	//@pTalkUsr: 在StartTalkback里面输入的ppTalkUsr参数
	******************************************************************************/
	virtual void TalkSetAudioParam(int nChannel, int nAudioType, int nFrmLength, void* pTalkUsr)	{}

	/*****************************************************************************
	//解码对讲数据
	//@nLength: 音频长度
	//@u64Stamp: 时间戳
	//@pData: 音频数据
	//@pTalkUsr: 在StartTalkback里面输入的ppTalkUsr参数
	******************************************************************************/
	virtual void TalkDecoder(int nChannel, int nLength, _u64long u64Stamp, const char* pData, void* pTalkUsr)	{}

	/*****************************************************************************
	//启动文件查找
	//@nYear: 年
	//@nMonth: 月
	//@nDay: 日
	//@nBeginTime: 开始时间，以秒为单位
	//@nEndTime: 结束时间，以秒为单位
	//@nRecType: 录像类型
	//@nChannel: 录像对应的通道
	//@pfnRecFindCB: 文件回调函数
	//@pFindUsr: 文件查找用户自定义数据
	//@pfnGetExitCB: 判断是否需要退出
	//@pExitUsr: 判断退出函数
	//网络库启动一个文件查找线程，进行录像文件查找
	//文件查找过程中，需要不停调用pfnGetExitCB，来判断是否需要退出
	//查找到文件，及时调用pfnRecFindCB，调用上层
	//查找过程中，每 个循环应当调用usleep(0)，避免CPU占用率高
	******************************************************************************/
	virtual void FindRecFile(int nYear, int nMonth, int nDay, int nBeginTime, int nEndTime, int nRecType, int nChannel
					, TTXPfnRecFindCB pfnRecFindCB, void* pFindUsr, TTXPfnGetExitCB pfnGetExitCB, void* pExitUsr) {}

	//支持跨天搜索(CMSV6客户端不支持跨天搜索,正常情况不需要重载此接口)
	virtual void FindRecFileEx(int nYearS, int nMonthS, int nDayS, int nBeginTime, int nYearE, int nMonthE, int nDayE, int nEndTime, int nRecType, int nChannel
					, TTXPfnRecFindCB pfnRecFindCB, void* pFindUsr, TTXPfnGetExitCB pfnGetExitCB, void* pExitUsr) {}

	/*****************************************************************************
	//启动音频文件查找
	//@nYear: 年
	//@nMonth: 月
	//@nDay: 日
	//@nBeginTime: 开始时间，以秒为单位
	//@nEndTime: 结束时间，以秒为单位
	//@nRecType: 文件类型
	//@nChannel: 音频对应的通道
	//@pfnRecFindCB: 文件回调函数
	//@pFindUsr: 文件查找用户自定义数据
	//@pfnGetExitCB: 判断是否需要退出
	//@pExitUsr: 判断退出函数
	//网络库启动一个文件查找线程，进行录像文件查找
	//文件查找过程中，需要不停调用pfnGetExitCB，来判断是否需要退出
	//查找到文件，及时调用pfnRecFindCB，调用上层
	//查找过程中，每 个循环应当调用usleep(0)，避免CPU占用率高
	******************************************************************************/
	virtual void FindAudioFile(int nYear, int nMonth, int nDay, int nBeginTime, int nEndTime, int nRecType, int nChannel
					, TTXPfnRecFindCB pfnRecFindCB, void* pFindUsr, TTXPfnGetExitCB pfnGetExitCB, void* pExitUsr) {}

	/*****************************************************************************
	//启动图片文件查找
	//@nYear: 年
	//@nMonth: 月
	//@nDay: 日
	//@nBeginTime: 开始时间，以秒为单位
	//@nEndTime: 结束时间，以秒为单位
	//@nType: 文件类型
	//@nChannel: 录像对应的通道
	//@pfnRecFindCB: 文件回调函数
	//@pFindUsr: 文件查找用户自定义数据
	//@pfnGetExitCB: 判断是否需要退出
	//@pExitUsr: 判断退出函数
	//文件查找过程中，需要不停调用pfnGetExitCB，来判断是否需要退出
	//查找到文件，及时调用pfnRecFindCB，调用上层
	******************************************************************************/
	virtual void FindJpegFile(int nYear, int nMonth, int nDay, int nBeginTime, int nEndTime, int nType, int nChannel
					, TTXPfnRecFindCB pfnRecFindCB, void* pFindUsr, TTXPfnGetExitCB pfnGetExitCB, void* pExitUsr) {}

	
	/*****************************************************************************
	//启动日志文件
	//@nYear: 年
	//@nMonth: 月
	//@nDay: 日
	//@nBeginTime: 开始时间，以秒为单位
	//@nEndTime: 结束时间，以秒为单位
	//@nType: 文件类型
	//@nChannel: 录像对应的通道
	//@pfnRecFindCB: 文件回调函数
	//@pFindUsr: 文件查找用户自定义数据
	//@pfnGetExitCB: 判断是否需要退出
	//@pExitUsr: 判断退出函数
	//文件查找过程中，需要不停调用pfnGetExitCB，来判断是否需要退出
	//查找到文件，及时调用pfnRecFindCB，调用上层
	******************************************************************************/
	virtual void FindLogFile(int nYear, int nMonth, int nDay, int nBeginTime, int nEndTime, int nType, int nChannel
					, TTXPfnRecFindCB pfnRecFindCB, void* pFindUsr, TTXPfnGetExitCB pfnGetExitCB, void* pExitUsr) {}

	/*****************************************************************************
	//通知进行录像文件下载，上层一般不需要重载此函数
	//@szFile: 录像文件名称
	//如果返回false，则不允许此文件的下载，上层一般不需要重载此函数
	******************************************************************************/
	virtual bool DownRecFile(const char* szFile) {	return true;	}

	/*****************************************************************************
	//获取下载的文件大小，上层一般不需要重载此函数
	//@szFile: 录像文件名称, szRealName真实的名称
	//如果返回true，表示改变了下载的文件名称
	******************************************************************************/
	virtual bool GetDownFileRealName(const char* szFile, char* szRealName, int nRealNameLength) {	return false;	}

	/*****************************************************************************
	//获取下载的文件偏移，上层一般不需要重载此函数
	//@szFile: 录像文件名称
	//如果返回0表示从文件头部开始下载，否则则从偏移处开始下载
	******************************************************************************/
	virtual _u64long GetDownRecOffset(const char* szFile) {	return 0;	}

	/*****************************************************************************
	//获取下载的文件大小，上层一般不需要重载此函数
	//@szFile: 录像文件名称
	//如果返回0表示下载整个文件，返回其它值表示下载指定长度的文件
	******************************************************************************/
	virtual _u64long GetDownRecLenth(const char* szFile) {	return 0;	}
	
	/*****************************************************************************
	//设备进行图片抓拍操作，并将图片保存到文件中
	//并将文件路径返回给网络库
	//网络库将保存好的图片传送到服务器上
	//@nChannel: 通道信息
	//@szFileName: 图片文件名称，全路径
	//@bDelete: 表示文件上传完成后，是否执行删除文件操作
	//设备可以将图片存储到硬盘上，也可以存储到内存中
	//如果设备没有硬盘，则建议存储到内存文件中
	******************************************************************************/
	virtual bool Snapshot(int nChannel, char* szFileName, bool& bDelete) {	return false;	}

	/*****************************************************************************
	//获取和设置参数是使用整个参数文件(有指定的格式) 
	//获取参数配置文件，并将参数配置文件返回到客户端
	//@szFileName: 参数配置文件名称
	//@bDelete: 表示文件上传完成后，是否执行删除文件操作
	******************************************************************************/
	virtual bool GetConfigFile(char* szFileName, bool& bDelete) {	return false;	}

	/*****************************************************************************
	//获取和设置参数是使用整个参数文件(有指定的格式) 
	//配置设备参数，由于考虑一般参数文件都比较小，
	//因此直接先缓存在内存
	******************************************************************************/
	virtual bool SetConfigFile( const char* pConfigBuf, int nBufLen ) {	return false;	}

	/*****************************************************************************
	//升级流程:   1、CheckUpgradeVer，判断升级文件版本信息
						客户端升级时，会先传送升级版本信息给设备
					  2、GetUpgradeFile，返回升级文件存储路径中
					  3、网络库接收升级文件，并存储到本地中
					  4、CheckUpgradeFile，校验升级文件
					  5、UpgradeDevice，校验成功后，执行升级
	//获取升级文件路径
	//返回升级文件的存储路径
	******************************************************************************/
	//校验升级版本
	virtual bool CheckUpgradeVer(const char* szVer){	return true;	}
	//获取升级文件存储路径
	virtual bool GetUpgradeFile(char* szFileName){	return false;	}
	//校验升级文件
	virtual bool CheckUpgradeFile(const char* szFileName)	{	return false;	}
	//进行设备升级
	virtual void UpgradeDevice(const char* szFileName)	{	}
	
	/*****************************************************************************
	//通知进行录像回放操作
	//@szFile: 录像文件名称
	//@ppRecFile:上层 需要创建录像解析对象子类返回给SDK，SDK调用此对象将文件解析成帧信息
	//如果返回false，则表示文件不存在
	//调用流程
	//	1、先InitRecFile，取得文件解析对象
	// 	2、pRecFile->OpenFile，调用文件解析对象打开文件接口
	//	3、pRecFile->GetFileInfo，取得文件信息
	//	4、pRecFile->ReadFrame，读取帧数据
	******************************************************************************/
	virtual bool InitRecFile(CTTXRecFile** ppRecFile) {	return false;	}
	
	/*****************************************************************************
	//释放文件解析对象
	//@pRecFile: 录像解析对象，此对象由InitRecFile 接口创建
	******************************************************************************/
	virtual void FreeRecFile(CTTXRecFile* pRecFile) {		}

	/*****************************************************************************
	//文件上传流程:   	1、GetUploadFilePath，获取上传文件的保存路径
							2、SaveUploadFile，文件上传完成后，调用SaveUploadFile，上层可以对文件进行相应的处理
	//获取文件上传的路径
	******************************************************************************/
	//获取文件存储路径
	//@nFileType: 文件类型	TTX_UPLOAD_FILE_TYPE_PICTURE
	//@szSvrFile: 对应在服务器上文件的名字
	//@szFileName: 输出参数，上层返回存储的文件路径
	virtual bool GetUploadFilePath(int nFileType, const char* szParam, const char* szSvrFile, char* szSaveFileName)	{	return false;	}
	//保存上传的文件
	virtual void SaveUploadFile(const char* szFileName, const char* szMd5)	{	}

	/*****************************************************************************
	//透明查询接口，用于查询设备日志等信息
	//@nType: 查询类型
	//@szParam: 查询参数
	//@pfnTranQueryData: 透明查询回调函数
	//@pFindUsr: 查询用户自定义数据
	//@pfnGetExitCB: 判断是否需要退出
	//@pExitUsr: 判断退出函数
	//网络库启动一个文件查找线程，进行录像文件查找
	//文件查找过程中，需要不停调用pfnGetExitCB，来判断是否需要退出
	//查找到文件，及时调用pfnTranQueryData，调用上层
	//查找过程中，每 个循环应当调用usleep(0)，避免CPU占用率高
	******************************************************************************/
	virtual void TransQuery(int nType, const char* szParam, TTXPfnTranQueryDataCB pfnTranQueryData, void* pFindUsr
				, TTXPfnGetExitCB pfnGetExitCB, void* pExitUsr) {}

	/*****************************************************************************
	//同步时间(与服务器进行时间同步)，设备需要跟据自身的时区，再更新本地的时间
	//参数为UTC是格林威治时间, 全球标准时间，每次登录成功后，都会进行校时操作
	******************************************************************************/
	virtual void SyncTime(struct tm& utcTime) {}


protected:
	TTXGpsInfo_S	m_GpsInfo;		//GPS位置信息
	TTXVehiStatus_S	m_VehiState;	//车辆状态信息
	TTXDiskStatus_S	m_DiskStatus;	//硬盘状态
	TTXIOStatus_S	m_IOStatus;		//IO状态
	TTXObdStatus_S m_ObdStatus;		//OBD状态
	TTXPeopleStatus_S m_PeopleStatus;	//人数统计状态
	TTXChannelStatus_S 	m_ChannelStaus;	//通道状态
	TTXModuleStatus_S	m_ModuleStatus;	//模块状态
	TTXTemperature_S	m_Temperature;	//温度状态
	TTXSlagStatus_S		m_SlagStatus;	//渣土车状态
	int				m_nGpsInterval;		//GPS发送间隔，单位秒
	int				m_nHeartInterval;	//心跳发送间隔, 单位秒
	int				m_nTtsFlag;		//tts标志
	int				m_nTtsParam;	//tts参数
	TTXGsensorInfo_S	m_Gsensorinfo; //gSensor信息
};

//文件回放注意事项
//GetFileInfo返回 _u64long u64BegPts; //文件起始的时间戳，为文件第一帧的时间戳
//ReadFrame帧接口时，会对每个帧返回的时间戳( _u64long u64Pts;)与u64BegPts文件起始的时间戳进行比对
//(u64Pts - u64BegPts)/1000 > uiTotalMinSecond，则表示文件播放结束了
//要注意音频帧的时间戳
class LIBDVRNET_API CTTXRecFile
{
public:
	CTTXRecFile() 
	{	
		memset(m_szRecFile, 0, sizeof(m_szRecFile));	
		m_usChnMask = 0;
	}
	virtual ~CTTXRecFile() {}

public:
	//配置要预览的通道信息,当一个录像文件有多个通道的录像时，此参数有效
	//按位表示第0位为1时表示需要获取通道1视频
	//如果文件只有单通道的录像，则不需要关注些接口
	//先调用SetChnMask，再调用OpenFile
	virtual void SetChnMask(unsigned short usChnMask) {	m_usChnMask = usChnMask;	}
	//打开文件
	//成功返回true，失败返回false
	virtual bool OpenFile( const char *pU8FileName) = 0;
	//关闭文件
	virtual bool CloseFile() = 0; 	
	//取得文件信息
	virtual void GetFileInfo(TTXFILEInfo_S* pFileInfo) = 0;
	//移动到文件头部
	virtual bool SeekBegin() = 0;
	//读取一帧数据
	//对视频和音频而言返回码流信息
	//有的视频帧内容还会包括GPS信息，请将需要将GPS信息当成信息帧返回
	virtual bool ReadFrame( TTXFILEFrame_S *pFrame1, TTXFILEFrame_S *pFrame2 ) = 0;
	//文件偏移
	//nMinSecond 相对于文件头部的起始时间，单位毫秒
	virtual bool SeekIFrame(int nMinSecond) = 0;
	//从文件头向后查找帧信息
	//用于快放，只查找I帧
	virtual bool ForwardIFrame( TTXFILEFrame_S *pFrame1, TTXFILEFrame_S *pFrame2) = 0;
		//打开文件
	//成功返回true，失败返回false
	//如果nChnMask不为0，则以nChnMask为主，否则以nChn为主
	virtual bool OpenTimeRange(int nChn, const struct tm& tmBeg, const struct tm& tmEnd) {	return false;	}

protected:
	char	m_szRecFile[256];
	unsigned short m_usChnMask;
};

class LIBDVRNET_API CTTXFrameReader
{
public:
	CTTXFrameReader(int nMediaType, int nChannel, int nStreamType) 
	{	
		m_nMediaType = nMediaType;
		m_nChannel = nChannel;
		m_nStreamType = nStreamType;
	}
	virtual ~CTTXFrameReader() {}

private:
	CTTXFrameReader();

public:
	//移动到最新的读取位置
	//实时视频时返回到最新的一个I帧的位置
	//音频监听或者对讲时，移动到最新的一个音频帧处
	virtual void SeekNewestFrame(bool bIFrame) = 0;
	//读取帧数据
	//nType帧类型	TTX_FRM_TYPE_I, TTX_FRM_TYPE_P, TTX_FRM_TYPE_A等
	//nLength帧长度
	//u64Stamp时间戳
	//pFrmBuf帧缓存，直接将帧数据拷贝到pFrmBuf中
	//nFBufLen输入时表示pFrmBuf的长度，拷贝的时候要判断实际的帧长度要比nFBufLen小
	//如果实际的帧长度要比nFBufLen大，则要返回false，并且将nFBufLen置为真实的帧长度
	virtual bool ReadFrame(int& nType, int& nLength, _u64long& u64Stamp, char* pFrmBuf, int& nFBufLen) = 0;
	//获取缓存中的帧数目
	virtual int GetFrameNum() = 0;
	//获取缓存中的帧的时间长度(单位毫秒)
	virtual long GetTotalTime() = 0;
	
protected:
	int 	m_nMediaType;
	int 	m_nChannel;
	int 	m_nStreamType;
};

#endif

