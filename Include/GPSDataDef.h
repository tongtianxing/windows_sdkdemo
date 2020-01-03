#ifndef _GPS_DATA_DEF_H_
#define _GPS_DATA_DEF_H_

#include "GPSDeviceDef.h"

#define GPS_DEV_ID_LEN						32
//#define GPS_MAX_DEV_CHN_NUM					16
#define GPS_MAX_DEV_CHN_NUM					12		//IO数目增加为12个，通道数目由16变为12个
#define GPS_MAX_DEV_CHN_NUM_EX				16		//过检时最多允许有16个通道的
#define GPS_MAX_DEV_IO_NUM_OLD				8
#define GPS_MAX_DEV_IO_NUM_NEW				12
#define GPS_MAX_DEV_IO_NUM_NEW_EX			16		// 16 [2018-8-21 ydl]
#define GPS_MAX_TEMP_SENSOR_NUM				4
#define GPS_MAX_TEMP_SENSOR_NUM_EX			6				

#define GPSSERVER_TYPE_LOGIN				1
#define GPSSERVER_TYPE_GATEWAY				2
#define GPSSERVER_TYPE_MEDIA				3
#define GPSSERVER_TYPE_USRMGR				4
#define GPSSERVER_TYPE_STORAGE				5
#define GPSSERVER_TYPE_WEB					6
#define GPSSERVER_TYPE_DOWN					7		//下载服务器
#define GPSSERVER_TYPE_MYSQL				8		//mysql服务 hw 2013/12/27
#define GPSSERVER_TYPE_LICENSE				9		//授权服务器
#define GPSSERVER_TYPE_GB28181				10
#define GPSSERVER_TYPE_FTP					11	
#define GPSSERVER_TYPE_MYCAT				12
#define GPSSERVER_TYPE_DATAPROC				13
#define GPSSERVER_TYPE_MANAGER				99		//管理服务器

#define GPS_FILE_LOCATION_DEVICE			1		//设备
#define GPS_FILE_LOCATION_STOSVR			2		//存储服务器
#define GPS_FILE_LOCATION_LOCAL				3		//客户端本地
#define GPS_FILE_LOCATION_DOWNSVR			4		//下载服务器

#define GPS_FILE_ATTRIBUTE_JPEG				1		//图片
#define GPS_FILE_ATTRIBUTE_RECORD			2		//录像
///#define GPS_FILE_ATTRIBUTE_ALL			3		//搜索时使用表示搜索所有录像文件
#define GPS_FILE_ATTRIBUTE_LOG				4		//log
#define GPS_FILE_ATTRIBUTE_AUDIO			5		//音频
#define GPS_FILE_ATTRIBUTE_TEXT				6		//苏标---文本
#define GPS_FILE_ATTRIBUTE_OTHER			7		//苏标---其它

#define GPS_FILE_SOURCE_PLAN				1		//存储计划生成
#define GPS_FILE_SOURCE_UPLOAD				2		//设备主动上传的
#define GPS_FILE_SOURCE_SB_ALARM			3		//苏标设备报警后下载

#define GPS_LOGIN_SUC						0		//Login direction server success
#define GPS_LOGIN_FAILED					1		//Login direction server failed
#define	GPS_LOGIN_DISCNT					2		//Login direction server disconnect
#define	GPS_LOGIN_NAME_ERR					3		//Login direction server user name error
#define	GPS_LOGIN_PWD_ERR					4		//Login direction server user pwd error
#define	GPS_LOGIN_FULL_ERR					5		//Login direction server （用户服务器用户满）
#define	GPS_LOGIN_VER_ERR					6		//Login direction server version error
#define	GPS_LOGIN_USR_CHANGE				7		//Login direction server （用户在其它位置进行登录）
#define GPS_LOGIN_USR_DEL					8		//Login direction server （用户被删除）
#define	GPS_LOGIN_EXPIRED					9		//Login direction server use expired
#define	GPS_LOGIN_SERVER_EMPTY				10		//Login direction server （或者不存在用户服务器信息）
#define GPS_LOGIN_PRIVILEGE_CHANGE			11		//用户权限发送变化
#define	GPS_LOGIN_SVR_CONFIG_CHANGE			12		//服务器配置信息发送变化
#define GPS_LOGIN_USR_DISABLED				13		//用户已停用
#define GPS_LOGIN_HAS_LOGINED				14		//用户已经登录
#define GPS_LOGIN_LOGOUT_IMPERATIVE			15		//用户强制下线
#define GPS_LOGIN_NO_SUPPORT_PTT			16		//不支持调度功能

#define GPS_LOGIN_TYPE_GPS_CLIENT			1

#define GPS_DEV_DOWN_DEV					0
#define GPS_DEV_DOWN_GROUP					1
#define GPS_DEV_DOWN_FAILED					2
#define GPS_DEV_DOWN_SUC					3
#define GPS_DEV_DOWN_RELATION				4
#define GPS_DEV_DOWN_DATA					5
#define GPS_DEV_DOWN_DATA_LONG				6	//设备信息中的过长数据


#define GPS_DOWN_CONFIG_DATA				1
#define GPS_DOWN_CONFIG_FAILED				2
#define GPS_DOWN_CONFIG_SUC					3
#define GPS_DOWN_MAP_MARKER					4		//地图标记信息
#define GPS_DOWN_MAP_LINE					5		//地图线路信息
#define GPS_DOWM_MAP_TAB_INFO				6		//地图标记属性
#define GPS_DOWN_ALL_USER_INFO				7		//所有用户信息
#define GPS_DOWN_ALL_GROUP_INFO				8		//所有分组信息
#define GPS_DOWN_USER_ONLINE_EX				9		//用户在线信息扩展
#define GPS_DOWN_MAP_MARKER_STR				10

// 客户端批量下载数据时,回调类型定义
#define GPS_BETCH_DOWN_DEVICE_VEHICLE_OTHER		10001	//车辆的扩展信息,对应结构体为GPSVehiOtherVariable_S
#define GPS_BETCH_DOWN_DEVICE_VEHICLE_WORKTIME	10002	//车辆的全月工作时长,对应结构体为GPSVehiWorkTimeVariable_S
#define GPS_BETCH_DOWN_DEVICE_VEHICLE_OTHER_NEW	10003	//车辆的扩展信息,对应结构体为GPSVehiOtherVariableNew_S
#define GPS_BETCH_DOWN_DEVICE_VEHICLE_LONG_STR	10004	//字符串数据

//hw 
#define GPS_VERSION_6_14_X_X				0		//6.14
#define GPS_VERSION_6_15_X_X				1		//6.15.X.X版本,修改了传输UFT8格式数据
#define GPS_VERSION_CUR		GPS_VERSION_6_15_X_X	//当前版本

#define GPS_VERSION_EX_X_X					0		//6.18.0.2之前版本版本
#define GPS_VERSION_EX_6_18_0_2				1		//6.18.0.2版本,修改了TTS传输1024长度
#define GPS_VERSION_EX_7_0_0_12				2		//7.0.0.12版本,地图从服务器加载 
#define GPS_VERSION_EX_7_6_0_4				3		//7.6.0.4版本,客户端识别服务器版本(修改获取地图标签为UTF8)
#define GPS_VERSION_EX_7_6_0_5				5		//7.6.0.5版本,客户端识别服务器版本(修改发送TTS为UTF8)
#define GPS_VERSION_EX_7_6_0_6				6		//7.6.0.6版本,客户端识别服务器版本(参数透传配置增加为2048字节)
#define GPS_VERSION_EX_7_6_0_7				7		//7.6.0.7版本,服务器支持录像多路回放
#define GPS_VERSION_EX_7_6_0_8				8		//7.6.0.8版本,服务器支持部分参数存储
#define GPS_VERSION_EX_7_6_0_9				9		//7.6.0.9版本,服务器的地图区域取消结构体,使用字符串拼接
#define GPS_VERSION_EX_CUR		GPS_VERSION_EX_7_6_0_9	//当前版本

//服务器版本类型定义 zjt 2014-01-05
#define GPS_SVR_VERSION_DEFUALT				0	//CMS服务器
#define GPS_SVR_VERSION_DJWL				1	//CMS服务器(DJWL)
#define GPS_SVR_VERSION_JT808				2	//JT808服务器


//hw 2013/1/19
//连接服务器的网络类型 0-使用局域网IP， 1-使用广域网IP
#define GPS_NET_TYPE_LAN		0
#define GPS_NET_TYPE_WAN		1

//客户端下载信息位定义
#define GPS_DOWN_CONFIG
#define GPS_DOWN_CONFIG_SVR_CONFIG			0	//0位服务器配置
#define GPS_DOWN_CONFIG_PRIVILEG			1	//1位用户权限
#define GPS_DOWN_CONFIG_MAP_CONFIG			2	//2位地图配置
#define GPS_DOWN_CONFIG_USER_INFO			3	//3位用户信息
#define	GPS_DWON_CONFIG_USER_TYPE			4	//4位用户类型
#define	GPS_DWON_CONFIG_CLIENT_FUNCTION		5	//5位客户端功能配置
#define GPS_DOWN_CONFIG_OTHER_PARAM			6	//6位其他控制参数(自动关闭等)
#define GPS_DOWN_CONFIG_GOOGLE_KEY			7	//谷歌地理解析的key


#define GPS_DOWNLOAD_MSG_FAILED				1 //失败
#define GPS_DOWNLOAD_MSG_BEGIN				2 //开始
#define GPS_DOWNLOAD_MSG_FINISHED			3 //完成
#define GPS_DOWNLOAD_MSG_PROCESS			4 //进度(文件长度)
#define GPS_DOWNLOAD_MSG_PROCESS_EX			5 //进度(百分比)


#define GPS_UPLOAD_MSG_FAILED				1
#define GPS_UPLOAD_MSG_FINISHED				2
#define GPS_UPLOAD_MSG_PROCESS				3


