#ifndef _GPS_PLATFORM_DEF_H_
#define _GPS_PLATFORM_DEF_H_

/******************************************************************************
  Author        : zjt
  Created       : 2018/06/11
  Last Modified :
  Description   : 政府平台通用信息定义
  History       :

******************************************************************************/

//政府平台
const int GPS_CB_PF_GET_COMPANY_INFO = 1;
const int GPS_CB_PF_GET_VEHICLE_INFO = 2;

typedef struct _tagGPSPFCompanyInfo
{
	int nPlatformID;					//公司ID
	char szIP[32];						//运营IP
	int nPort;							//端口
	unsigned int uiCenterID;			//中心ID
	unsigned int uiUserID;				//平台账号
	char szPassword[32];				//平台密码
	unsigned int uiM1;					//加密参数M1
	unsigned int uiIA1;					//加密参数IA1
	unsigned int uiIC1;					//加密参数IC1
	BOOL bCheckIP;						//登录时检验IP，0为不校验,1为校验
	char szVideoPlateFormCode[32];		//企业视频平台唯一编码
	char szAuthorizeCode1[68];			//归属地区政府平台使用的时效口令
	char szAuthorizeCode2[68];			//跨越地区政府平台使用的时效口令
	int  nStatus;						//运营状态,0为停止运营,1为正常运营
}GPSPFCompanyInfo, *LPGPSPFCompanyInfo;


typedef struct _tagGPSPFVehicleInfo
{
	char szVehiIDNO[32];
	unsigned char ucColor;		
	unsigned char ucResert[3];	
	int nCompanyID;
	char szDevIDNO[32];
}GPSPFVehicleInfo_S, *LPGPSPFVehicleInfo_S;


//主动通知上层
const int GPS_CB_PF_NOTIFY_PLATFORM_CONNECT = 1;
const int GPS_CB_PF_NOTIFY_PLATFORM_DISCONNECT = 2;
const int GPS_CB_PF_NOTIFY_VEHICLE_REGISTER = 3;
const int GPS_CB_PF_NOTIFY_PLATFORM_MSG_ACK = 4;
const int GPS_CB_PF_NOTIFY_AUTHORIZE_INFO = 5;
const int GPS_CB_PF_NOTIFY_WARN_ACK = 6;

typedef struct _tagGPSPFPlaformConnect
{
	unsigned int uiCenterID;
	int nMCompanyID;
	int nRet;
}GPSPFPlatformConnect_S, *LPGPSPFPlatformConnect_S;

typedef struct _tagGPSPFPlatformDisconnect
{
	unsigned int uiCenterID;
	int nMCompanyID;
}GPSPFPlatformDisconnect_S, *LPGPSPFPlatformDisconnect_S;

typedef struct _tagGPSPFVehicleRegister
{
	int nMCompanyID;				//平台ID
	char szVehiIDNO[32];			//车牌号
	unsigned char ucColor;						//颜色
	char szPlatformID[15];			//平台唯一编码。
	char szProductID[16];			//车载终端厂商唯一编码，由行政区划代码和厂家编号组成。
	char szTerminalModelType[32];	//车载终端型号，不足20位时以"\0"终结。
	char szTerminalID[16];			//车载终端编号，大写字母和数字组成。
	char szTerminalSimCode[16];		//车载终端SIM卡电话号码。号码不足12位，则在前补充数字0。
}GPSPFVehicleRegister_S, *LPGPSPFVehicleRegister_S;

typedef struct _tagGPSPFPlatformMsgAck
{
	int nMCompanyID;
	unsigned short usType;				//子业务类型标识
	unsigned short usObjType;			//对象类型
	char szObjID[16];					//对象ID
	unsigned int uiInfoID;				//信息ID
	char szInfo[512];					//信息内容
}GPSPFPlatformMsgAck_S, *LPGPSPFPlatformMsgAck_S;

typedef struct _tagGPSPFAuthorizeInfo
{
	unsigned int uiCenterID;
	char szVideoPlateFormCode[32];	//企业视频平台唯一编码
	char szAuthorizeCode1[68];		//归属地区政府平台使用的时效口令
	char szAuthorizeCode2[68];		//跨越地区政府平台使用的时效口令
}GPSPFAuthorizeInfo_S, *LPGPSPFAuthorizeInfo_S;


typedef struct _tagGPSPFWarnAck
{
	int nMCompanyID;
	int nSCompanyID;
	char szDevIDNO[32];
	unsigned int uiAlarmID;
	unsigned int uiResult;
}GPSPFWarnAck_S, *LPGPSPFWarnAck_S;


