#ifndef _NET_CLIENT_API_H_
#define _NET_CLIENT_API_H_ 

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LIBNETCLIENT_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// NETCLIENT_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef LIBNETCLIENT_EXPORTS
#define NETCLIENT_API __declspec(dllexport)
#else
#define NETCLIENT_API __declspec(dllimport)
#endif

#define  API_CALL	WINAPI

#include "GPSDeviceDef.h"
#include "GPSDataDef.h"
#include "GPSErrorDef.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(4)


typedef struct _tagGPSMCMsg
{
	int nMsgType;
	int nResult;
	void* pParam[6];
	void* pMngCmdClass;
}GPSMCMsg_S, *LPGPSMCMsg_S;

typedef void (__stdcall * FUNDownDataCB)(int nType, void* pData, void * pUsr);
typedef void (CALLBACK * FUNDownConfigCB)(int nType, const char* pDataBuf, int nDataLen, void * pUsr);
typedef void (CALLBACK *FUNCMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr);

#pragma pack()

NETCLIENT_API int	API_CALL	NETCLIENT_Initialize(int bPriorRGB16 = FALSE);
NETCLIENT_API void	API_CALL	NETCLIENT_UnInitialize();
//配置重连次数，范围1-10，如果下层与服务器通信中断后，会进行重连
//如日志查询，轨迹搜索等
NETCLIENT_API void	API_CALL	NETCLIENT_SetRecntCount(int nCount);