//设备模块位定义
#define GPS_DEV_MOUDLE_VIDEO			0	//视频
#define GPS_DEV_MODULE_OIL_CONTROL		1	//油路控制
#define GPS_DEV_MODULE_POWER_CONTROL	2	//电路控制
#define GPS_DEV_MODULE_TTS				3	//tts语音
#define GPS_DEV_MODULE_BK_TALK			4	//数字对讲
#define GPS_DEV_MOUDLE_SNAPSHOT			5	//抓拍
#define GPS_DEV_MOUDLE_MONITOR			6	//监听
#define GPS_DEV_MOUDLE_OIL_SEN			7	//油量传感器
#define GPS_DEV_MOUDLE_TALK				8	//对讲
#define GPS_DEV_MOUDLE_ODB				9	//ODB外设
#define GPS_DEV_MOUDLE_COUNT_PEOPLE		10	//人数统计模块
#define GPS_DEV_MOUDLE_OIL_EXPAND_100	14	//油量放大100倍

//老服务器油量模块定义
#define GPS_DEV_MOUDLE_OIL_SEN_V6		0	//V6版本油量模块

//浏览器类型
#define GPS_BROWSER_TYPE_IE				0
#define GPS_BROWSER_TYPE_WEBKIT			1




const int GPS_CTRL_TYPE_OIL_STOP			= 1;	//断开油路
const int GPS_CTRL_TYPE_OIL_RESTORE			= 2;	//恢复油路
const int GPS_CTRL_TYPE_ELEC_STOP			= 3;	//断开电路
const int GPS_CTRL_TYPE_ELEC_RESTORE		= 4;	//恢复电路
const int GPS_CTRL_TYPE_REBOOT				= 5;	//重启机器 
const int GPS_CTRL_TYPE_RESET				= 6;	//设备复位
const int GPS_CTRL_TYPE_MOD_DEV_NUM_OR_GET_STATUS = 7;//修改设备号、获取设备状态
const int GPS_CTRL_TYPE_3G_REBOOT_IP       =8;     //IP,3G,重启

const int  GPS_CTRL_TYPE_SLEEP				= 7;	//休眠
const int  GPS_CTRL_TYPE_WAKE				= 8;	//唤醒
//录像的通道号0表示通道1，1表示通道2     98表示所有通道(TTX_CHANNEL_ALL)
const int  GPS_CTRL_TYPE_START_RECORD		= 9;	//开始录像	//高两字节为录像的通道号，低两字节为指令
const int  GPS_CTRL_TYPE_STOP_RECORD		= 10;	//停止录像	//高两字节为录像的通道号，低两字节为指令
const int  GPS_CTRL_TYPE_START_CRUISE		= 11;	//客户端开始对此通道进行轮询，高两字节为通道号，低两字节为指令
const int  GPS_CTRL_TYPE_STOP_CRUISE		= 12;	//客户端停止对此通道进行轮询，高两字节为通道号，低两字节为指令
const int  GPS_CTRL_TYPE_WRITE_LOG		= 13;	//启动记录日志功能	高两个字节大于0表示写日志，0表示不写日志
const int  GPS_CTRL_TYPE_FORMAT_HDD		= 14;	//格式化硬盘(高位表示硬盘号,硬盘号从0开始,低位表示命令号)
const int  GPS_CTRL_TYPE_MILEAGE_CLEARED 	= 15;	//里程清零	
const int  GPS_CTRL_TYPE_FLIP_HORIZONTAL 	= 16;	//水平翻转	//高两字节为通道号，低两字节为指令
const int  GPS_CTRL_TYPE_FLIP_VERTICAL 		= 17;	//垂直翻转	//高两字节为通道号，低两字节为指令
const int  GPS_CTRL_TYPE_CLEAR_ALARM		= 18;	//清除报警
const int  GPS__CTRL_TYPE_SWITCH_CAM		= 19;		//切换摄像头
const int  GPS__CTRL_TYPE_RECORD_SOUND		= 20;		//开始录音    //高两字节为录音的通道号，低两字节为指令
const int  GPS__CTRL_TYPE_STOP_REC_SOUND	= 21;		//停止录音    //高两字节为录音的通道号，低两字节为指令
const int  GPS__CTRL_TYPE_WIFI_DOWN_FINISH	= 22;		//wifi下载结束
const int  GPS_CTRL_TYPE_RESET_PEOPLE		= 23;	//复位人数统计

const int GPS_MNGCMD_SEND_SMS				= 1;    //发送短消息
const int GPS_MNGCMD_SEND_TEXT				= 2;    //发送TTS，设备上进行播放发送的文件
const int GPS_MNGCMD_SEND_PTZ				= 3;    //PTZ控制指令
const int GPS_MNGCMD_SEND_CTRL				= 4;    //发送控制指令，如断油、断电等
const int GPS_MNGCMD_READ_STATUS			= 5;    //获取车辆状态
const int GPS_MNGCMD_CHANGE_USR_PWD			= 6;    //修改用户密码
const int GPS_MNGCMD_SET_GPS_INTERVAL		= 7;    //设置GPS间隔时间
const int GPS_MNGCMD_CHECK_CTRL_USR			= 8;	//发送控制命令前校验用户
const int GPS_MNGCMD_READ_MOTION_PARAM		= 9;	//获取移动侦测参数
const int GPS_MNGCMD_SET_MOTION_PARAM		= 10;   //配置移动侦测参数
const int GPS_MNGCMD_READ_NETFLOW_STATISTICS	= 11;   //获取流量信息
const int GPS_MNGCMD_SET_NETFLOW_PARAM			= 12;	//配置流量参数
const int GPS_MNGCMD_CLEAR_NETFLOW_STATISTICS	= 13;   //清空流量统计
const int GPS_MNGCMD_ADJUST_NETFLOW_STATISTICS	= 14;	//调整流量统计
const int GPS_MNGCMD_SET_USR_ALARMSHIELD	= 15;		//配置报警屏蔽
const int GPS_MNGCMD_ADD_MAP_MARKER			= 16;		//添加地图标记信息
const int GPS_MNGCMD_DEL_MAP_MARKER			= 17;		//删除地图标记信息
const int GPS_MNGCMD_SEND_DISPATCH_COMMAND	= 18;		//发送调度指令信息
const int GPS_MNGCMD_ADD_MAP_MARKERINFO		= 19;		//添加地图标记属性
const int GPS_MNGCMD_SET_USER_MAP_CONFIG	= 20;		//设置用户地图配置
const int GPS_MNGCMD_TRANSPARENT_DATA		= 24;		//透传数据
const int GPS_MNGCMD_TRANSPARENT_CONFIG		= 25;		//参数透传功能
const int GPS_MNGCMD_FREE_PRESET_GET		= 26;		//获取空闲预置位
const int GPS_MNGCMD_SET_VIDEO_COLOR		= 27;		//设置颜色
const int GPS_MNGCMD_GET_VIDEO_COLOR		= 28;		//获取颜色
const int GPS_MNGCMD_SET_DEV_FIX_GPS		= 29;		//设置设备的GPS位置
const int GPS_MNGCMD_SET_DEV_OIL_RESISTANCE	= 30;		//设置设备的油量刻度值
const int GPS_MNGCMD_SET_DEV_HANDLE_ALARM   = 31;		//设备报警处理
const int GPS_MNGCMD_ACK_809_PLATFORM		= 32;		//809查岗信息应答
const int GPS_MNGCMD_JT809_BUSINESS_PLATFORM	= 33;	//809相关业务
const int GPS_MNGCMD_SEND_USER_TEXT = 34;				//向用户发送文本消息
const int GPS_MNGCMD_SEND_FTP_TASK_CTRL = 35;			//车辆发送FTP任务
const int GPS_MNGCMD_SEND_CREATE_CLIENT_ALARM = 36;		//制造一个报警
const int GPS_MNGCMD_CHANGE_USE_STATUS = 37;			//改变车辆使用状态

// const int GPS_MNGCMD_SET_VIDEO_CONFIG		= 21;		//设置设备视频参数
// const int GPS_MNGCMD_SET_AUDIO_CONFIG		= 22;		//设置设备音频参数
// const int GPS_MNGCMD_SET_PTZ_CONFIG			= 23;		//设置设备云台参数
// const int GPS_MNGCMD_GET_VIDEO_CONFIG		= 24;		//获取设备视频参数
// const int GPS_MNGCMD_GET_AUDIO_CONFIG		= 25;		//获取设备音频参数
// const int GPS_MNGCMD_GET_PTZ_CONFIG			= 26;		//获取设备云台参数

const int GPS_MAPMARKER_TYPE_POINT			= 1;		//点
const int GPS_MAPMARKER_TYPE_RECTANGLE		= 2;		//矩形
const int GPS_MAPMARKER_TYPE_POLYGON		= 3;		//多边形
const int GPS_MAPMARKER_TYPE_LINE			= 4;		//路线
const int GPS_MAPMARKER_TYPE_CIRCLE			= 10;		//圆
const int GPS_MAPMARKER_TYPE_RECTANGLE_RESTRICTED = 11;	//禁行区域矩形
const int GPS_MAPMARKER_TYPE_POLYGON_RESTRICTED = 12;	//禁行区域多边形
const int GPS_MAPMARKER_TYPE_LINE_RESTRICTED = 13;		//禁行区域路线
const int GPS_MAPMARKER_TYPE_CIRCLE_RESTRICTED = 14;	//禁行区域圆

#include <tchar.h>
//存储路径定义，存储示例	"E:\\gStorage\\RECORD_FILE\\100001\\2012-07-03\\"
const TCHAR GPS_STORAGE_PATH[]				= _T("gStorage");
const TCHAR GPS_RECORD_PATH[]				= _T("RECORD_FILE");
const TCHAR GPS_JPEG_PATH[]					= _T("JPEG_FILE");
const TCHAR GPS_LOG_PATH[]					= _T("LOG_FILE");