//主动请求下发平台消息
//主动请求下发平台消息
const int GPS_SEND_PF_TYPE_PLATFORM_MSG = 1;
const int GPS_SEND_PF_TYPE_DOWN_MSG = 2;

const int GPS_PLATFORM_MSG_TYPE_POST_QUERY = 1;		//查岗
const int GPS_PALTFORM_MSG_TYPE_MSG_INFO = 2;		//报文
typedef struct _tagGPSPFPlatformMsgReq
{
	unsigned int uiCenterID;			//中心接入码
	unsigned short usType;				//子业务类型标识
	unsigned short usObjType;			//对象类型
	char szObjID[16];					//对象ID
	unsigned int uiInfoID;				//信息ID
	char szInfo[512];					//信息内容
	char szIP[32];						//IP
}GPSPFPlatformMsgReq_S, *LPGPSPFPlatformMsgReq;


const int GPS_DOWN_MSG_TYPE_EXG_DRIVER_INFO = 1;			//司机采集
const int GPS_DOWN_MSG_TYPE_EXG_EWAYBILL = 2;				//电子运单
const int GPS_DOWN_MSG_TYPE_EXG_RETURN_STARTUP = 3;			//启动交换定位信息
const int GPS_DOWN_MSG_TYPE_EXG_RETURN_END = 4;				//结束交换定位信息
const int GPS_DOWN_MSG_TYPE_EXG_STATCI_INFO = 5;			//车辆静态信息
const int GPS_DOWN_MSG_TYPE_EXG_REAL_LOCATION = 6;			//实时位置
const int GPS_DOWN_MSG_TYPE_EXG_HISTORY_LOCATION = 7;		//历史位置
const int GPS_DOWN_MSG_TYPE_WARN_URGE_TODO = 8;				//报警督办
const int GPS_DOWN_MSG_TYPE_WARN_INFORM_TIPS = 9;			//报警预警
const int GPS_DOWN_MSG_TYPE_WARN_INFORM = 10;				//实时交换报警
const int GPS_DOWN_MSG_TYPE_DISCONNECT = 11;				//从链路注销请求
const int GPS_DOWN_MSG_TYPE_DISCONNECT_INFO = 12;			//从链路断开通知
const int GPS_DOWN_MSG_TYPE_CLOSELINK_INFO = 13;			//主从链路断开通知

typedef struct _tagGPSPFDownMsgReq
{
	unsigned int uiCenterID;
	unsigned short usType;				
	unsigned short sReserve;			
	char szVehiIDNO[32];
	unsigned char ucColor;	
	char szDevIDNO[32];
	char cData[511];	
}GPSPFDownMsgReq_S, *LPGPSPFDownMsgReq_S;

//车辆静态信息
typedef struct _tagGPSPFDownMsgExgVehiInfo
{
	char szVehiType[16];
	char szTransType[32];
	char szVehiNationality[32];
	char szOwerID[32];
	char szOwerName[32];
	char szOwerTel[32];
}GPSPFDownExgVehiInfo_S, *LPGPSPFDownExgVehiInfo_S;

//督办信息
typedef struct _tagGPSPFDownMsgWarnUrgeTodo
{
	unsigned char ucSource;			//报警来源 0X01;车载终端  0X02:企业监控平台 0X03;政府监管平台 0X04:其他
	SYSTEMTIME WarnTime;			//报警时间
	int nWarnType;					//报警类型
	unsigned int uiSupervisorID;	//报警ID
	SYSTEMTIME SupervisorEndTime;	//督办时间
	unsigned char ucLevle;			//督办级别
	char szSupervisor[32];			//督办人
	char szSupervisorTel[32];		//督办人电话
	char szSupervisorEmail[64];		//督办人邮件
}GPSPFDownMsgWarnUrgeTodo_S, *LPGPSPFDownMsgWarnUrgeTodo_S;

//报警信息
typedef struct _tagGPSPFDownMsgWarnInform
{
	unsigned char ucSource;		//报警来源 0X01;车载终端  0X02:企业监控平台 0X03;政府监管平台 0X04:其他
	int nWarnType;				//报警类型
	SYSTEMTIME WarnTime;		//报警时间
	char szWarnContent[256];	//报警内容
}GPSPFDownMsgWarnInform_S, *LPGPSPFDownMsgWarnInform_S;




#endif