//=============================通用接口====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_SetDataCB(LONG_PTR lHandle, void* pUsr, FUNDownDataCB pfnDownData);
NETCLIENT_API int	API_CALL	NETCLIENT_SetDataConfigCB(LONG_PTR lHandle, void* pUsr, FUNDownConfigCB pfnDownData);
NETCLIENT_API int	API_CALL	NETCLIENT_Start(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_Stop(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_Close(LONG_PTR lHandle);

//=============================客户端登录====================================//
NETCLIENT_API int  API_CALL		NETCLIENT_RegLoginMsg(void* pUsr, void (CALLBACK * FUNLoginMsgCB)(int nMsg, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_LoginDirSvr(const char* pSvrIP, unsigned short usPort, const char* szCompany, const char* szUsr, const char* szPwd, int nType);
NETCLIENT_API int	API_CALL	NETCLIENT_LogoutDirSvr();
NETCLIENT_API int	API_CALL	NETCLIENT_GetDirSvr(char* pSvrIP, unsigned int nIPLen, unsigned short* pPort, char* pSession, unsigned int nSessionLen);
NETCLIENT_API int	API_CALL	NETCLIENT_SetUserSvrInfo(const char* pSvrIP, unsigned short usPort);
NETCLIENT_API int	API_CALL	NETCLIENT_GetSvrVersion();
NETCLIENT_API int	API_CALL	NETCLIENT_GetSvrWorkMode();	//获取服务器类型，GPS_SERVER_MODE_VEHICLE为车载平台，GPS_SERVER_MODE_POLICE为执法仪平台，GPS_SERVER_MODE_VEHI_POLI为车载和执法仪共用平台
NETCLIENT_API int	API_CALL	NETCLIENT_GetGWaySvrAddr(char* szSvrIP, int nSvrIPLen, unsigned short& usSvrPort);
//判断是否为调度员，在登录成功后调用，1为是，0为不是
NETCLIENT_API BOOL	API_CALL	NETCLIENT_IsDispatch();
//判断密码是否能修改 1可以修改
NETCLIENT_API BOOL	API_CALL	NETCLIENT_IsModifyPwd();

//=============================获取服务器的客户端和WEB前台端口信息====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DOWNOpenAppInfo(LONG_PTR* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DOWNRegAppInfoCB(LONG_PTR lHandle, void* pUsr, void (CALLBACK * FUNDownAppInfoCB)(int nType, void* pData, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DOWNStartAppInfo(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DOWNStopAppInfo(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DOWNCloseAppInfo(LONG_PTR lHandle);

//=============================设备管理====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DEVDeviceChangeCB(void* pUsr, void (CALLBACK * FUNDeviceChangeCB)(int nReserve, void* pUsr));

//=============================设备信息下载，使用线程方式====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DEVOpenDevDownEx(LONG_PTR* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVSetCharEx(LONG_PTR lHandle, BOOL bUtf8 = TRUE);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVSetStringMode(LONG_PTR lHandle, BOOL bStrMode = TRUE);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVRegDevDownCBEx(LONG_PTR lHandle, void* pUsr, void (CALLBACK * FUNDownDevCBEx)(int nType, void* pData, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DEVRegDevDownDataCBEx(LONG_PTR lHandle, void* pUsr, void (CALLBACK * FUNDevDownDataCBEx)(int nType, const char* pDataBuf, int nDataLen, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStartDevDownEx(LONG_PTR lHandle, int nMgrType, int nDevType);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStopDevDownEx(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVCloseDevDownEx(LONG_PTR lHandle);

//=============================获取协同小组的成员列表, 使用线程方式====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DEVOpenPttDev(LONG_PTR* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVRegPttDownDataCB(LONG_PTR lHandle, void* pUsr, void (CALLBACK * FUNDevDownDataCB)(int nType, const char* pDataBuf, int nDataLen, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStartPttDown(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStopPttDown(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVClosePttDown(LONG_PTR lHandle);

//=============================车辆状态下载, 使用线程方式====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DEVOpenDevStatusDown(LONG_PTR* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVRegDevStatusCB(LONG_PTR lHandle, void* pUsr, void (CALLBACK * FUNDownStatusCB)(int nType, void* pData, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DEVRegDevStatusCBEx(LONG_PTR lHandle, void* pUsr, void (CALLBACK * FUNDownStatusCBEx)(int nType, const char* pDataBuf, int nDataLen, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DEVSetStatusDevice(LONG_PTR lHandle, GPSDeviceIDNO_S* pDevice, int nCount);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStartDevStatusDown(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStopDevStatusDown(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVCloseDevStatusDown(LONG_PTR lHandle);

//=============================报警屏蔽管理, 使用线程方式====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DEVOpenArmShieldDown(LONG_PTR* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVRegArmShieldDownCB(LONG_PTR lHandle, void* pUsr, void (CALLBACK * FUNDownArmShieldCB)(int nType, void* pData, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStartArmShieldDown(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStopArmShieldDown(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVCloseArmShieldDown(LONG_PTR lHandle);

//=============================地图标签管理, 使用线程方式====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DEVOpenMapTabDown(LONG_PTR* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVRegMapTabDownCB(LONG_PTR lHandle, void* pUsr, void (CALLBACK * FUNDownMapTabCB)(int nType, void* pData, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStartMapTabDown(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStopMapTabDown(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVCloseMapTabDown(LONG_PTR lHandle);

//=============================用户信息，使用线程方式====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DEVOpenUserInfoDown(LONG_PTR* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVRegUserInfoDownCB(LONG_PTR lHandle, void* pUsr, void (CALLBACK * FUNDownUserInfoCB)(int nType, int nSubType, void* pData, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DEVSetUserInfoConfigDown(LONG_PTR lHandle, unsigned int nDownConfig);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStartUserInfoDown(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStopUserInfoDown(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVCloseUserInfoDown(LONG_PTR lHandle);

//=============================获取用户列表====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_USROpenDownUsrList(LONG_PTR* lpHandle, int nType, int nCompany = -1);
NETCLIENT_API int	API_CALL	NETCLIENT_USROpenDownUsrListEx(LONG_PTR* lpHandle, int nType, int nCompany = -1);
NETCLIENT_API int	API_CALL	NETCLIENT_USRSetDownUsrListCB(LONG_PTR lHandle, void* pUsr, void (CALLBACK* FUNDownUsrListCB)(int nType, void* pData, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_USRStartDownUsrList(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_USRStopDownUsrList(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_USRCloseDownUsrList(LONG_PTR lHandle);

//=============================获取设备油量电阻值====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_USROpenDevOliResistance(LONG_PTR* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_USRSetDevOliResistanceCB(LONG_PTR lHandle, void* pUsr, void (CALLBACK* FUNDevOliResistanceCB)(int nType, void* pData, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_USRStartDevOliResistance(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_USRStopDevOliResistance(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_USRCloseDevOliResistance(LONG_PTR lHandle);

//=============================获取设备抓拍计划====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_USROpenDevSnapshotPlan(LONG_PTR* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_USRSetDevSnapshotPlanCB(LONG_PTR lHandle, void* pUsr, void (CALLBACK* FUNDevSnapshotPlan)(int nType, void* pData, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_USRStartDevSnapshotPlan(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_USRStopDevSnapshotPlan(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_USRCloseDevSnapshotPlan(LONG_PTR lHandle);

//=============================获取设备电子围栏信息====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_USROpenDevFence(LONG_PTR* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_USRSetDevFence(LONG_PTR lHandle, void* pUsr, void (CALLBACK* FUNDevFence)(int nType, void* pData, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_USRStartDevFence(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_USRStopDevFence(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_USRCloseDevFence(LONG_PTR lHandle);

//=============================获取车辆驾驶状态====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_USROpenVehiDirveStatus(LONG_PTR* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_USRSetVehiDirveStatus(LONG_PTR lHandle, void* pUsr, void (CALLBACK* FUNDriverSta)(int nType, void* pData, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_USRSetVehiDirveStatusStr(LONG_PTR lHandle, BOOL bIsStr);
NETCLIENT_API int	API_CALL	NETCLIENT_USRStartVehiDirveStatus(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_USRStopVehiDirveStatus(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_USRCloseVehiDirveStatus(LONG_PTR lHandle);

//=============================数据透传到服务器====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_OpenUserTransparent(LONG_PTR* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_RegUserTransparentCB(LONG_PTR lHandle, void* pUsr, void (CALLBACK * FUNUserTransparentCB)(int nType, const char* pDataBuf, int nDataLen, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_SetUserTransData(LONG_PTR lHandle, const char* pDataBuf, int nDataLen);
NETCLIENT_API int	API_CALL	NETCLIENT_StartUserTransparent(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_StopUserTransparent(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_CloseUserTransparent(LONG_PTR lHandle);

//=============================获取设备参数====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DLOpenGetDevCfg(LONG_PTR* lpGetDevCfg, const char* szDevIDNO);
NETCLIENT_API int	API_CALL	NETCLIENT_DLSetGetDCfgMsgCB(LONG_PTR lGetDevCfg, void* pUsr
														 , void (CALLBACK *FUNMsgCB)(int nMsg, int nParam, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DLSetGetDCfgDataCB(LONG_PTR lGetDevCfg, void* pUsr
														  , void (CALLBACK *FUNDataCB)(const char* pBuf, int nLen, long nPos, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DLStartGetDevCfg(LONG_PTR lGetDevCfg);
NETCLIENT_API int	API_CALL	NETCLIENT_DLStopGetDevCfg(LONG_PTR lGetDevCfg);
NETCLIENT_API int	API_CALL	NETCLIENT_DLCloseGetDevCfg(LONG_PTR lGetDevCfg);	

//=============================从服务器将配置文件上传到设备====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_ULOpenSetDevCfg(LONG_PTR* lpSetDevCfg, const char* szDevIDNO, int nSvrID, const char* szFile);
NETCLIENT_API int	API_CALL	NETCLIENT_ULSetSetDCfgMsgCB(LONG_PTR lSetDevCfg, void* pUsr
														 , void (CALLBACK *FUNMsgCB)(int nMsg, int nParam, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_ULStartSetDevCfg(LONG_PTR lSetDevCfg);
NETCLIENT_API int	API_CALL	NETCLIENT_ULStopSetDevCfg(LONG_PTR lSetDevCfg);
NETCLIENT_API int	API_CALL	NETCLIENT_ULCloseSetDevCfg(LONG_PTR lSetDevCfg);	

//=============================获取设备状态信息====================================//
//下层每5分钟从服务器更新一次设备状态信息
NETCLIENT_API int	API_CALL	NETCLIENT_VSOpenVehiStatus(LONG_PTR* lpVSHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VSSetStatusCB(LONG_PTR lVSHandle, void* pUsr, void (CALLBACK *FUNVehiStatusCB)(GPSVehicleState_S* pVehiRun, char* pOnline, int nCount, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_VSSetStatusDevice(LONG_PTR lVSHandle, GPSDeviceIDNO_S* pDevice, int nCount);
NETCLIENT_API int	API_CALL	NETCLIENT_VSStartVSChan(LONG_PTR lVSHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VSStopVSChan(LONG_PTR lVSHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VSCloseVehiStatus(LONG_PTR lVSHandle);

//=============================设备运行GPS====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_VROpenVehiRun(LONG_PTR* lpVRHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VRSetRunningCB(LONG_PTR lVRHandle, void* pUsr, void (CALLBACK *FUNVehiRunningCB)(GPSVehicleState_S* pVehiRun, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_VRSetStateExDataCB(LONG_PTR lVRHandle, void* pUsr, void (CALLBACK *FUNVehiStateExDataCB)(GPSVehicleStateExData_S* pVehiStateExData, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_VRStartVRChan(LONG_PTR lVRHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VRStopVRChan(LONG_PTR lVRHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VRAddDevice(LONG_PTR lVRHandle, int nDevID, const char* szDevIDNO);
NETCLIENT_API int	API_CALL	NETCLIENT_VRDelDevice(LONG_PTR lVRHandle, int nDevID);
NETCLIENT_API int	API_CALL	NETCLIENT_VRCloseVehiRun(LONG_PTR lVRHandle);

//=============================设备报警信息====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_VAOpenVehiAlarm(LONG_PTR* lpVAHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VASetAlarmDevice(LONG_PTR lVAHandle, GPSDeviceIDNO_S* pDevice, int nCount);
NETCLIENT_API int	API_CALL	NETCLIENT_VASetAlarmInfoCB(LONG_PTR lVAHandle, void* pUsr, void (CALLBACK *FUNAlarmInfoCB)(const char* pAlarm, int nLength, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_VAStartVAChan(LONG_PTR lVAHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VAStopVAChan(LONG_PTR lVAHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VACloseVehiAlarm(LONG_PTR lVAHandle);

//=============================轨迹查询====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_VTOpenVehiTrack(LONG_PTR* lpVTrackHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VTSetVTrackMsgCB(LONG_PTR lVTrackHandle, void* pUsr, void (CALLBACK *FUNVehiTrackMsgCB)(int nMsg, int nParam, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_VTSetVTrackDataCB(LONG_PTR lVTrackHandle, void* pUsr, void (CALLBACK *FUNVehiTrackDataCB)(GPSVehicleTrack_S* pVehiTrack, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_VTSetVTrackCountCB(LONG_PTR lVTrackHandle, void* pUsr, void (CALLBACK *FUNTrackCountCB)(GPSTrackCount_S* pTrackCount, void* pUsr));
NETCLIENT_API int   API_CALL	NETCLIENT_VTSetVTrackDevCountCB(LONG_PTR lVTrackHandle, void* pUsr, void (CALLBACK *FUNTrackDevCountCB)(GPSTrackDevCount_S* pTrackDevCount, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_VTSetVehiID(LONG_PTR lVTrackHandle, int nVehiID);
NETCLIENT_API int	API_CALL	NETCLIENT_VTStartVehiTrack(LONG_PTR lVTrackHandle, char* szDevIDNO, const SYSTEMTIME* pBegTime, const SYSTEMTIME* pEndTime, int nType, int nDistance, int nParkTime);
NETCLIENT_API int	API_CALL	NETCLIENT_VTStopVehiTrack(LONG_PTR lVTrackHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VTCloseVehiTrack(LONG_PTR lVTrackHandle);

//=============================经过某区域的车辆查询====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_VTOpenVehiTrackInFence(LONG_PTR* lpVTrackHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VTSetVTrackInFenceMsgCB(LONG_PTR lVTrackHandle, void* pUsr, void (CALLBACK *FUNVehiTrackMsgCB)(int nMsg, int nParam, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_VTSetVTrackInFenceDataCB(LONG_PTR lVTrackHandle, void* pUsr, void (CALLBACK *FUNVehiTrackDataCB)(GPSTrackInFenceInfo_S* pTrackInFenceInfo, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_VTStartVehiTrackInFence(LONG_PTR lVTrackHandle, int* pDevID, int nDevCount, const SYSTEMTIME* pBegTime, const SYSTEMTIME* pEndTime, int nMapType, int nMarkerType, char* pJingDu, char* pWeiDu, int nRadius);
NETCLIENT_API int	API_CALL	NETCLIENT_VTStopVehiTrackInFence(LONG_PTR lVTrackHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VTCloseVehiTrackInFence(LONG_PTR lVTrackHandle);

//=============================串口透传数据查询====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_TPOpenTransPortData(LONG_PTR* lpTransPortHandle, int nStartIndex, int nCount);
NETCLIENT_API int	API_CALL	NETCLIENT_TPSetTransPortMsgCB(LONG_PTR lTransPortHandle, void* pUsr, void (CALLBACK *FUNTransPortMsgCB)(int nMsg, int nParam, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_TPSetTransPortDataCB(LONG_PTR lTransPortHandle, void* pUsr, void (CALLBACK *FUNTransPortDataCB)(GPSTranPortData_S* pData, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_TPSetTransPortDataCountCB(LONG_PTR lTransPortHandle, void* pUsr, void (CALLBACK *FUNTransPortDataCountCB)(const GPSTranPortDataCount_S* pCount, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_TPStartTransPort(LONG_PTR lTransPortHandle, GPSDeviceIDNO_S* pDevice, int nDevCount, int nType, const SYSTEMTIME* pBegTime, const SYSTEMTIME* pEndTime);
NETCLIENT_API int	API_CALL	NETCLIENT_TPStopTransPort(LONG_PTR lTransPortHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_TPCloseTransPort(LONG_PTR lTransPortHandle);

//=============================报警日志查询====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_OpenAlarmQuery(LONG_PTR* lpAlarmQueryHandle, int nStartIndex, int nCount);
NETCLIENT_API int	API_CALL	NETCLIENT_SetAlarmQueryMsgCB(LONG_PTR lAlarmQueryHandle, void* pUsr, void (CALLBACK *FUNMsgCB)(int nMsg, int nParam, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_SetAlarmQueryDataCB(LONG_PTR lAlarmQueryHandle, void* pUsr, void (CALLBACK *FUNVehiArmCB)(const GPSVehicleAlarm_S* pAlarm, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_SetAlarmQueryDataExCB(LONG_PTR lAlarmQueryHandle, void* pUsr, void (CALLBACK *FUNVehiArmCB)(const char* pData, int nDataLen, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_SetAlarmQueryCountCB(LONG_PTR lAlarmQueryHandle, void* pUsr, void (CALLBACK *FUNVehiArmCountCB)(const GPSAlarmCount_S* pAlarmCount, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_StartAlarmQuery(LONG_PTR lAlarmQueryHandle, GPSDeviceIDNO_S* pDevice, int nDevCount, int* pArmType, int nTyCount, SYSTEMTIME* tmBeg, SYSTEMTIME* tmEnd);
NETCLIENT_API int	API_CALL	NETCLIENT_StartAlarmQueryEx(LONG_PTR lAlarmQueryHandle, GPSDeviceIDNO_S* pDevice, int nDevCount, AlarmQueryParam_S* pArmParam, int nTyCount, SYSTEMTIME* tmBeg, SYSTEMTIME* tmEnd);
NETCLIENT_API int	API_CALL	NETCLIENT_StartAlarmQueryMore(LONG_PTR lAlarmQueryHandle, GPSDeviceIDNO_S* pDevice, int nDevCount, AlarmQueryParamMore_S* pArmParam, int nTyCount, SYSTEMTIME* tmBeg, SYSTEMTIME* tmEnd);
NETCLIENT_API int	API_CALL	NETCLIENT_StartAlarmQueryStr(LONG_PTR lAlarmQueryHandle, GPSDeviceIDNO_S* pDevice, int nDevCount, AlarmQueryParamMore_S* pArmParam, int nTyCount, SYSTEMTIME* tmBeg, SYSTEMTIME* tmEnd);
NETCLIENT_API int	API_CALL	NETCLIENT_StopAlarmQuery(LONG_PTR lAlarmQueryHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_CloseAlarmQuery(LONG_PTR lAlarmQueryHandle);

//=============================用户日志查询====================================//
// NETCLIENT_API int	API_CALL	NETCLIENT_OpenUsrLogQuery(LONG_PTR* lpUsrLogHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_OpenUsrLogQueryEx(LONG_PTR* lpUsrLogHandle, int nStartIndex, int nCount);
NETCLIENT_API int	API_CALL	NETCLIENT_SetUsrLogMsgCB(LONG_PTR lUsrLogHandle, void* pUsr, void (CALLBACK *FUNMsgCB)(int nMsg, int nParam, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_SetUsrLogDataCB(LONG_PTR lUsrLogHandle, void* pUsr, void (CALLBACK *FUNUsrLogCB)(const GPSUsrLog_S* pUsrLog, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_SetUsrLogCountCB(LONG_PTR lUsrLogHandle, void* pUsr, void (CALLBACK *FUNUsrLogCountCB)(const GPSUsrLogCount_S* pUsrLogCount, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_StartUsrLogQuery(LONG_PTR lUsrLogHandle, int* pUsrID, int nCount, SYSTEMTIME* tmBeg, SYSTEMTIME* tmEnd);
NETCLIENT_API int	API_CALL	NETCLIENT_StopUsrLogQuery(LONG_PTR lUsrLogHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_CloseUsrLogQuery(LONG_PTR lUsrLogHandle);

//=============================自定义数据查询=================================//
NETCLIENT_API int	API_CALL	NETCLIENT_OpenQueryCustom(LONG_PTR* lpQueryHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_SetCustomMsgCB(LONG_PTR lpQueryHandle, void* pUsr, void (CALLBACK *FUNMsgCB)(int nMsg, int nParam, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_SetCustomDataCB(LONG_PTR lpQueryHandle, void* pUsr, void (CALLBACK *FUNDataCB)(const char* pBuf, int nLen, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_SetCustomCountCB(LONG_PTR lpQueryHandle, void* pUsr, void (CALLBACK *FUNCountCB)(int nCount, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_StartCustomQuery(LONG_PTR lpQueryHandle, int* pID, int nCount, int nType, const char* szParam, const char* szFlg);
NETCLIENT_API int	API_CALL	NETCLIENT_StopCustomQuery(LONG_PTR lpQueryHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_CloseCustomQuery(LONG_PTR lpQueryHandle);

//=============================下载任务查询====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_OpenDloadTaskQuery(LONG_PTR* lpQueryHandle, int nStartIndex, int nCount);
NETCLIENT_API int	API_CALL	NETCLIENT_SetDloadTaskQueryMsgCB(LONG_PTR lpQueryHandle, void* pUsr, void (CALLBACK *FUNMsgCB)(int nMsg, int nParam, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_SetDloadTaskQueryDataCB(LONG_PTR lpQueryHandle, void* pUsr, void (CALLBACK *FUNDloadTaskCB)(const GPSDevDloadTask_S* pTask, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_SetDloadTaskQueryCountCB(LONG_PTR lpQueryHandle, void* pUsr, void (CALLBACK *FUNDloadTaskCountCB)(int nCount, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_StartDloadTaskQuery(LONG_PTR lpQueryHandle, GPSDeviceIDNO_S* pDevice, int nDevCount, int nStatus, char* szLable, SYSTEMTIME* tmBeg, SYSTEMTIME* tmEnd);
NETCLIENT_API int	API_CALL	NETCLIENT_StopDloadTaskQuery(LONG_PTR lpQueryHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_CloseDloadTaskQuery(LONG_PTR lpQueryHandle);

//=============================上传文件====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_GetDevUpgradeFileInfoW(const wchar_t* wszFile, GPSDEVUpgradeFile_S* pFileInfo);
NETCLIENT_API int	API_CALL	NETCLIENT_GetDevUpgradeFileInfo(const char* szFile, GPSDEVUpgradeFile_S* pFileInfo);
NETCLIENT_API int	API_CALL	NETCLIENT_ULOpenDevUpgradeFileW(LONG_PTR* lHandle, GPSDEVUpgradeFile_S* pFile, const wchar_t* wszSrcFile);
NETCLIENT_API int	API_CALL	NETCLIENT_ULOpenDevUpgradeFile(LONG_PTR* lHandle, GPSDEVUpgradeFile_S* pFile, const char* szSrcFile);
NETCLIENT_API int	API_CALL	NETCLIENT_ULOpenDevParamFile(LONG_PTR* lHandle, const char* szSrcFile);
NETCLIENT_API int	API_CALL	NETCLIENT_ULOpenDevParamFileW(LONG_PTR* lHandle, const wchar_t* wszSrcFile);
NETCLIENT_API int	API_CALL	NETCLIENT_ULOpenFile2SvrMD5(LONG_PTR* lHandle, const char* szSrcFile, int nFileType);
NETCLIENT_API int	API_CALL	NETCLIENT_ULOpenFile2SvrMD5W(LONG_PTR* lHandle, const wchar_t* wszSrcFile, int nFileType);
NETCLIENT_API int	API_CALL	NETCLIENT_ULOpenFile2SvrMD5Ex(LONG_PTR* lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_ULOpenFile2FtpSvrMD5(LONG_PTR* lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_ULSetDevIDNO(LONG_PTR lUploadHandle, const char* szDevIDNO);
NETCLIENT_API int	API_CALL	NETCLIENT_ULSetFileInfoMD5Ex(LONG_PTR lUploadHandle, const char* szSrcFile, const GPSFile2SvrMD5Ex_S* pFileInfo);
NETCLIENT_API int	API_CALL	NETCLIENT_ULSetFileInfoMD5ExW(LONG_PTR lUploadHandle, const wchar_t* wszSrcFile, const GPSFile2SvrMD5Ex_S* pFileInfo);
NETCLIENT_API int	API_CALL	NETCLIENT_ULSetUploadMsgCB(LONG_PTR lUploadHandle, void* pUsr, void (CALLBACK *FUNMsgCB)(int nMsg, int nParam, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_ULStartUpload(LONG_PTR lUploadHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_ULStopUpload(LONG_PTR lUploadHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_ULGetDestFileName(LONG_PTR lUploadHandle, int* lpSvrID, char* pDestFile);
NETCLIENT_API int	API_CALL	NETCLIENT_ULGetDestFileID(LONG_PTR lUploadHandle, int* lpFileID);
NETCLIENT_API int	API_CALL	NETCLIENT_ULGetDestFileFtpInfo(LONG_PTR lUploadHandle, char* szIP, int* pPort, char* szAccount, char* szPassword, char* szPath);
NETCLIENT_API int	API_CALL	NETCLIENT_ULCloseUpload(LONG_PTR lUploadHandle);

//=============================远程升级====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DUOpenDevUpgrade(LONG_PTR* lHandle, const char* szDevIDNO, GPSDEVUpgradeFile_S* pFile, int nSvrID, const char* szUpFile);
NETCLIENT_API int	API_CALL	NETCLIENT_DUChangeUpgradeFile(LONG_PTR lUploadHandle, GPSDEVUpgradeFileEx_S* pFile);
NETCLIENT_API int	API_CALL	NETCLIENT_DUSetDevUpMsgCB(LONG_PTR lUploadHandle, void* pUsr, void (CALLBACK *FUNMsgCB)(int nMsg, int nParam, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DUStartDevUpgrade(LONG_PTR lUploadHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DUStopDevUgprade(LONG_PTR lUploadHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DUCloseDevUpgrade(LONG_PTR lUploadHandle);

//=============================上传文件到设备====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DUOpenDevUploadFile(LONG_PTR* lHandle, const char* szDevIDNO, int nFileType, const char* cReserve, int nSvrID, const char* szSvrFile);
NETCLIENT_API int	API_CALL	NETCLIENT_DUSetDevUploadFileMsgCB(LONG_PTR lUploadHandle, void* pUsr, void (CALLBACK *FUNMsgCB)(int nMsg, int nParam, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DUStartDevUploadFile(LONG_PTR lUploadHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DUStopDevUploadFile(LONG_PTR lUploadHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DUCloseDevUploadFile(LONG_PTR lUploadHandle);

//=============================获取设备IP====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DEVOpenGetDevIP(LONG_PTR* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVSetGetDevIPCB(LONG_PTR lHandle, void* pUsr, void (CALLBACK* FUNGetDevIPCB)(int nType, void* pData, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStartGetDevIP(LONG_PTR lHandle, GPSDeviceIDNO_S* pDevice, unsigned int nDevCount);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStopGetDevIPt(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVCloseGetDevIP(LONG_PTR lHandle);

//=============================离线任务=======================================//
//=============================离线文件信息=======================================//
NETCLIENT_API int	API_CALL	NETCLIENT_OFLOpenGetFileInfo(LONG_PTR* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_OFLSetGetFileInfo(LONG_PTR lHandle, int nFileType, int nProtocol=0, int nFactoryType=0, int nDevType=0, int nDevSubType=0);
NETCLIENT_API int	API_CALL	NETCLIENT_OFLSetQueryInfo(LONG_PTR lHandle, const char* szVesion, SYSTEMTIME& tmBeg, SYSTEMTIME& tmEnd);
NETCLIENT_API int	API_CALL	NETCLIENT_OFLSetGetFileInfoCB(LONG_PTR lHandle, void* pUsr, FUNDownDataCB pfn);
NETCLIENT_API int	API_CALL	NETCLIENT_OFLStartGetOflFileInfo(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_OFLStopGetFileInfo(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_OFLCloseGetFileInfo(LONG_PTR lHandle);
//=============================获取设备离线任务=======================================//
NETCLIENT_API int	API_CALL	NETCLIENT_OFLOpenGetDevOflTask(LONG_PTR* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_OFLSetGetDevTaskInfo(LONG_PTR lHandle, const char* szDevIDNO, int nFileType=0);
NETCLIENT_API int	API_CALL	NETCLIENT_OFLSetGetDevTaskCB(LONG_PTR lHandle, void* pUsr, FUNDownDataCB pfn);
NETCLIENT_API int	API_CALL	NETCLIENT_OFLStartGetDevTask(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_OFLStopGetDevTask(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_OFLCloseGetDevTask(LONG_PTR lHandle);

//=============================向服务器发送命令====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_MCStartWork();
NETCLIENT_API int	API_CALL	NETCLIENT_MCStopWork();
NETCLIENT_API int	API_CALL	NETCLIENT_MCRegMsgCB(void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_MCReleaseMsg(GPSMCMsg_S* pMsg);
NETCLIENT_API int	API_CALL	NETCLIENT_MCReleaseHandle(LONG_PTR lHandle);

//发送短信息，如短信通知设备重启、配置中心地址
NETCLIENT_API int	API_CALL	NETCLIENT_MCSendSMS(const char* szDevIDNO, int nSMSType, const char* szPhoneNO, const char* szText); //发送短信
NETCLIENT_API int	API_CALL	NETCLIENT_MCSendSMSEx(const char* szDevIDNO, int nSMSType, const char* szPhoneNO, const char* szText); //发送短信
//发送TTS
NETCLIENT_API int	API_CALL	NETCLIENT_MCSendText(const char* szDevIDNO, const char* szText, void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_MCSendTextEx(const char* szDevIDNO, const char* szText, void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_MCSendTextMoreEx(const char* szDevIDNO, const char* szText, void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_MCSendTextMoreEx2(const char* szDevIDNO, const char* szText, int nFlag, int nParam, void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr));

//发送重启，断油断电
NETCLIENT_API int	API_CALL	NETCLIENT_MCSendCtrl(const char* szDevIDNO, int nCtrlType, const char* szUsr, const char* szPwd);
//云台控制
NETCLIENT_API int	API_CALL	NETCLIENT_MCSendPtz(const char* szDevIDNO, int nChn, int nCommand, int nSpeed, int nParam, void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr));
//获取车辆状态
NETCLIENT_API int	API_CALL	NETCLIENT_MCFreePresetGet(const char* szDevIDNO, int nChn, void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr), LONG_PTR* lpHandle);
//获取车辆状态
NETCLIENT_API int	API_CALL	NETCLIENT_MCReadDevStatus(const char* szDevIDNO, void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr));
//修改用户密码
NETCLIENT_API int	API_CALL	NETCLIENT_MCChangeUsrPwd(const char* szOld, const char* szNew, void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr), LONG_PTR* lpHandle);
//设置GPS时间间隔
NETCLIENT_API int	API_CALL	NETCLIENT_MCSetGpsInterval(const char* szDevIDNO, BOOL bStart, int nDistance, int nTime, int nType);
//发送控制指令时校验平台用户
NETCLIENT_API int	API_CALL	NETCLIENT_MCCheckCtrlUsr(const char* szUsr, const char* szPwd);
//获取移动侦测参数
NETCLIENT_API int	API_CALL	NETCLIENT_MCReadMotionParam(const char* szDevIDNO, int nChannel
														  , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														  , LONG_PTR* lpHandle);
//配置移动侦测参数
NETCLIENT_API int	API_CALL	NETCLIENT_MCSetMotionParam(const char* szDevIDNO, int nChannel, GPSMotionParam_S* pMotion
														 , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														 , LONG_PTR* lpHandle);
//获取网络流量参数信息
NETCLIENT_API int	API_CALL	NETCLIENT_MCReadNetFlowStatistics(const char* szDevIDNO
														  , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														  , LONG_PTR* lpHandle);
//配置网络流量统计参数
NETCLIENT_API int	API_CALL	NETCLIENT_MCSetNetFlowParam(const char* szDevIDNO, GPSNetFlowStatistics_S* pNetParam
														 , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														 , LONG_PTR* lpHandle);
//清空网络流量统计
NETCLIENT_API int	API_CALL	NETCLIENT_MCClearNetFlowStatistics(const char* szDevIDNO
														  , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														  , LONG_PTR* lpHandle);
//调整网络流量参数
NETCLIENT_API int	API_CALL	NETCLIENT_MCAdjustNetFlowStatistics(const char* szDevIDNO, int nMBFlow
														 , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														 , LONG_PTR* lpHandle);
//设置用户报警屏蔽 
NETCLIENT_API int	API_CALL	NETCLIENT_MCSetUsrAlarmShield(const GPSAlarmShield_S* pAlarm, int nCount
														 , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														 , LONG_PTR* lpHandle);
//设置用户AI报警屏蔽 
NETCLIENT_API int	API_CALL	NETCLIENT_MCSetUsrAiAlarmShield(int nAiType, const GPSAlarmShield_S* pAlarm, int nCount
	, void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr), LONG_PTR* lpHandle);
//添加地图标记信息
NETCLIENT_API int	API_CALL	NETCLIENT_MCAddMapMarker(const GPSMapMarker_S* pMarker
														  , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														  , LONG_PTR* lpHandle);
//添加地图标记属性
NETCLIENT_API int	API_CALL	NETCLIENT_MCAddMapMarkerInfo(const GPSMarkerInfo_S* pMarkerInfo
														 , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														  , LONG_PTR* lpHandle);

//添加地图标记属性(按照字符串,支持全部区域属性)
// pBaseData参数说明,使用\x09(0x09)字符分隔数据,编码必须为utf8
// 0	1		2		3		4	5		6	7		8		9	10
//ID MarkerType Type Creator Share Name Color Remark Radius MapType Update
// 请注意,调用此接口需要判断用户服务器版本大于等于 GPS_VERSION_EX_7_6_0_9 (9)//7.6.0.9版本,服务器的地图区域取消结构体,使用字符串拼接
NETCLIENT_API int	API_CALL	NETCLIENT_MCAddMapMarkerByStr(const char* pBaseData, const char* pJingDu, const char* pWeiDu
														 , void* pUsr, FUNDownDataCB pfnDownData
														  , LONG_PTR* lpHandle);

//删除地图标记信息
NETCLIENT_API int	API_CALL	NETCLIENT_MCDelMapMarker(int nMarkerID
														 , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														 , LONG_PTR* lpHandle);
//发送调度指令信息
NETCLIENT_API int	API_CALL	NETCLIENT_MCSendDispatchCommand(const char* szDevIDNO, const GPSDispatchCommand_S* lpDispatch
														 , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														 , LONG_PTR* lpHandle);
//设置用户地图配置
NETCLIENT_API int	API_CALL	NETCLIENT_MCSetUsrMapConfig(const UserMapConfig_S* pUserMapConfig, void* pUsr, 
															void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
															  , LONG_PTR* lpHandle);
//参数透传
NETCLIENT_API int	API_CALL	NETCLIENT_MCTransparentConfig(const char* szDevIDNO, int nType, GPSConfigData_S* pConfig
													 , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
													  , LONG_PTR* lpHandle);

NETCLIENT_API int	API_CALL	NETCLIENT_MCTransparentConfigEx(const char* szDevIDNO, int nType, GPSConfigDataEx_S* pConfig
														, void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														, LONG_PTR* lpHandle);

//透传数据
NETCLIENT_API int	API_CALL	NETCLIENT_MCTransparentPortData(const char* szDevIDNO, int nType, const char* pData, int nLength
															  , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
															  , LONG_PTR* lpHandle);
//获取和设置颜色参数
NETCLIENT_API int	API_CALL	NETCLIENT_MCGetVideoColor(const char* szDevIDNO, int nChannel
													, void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
													, LONG_PTR* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_MCSetVideoColor(const char* szDevIDNO, int nChannel, GPSVideoColor_S* pColor
													, void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
													, LONG_PTR* lpHandle);
//配置设备GPS位置
NETCLIENT_API int	API_CALL	NETCLIENT_MCSetDevFixGPS(DevFixGPS_S* pDevFixGPS
														  , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														  , LONG_PTR* lpHandle);

//报警处理
NETCLIENT_API int	API_CALL	NETCLIENT_MCSetDevHandleAlarm(DevHandleAlarm_S* pDevHandleAlarm
														 , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														  , LONG_PTR* lpHandle);

//809查岗信息应答
NETCLIENT_API int	API_CALL	NETCLIENT_MCAck809Platform(Ack809Platform_S* pPlatform
														   , void* pUsr,void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														  , LONG_PTR* lpHandle);

//JT809相关业务
NETCLIENT_API int	API_CALL	NETCLIENT_MCJT809Business(GPSJT809Business_S* pBusiness
														, void* pUsr,void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														, LONG_PTR* lpHandle);

//向用户发送消息
NETCLIENT_API int	API_CALL	NETCLIENT_MCSendUserText(int nUserID, const char* szText, int nFlag, int nParam
														, void* pUsr,void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														, LONG_PTR* lpHandle);
//下发设备FTP任务
NETCLIENT_API int	API_CALL	NETCLIENT_MCSendFtpTaskCtrl(const char* szDevIDNO, int nUserID, GPSFtpUploadFileTask_S* pTask
														, void* pUsr,void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														, LONG_PTR* lpHandle);

//创造一个报警,pHandleAlarm为报警处理参数,可传NULL表示不处理
NETCLIENT_API int	API_CALL	NETCLIENT_MCCreateClientAlarm(const GPSVehicleAlarm_S* pVehiAlarm, const DevHandleAlarm_S* pHandleAlarm
														, void* pUsr,void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														, LONG_PTR* lpHandle);

//给媒体文件增加备注
NETCLIENT_API int	API_CALL	NETCLIENT_MCSetMediaFileRemarks(GPSFile_S* pFile, const char* szRemarksUtf8
														, void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														, LONG_PTR* lpHandle);

//修改车辆的使用状态(单次处理数量最大100个)
NETCLIENT_API int	API_CALL	NETCLIENT_MCChangeUseStatus(int* pVehiID, int nCount, int nUseStatus
	, void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr), LONG_PTR* lpHandle);

//发送苏标上传命令
NETCLIENT_API int	API_CALL	NETCLIENT_MCSendSbUpload(const char* szDevIDNO, const char* szGuid, const char* szAlarmCode
	, void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr), LONG_PTR* lpHandle);


//============================获取最新抓拍图片文件====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_MCGetLastestSnapshot(const char* szDevIDNO, int nChn, void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr), LONG_PTR* lpHandle);

//=============================与服务器进行指令交互（使用TCP方式直接服务器）====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_CMDAddMapLine(const GPSMapLine_S* pLine, void* pUsr, FUNDownDataCB pfnDownData
														 , LONG_PTR* lpHandle);
//设置设备油量刻度表(兼容旧版本)
NETCLIENT_API int	API_CALL	NETCLIENT_MCSetDevOliResistanceOld(const OilResistanceOld_S* pOilResistance, int nCount
																, void* pUsr, FUNDownDataCB pfnDownData
																, LONG_PTR* lpHandle);
//设置设备油量刻度表 
NETCLIENT_API int	API_CALL	NETCLIENT_MCSetDevOliResistance(const OilResistance_S* pOilResistance, int nCount
																, void* pUsr, FUNDownDataCB pfnDownData
																, LONG_PTR* lpHandle);

//设置设备抓拍计划 
NETCLIENT_API int	API_CALL	NETCLIENT_MCSetDevSnapshotPlan(const GPSDevSnapshotPlan_S* pDevSnapshotPlan, int nCount
																, void* pUsr, FUNDownDataCB pfnDownData
																, LONG_PTR* lpHandle);
//设置设备电子围栏
NETCLIENT_API int	API_CALL	NETCLIENT_MCSetDevFence(const GPSMapFence_S* pDevFence, GPSDeviceIDNO_S* pDevIDNO, int nCountIDNO
															   , void* pUsr, FUNDownDataCB pfnDownData
															   , LONG_PTR* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_MCDelDevFence(int* pFenceID, int nCount, void* pUsr, FUNDownDataCB pfnDownData, LONG_PTR* lpHandle);
//添加和修改设备离线任务 
NETCLIENT_API int	API_CALL	NETCLIENT_MCSetDevOflTask(GPSDevOflTask_S* pDevTask, void* pUsr, FUNDownDataCB pfnDownData, LONG_PTR* lpHandle);
//复制设备离线任务
NETCLIENT_API int	API_CALL	NETCLIENT_MCCopyDevOflTask(GPSDeviceIDNO_S* pDevice, int nFileType, unsigned int nDevCount, const char* szSrvDev
														   , void* pUsr, FUNDownDataCB pfnDownData, LONG_PTR* lpHandle);
//配置设备离线任务
NETCLIENT_API int	API_CALL	NETCLIENT_MCSetMulDevOflTask(GPSDeviceIDNO_S* pDevice, unsigned int nDevCount, int nFileID, int nFileType
														   , void* pUsr, FUNDownDataCB pfnDownData, LONG_PTR* lpHandle);
//批量删除设备离线任务
NETCLIENT_API int	API_CALL	NETCLIENT_MCDelDevOflTask(GPSDeviceIDNO_S* pDevice, unsigned int nDevCount
														   , void* pUsr, FUNDownDataCB pfnDownData, LONG_PTR* lpHandle);
//增加设备下载计划
NETCLIENT_API int	API_CALL	NETCLIENT_MCAddDevDloadTask(const GPSDevDloadTask_S* pDownloadTask, int nCount
															   , void* pUsr, FUNDownDataCB pfnDownData, LONG_PTR* lpHandle);
//批量删除设备下载计划
NETCLIENT_API int	API_CALL	NETCLIENT_MCDelDevDloadTask(const int* pID, int nCount
															   , void* pUsr, FUNDownDataCB pfnDownData, LONG_PTR* lpHandle);
//批量下载指定类型的数据
#define GPS_DOWN_DATA_FLAG_VEHICLE_OTHER		0x1	//返回类型:GPS_BETCH_DOWN_DEVICE_VEHICLE_OTHER 结构体:GPSVehiOtherVariable_S
NETCLIENT_API int	API_CALL	NETCLIENT_MCDownBatchData(unsigned int uFlag, void* pUsr, FUNDownConfigCB pfnDownData, LONG_PTR* lpHandle);

NETCLIENT_API int	API_CALL	NETCLIENT_CMDReleaseHandle(LONG_PTR lHandle);

//=============================MD5加密====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_Md5Encrypt(const char* szPwd, char* szEncrypt, int nEncryLen);
//=============================获取登录会话====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_GetSession(char* szSession, int nSessLen);
//============================进行用户登录====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_CheckLogin(const char* szUser, const char* szPwd, const char* szServer, unsigned short usPort);
//============================判断设备是否在线====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_CheckOnline(const char* szDevIDNO, const char* szServer, unsigned short usPort);
//============================获取空闲预置位====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_FreePresetGet(const char* szDevIDNO, int nChn, const char* szServer, unsigned short usPort, int* lpFreePresetNO);

//============================向服务器发送车辆普通命令(参数为JSON格式)====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_MNOpenNormalCmd(LONG_PTR* lpHandle, const char* szDevIDNO, const char* szParam, const char* szContent);
NETCLIENT_API int	API_CALL	NETCLIENT_MNSetNormalCmdCB(LONG_PTR lHandle, void* pUsr, void (CALLBACK* FUNHttpCmdCB)(int nMsg, const char* szContent, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_MNStartNormalCmd(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_MNStopNormalCmd(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_MNCloseNormalCmd(LONG_PTR lHandle);

//============================向服务器获取车辆保险,许可证等提醒信息====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_RMOpenRemindInfo(LONG_PTR* lpHandle, int nType, const SYSTEMTIME* pTimeStamp);
// 设置已下载的数据的ID
NETCLIENT_API int	API_CALL	NETCLIENT_RMSetRemindIDs(LONG_PTR lHandle, int* pID, int nCount);
NETCLIENT_API int	API_CALL	NETCLIENT_RMSetRemindInfoCB(LONG_PTR lHandle, void* pUsr, void (CALLBACK* FUNRemindInfoCB)(int nType, int nSubType, void* pData, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_RMStartRemindInfo(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_RMStopRemindInfo(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_RMCloseRemindInfo(LONG_PTR lHandle);

//=============================809查岗数据=================================//
NETCLIENT_API int	API_CALL	NETCLIENT_CPOpenCheckPostQuery(LONG_PTR* lpCheckPostHandle, int nStartIndex, int nCount);
NETCLIENT_API int	API_CALL	NETCLIENT_CPSetCheckPostQueryMsgCB(LONG_PTR lCheckPostHandle, void* pUsr, void (CALLBACK *FUNMsgCB)(int nMsg, int nParam, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_CPSetCheckPostQueryDataCB(LONG_PTR lCheckPostHandle, void* pUsr, void (CALLBACK *FUNDataCB)(const GPSVehicleAlarm_S* pAlarm, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_CPSetCheckPostQueryCountCB(LONG_PTR lCheckPostHandle, void* pUsr, void (CALLBACK *FUNCountCB)(const GPSAlarmCount_S* pAlarmCount, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_CPStartCheckPostQuery(LONG_PTR lCheckPostHandle, int nHandleStatus, const SYSTEMTIME* pTmBeg, const SYSTEMTIME* pTmEnd);
NETCLIENT_API int	API_CALL	NETCLIENT_CPStopCheckPostQuery(LONG_PTR lCheckPostHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_CPCloseCheckPostQuery(LONG_PTR lCheckPostHandle);

//=============================查询FTP任务列表=================================//
NETCLIENT_API int	API_CALL	NETCLIENT_FTPOpenFtpTaskQuery(LONG_PTR* lpHandle, int nStartIndex, int nCount);
NETCLIENT_API int	API_CALL	NETCLIENT_FTPSetFtpTaskQueryMsgCB(LONG_PTR lHandle, void* pUsr, void (CALLBACK *FUNMsgCB)(int nMsg, int nParam, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_FTPSetFtpTaskQueryDataCB(LONG_PTR lHandle, void* pUsr, void (CALLBACK *FUNDataCB)(const GPSVehiFtpTaskData_S* pTaskData, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_FTPSetFtpTaskQueryCountCB(LONG_PTR lHandle, void* pUsr, void (CALLBACK *FUNCountCB)(const GPSFtpTaskDataCount_S* pTaskCount, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_FTPStartFtpTaskQuery(LONG_PTR lHandle, int nCompanyID, GPSDeviceIDNO_S* pDevice, int nDevCount, const SYSTEMTIME* pTmBeg, const SYSTEMTIME* pTmEnd);
NETCLIENT_API int	API_CALL	NETCLIENT_FTPStopFtpTaskQuery(LONG_PTR lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_FTPCloseFtpTaskQuery(LONG_PTR lHandle);

//=============================查询子用户的在线状态(Child User)=================================//
NETCLIENT_API int	API_CALL	NETCLIENT_CUOpenOnlineStatusQuery(LONG_PTR* lpHandle, const char* szAccount, int nType);
#define NETCLIENT_CUSetOnlineStatusQueryDataCB	NETCLIENT_SetDataCB
#define NETCLIENT_CUStartOnlineStatusQuery		NETCLIENT_Start
#define NETCLIENT_CUStopOnlineStatusQuery		NETCLIENT_Stop
#define NETCLIENT_CUCloseOnlineStatusQuery		NETCLIENT_Close

//=============================查询809连接状态(使用通用接口操作)=================================//
NETCLIENT_API int	API_CALL	NETCLIENT_CS809OpenQuery(LONG_PTR* lpHandle);

//获取司机的证件照(1张)
NETCLIENT_API int	API_CALL	NETCLIENT_GetDriverFace(LONG_PTR* lpHandle, int nDriverID, const char* szFileMD5 = NULL);

//获取自定义报警名称
NETCLIENT_API int	API_CALL	NETCLIENT_OpenGetAlarmCustomName(LONG_PTR* lpHandle, const char* szLanguage);

//获取车辆风险信息
NETCLIENT_API int	API_CALL	NETCLIENT_OpenGetVehicleRiskScore(LONG_PTR* lpHandle, int* pVehiID, int nVehiCount);


#ifdef __cplusplus
}
#endif

#endif