//0位-电子围栏
//1位-短信
//2位-自动下载
//3位-3g流量统计
//4位-手机客户端
//5位-点播
//6位-中心存储
//7位-人员定位
#define GPS_SVR_CONFIG_FENCE			0
#define GPS_SVR_CONFIG_SMS				1
#define GPS_SVR_CONFIG_AUTO_DONW		2
#define GPS_SVR_CONFIG_FLOW				3
#define GPS_SVR_CONFIG_PHONE			4
#define GPS_SVR_CONFIG_PLAYBACK			5
#define GPS_SVR_CONFIG_CENTER_STORAGE	6
#define GPS_SVR_CONFIG_TRACKER			7

//用户类型定义
#define GPS_USER_TYPE_SYS_ADMIN		-1	//管理员
#define GPS_USER_TYPE_COMMON		0	//普通用户
#define GPS_USER_TYPE_ADMIN			1	//企业管理员
#define GPS_USER_TYPE_TEST			2	//测试用户

//下载任务状态定义
#define GPS_DOWNTASK_STATUS_INIT		1		//处于未分配状态
#define GPS_DOWNTASK_STATUS_ALLOC		2		//已经分配，表示正在下载
#define GPS_DOWNTASK_STATUS_FAILED		3		//下载失败
#define GPS_DOWNTASK_STATUS_SUC			4		//下载成功

#define GPS_DOWNTASK_DOWNTYPE_FILE				1		//下载类型，文件下载
#define GPS_DOWNTASK_DOWNTYPE_RANGE				2		//分段下载

#define GPS_SERVER_MODE_VEHICLE						0			//车载系统
#define GPS_SERVER_MODE_POLICE						1001		//执法仪
#define GPS_SERVER_MODE_VEHI_POLI					1002		//车载和执法仪

// 长字符串的ID定义
#define GPS_LONG_STR_FLAG
// CMsgClientDevice::GetUsrDevPermitJT808处使用
#define GPS_LONG_STR_FLAG_CHN_NAME_1		1	//通道名称 车辆ID,编号
#define GPS_LONG_STR_FLAG_CHN_NAME_16		16
#define GPS_LONG_STR_FLAG_IO_NAME_1			17	//IO名称 车辆ID,编号
#define GPS_LONG_STR_FLAG_IO_NAME_16		32
#define GPS_LONG_STR_FLAG_TEMP_NAME_1		33	//温度传感器 车辆ID,编号
#define GPS_LONG_STR_FLAG_TEMP_NAME_16		48
#define GPS_LONG_STR_FLAG_VEHI_COLOR		49	//车辆颜色 车辆ID
#define GPS_LONG_STR_FLAG_VEHI_BAND			50	//车辆品牌 车辆ID
#define GPS_LONG_STR_FLAG_VEHI_TYPE			51	//车辆类型 车辆ID
#define GPS_LONG_STR_FLAG_VEHI_USE			52	//车辆使用 车辆ID
#define GPS_LONG_STR_FLAG_VEHI_COMPANY		53	//车辆公司 车辆ID
#define GPS_LONG_STR_FLAG_VEHI_DRIVER_NAME	54	//车辆司机 车辆ID
#define GPS_LONG_STR_FLAG_VEHI_DRIVER_TEL	55	//车辆司机电话 车辆ID
#define GPS_LONG_STR_FLAG_VEHI_PEOPLE_NAME	56	//警员名(ptt) 车辆ID

// CMsgClientDevice::DoBetchData处使用
#define GPS_LONG_STR_FLAG_DBD_LINES_OPER	1000 //运营线路
#define GPS_LONG_STR_FLAG_DBD_MODEL_ADAS	1001 //ADAS型号
#define GPS_LONG_STR_FLAG_DBD_MODEL_DSM		1002 //DSM型号
#define GPS_LONG_STR_FLAG_DBD_MODEL_TPMS	1003 //TPMS型号
#define GPS_LONG_STR_FLAG_DBD_MODEL_BSD		1004 //BSD型号
#define GPS_LONG_STR_FLAG_DBD_BRAND_ADAS	1005 //ADAS品牌
#define GPS_LONG_STR_FLAG_DBD_BRAND_DSM		1006 //DSM品牌
#define GPS_LONG_STR_FLAG_DBD_BRAND_TPMS	1007 //TPMS品牌
#define GPS_LONG_STR_FLAG_DBD_BRAND_BSD		1008 //BSD品牌

#pragma pack(4)

typedef struct _tagGPSDEVDevInfo
{
	int		nID;				//Device Index
	char	szName[32];			//Device Name
	char	szIDNO[32];			//Device id
	int		nType;				//0 :Encoder, 1 :Decoder
	unsigned char ucChanNum;			//Channel Number
	unsigned char ucIoInNum;			//IO 输入数目
	unsigned char ucTempSensorNum;	//温度传感器数目
	unsigned char ucIcon;	//车辆图标
	char	szChnName[GPS_MAX_DEV_CHN_NUM][16];		
	char	szIoInExtent[4][16];	//增加4个IO定义		2013-06-22，变为12个IO
	char	szIoInName[GPS_MAX_DEV_IO_NUM_OLD][16];
	char	szTempSensorName[GPS_MAX_TEMP_SENSOR_NUM][16];
	int		nGroup;				//Device Group Index
	int		nOnline;			//Device Online Status
	
	char	szSIMCard[16];		//SIM卡号
	char	szVehiColor[16];	//车辆颜色
	char	szVehiBand[16];		//车辆品牌
	char	szVehiType[16];		//车辆类型
	char	szVehiUse[16];		//车辆用途
	char	szVehiCampany[16];	//车辆公司
	char	szDriverName[16];	//司机名称
	char	szDriverTele[16];	//司机电话
	unsigned int uiModule;		//模块参数

	//hw2013/11/14
	char cPayEnable;			//是否启用缴费功能
	char cPayPeriod;			//合约期限（以月为单位）
	char cPayMonth;				//已付费
	char cPayDelayDay;			//宽限天数
	unsigned int uiPayBegin;	//合约开始日
	
	char    szReserve[52];		//保留字段	60
}GPSDEVDevInfo_S, *LPGPSDEVDevInfo_S;

//此结构体和GPSDEVDevInfo_S一致，去除保留的52字节
//hw2013/11/14
typedef struct _tagGPSDEVDevInfoEx
{
	int		nID;				//Device Index
	char	szName[32];			//Device Name
	char	szIDNO[32];			//Device id
	int		nType;				//0 :Encoder, 1 :Decoder
	unsigned char ucChanNum;			//Channel Number
	unsigned char ucIoInNum;			//IO 输入数目
	unsigned char ucTempSensorNum;	//温度传感器数目
	unsigned char ucIcon;	//车辆图标
	char	szChnName[GPS_MAX_DEV_CHN_NUM][16];		
	char	szIoInExtent[4][16];	//增加4个IO定义		2013-06-22，变为12个IO
	char	szIoInName[GPS_MAX_DEV_IO_NUM_OLD][16];
	char	szTempSensorName[GPS_MAX_TEMP_SENSOR_NUM][16];
	int		nGroup;				//Device Group Index
	int		nOnline;			//Device Online Status
	
	char	szSIMCard[16];		//SIM卡号
	char	szVehiColor[16];	//车辆颜色
	char	szVehiBand[16];		//车辆品牌
	char	szVehiType[16];		//车辆类型
	char	szVehiUse[16];		//车辆用途
	char	szVehiCampany[16];	//车辆公司
	char	szDriverName[16];	//司机名称
	char	szDriverTele[16];	//司机电话
	unsigned int uiModule;		//模块参数

	char cPayEnable;			//是否启用缴费功能
	char cPayPeriod;			//合约期限（以月为单位）
	char cPayMonth;				//已付费
	char cPayDelayDay;			//宽限天数
	unsigned int uiPayBegin;	//合约开始日

}GPSDEVDevInfoEx_S, *LPGPSDEVDevInfoEx_S;

typedef struct _tagGPSMDVRInfo
{
	unsigned char ucIoInNum;			//IO 输入数目
	unsigned char ucTempSensorNum;	//温度传感器数目
	unsigned char ucPlateColor;		//车牌颜色	808用到	afu 2014-04-28
	unsigned char szRes;
	char	szChnName[GPS_MAX_DEV_CHN_NUM][16];		
	char	szIoInExtent[4][16];
	char	szIoInName[GPS_MAX_DEV_IO_NUM_OLD][16];
	char	szTempSensorName[GPS_MAX_TEMP_SENSOR_NUM][16];
	
	char	szVehiColor[16];	//车辆颜色
	char	szVehiBand[16];		//车辆品牌
	char	szVehiType[16];		//车辆类型
	char	szVehiUse[16];		//车辆用途 
	char	szVehiCampany[16];	//车辆公司
	char	szDriverName[16];	//司机名称
	char	szDriverTele[16];	//司机电话
	char	szSerialNumber[16];	//设备序列号
	int		nDriverID;			//司机ID
	char    cSensorType[6];		//0-温度，1-湿度
	char    szReserve[2];		//保留字段//保留 44->40 zjt-2016/04/08 
	//40->36  zjt-2017/04/18 增加传感器类型
	//36-2  zjt 2017/05/23  增加传感器类型
	char	szTempSensorNameEx[2][16];
}GPSMDVRInfo_S, *LPGPSMDVRInfo_S;	//总大小624字节

typedef struct _tagGPSDVSInfo_S
{
	char	szChnName[16][16];								//16个通道名称
	char	szIoInName[GPS_MAX_DEV_IO_NUM_NEW][16];			//12个IO名称
	char	szTempSensorName[GPS_MAX_TEMP_SENSOR_NUM][16];	//温度传感器名称
	char	szContactName[16];			//联系人名称
	char	szContactTel[16];			//联系人电话
	unsigned char ucIoInNum;			//IO 输入数目
	unsigned char ucTempSensorNum;		//温度传感器数目
	char    szReserve[78];				//保留78字段
}GPSDVSInfo_S, *LPGPSDVSInfo_S;			//总大小624字节


typedef struct _tagGPSMobileDevInfo
{
	unsigned char nSex;			//性别
	char strIDCar[19];			//身份证18位
	char strUserNumber[16];		//编号15
	char strGroupName[64];		//所属队名
	char strAddress[256];		//住址
	int nUserPost;				//职位
	int	nEquip;					//一位表示一种装备
	char szReserve[64];			//保留64字段
}GPSMobileDevInfo_S, *LPGPSMobileDevInfo_S;	//总大小428

typedef struct _tagGPSDevInfo
{
	int nID;
	char szIDNO[32];				//Device id
	char szName[32];				//Device Name
	char szSIMCard[16];				//电话
	int nDevType;					//设备主类型		MDVR、MOBILE、
	int	nDevSubType;				//设备子类型		普通GPS，通道数目需要配置为0个
	int	nGroup;						//Device Group Index
	int nOnline;					//Device Online Status
	unsigned int uiModule;			//模块参数
	unsigned char ucChanNum;		//Channel Number
	unsigned char ucIcon;			//车辆图标
	char strRemark[94];				//备注		//原来为126
	char cProtocol;					//协议类型
	char cAudioCodec;				//音频解码器类型，请求对讲时，使用此参数
	char cDiskType;					//磁盘类型
	char cFactoryType;				//厂家定义设备类型	在WKP协议下使用	
	char cFactoryDevType;			//厂商设备类型，用作区分1078设备
	char cExtendedProtocol;			//0:无, 1:苏标
	unsigned char ucMapValid;		//设置的位置是否有效
	unsigned char ucMapType;		//地图类型
	int	nJingDu;					//经度	4字节 整数部分	9999999 = 9.999999 
	int nWeiDu;						//纬度	4字节 整数部分	9999999 = 9.999999
	char cPayEnable;				//是否启用缴费功能
	char cPayPeriod;				//合约期限（以月为单位）
	char cPayMonth;					//已付费
	char cPayDelayDay;				//宽限天数
	unsigned int uiPayBegin;		//合约开始日
	char cDevStatus;				//设备维修状态(V7) 0-正常 1-维修 2-停用 3-欠费
	char cProtocolVersion;			//协议版本
	char strReserve[4];				//保留 zjt 7-5 2018/4/23 ,8->7 hw2014/07/23 16->8 hw2013/11/12, 27->16 hw2013/8/1
	unsigned short usSpeedLimit;	//平台配置车辆超速值
	union
	{
		GPSMDVRInfo_S gDVRInfo;
		GPSMobileDevInfo_S gMobileDevInfo;
		GPSDVSInfo_S DVSInfo;
	};
}GPSDevInfo_S, *LPGPSDevInfo_S;

static_assert(856 == sizeof(GPSDevInfo_S), "GPSDevInfo_S Size Error");

typedef struct _tagGPSChnName
{
	char szName[16];		// Channel Name
}GPSChnName_S, *LPGPSChnName_S;

typedef GPSChnName_S GPSIOName_S;

typedef struct _tagGPSDEVGroup
{
	int		nID;			//Group Index
	char	szName[32];		//Group Name
	int		nParent;		//Parent Group,  -1 : no Parent
	char	szRemarks[48];	//2016-2-23，从64位改为48位
	char	cLevel;			//级别,1为普通公司,2为车队 3-线路
	char	cReserve[15];	//备用字段
}GPSDEVGroup_S, *LPGPSDEVGroup_S;

//公司信息
typedef struct _tagCompanyInfo
{
	int  nID;
	char szName[32];
	int  nParent;	
	char cLevel;				//级别,1为普通公司,2为车队, 3-线路
	int  nStationCount[2];		//站点个数, 级别为3时才有效
}CompanyInfo_S, *LPCompanyInfo_S;

//司机信息
typedef struct _tagGPSDriverInfo
{
	int		nID;				// ID, 唯一
	char	szJobNum[32];		//工号, 唯一
	char	szName[32];			//名称
	int		nCompanyID;			//所属公司ID
	int		nSex;				//性别,1男2女
	char	IDNumber[32];		//驾驶证号
	char	szLicenseType[32];	//行驶证类型
	SYSTEMTIME tmValid;			//有效时间
	int nRemindDay;				//到期提醒天数
	char	cReserve[32];		//备用字段
}GPSDriverInfo_S, *LPGPSDriverInfo_S;

typedef struct _tagGPSDriverInfoEx_S 
{
	unsigned short usSize;		//本结构体大小
	unsigned short usDataLen;	//跟随的数据长度
	int nID;					//数据库ID
	int nDelete;				//删除标记,当此标志有效时,表示本ID被删除
	GPSTime_S ValidTime;		//有效时间
	int nCompanyID;				//所属公司ID
	int nSex;					//性别,1=男 2=女
	int nRemindDay;				//到期提醒天数
	unsigned char ucJobNumLen;	//工号, 唯一
	unsigned char ucNameLen;	//名称
	unsigned char ucContactLen;	//联系方式
	unsigned char ucDriverLicenseLen;//驾驶证
	unsigned char ucIDNumberLen;//身份证
	unsigned char ucLicenseTypeLen;	//驾照类型
	unsigned char ucRemarkLen;	//备注
	unsigned char ucResvered[5];//预留(5个字节)
}GPSDriverInfoEx_S, *LPGPSDriverInfoEx_S;

//车辆设备关联
typedef struct _tagGPSVehiDevRelation
{
	int		nID;					//ID （设备ID）
	char	szVehiIDNO[32];			//车牌号
	char	szDevIDNO[32];			//设备号
	char	szSIMCard[16];			//电话
	char	szChnAttr[40];			//通道属性 用,分隔  如:0,1 表示通道1,通道2
	char	szIOInAttr[40];			//IO输入属性
	char	szIOOutAttr[40];		//IO输出属性
	char	szTempAttr[40];			//温度传感器属性
	int		nMoudle;				//车辆外设属性, 每一位表示一种外设,第一位视频,第二位抓拍,第三位监听,第四位对讲
	int		nDevType;				//设备主类型		MDVR、MOBILE、
	int		nDevSubType;			//设备子类型		普通GPS，通道数目需要配置为0个
	char	cMainDevFlag;			//主设备标识,非0表示主设备
	char	cProtocol;				//协议类型
	char	cAudioCodec;			//音频解码器类型，请求对讲时，使用此参数
	char	cDiskType;				//磁盘类型
	char	cFactoryType;			//厂家定义设备类型	在WKP协议下使用	
	char	cFactoryDevType;		//未用
	unsigned char ucMapValid;		//设置的位置是否有效
	unsigned char ucMapType;		//地图类型
	int nOnline;					//Device Online Status
	int		nJingDu;				//经度	4字节 整数部分	9999999 = 9.999999 
	int		nWeiDu;					//纬度	4字节 整数部分	9999999 = 9.999999
	union
	{
		GPSMDVRInfo_S gDVRInfo;
		GPSMobileDevInfo_S gMobileDevInfo;
		GPSDVSInfo_S DVSInfo;
	};
	char  szRemarks[52];	
	char  cProtocolVersion;			//协议版本
	char  cExtendedProtocol;		//扩展协议,0:无, 1:苏标
	char  cLoginType;
	char  cUseState;	//设备使用状态
	short sChnUseStatus;  //使用状态 0 使用 1 禁用  按位
	short sPTZFunction;  //云台功能  0 启用 1禁用   按位来
}GPSVehiDevRelation_S, *LPGPSVehiDevRelation_S;

typedef struct _tagGPSAddrInfoEx
{
	char szLanIP[64];
	char szDeviceIP1[32];		//afu  2013-06-16	增加多个地址配置
	char szDeviceIP2[32];
	char szClientIP1[32];
	char szClientIP2[32];
	unsigned short usDevicePort;
	unsigned short usClientPort;
//	unsigned short usReserve[2];
	unsigned short usSvrVersion;	//服务器版本 说明:v6和之前的版本为0,v7为7,参考LOGIN_SERVER_VERSION_V7定义 hw2014-12-04 
	unsigned short usReserve;
}GPSAddrInfoEx_S;

typedef struct _tagGPSAddrInfo
{
	char szLanIP[64];			//此字段可能包含多个ip地址,以'\0'分隔,第二个ip表示ClientIP3
	char szDeviceIP1[32];		//afu  2013-06-16	增加多个地址配置
	char szDeviceIP2[32];
	char szClientIP1[32];
	char szClientIP2[32];
	unsigned short usDevicePort;
	unsigned short usClientPort;
	//	unsigned short usReserve[2];
	unsigned short usSvrVersion;	//服务器版本 说明:v6和之前的版本为0,v7为7,参考LOGIN_SERVER_VERSION_V7定义 hw2014-12-04 
	unsigned short usReserve;
}GPSAddrInfo_S;

typedef struct _tagGPSServerInfo
{
	int nID;
	char szIDNO[32];
	char szName[32];
	long nGroup;
	GPSAddrInfo_S	Addr;
}GPSServerInfo_S, *LPGPSServerInfo_S;

typedef struct _tagGPSServerInfoEx
{
	GPSServerInfo_S svrInfo;
	char szClientOtherPort[128];	//其它端口
	int	nOfflineTimeout;			//离线超时时长
	char szReserve[28];				//保留字段
}GPSServerInfoEx_S, *LPGPSServerInfoEx_S;

typedef struct _tagGPSServerAddr
{
	int nSvrID;
	GPSAddrInfo_S Addr;
}GPSServerAddr_S, *LPGPSServerAddr_S;

typedef struct _tagGPSMEDIAFile
{
	char	szFile[225]; 	/*带路径的文件名*/  // 2015-03-14  256变为252，增加uiAlarmType;1个文件可能有多个类型的报警
							// 2015-04-08  252变为244，增加nChnMask通道掩码
							// 2015-4-30	244变为240， 增加文件偏移量
							// 2015-8-17	240变为239， 增加录像标识
							// 2016-3-16	239变为238， 增加流标识
							// 2017-3-06	238变为232， 增加1078协议上需求的资源类型,码流类型,存储类型,报警标志
							// 2017-4-25	232变为228， 增加报警标志2,以前报警信息不动
							// 2019-3-22	228变为225， 增加是否支持多路远程回放和远程回放通道的标志
	char 	bMulPlay;			//是否支持多路同时回放
	unsigned short usMulChn;	//可以多路回放的通道，按位表示
	int nAlarmFlag1;
	int nAlarmFlag2;		
	char cResourceType;		//0：音视频， 1：音频， 2：视频
	char cStreamType;		//0：主码流， 1：子码流
	char	bStream;		//是否为流式文件，当为流式文件时，客户端会使用回放的方式进行文件下载
	char	bRecording;		//是否正在录像的文件，0表示没有，1表示正在录像
	unsigned int nFileOffset;	//文件偏移量
	unsigned char ucYear;	// 14表示  14年
	unsigned char ucMonth;
	unsigned char ucDay;	
	unsigned char cStoreType;		//1：主存储器， 2：灾备存储器
	int nChnMask;			//通道掩码
	int nAlarmInfo;			//当文件为报警时有效
	unsigned int uiBegintime;
	unsigned int uiEndtime;
	char	szDevID[GPS_DEV_ID_LEN];			//设备ID
	int		nChn;
	unsigned int nFileLen;
	int		nFileType;
	int		nLocation;		//位置，设备上的录像文件，还是存储服务上的录像文件
	int		nSvrID;			//存储服务器ID，在为存储服务器上的文件时有效
}GPSMEDIAFile_S, *LPGPSMEDIAFile_S;

typedef struct _tagGPSMEDIAFileEx
{
	int nID;
	GPSMEDIAFile_S FileInfo;
	char szLabel[256];
}GPSMEDIAFileEx_S, *LPGPSMEDIAFileEx_S;;


typedef struct _tagGPSDEVUpgradeFile
{
	char szVersion[32];
	int	nDevType;
	int nFileLength;
}GPSDEVUpgradeFile_S, *LPGPSDEVUpgradeFile_S;

typedef struct _tagGPSFile2SvrMD5
{
	char szFileName[128];
	int	nFileLength;
	char szMd5[64];
	int nFileType;
	char cReserve[32];
}GPSFile2SvrMD5_S, *LPGPSFile2SvrMD5_S;

//离线文件类型定义
#define GPS_OLF_TYPE_PICTURE	    1	//图片文件
#define GPS_OLF_TYPE_UPGRADE	    2	//升级文件
#define GPS_OLF_TYPE_DEV_CONF	    3	//设备参数配置
#define GPS_OLF_TYPE_WIFI_LOCATION	4	//wifi围栏开关

#define GPS_DEV_FILE_TASK_STATUS_CREATE		0	//未执行
#define GPS_DEV_FILE_TASK_STATUS_ING		1	//任务中
#define GPS_DEV_FILE_TASK_STATUS_SUCCESS	2	//成功
#define GPS_DEV_FILE_TASK_STATUS_FAIL		3	//失败

typedef struct _tagGPSFile2SvrMD5Ex
{
	char szFileName[64];	//文件名称
	int	nFileLength;		//文件长度
	char szMd5[40];			//文件MD5值
	int nFileType;			//文件类型 1 - 升级文件 
	char nProtocol;			//协议类型 0表示所有
	char nFactoryType;		//厂家类型 0表示所有
	char nDevType;			//设备类型 0表示所有
	char nDevSubType;		//设备子类型 0表示所有
	char szParam[116];		//文件参数信息,多个参数用|分隔(升级文件参数:版本号,版本名称)
}GPSFile2SvrMD5Ex_S, *LPGPSFile2SvrMD5Ex_S;

//屏蔽报警类型
typedef struct _tagGPSAlarmShield
{
	int		nAlarmType;			//报警类型		
}GPSAlarmShield_S, *LPGPSAlarmShield_S;

//地图标记的属性
typedef struct _tagGPSMarkerInfo
{
	int nID;				//数据库ID索引
	int nMarkerID;			//GPSMapMarker_S结构体的nID
	unsigned char nType;	//设备类型
	unsigned char nDevNum;	//数目(如nType为灭火器时候，nNum为灭火器的数目)
	unsigned char nMapType;	//地图类型，参照 mapapi.h 内的定义
	char	szReserve[25];	//保留
}GPSMarkerInfo_S, *LPGPSMarkerInfo_S;

//地图标记
typedef struct _tagGPSMapMarker
{
	int		nID;
	int		nMarkerType;		//标记类型，形状类型(点线面)
	int		nType;				//工厂，码头，物流园等
	int		nCreator;			//创建此标记的用户
	BOOL	bShare;				//是否允许共享，共享则公司所有用户都可以看到此标记信息
	char	szName[32];			//标记名称
	char	szJingDu[256];		//经度字符串,可包含多个经度由形状类型决定
	char	szWeiDu[256];		//纬度字符串,和经度字符串一一对应
	char	szColor[10];		//颜色
	char	szRemark[64];		//备注
	unsigned short	nExtinguisherNum;	//灭火器数量
	unsigned short 	nMapType;		//地图类型	MAP_YPE_GOOGLE(地图类型， 跟gps地图类型不同)
	unsigned char nUpdate;			//0新增1更新已存在的记录
	char	cImageSuffix[4];		//图片后缀名（最多4个字节）
	unsigned short nHighRadius;		//半径高位,兼容老版本
	char	szReserver[21];			//2016-07-19 从23备用到21
}GPSMapMarker_S, *LPGPSMapMarker_S;

typedef struct _tagGPSMapLine
{
	GPSMapMarker_S	Marker;		//其它参数与mapMarker保持一致
	char	szJingDu[110000];	//最多允许9999个轨迹点（每个轨迹点最多11个字符  113.134234）
	char	szWeiDu[110000];	//最多允许9999个轨迹点
}GPSMapLine_S, *LPGPSMapLine_S;

//扩展区域类型,客户端使用,保证线路和区域为同一类型
typedef struct _tagGPSMapMarkerEx
{
	GPSMapMarker_S	Marker;		//区域
	char*			pJingDu;	//经度
	char*			pWeiDu;		//纬度
}GPSMapMarkerEx_S, *LPGPSMapMarkerEx_S;
#define GetMarkerExJingDu(pMarker) ((pMarker)->pJingDu ? (pMarker)->pJingDu : (pMarker)->Marker.szJingDu)
#define GetMarkerExWeiDu(pMarker) ((pMarker)->pJingDu ? (pMarker)->pWeiDu : (pMarker)->Marker.szWeiDu)

//区域围栏
typedef struct _tagGPSMapFence
{
	int		nID;					//围栏编号
	char	szDevIDNO[40];			//车辆编号
	int		nMarkerID;				//地图标记编号
	int		nAccessAlarm;			//访问区域报警（0不报警，1区域内报警，2区域外报警）
	int		nSpeedAlarm;			//速度报警（0不报警，1区域内报警，2区域外报警）
	int		nSpeedHigh;				//最高速度（单位公里  100 = 10.0公里）
	int		nSpeedLow;				//最低速度
	int		nParkAlarm;				//停车报警（0不报警，1区域内报警，2区域外报警）
	int		nParkTime;				//停车报警延时、最低60秒）单位秒
	int		nDoorAlarm;				//开门报警
	int		nBeginTime;				//开始时间、布防开始时间
	int		nEndTime;				//结束时间、布防结束时间
	int		nSpeedHighWarn;			//高速预警速度
	int		nSpeedLowWarn;			//低速预警速度
	char	szSpeedHighTts[128];	//高速TTS
	char	szSpeedHighWarnTts[128];//高速预警TTS
	char	szSpeedLowTts[128];		//低速TTS
	char	szSpeedLowWarnTts[128];	//低速预警TTS
}GPSMapFence_S, *LPGPSMapFence_S;

//围栏
typedef struct _tagGPSMapFenceInfo
{
	GPSMapFence_S mapFence;
	GPSMapMarker_S mapMarker;
}GPSMapFenceInfo_S, *LPGPSMapFenceInfo_S;

//线路
typedef struct _tagGPSMapLineInfo
{
	GPSMapFence_S mapFence;
	GPSMapLine_S mapLine;
}GPSMapLineInfo_S, *LPGPSMapLineInfo_S;

//客户端升级用到的信息
typedef struct _tagGPSUPFileInfo
{
	char	szModuleName[32];
	char	szVersion[128];
	char 	szPath[128];
	char	szSHA1[128];
	int		nFileLength;
	char	szReserve[32];	//保留
}GPSUPFileInfo_S, *LPGPSUPFileInfo_S;
typedef struct _tagGPSUPFileInfoW
{
	wchar_t	szModuleName[32];
	wchar_t	szVersion[128];
	wchar_t szPath[128];
	wchar_t	szSHA1[128];
	int		nFileLength;
	wchar_t	szReserve[32];	//保留
}GPSUPFileInfoW_S, *LPGPSUPFileInfoW_S;
#ifdef _UNICODE
#define GPSUPFileInfoT_S	GPSUPFileInfoW_S
#else
#define GPSUPFileInfoT_S	GPSUPFileInfo_S
#endif // _UNICODE

typedef struct _tagGPSUPVersion
{
	char	szVersion[32];
	char	szDate[32];
	char	szSHA1[128];
	char	szKeyModule[32];
	char	szReserve[32];	//保留
}GPSUPVersion_S, *LPGPSUPVersion_S;
typedef struct _tagGPSUPVersionW
{
	wchar_t	szVersion[32];
	wchar_t	szDate[32];
	wchar_t	szSHA1[128];
	wchar_t	szKeyModule[32];
	wchar_t	szReserve[32];	//保留
}GPSUPVersionW_S, *LPGPSUPVersionW_S;
#ifdef _UNICODE
#define GPSUPVersionT_S	GPSUPVersionW_S
#else
#define GPSUPVersionT_S	GPSUPVersion_S
#endif // _UNICODE

//客户端登录时、从服务器中获取客户端APP信息
typedef struct _tagGPSAppInfo
{
	int		nAppVersion;				//客户端版本	6.1.1.1	=  6 * 1000000 + 1 * 10000 + 1 * 100 + 1	每个版本最多两个数字
	int		nWebPort;					//WEB服务器端口
	char	szHost[128];				//地址，如  192.168.1.100，如果此参数为空则直接使用用户服务器的ip
	char	szWebApp[32];				//网关设备地址1
	char	szVerUrl[128];				//版本描述链接		/product/gViewer/upgrade.html
										//说明访问地址为  http://szHost:nWebPort/szWebApp/szVerUrl	或者 http://用户服务器址:nWebPort/szVerUrl
	char	cVersionChange;				//0:6.15.x.x之前的版本,1:6.15.x.x版本,依次增加,以后新老服务器不兼容,通过配置此参数来区别服务器的版本hw2013/11/21
	char	cVersionChangeEx;			//hw2014/8/13 cVersionChange版本客户端判断有问题,所以增加一个版本,以后cVersionChange不再改变,用此字段
	short	sUsrVersion;				//用户服务器版本
	int		nAppVersionEx;				//新的版本号
	UINT	nAppMainVer;				//企业版本（新增，主要是界面不同，通过打包脚本添加上去, 通用版本用0）
	UINT	nAppFunVer;					//功能定制版本（客户端内部使用版本标志，通过此版本区分不同的功能, 通用版本用0）
	UINT	nAppFunSunVer;				//功能定制子版本, 通用版本用0
	char	bHttps;						//服务器是否为HTTPS
	char	szReserve[7];				//保留参数	30->8  hw 2015/3/27 
}GPSAppInfo_S;

//用户地图配置信息
typedef struct _tagUserMapConfig
{
	int nMapType;		//地图类型
	int	nJingDu;		//经度	4字节 整数部分	9999999 = 9.999999 
	int nWeiDu;			//纬度	4字节 整数部分	9999999 = 9.999999
	int nZoom;			//缩放级别
	char szReserve[128];
}UserMapConfig_S, *LPUserMapConfig_S;

//服务器配置信息
typedef struct _tagSvrConfig
{
	unsigned long lSvrConfig;
}SvrConfig_S, *LPSvrConfig_S;

//用户信息
typedef struct _tagClientUserInfo
{
	char szCompanyLogoFile[MAX_PATH];		//公司logo文件路径
	SYSTEMTIME timeCompanyLogoUpdate;		//公司logo更新时间
	char szUserLogoFile[MAX_PATH];			//用户logo文件路径
	SYSTEMTIME timeUserLogoUpdate;			//用户logo更新时间
}ClientUserInfo_S, *LPClientUserInfo_S;

//客户端功能
typedef struct _tagClientFunction
{
	unsigned char nMDVRValid;				//MDVR
	unsigned char nDVSValid;				//DVS
	unsigned char nMoblieValid;				//Moblie
	unsigned char nWifiSvrValid;			//自动下载服务器
	unsigned char nTarckBackValid;			//轨迹回放
	unsigned char nMapValid;				//地图	
	unsigned char nPTZValid;				//云台
	unsigned char nColorValid;				//色彩
	unsigned char nTalkbackValid;			//对讲
	unsigned char nAudioMonitorValid;		//监听
	unsigned char nBroadcastValid;			//广播
	unsigned char nReportValid;				//报表查询
	unsigned char nBusMgr;					//校车管理
	unsigned char nDevStatus;				//设备状态
	char szReserve[13];						//保留14 05-07 14->13
	unsigned char cChildUser : 1;			//子用户管理
	unsigned char cCheckPost : 1;			//手动查岗功能
	unsigned char cGSensor : 1;				//G-sensor
	unsigned char cReserve : 5;				//预留
}ClientFunction_S, *LPClientFunction_S;
static_assert(sizeof(ClientFunction_S) == 28, "sizeof ClientFunction_S !- 28");

// 用户参数类型定义
#define USER_PARAM_TYPE_AUTO_CLOSE_VIDEO        1   //关闭视频 p0:时长(秒),为0不自动关闭 p1:超时后处理方式,0自动关闭,1提示关闭 p2:提示关闭时提示时长(秒) 
#define USER_PARAM_TYPE_CLOSE_VIDEO_NO_OPER     2   //无操作关闭视频(无操作) 参数同上                                                                    
#define USER_PARAM_TYPE_AUTO_CLOSE_TALK_MONITOR 3   //关闭对讲和监听(自动) 参数同上                                                                      
#define USER_PARAM_TYPE_AUTO_CLOSE_CLIENT       4   //关闭客户端(自动) 参数同上                                                                          
#define USER_PARAM_TYPE_CLOSE_CLIENT_NO_OPER    5   //关闭客户端(无操作) 参数同上                                                                        
#define USER_PARAM_TYPE_CLOSE_TCP_LINK          6   //关闭TCP链接 参数同上  
typedef struct _tagGPSUserParam_S  
{  
	short nSize;        //结构体大小  
	int nUserID;        //用户ID  
	int nType;          //类型  
	int nParam[4];      //参数(整型)  
	char szParam[256];  //参数(字符串)
}GPSUserParam_S;

typedef struct _tagDevFixGPS
{
	char szDevIDNO[32];
	unsigned char ucMapValid;			//设置的位置是否有效
	unsigned char ucMapType;			//地图类型
	int	nJingDu;						//经度	4字节 整数部分	9999999 = 9.999999 
	int nWeiDu;							//纬度	4字节 整数部分	9999999 = 9.999999
}DevFixGPS_S, *LPDevFixGPS_S;

//电阻值对应油量
typedef struct _tagOilResistance
{
	char szDevIDNO[32];
	int nTimeCount;				//单位时间(秒)
	int nChangeOil;				//油量变化值(L)
	char szResistance[512];		//电阻值
	char szOil[512];			//油量	
}OilResistance_S, *LPOilResistance_S;


#define GPS_SNAPSHOT_PLAN_TIME_COUNT		2		//抓拍时间段数目
#define GPS_SNAPSHOT_PLAN_DAY_COUNT			7		//抓拍计划天数

#define GPS_SNAPSHOT_MODE_LOOP				1		//1表示通道循环抓拍(抓完通道1后,间隔时间后再抓拍通道2)
#define GPS_SNAPSHOT_MODE_ALL				2		//2表示独立进行抓拍，同时抓拍所有通道
//时间
typedef struct _tagGPSSnapshotDay						//抓拍每日计划
{	
	int	nBegin[GPS_SNAPSHOT_PLAN_TIME_COUNT];		//以秒为单位(时*3600+分*60+秒)
	int nEnd[GPS_SNAPSHOT_PLAN_TIME_COUNT];			//同上
}GPSSnapshotDay_S, *LPGPSSnapshotDay_S;
//抓拍计划
typedef struct _tagGPSSnapshotPlan						//抓拍计划
{	
	GPSSnapshotDay_S	Day[GPS_SNAPSHOT_PLAN_DAY_COUNT]; //0-周日,1-周一,...
	int nSpan;										//抓拍间隔 单位秒
	int	nSnapshotMode;								//1表示通道循环抓拍(抓完通道1后,间隔时间后再抓拍通道2)，2表示独立进行抓拍
	int nChannel;									//抓拍的通道号，0位-表示通道0，1位-表示通道1，依次类推
}GPSSnapshotPlan_S, *LPGPSSnapshotPlan_S;

//设备抓拍计划
typedef struct _tagGPSDevSnapshotPlan
{
	char szDevIDNO[32];								//设备IDNO
	GPSSnapshotPlan_S Plan;							//计划
}GPSDevSnapshotPlan_S, *LPGPSDevSnapshotPlan_S;

//报警处理
const int HANLEWAY_TYPE_PROCESSING = -1;	//处理中
const int HANLEWAY_TYPE_OVERTIME = 0;		//超时未处理
const int HANLEWAY_TYPE_MMS = 1;			//发送彩信
const int HANLEWAY_TYPE_IGNORE = 2;			//不处理
const int HADLEWAY_TYPE_ABNORMAL = 3;		//已处理,异常报警 hw2016-11-8
typedef struct _tagDevHandleAlarm
{
	char guid[40];			//报警guid
	char szAccount[40];		//登陆账户
	char szHandleInfo[256];	//处理方法
	int nHandleWay;
	char szDevIDNO[32];

	//afu  增加源报警的报警类型等相关信息 原来szParam[92]改为szParam[80]		//20170307
	GPSTime_S Time;				//报警时间
	GPSTime_S srcTime;			//源报警时间
	short AlarmType;			//报警类型
	short AlarmStartType;

	short AlarmInfo;			//处理信息
	char szParam[78];		//保留80
}DevHandleAlarm_S, *LPDevHandleAlarm_S;

//报警查询
const int QUERY_ALARMINO_ALL = - 1;
typedef struct _tagAlarmQueryParam
{
	int nArmType;		//报警类型
	int nArmInfo;		//报警信息(为-1则忽略该参数)
}AlarmQueryParam_S, *LPAlarmQueryParam_S;


typedef struct _tagAlarmQueryParamMore
{
	int nArmType;		//报警类型(为-1则忽略该参数)
	int nArmInfo;		//报警信息(为-1则忽略该参数)
	int nHandleStaus;	//处理状态(为-1则忽略该参数 0-未处理, 1处理);
	int nParam[4];		//报警参数(为-1则忽略该参数)
}AlarmQueryParamMore_S, *LPAlarmQueryParamMore_S;

//离线文件信息
typedef struct _tagGPSOflFileInfo
{
	int nID;
	GPSFile2SvrMD5Ex_S FileInfo;
	int nSvrID;					//存储服务器的ID
	SYSTEMTIME dtUploaded;		//文件上传时间
}GPSOflFileInfo_S, *LPGPSOflFileInfo_S;

//设备离线任务
typedef struct _tagGPSDevOflTask
{
	int nID;				//数据库索引
	char szDevIDNO[40];		//设备ID
	int nFileType;			//文件类型，1表示升级文件
	int nFileID;			//文件ID
	SYSTEMTIME dtCreate;	//任务创建时间
	char szReserve[32];		//保留参数
}GPSDevOflTask_S, *LPGPSDevOflTask_S;

//录像类型
#define AUTODOWN_DOWN_TYPE_ALL				1		//1下载所有，2下载录像，3下载图片
#define AUTODOWN_DOWN_TYPE_RECORD			2		
#define AUTODOWN_DOWN_TYPE_JPEG				3		
#define AUTODOWN_DOWN_TYPE_RECORD_ALARM		4		
#define AUTODOWN_DOWN_TYPE_JPEG_ALARM		5
//设备下载计划
#define TASK_STATUS_ALL			-1
#define TASK_STATUS_NO_FINISH	0
#define TASK_STATUS_SUCCESS		1
#define TASK_STATUS_FAIL		2
typedef struct _tagGPSDevDloadTask
{
	int nID;				//数据库索引
	char szIDNO[64];		//设备编号或者车牌号
	int  nChannle;			//通道号(单个通道号或者全部通道号)
	int  nType;				//类型(1-所有 2-录像 3-图片 4-报警录像 5-报警图片);
	SYSTEMTIME BegTime;		//开始时间
	SYSTEMTIME EndTime;		//开始时间
	int	nStatus;			//状态
	char szLable[256];		//标签
	char szRemark[256];		//备注
	int  nAlarmInfo;		//4-报警录像 5-报警图片时，下载的文件类型	
							//REC_IOALARM = 0,	// IO 报警	REC_SPEED_H = 1,	// 超速报警	REC_SPEED_L = 2,	// 低速报警		REC_GSENSOR = 3,	// GSensor 
							//REC_TEMP = 4,      // 温度报警		REC_MD = 5,	   // 移动侦测		REC_UPSACT = 6,	 // UPS 报警
	char szReserve[60];		//保留参数
}GPSDevDloadTask_S, *LPGPSDevDloadTask_S;



//809查岗确认信息
typedef struct _tagAck809Platform
{
	char szDevIDNO[36];			//服务器IDNO
	int	 nSvrID;				//服务器ID
	unsigned int uiInfoID;		//信息ID	当为报警督办ID，表示报警督办ID
	char szinfoContent[432];	//信息类容
	char szResponderName[20];	//应答人姓名
	char szResponderTel[24];	//应答人联系电话
	char guid[36];				//guid, 唯一标志
	unsigned int uiType;		//1表示查岗，2表示报警督办应答，报警督办时，szSvrIDNO表示设备编号
	unsigned int uiResult;		//报警处理结果，0处理中，1处理完必，2不处理，3将来处理
	BYTE  nObjType;				// 查岗对象类型;
	char szObjectID[15];		//营运证号
	int  nAccountID;			//用户ID
	unsigned int uiCenterID;	//中心接入码
	GPSTime_S GPSTime;			//报警时间
	unsigned int uiSrcSN;		//原始序号
	//char szReserve[4];
}Ack809Platform_S, *LPAck809Platform_S;

//809相关业务
typedef struct _tagGPSJT809Business
{
	int	nType;				//类型
	char szDevIDNO[GPS_DEV_ID_LEN];	//设备编号
	SYSTEMTIME begTime;		//开始时间
	SYSTEMTIME endTime;		//结束时间
	char szReserve[512];	//保留数据
}GPSJT809Business_S, *LPGPSJT809Business_S;

//车辆动态信息交换业务
#define JT809_BUSINESS_TYPE_HISTORY_LOCATION			1			//下级平台 ---》  上级平台		自动补报车辆历史位置		设备编号，开始时间和结束时间
#define JT809_BUSINESS_TYPE_MONITOR_START_UP			2			//下级平台 ---》  上级平台		申请交换车辆定位信息		主动监视上级平台车辆信息时使用		设备编号，开始时间和结束时间
#define JT809_BUSINESS_TYPE_MONITOR_END				3				//下级平台 ---》  上级平台		取消申请交换车辆定位信息	车牌号
#define JT809_BUSINESS_TYPE_HISGNSSDATA				4				//下级平台 ---》  上级平台		补发车辆定位信息请求		设备编号，开始时间和结束时间	

//暂缓
#define JT809_BUSINESS_TYPE_ADPT_TODO_INF			5				//下级平台 ---》  上级平台		主动上报报警处理消息		设备编号，报警ID、处理结果	(0x00：处理中；0x01：已处理完毕；0x02：不作处理；0x03：将来处理。)

#define JT809_BUSINESS_TYPE_MAIN_LINK_CONNECT		6				//登录主链路，会与上级平台建立通信链路，并发送登录包
#define JT809_BUSINESS_TYPE_MAIN_LINK_DISCONN		7				//注销主链路，会与上级平台发送注销包，并断开连接
#define JT809_BUSINESS_TYPE_LINK_STATUS				8				//查看与上级监管平台的连接状态
#define JT809_BUSINESS_TYPE_UP_SINGLE_REGISTER		9				//上传单个车辆注册信息
#define JT809_BUSINESS_TYPE_UP_ALL_REGISTER			10				//上传所有车辆注册信息


//车辆驾驶状态
typedef struct _tagGPSVehiDriveStatus
{
	char szVehiIDNO[32];		//车牌号
	char szDirverName[64];		//姓名
	char szCardNO[32];			//身份证
	char szLicense[64];			//从业资格证编码
	char szOrgName[256];		//发证机构名称
	char szWaybill[512];		//运单信息
	char szReserve[128];		//保留参数
}GPSVehiDriveStatus_S, *LPGPSVehiDriveStatus;


const int REAMIND_TYPE_TIMESTAMP = 0;				//对应结构体SYSTEMTIME
const int REAMIND_TYPE_VEHI_INSURANCE = 1;			//对应结构体GPSVehiInsuranceInfo_S
const int REAMIND_TYPE_VEHI_TRANSPORTATION = 2;		//对应结构体GPSVehiTransportationInfo_S
const int REAMIND_TYPE_VEHI_LICENSE = 3;			//对应结构体GPSVehiLicenseInfo_S
const int REAMIND_TYPE_DIRVER = 4;					//对应结构体GPSDriverInfo_S


// 扩展类型:仅用于返回数据
const int REAMIND_TYPE_VEHI_INSURANCE_EX = 101;		//格式=SYSTEMTIME + N * GPSVehiInsuranceInfoEx_S
const int REAMIND_TYPE_VEHI_TRANSPORTATION_EX = 102;//格式=SYSTEMTIME + N * GPSVehiTransportationInfoEx_S
const int REAMIND_TYPE_VEHI_LICENSE_EX = 103;		//格式=SYSTEMTIME + N * GPSVehiLicenseInfoEx_S
const int REAMIND_TYPE_DIRVER_EX = 104;				//格式=SYSTEMTIME + N * GPSDriverInfoEx_S


//车辆保险
typedef struct _tagGPSVehiInsuranceInfo
{
	int nVehiID;				//车辆ID
	char szCompany[64];			//保险公司
	char szTyp[64];				//保险类型
	char szNumber[64];			//单号
	int	 nAmount;				//保险金额单位0.01元
	char szClaimStatus[64];		//理赔状态
	SYSTEMTIME tmStart;			//开始时间
	SYSTEMTIME tmEnd;			//结束时间
	int nRemindDay;				//到期提醒天数
}GPSVehiInsuranceInfo_S, *LPGPSVehiInsuranceInfo_S;

typedef struct _tagGPSVehiInsuranceInfoEx_S
{
	unsigned short usSize;		//本结构体大小
	unsigned short usDataLen;	//跟随的数据长度
	int nID;					//数据库ID
	int nDelete;				//删除标记,当此标志有效时,表示本ID被删除
	int nVehiID;				//车辆ID
	GPSTime_S BegTime;			//开始时间
	GPSTime_S EndTime;			//结束时间
	int nRemindDay;				//到期提醒天数
	int nPrice;					//价格
	int nDiscount;				//折扣   实际金额=价格*折扣/100
	unsigned char ucCompanyLen;	//保险公司(长度)
	unsigned char ucAgentLen;	//代理人(长度)
	unsigned char ucTelephoneLen; //联系电话(长度)
	unsigned char ucTypeLen;	//保险类型(长度)
	unsigned char ucIDNOLen;	//保险单号(长度)
	unsigned char ucConditionLen;//理赔情况(长度)
	unsigned char ucRemarkLen;	//备注(长度)
	unsigned char ucResvered[5];//预留(5个字节)
}GPSVehiInsuranceInfoEx_S, *LPGPSVehiInsuranceInfoEx_S;

//车辆运输证
typedef struct _tagGPSVehiTransportationInfo
{
	int nVehiID;				//车辆ID
	char szBusinessLicense[64];	//经营许可证号
	char szBusinessScope[64];	//经营范围
	SYSTEMTIME tmStart;			//开始时间
	SYSTEMTIME tmEnd;			//结束时间
	int nRemindDay;				//到期提醒天数
}GPSVehiTransportationInfo_S, *LPGPSVehiTransportationInfo_S;

typedef struct _tagGPSVehiTransportationInfoEx_S
{
	unsigned short usSize;		//本结构体大小
	unsigned short usDataLen;	//跟随的数据长度
	int nID;					//数据库ID
	int nDelete;				//删除标记,当此标志有效时,表示本ID被删除
	int nVehiID;				//车辆ID
	GPSTime_S BegTime;			//开始时间
	GPSTime_S EndTime;			//结束时间
	int nRemindDay;				//到期提醒天数
	unsigned char ucLicenseLen;	//经营许可证号(长度)
	unsigned char ucScopeLen;	//经营范围(长度)
	unsigned char ucRemarkLen;	//备注(长度)
	unsigned char ucResvered[5];//预留(5个字节)
}GPSVehiTransportationInfoEx_S, *LPGPSVehiTransportationInfoEx_S;

//车辆行驶证
typedef struct _tagGPSVehiLicenseInfo
{
	int nVehiID;				//车辆ID
	char szIDCode[64];			//识别代码
	char szEngineCode[64];		//发动机代码
	char szLicense[64];			//行驶证
	char szUseNature[64];		//使用性质
	char szBrandModel[64];		//品牌型号
	SYSTEMTIME tmStart;			//开始时间
	SYSTEMTIME tmEnd;			//结束时间
	int nRemindDay;				//到期提醒天数
}GPSVehiLicenseInfo_S, *LPGPSVehiLicenseInfo_S;

typedef struct _tagGPSVehiLicenseInfoEx_S
{
	unsigned short usSize;		//本结构体大小
	unsigned short usDataLen;	//跟随的数据长度
	int nID;					//数据库ID
	int nDelete;				//删除标记,当此标志有效时,表示本ID被删除
	int nVehiID;				//车辆ID
	GPSTime_S BegTime;			//开始时间
	GPSTime_S EndTime;			//结束时间
	int nRemindDay;				//到期提醒天数
	unsigned char ucEngineCodeLen; //发动机代码
	unsigned char ucLicenseLen;	//行驶证
	unsigned char ucUseNatureLen; //使用性质
	unsigned char ucBrandModelLen; //品牌型号
	unsigned char ucRemarkLen;	//备注
	unsigned char ucResvered[3];//预留(3个字节)
}GPSVehiLicenseInfoEx_S, *LPGPSVehiLicenseInfoEx_S;


//车辆抽查类型
const int VEHI_CHECK_TYPE_LOCATION = 1;
const int VEHI_CHECK_TYPE_TRACK = 2;
const int VEHI_CHECK_TYPE_REALPALY = 3;
const int VEHI_CHECK_TYPE_DEALALARM = 4;
const int VEHI_CHECK_TYPE_OTHER = 5;

typedef struct _tagGPSVehiFtpTaskData
{
	int nID;						//数据库ID
	int nVehiID;					//车辆ID
	char szDevIDNO[32];				//设备编号
	unsigned short usSequence;		//流水号 
	unsigned short usReserve;		//备用字段
	char szFilePath[MAX_PATH];		//上传路径
	int nChnMask;					//逻辑通道号
	SYSTEMTIME BegTime;				//开始时间
	SYSTEMTIME EndTime;				//结束时间
	int nAlarmFlag1;				//报警标志位1
	int nAlarmFlag2;				//报警标志位2
	char cResourceType;				//0：音视频， 1：音频， 2：视频, 3.音视频或者音频
	char cStreamType;				//-1:主码流或者子码流,0：主码流,1：子码流
	char cStoreType;				//0:主存储器或者灾备存储器, 1：主存储器， 2：灾备存储器
	char cNetworkMask;				//任务执行网络 bit0:WFIF,bit1:LAN,bit2:3G/4
	int nUserID;					//用户ID
	int nDownStatus;				//下载状态  0:暂停状态 1:正在下载 2:取消 3:失败 4:成功 ,
	SYSTEMTIME TaskTime;			//任务开始时间
	char szReserve[32];
}GPSVehiFtpTaskData_S, *LPGPSVehiFtpTaskData_S;

//FTP数据数目
typedef struct _tagGPSFtpTaskDataCount
{
	int nCount;
	char szReserve[8];
}GPSFtpTaskDataCount_S, *LPGPSFtpTaskDataCount_S;


//录像查找参数
typedef struct _tagGPSRecFileSearchParam
{
	int nChannel;				//通道
	int nYearS;					//年
	int nMonthS;				//月
	int nDayS;					//日
	int nBegTime;				//开始时间
	int nYearE;					//年
	int nMonthE;				//月
	int nDayE;					//日	
	int nEndTime;				//结束时间
	short nRecType;				//录像类型
	short nFileAttr;			//文件属性，图片文件或者为录像文件	GPS_FILE_ATTRIBUTE_RECORD(WKP协议)
	int nLoc;					//文件位置
	int nAlarmType;				//报警类型(WKP协议, 报警联动存储的)
	int nAlarmFlag1;			//报警标志1		//1078
	int nAlarmFlag2;			//报警标志2		//1078
	char cResourceType;			//0：音视频， 1：音频， 2：视频 3;视频或者音视频
	char cStreamType;			//-1:主码流或者子码流,0：主码流,1：子码流
	char cStoreType;			//0:主存储器或者灾备存储器, 1：主存储器， 2：灾备存储器
	char cReserve1;
	char cReserve[32];
}GPSRecFileSearchParam_S, *LPGPSRecFileSearchParam_S;


const int PLAY_BACK_MODE_NORAML = 0;		//正常
const int PLAY_BACK_MODE_FAST = 1;			//快进
const int PLAY_BACK_MODE_REWIND = 2;		//快退
const int PLAY_BACK_MODE_I_FARAM = 3;		//关键帧播放
const int PLAY_BACK_MODE_SIGALE_FRAM = 4;	//单帧播放

//录像回放参数
typedef struct _tagGPSRecPlaybackParam
{
	GPSFile_S File[16];
	int nPlayChannel[16];
	int nFileNum;
	int nBegMinSecond;
	int nEndMinSecond;
	int nMode;					//1078  回放模式 (当为3则为I帧播放)
	int nTimes;					//1078	回放倍数
	char cMultiPlay;			//多路回放(客户端使用)
	char cReserve[31];			//备用字段
								//32->31 [2019-3-27 ydl]

}GPSRecPlaybackParam_S, *LPGPSRecPlaybackParam_S;


// 可变长度,长度变化时应考虑字节对齐
// 车辆的其他信息
typedef struct _tagGPSVehiOtherVariable_S
{
	int nVehiID;					//车辆ID
	int nSpeedLimit;				//限速值
	char szLinesOperation[64];		//运营线路	//到此处72字节
}GPSVehiOtherVariable_S, *LPGPSVehiOtherVariable_S;

// int nInstallFlag;				//是否安装外设,0:ADAS 1:DSM 2:TPMS 3:BSD
// char szBrand[4][128];			//外设名称
// char szModel[4][128];			//外设品牌

// 车辆的工作时长信息
typedef struct _tagGPSVehiWorkTimeVariable_S
{
	int nVehiID;					//车辆ID
	int nMonthWorkTime;				//当月工作时长	//8字节
}GPSVehiWorkTimeVariable_S, *LPGPSVehiWorkTimeVariable_S;

typedef struct _tagGPSVehiOtherVariableNew_S
{
	int nVehiID;					//车辆ID
	int nSpeedLimit;				//限速值
	int nInstallFlag;				//是否安装外设
	int nVehicleType;				//车辆类型
}GPSVehiOtherVariableNew_S, *LPGPSVehiOtherVariableNew_S;

typedef struct _tagGPSLongStrHead_S 
{
	int nSize;						//结构体大小
	int nFlag;						//数据标准,参考GPS_LONG_STR_FLAG	
	int nID;
	int nLen;
}GPSLongStrHead_S ;

//平台信息
typedef struct _tagPlatformInfo
{
	int nID;
	char szIP[32];					//运营IP
	int nPort;						//端口
	unsigned int uiCenterID;		//中心ID
	unsigned int uiUserID;			//平台账号
	char szPassword[32];			//平台密码
	unsigned int uiM1;				//加密参数M1
	unsigned int uiIA1;				//加密参数IA1
	unsigned int uiIC1;				//加密参数IC1
	BOOL bCheckIP;					//登录时检验IP，0为不校验,1为校验
	char szVideoPlateFormCode[32];	//企业视频平台唯一编码
	char szAuthorizeCode1[68];		//归属地区政府平台使用的时效口令
	char szAuthorizeCode2[68];		//跨越地区政府平台使用的时效口令
	int  nStatus;				//运营状态,0为停止运营,1为正常运营
}PlatformInfo_S, *LPPlatformInfo_S;

//公司信息
typedef struct _tagCompanyInfoEx
{
	CompanyInfo_S CInfo;			//公司信息
	char szCode[32];				//公司编码
	int nMarkerID;					//行政区域ID,对应map_marker ID字段
	PlatformInfo_S PInfo;			//平台信息
}CompanyInfoEx_S, *LPCompanyInfoEx_S;


//809连接状态
typedef struct _tagConnectStatus809
{
	char szPluginName[64];			//插件名称		如:libgpstran_jt809V2

	int nServerIndex;				//服务编号

	char szHost[64];				//上级平台的IP地址
	int nPort;						//上级平台的端口
	unsigned int uiCenterID;		//平台接入码

	int nEnableStatus;				//启用状态
	int nMainConnectStatus;			//主链路连接状态 0:断开  1:连接中
	int nSubConnectStatus;			//从链路连接状态 0:断开  1:连接中

	char cReserve[360];				//预留
}ConnectStatus809_S, *LPConnectStatus809_S;
// 512字节
const int ConnectStatus809_LEN = sizeof(ConnectStatus809_S);


#pragma pack()

#endif