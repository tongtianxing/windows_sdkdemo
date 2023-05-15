#ifndef _NET_MEDIA_API_H_
#define _NET_MEDIA_API_H_

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the IREALPLAY_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// NETMEDIA_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef LIBNETMEDIA_EXPORTS
#define NETMEDIA_API __declspec(dllexport)
#else
#define NETMEDIA_API __declspec(dllimport)
#endif

#ifndef API_CALL
#define  API_CALL	WINAPI
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "netclientapi.h"

#define NETMEDIA_OK			0
#define NETMEDIA_FALSE		1

#define NETMEDIA_TYPE_VIEWER				0
#define NETMEDIA_TYPE_REC_SVR				1

#define NETMEDIA_REAL_MSG_SUCCESS			0
#define NETMEDIA_REAL_MSG_CNT_DS_FD			-1
#define NETMEDIA_REAL_MSG_USR_NORIGHT		-2
#define NETMEDIA_REAL_MSG_MS_EMPTY			-3
#define NETMEDIA_REAL_MSG_CNT_MS_FD			-4
#define NETMEDIA_REAL_MSG_CNT_MS_SUC			-5
#define NETMEDIA_REAL_MSG_CNT_DEV_FD			-6
#define NETMEDIA_REAL_MSG_CNT_DEV_SUC		-7
#define NETMEDIA_REAL_MSG_MS_DISCONNECT		-8
#define NETMEDIA_REAL_MSG_USR_FULL_ERROR		-9
#define NETMEDIA_REAL_MSG_USR_ERROR			-10
#define NETMEDIA_REAL_MSG_UNKNOW				-11
#define NETMEDIA_REAL_MSG_FINISHED			-12
#define NETMEDIA_REAL_MSG_SESSION_END		-13
#define NETMEDIA_REAL_MSG_DEV_USED			-14
#define NETMEDIA_REAL_MSG_DEV_OFFLINE		-15	
#define NETMEDIA_REAL_MSG_PLAY_FINISHED		-16
#define NETMEDIA_REAL_DEV_NO_SUPPORT		-17

#define NETMEDIA_REAL_TYPE_MAIN				0
#define NETMEDIA_REAL_TYPE_SUB				1

#define NETMEDIA_CNT_TYPE_TCP				0
#define NETMEDIA_CNT_TYPE_UDP				1

#define NETMEDIA_REAL_DATA_TYPE_HEAD			1
#define NETMEDIA_REAL_DATA_TYPE_I_FRAME		0x63643030
#define NETMEDIA_REAL_DATA_TYPE_P_FRAME		0x63643130
#define NETMEDIA_REAL_DATA_TYPE_A_FRAME		0x63643230

#define NETMEDIA_AUDIO_MIC_CHANNEL			98


NETMEDIA_API int	API_CALL	NETMEDIA_Initialize(int nType, UINT uiNetPoolSockCtxtNum = 128, UINT uiNetPoolBufNum = 2000, UINT nThrd = 2);
NETMEDIA_API int	API_CALL	NETMEDIA_UnInitialize();

NETMEDIA_API HANDLE API_CALL	NETMEDIA_GetDecHandle(int nType = 0);

NETMEDIA_API int	API_CALL	NETMEDIA_SetSession(const char* szGUID);
NETMEDIA_API int	API_CALL	NETMEDIA_SetDirSvr(const char* szIP, unsigned short usPort);

NETMEDIA_API int	API_CALL	NETMEDIA_SetAudioGain(double lfGain);

// ��ȡ�ϴ�IO���ݵ�ʱ��,GetTickCount,��ʱ������Խ��ͼ���
NETMEDIA_API int	API_CALL	NETMEDIA_GetIOTime(LONG_PTR lHandle, DWORD& dwTime);
NETMEDIA_API int	API_CALL	NETMEDIA_SetIOTime(LONG_PTR lHandle, DWORD dwTime);
//��ȡIO��������
NETMEDIA_API int	API_CALL	NETMEDIA_GetFolwTotal(LONG_PTR lHandle, int* lpSecond, int* lpFlowTotal);

//ʵʱԤ��
NETMEDIA_API int	API_CALL	NETMEDIA_OpenRealPlay(const char* szDevIDNO, int nChn, int nMode, int nCntMode, BOOL bTransmit, LONG_PTR* lpRealHandle);	
//ͬһ������ʱ�����ͨ������Ƶ������ʹ��ͬһ�����ӽ��д��䣬���ϲ���ԣ������Ľӿڶ�����ͬ��
NETMEDIA_API int	API_CALL	NETMEDIA_OpenRealPlayEx(const char* szDevIDNO, int nChn, int nMode, int nCntMode, BOOL bTransmit, LONG_PTR* lpRealHandle);	
//�ؼ�������Ҫ���ô˽ӿڣ����ÿؼ���Ӧ�ķ�������ַ
NETMEDIA_API int	API_CALL	NETMEDIA_SetRealServer(LONG_PTR lRealHandle, const char* szIP, unsigned short usPort, const char* szSession);	
NETMEDIA_API int	API_CALL	NETMEDIA_SetRealMsgCallBack(LONG_PTR lRealHandle, void* pUsr, void (CALLBACK *FUNRealMsgCB)(int nMsg, void* pUsr));
NETMEDIA_API int	API_CALL	NETMEDIA_SetRealDataCallBack(LONG_PTR lRealHandle, void* pUsr, void (CALLBACK *FUNRealDataCB)(const char* pFrameBuf
									, int nFrameLen, int nFrameType, unsigned __int64 llFrameStamp, void* pUsr));
//�˻ص�����FUNRealDataCB�е�pFrameBuf����֡ͷ��Ϣ
NETMEDIA_API int	API_CALL	NETMEDIA_SetRealDataCallBackEx(LONG_PTR lRealHandle, void* pUsr, void (CALLBACK *FUNRealDataCB)(const char* pFrameBuf
									, int nFrameLen, int nFrameType, unsigned __int64 llFrameStamp, void* pUsr));
NETMEDIA_API int	API_CALL	NETMEDIA_SetRealDecCallBack(LONG_PTR lRealHandle, void* pUsr
									, void (CALLBACK* FUNRealDecCB)(unsigned char* pY, int nYStride, unsigned char* pU, unsigned char* pV, int nUVStride, 
									int nWidth, int nHeight, unsigned __int64 nStamp, int nType, void* pUsr));
NETMEDIA_API int	API_CALL	NETMEDIA_SetRealDisplayCallBack(LONG_PTR lRealHandle, void* pUsr
									, void (CALLBACK* FUNRealDisplayCB)(HDC hDc 
									, int nWidth, int nHeight, unsigned __int64 nStamp
									, int nWndWidth, int nWndHeight, void* pUsr));
NETMEDIA_API int	API_CALL	NETMEDIA_SetRealDecUsrDataCallBack(LONG_PTR lRealHandle, void* pUsr
									, void (CALLBACK *FUNDecUsrDataCB)(const char* pUsrData
									, int nDataLen, int nDataType, void* pUsr));
//bOnlyVideo�����Ƿ�ֻ����Ƶ, ����808��Ƶ������ʹ�ã�Ĭ��Ϊfalse
NETMEDIA_API int	API_CALL	NETMEDIA_SetRealParam(LONG_PTR lRealHandle, BOOL bOnlyVideo, int nReserve1, int nReserve2);
//�����Ƿ�ʹ��rtspЭ�飬Ĭ��ʹ��rtspЭ�鴫����Ƶ�����Ϊfalse����ʹ��˽��Э�鴫����Ƶ����NETMEDIA_StartRealPlay֮ǰ������Ч
NETMEDIA_API int	API_CALL	NETMEDIA_SetUseRtsp(LONG_PTR lRealHandle, BOOL bRtsp);
NETMEDIA_API int	API_CALL	NETMEDIA_StartRealPlay(LONG_PTR lRealHandle, HWND hWnd, BOOL bPriorRGB16=FALSE);
NETMEDIA_API int	API_CALL	NETMEDIA_StopRealPlay(LONG_PTR lRealHandle);
NETMEDIA_API int	API_CALL	NETMEDIA_StartView(LONG_PTR lRealHandle, HWND hWnd, BOOL bPriorRGB16=FALSE);
NETMEDIA_API int	API_CALL	NETMEDIA_StopView(LONG_PTR lRealHandle);
NETMEDIA_API int	API_CALL	NETMEDIA_SetStreamMode(LONG_PTR lRealHandle, int nMode);
NETMEDIA_API int	API_CALL	NETMEDIA_SetDelayTime(LONG_PTR lRealHandle, DWORD dwMinMinsecond, DWORD dwMaxMinsecond);
NETMEDIA_API int	API_CALL	NETMEDIA_AdjustedWndRect(LONG_PTR lRealHandle);
NETMEDIA_API int	API_CALL	NETMEDIA_PlaySound(LONG_PTR lRealHandle, long lPlay);
NETMEDIA_API int	API_CALL	NETMEDIA_SetVolume(LONG_PTR lRealHandle, WORD wVolume);
NETMEDIA_API int	API_CALL	NETMEDIA_RequireAudio(LONG_PTR lRealHandle);
NETMEDIA_API int	API_CALL	NETMEDIA_CaptureBMP(LONG_PTR lRealHandle, const char* szBmpFile);
NETMEDIA_API int	API_CALL	NETMEDIA_CaptureJPEG(LONG_PTR lRealHandle, const char* szJPEGFile);
NETMEDIA_API int	API_CALL	NETMEDIA_FlashWnd(LONG_PTR lRealHandle);
NETMEDIA_API int	API_CALL	NETMEDIA_SetDivHwnd(LONG_PTR lRealHandle, int nIndex, HWND hWnd);
NETMEDIA_API int	API_CALL	NETMEDIA_SetDivRect(LONG_PTR lRealHandle, int nIndex, RECT* pRect);
NETMEDIA_API int	API_CALL	NETMEDIA_GetDivRect(LONG_PTR lRealHandle, int nIndex, RECT* pRect);
NETMEDIA_API int	API_CALL	NETMEDIA_SetDivPlay(LONG_PTR lRealHandle, int nIndex, int nPlay);
NETMEDIA_API int	API_CALL	NETMEDIA_GetDivPlay(LONG_PTR lRealHandle, int nIndex, int* nPlay);
NETMEDIA_API int	API_CALL	NETMEDIA_GetFlowRate(LONG_PTR lRealHandle, int* lpFlowRate);
NETMEDIA_API int	API_CALL	NETMEDIA_PtzCtrl(LONG_PTR lRealHandle, int nCommand, int nSpeed, int nParam);
NETMEDIA_API int	API_CALL	NETMEDIA_ShowOSDText(LONG_PTR lRealHandle, int nOsdIndex, const char* szText, int nLeft, int nTop, int nPos, COLORREF clr);
NETMEDIA_API int	API_CALL	NETMEDIA_SwitchStream(LONG_PTR lRealHandle, bool bMainStream);
// ʵʱԤ������ô˽ӿ� [2017-7-5 ydl]
NETMEDIA_API int	API_CALL	NETMEDIA_GetRealIOTime(LONG_PTR lRealHandle, DWORD& dwTime);
NETMEDIA_API int	API_CALL	NETMEDIA_SetRealIOTime(LONG_PTR lRealHandle, DWORD dwTime);
NETMEDIA_API int	API_CALL	NETMEDIA_GetRealFolwTotal(LONG_PTR lRealHandle, int* lpSecond, int* lpFlowTotal);
NETMEDIA_API int	API_CALL	NETMEDIA_CloseRealPlay(LONG_PTR lRealHandle);

//��������
NETMEDIA_API int	API_CALL	NETMEDIA_RAOpenRealAudio(const char* szDevIDNO, int nChn, int nMode, int nCntMode, BOOL bTransmit, LONG_PTR* lpRealHandle);	
NETMEDIA_API int	API_CALL	NETMEDIA_RASetRealServer(LONG_PTR lRealHandle, const char* szIP, unsigned short usPort, const char* szSession);	
NETMEDIA_API int	API_CALL	NETMEDIA_RASetRAudioMsgCallBack(LONG_PTR lRealHandle, void* pUsr, void (CALLBACK *FUNRealMsgCB)(int nMsg, void* pUsr));
NETMEDIA_API int	API_CALL	NETMEDIA_RASetAudioDelay(LONG_PTR lRealHandle, int nMinSecond);
NETMEDIA_API int	API_CALL	NETMEDIA_RAStartRealAudio(LONG_PTR lRealHandle);
NETMEDIA_API int	API_CALL	NETMEDIA_RAStopRealAudio(LONG_PTR lRealHandle);
NETMEDIA_API int	API_CALL	NETMEDIA_RAPlaySound(LONG_PTR lRealHandle, long lPlay);
NETMEDIA_API int	API_CALL	NETMEDIA_RASetVolume(LONG_PTR lRealHandle, WORD wVolume);
NETMEDIA_API int	API_CALL	NETMEDIA_RASetGain(LONG_PTR lRealHandle, double lfGain);
NETMEDIA_API int	API_CALL	NETMEDIA_RACloseRealAudio(LONG_PTR lRealHandle);

//ǰ��ץ��
NETMEDIA_API int	API_CALL	NETMEDIA_SNOpenSnapshot(LONG_PTR* lpSnapshot, const char* szDevIDNO, int nChn);
NETMEDIA_API int	API_CALL	NETMEDIA_SNOpenSnapshotEx(LONG_PTR* lpSnapshot, const char* szDevIDNO, int nChn, unsigned char ucResolution);
NETMEDIA_API int	API_CALL	NETMEDIA_SNSetRealServer(LONG_PTR lSnapshotHandle, const char* szIP, unsigned short usPort, const char* szSession);	
NETMEDIA_API int	API_CALL	NETMEDIA_SNSetSnapMsgCB(LONG_PTR lSnapshotHandle, void* pUsr
													   , void (CALLBACK *FUNMsgCB)(int nMsg, void* pUsr));
NETMEDIA_API int	API_CALL	NETMEDIA_SNSetSnapDataCB(LONG_PTR lSnapshotHandle, void* pUsr
														, void (CALLBACK *FUNDataCB)(const char* pBuf, int nLen, long nPos, void* pUsr));
NETMEDIA_API int	API_CALL	NETMEDIA_SNStartSnapshot(LONG_PTR lSnapshotHandle);
NETMEDIA_API int	API_CALL	NETMEDIA_SNStopSnapshot(LONG_PTR lSnapshotHandle);
NETMEDIA_API int	API_CALL	NETMEDIA_SNCloseSnapshot(LONG_PTR lSnapshotHandle);	

//��ʱǰ��ץ��
NETMEDIA_API int	API_CALL	NETMEDIA_SNOpenSnapshotTimer();
//NETMEDIA_API int	API_CALL	NETMEDIA_SNSetSnapshotTimerInterval(UINT nTime);
NETMEDIA_API int	API_CALL	NETMEDIA_SNSetSnapshotTimerDataCB(void* pUsr
								, void (CALLBACK *FUNDataCB)(const char* szDevIDNO, int nChn, const char* pBuf, int nLen, void* pUsr));
//���ɾ���޸Ķ�ʱץ�ĵ��豸
//nType �������� ��������
#define NETMEDIA_SNAPSHOT_TIMER_DEV_ADD		0	//��Ӷ�ʱץ�ĵ��豸
#define NETMEDIA_SNAPSHOT_TIMER_DEV_DEL		1	//ɾ����ʱץ�ĵ��豸
#define NETMEDIA_SNAPSHOT_TIMER_DEV_MODIFY	2	//�޸Ķ�ʱץ�ĵ��豸
//nTimeSecond - ��ʱץ�ļ��,��λ��
//nIntervalSecond - ����ץ�ļ��,��λ��
//nSnapshotNum - ����ץ����Ŀ
NETMEDIA_API int	API_CALL	NETMEDIA_SNSetSnapshotDev(const char* szDevIDNO, int nChn, int nType, UINT nTimeSecond, UINT nIntervalSecond, UINT nSnapshotNum);
NETMEDIA_API int	API_CALL	NETMEDIA_SNStopSnapshotTimer();


//=============================�ļ�������ͼƬ����¼���ļ���====================================//
NETMEDIA_API int	API_CALL	NETMEDIA_SFOpenSrchFile(LONG_PTR* lpSearchHandle, const char* szDevIDNO, int nLocation, int nAttributenFile);
NETMEDIA_API int	API_CALL	NETMEDIA_SFSetRealServer(LONG_PTR lTalkbackHandle, const char* szIP, unsigned short usPort, const char* szSession);	
NETMEDIA_API int	API_CALL	NETMEDIA_SFSetSearchMsgCB(LONG_PTR lSearchHandle, void* pUsr
														   , void (CALLBACK *FUNMsgCB)(int nMsg, int nParam, void* pUsr));
NETMEDIA_API int	API_CALL	NETMEDIA_SFGetSearchMsg(LONG_PTR lSearchHandle, int* lpMsg, int* lpParam);
NETMEDIA_API int	API_CALL	NETMEDIA_SFSetSearchFileCB(LONG_PTR lSearchHandle, void* pUsr
															, void (CALLBACK *FUNFileCB)(GPSFile_S* pFile, void* pUsr));
NETMEDIA_API int	API_CALL	NETMEDIA_SFStartSearchFile(LONG_PTR lSearchHandle, int nYear, int nMonth, int nDay
															, int nRecType, int nChn, int nBegTime, int nEndTime, int nAlarmType=0);
NETMEDIA_API int	API_CALL	NETMEDIA_SFStartSearchFileEx(LONG_PTR lSearchHandle, int nYearS, int nMonthS, int nDayS, int nBegTime
															 , int nYearE, int nMonthE, int nDayE, int nEndTime, int nRecType
															 , int nChn, int nAlarmType=0);
NETMEDIA_API int	API_CALL	NETMEDIA_SFStartSearchFileMoreEx(LONG_PTR lSearchHandle, GPSRecFileSearchParam_S* pParam);
NETMEDIA_API int	API_CALL	NETMEDIA_SFSetSearchParam(LONG_PTR lSearchHandle, int nParamType);
NETMEDIA_API int	API_CALL	NETMEDIA_SFSetSearchCompanyID(LONG_PTR lSearchHandle, int nCompanyID);
NETMEDIA_API int	API_CALL	NETMEDIA_SFStopSearchFile(LONG_PTR lSearchHandle);
NETMEDIA_API int	API_CALL	NETMEDIA_SFCloseSearchFile(LONG_PTR lSearchHandle);	

//=============================�ļ����أ�ͼƬ����¼���ļ���====================================//
NETMEDIA_API int	API_CALL	NETMEDIA_DFOpenDownFile(LONG_PTR* lpDownHandle, int nAttribute);
NETMEDIA_API int	API_CALL	NETMEDIA_DFSetRealServer(LONG_PTR lDownHandle, const char* szIP, unsigned short usPort, const char* szSession);	
NETMEDIA_API int	API_CALL	NETMEDIA_DFSetDFileMsgCB(LONG_PTR lDownHandle, void* pUsr
														  , void (CALLBACK *FUNMsgCB)(int nMsg, int nParam, void* pUsr));
NETMEDIA_API int	API_CALL	NETMEDIA_DFGetDFileMsg(LONG_PTR lDownHandle, int* lpMsg, int* lpParam);
//ȡ�ļ��������ݣ���λKByte
NETMEDIA_API int	API_CALL	NETMEDIA_DFGetFlowRate(LONG_PTR lDownHandle, int* lpFlowRate);
//�����ط�ʽ����׷�����أ��߱��ϵ�̴�����
NETMEDIA_API int	API_CALL	NETMEDIA_DFStartDownFile(LONG_PTR lDownHandle, GPSFile_S* pFile, char* szDownFile);
NETMEDIA_API int	API_CALL	NETMEDIA_DFStartDownFileW(LONG_PTR lDownHandle, GPSFile_S* pFile, wchar_t* szDownFile);
NETMEDIA_API int	API_CALL	NETMEDIA_DFStopDownFile(LONG_PTR lDownHandle);
NETMEDIA_API int	API_CALL	NETMEDIA_DFCloseDownFile(LONG_PTR lDownHandle);

//˫��Խ�
NETMEDIA_API int	API_CALL	NETMEDIA_TBOpenTalkback(const char* szDevIDNO, int nChn, int nCntMode, LONG_PTR* lpTalkbackHandle);	
NETMEDIA_API int	API_CALL	NETMEDIA_TBSetRealServer(LONG_PTR lTalkbackHandle, const char* szIP, unsigned short usPort, const char* szSession);	
NETMEDIA_API int	API_CALL	NETMEDIA_TBSetTalkbackMsgCallBack(LONG_PTR lTalkbackHandle, void* pUsr, void (CALLBACK *FUNRealMsgCB)(int nMsg, void* pUsr));
NETMEDIA_API int	API_CALL	NETMEDIA_TBSetAudioType(LONG_PTR lTalkbackHandle, int nAudioType);
NETMEDIA_API int	API_CALL	NETMEDIA_TBSetAudioDelay(LONG_PTR lTalkbackHandle, int nMinSecond);
NETMEDIA_API int	API_CALL	NETMEDIA_TBStartTalkback(LONG_PTR lTalkbackHandle);
NETMEDIA_API int	API_CALL	NETMEDIA_TBStopTalkback(LONG_PTR lTalkbackHandle);
NETMEDIA_API int	API_CALL	NETMEDIA_TBPlaySound(LONG_PTR lTalkbackHandle, long lPlay);
NETMEDIA_API int	API_CALL	NETMEDIA_TBSetVolume(LONG_PTR lTalkbackHandle, WORD wVolume);
NETMEDIA_API int	API_CALL	NETMEDIA_TBSetGain(LONG_PTR lTalkbackHandle, double lfGain);
NETMEDIA_API int	API_CALL	NETMEDIA_TBCloseTalkback(LONG_PTR lTalkbackHandle);
//�Խ�ת��
NETMEDIA_API int	API_CALL	NETMEDIA_TBOpenTalkbackTran(const char* szDevIDNO, int nChn, int nCntMode, LONG_PTR* lpTalkbackHandle);	
NETMEDIA_API int	API_CALL	NETMEDIA_TBSetAudioDataCB(LONG_PTR lTalkbackHandle, void* pUsr, void (CALLBACK *FUNAudioDataCB)(const char* pFrameBuf
	, int nFrameLen, int nFrameType, unsigned __int64 llFrameStamp, void* pUsr));
NETMEDIA_API int	API_CALL	NETMEDIA_TBInputAudioData(LONG_PTR lTalkbackHandle, const char* pFrameBuf, int nFrameLen, int nFrameType, unsigned __int64 llFrameStamp);
NETMEDIA_API int	API_CALL	NETMEDIA_TBCloseTalkbackTran(LONG_PTR lTalkbackHandle);	

//�㲥����
NETMEDIA_API int	API_CALL	NETMEDIA_BCOpenBroadcast(LONG_PTR* lpBroadcastHandle);	
NETMEDIA_API int	API_CALL	NETMEDIA_BCSetRealServer(LONG_PTR lBroadcastHandle, const char* szIP, unsigned short usPort, const char* szSession);	
NETMEDIA_API int	API_CALL	NETMEDIA_BCSetBroadcastMsgCallBack(LONG_PTR lBroadcastHandle, void* pUsr, void (CALLBACK *FUNRealMsgCB)(int nMsg, void* pUsr));
NETMEDIA_API int	API_CALL	NETMEDIA_BCStartBroadcast(LONG_PTR lBroadcastHandle);
NETMEDIA_API int	API_CALL	NETMEDIA_BCStopBroadcast(LONG_PTR lBroadcastHandle);
NETMEDIA_API int	API_CALL	NETMEDIA_BCAddDevice(LONG_PTR lBroadcastHandle, const char* szDevIDNO, int nChn); 
NETMEDIA_API int	API_CALL	NETMEDIA_BCDelDevice(LONG_PTR lBroadcastHandle, const char* szDevIDNO, int nChn);
NETMEDIA_API int	API_CALL	NETMEDIA_BCCloseBroadcast(LONG_PTR lBroadcastHandle);

//Զ�̻طŽӿ� PB = PlayBack
// ���ֽӿ����Ӷ�¼����� [2017-6-6 ydl]
// ˵��:PB --> MPB,���Ӳ���:���,�����Ϊ0ʱ,���Ͻӿڹ�����ͬ,�����Ϊ-1ʱ,����ȫ��
NETMEDIA_API int	API_CALL	NETMEDIA_PBOpenPlayBack(LONG_PTR* lpPlaybackHandle);	
NETMEDIA_API int	API_CALL	NETMEDIA_PBSetRealServer(LONG_PTR lPlaybackHandle, const char* szIP, unsigned short usPort, const char* szSession);	
NETMEDIA_API int	API_CALL	NETMEDIA_PBSetPlayMsgCallBack(LONG_PTR lPlaybackHandle, void* pUsr, void (CALLBACK *FUNRealMsgCB)(int nMsg, void* pUsr));
NETMEDIA_API int	API_CALL	NETMEDIA_PBSetFrameDataCallBack(LONG_PTR lPlaybackHandle, void* pUsr, void (CALLBACK *FUNFrameDataCB)(const char* pFrameBuf
	, int nFrameLen, int nFrameType, unsigned __int64 llFrameStamp, void* pUsr));
NETMEDIA_API int	API_CALL	NETMEDIA_PBSetRealDecCallBack(LONG_PTR lPlaybackHandle, void* pUsr
	, void (CALLBACK* FUNRealDecCB)(unsigned char* pY, int nYStride, unsigned char* pU, unsigned char* pV, int nUVStride, 
	int nWidth, int nHeight, unsigned __int64 nStamp, int nType, void* pUsr));

//GPS���ݻص��ӿ�,GPSָ��ΪAVFILEGPSInfo_S�ṹ��
NETMEDIA_API int	API_CALL	NETMEDIA_PBSetGPSInfoCallBack(LONG_PTR lPlaybackHandle, void* pUsr, void (CALLBACK *FUNGPSInfoCB)(void* pGps, unsigned __int64 u64Pts, void* pUsr));
NETMEDIA_API int	API_CALL	NETMEDIA_PBGetPlayMsg(LONG_PTR lPlaybackHandle, int* lpMsg);
//�ط�
NETMEDIA_API int	API_CALL	NETMEDIA_PBStartPlayback(LONG_PTR lPlaybackHandle, GPSFile_S* pFile, int nPlayChannel, int nBegMinSecond, int nEndMinSecond
														 , BOOL bPlayOnlyIFrame, HWND hWnd, BOOL bPriorRGB16=FALSE);
//nPlayChnMask��λ��ʾ��ͬ��ͨ������ʱֻ���Ƕ��豸¼��طţ������ļ����ڶ��ͨ������Ƶʱ
NETMEDIA_API int	API_CALL	NETMEDIA_PBStartPlaybackMul(LONG_PTR lPlaybackHandle, GPSFile_S* pFile, int nPlayChnMask, int nBegMinSecond, int nEndMinSecond
														, BOOL bPlayOnlyIFrame, HWND hWnd[], BOOL bPriorRGB16=FALSE);
//�ط�
NETMEDIA_API int	API_CALL	NETMEDIA_PBStartPlaybackEx(LONG_PTR lPlaybackHandle, GPSRecPlaybackParam_S* pParam, HWND hWnd[], BOOL bPriorRGB16=FALSE);
NETMEDIA_API int	API_CALL	NETMEDIA_PBStopPlayback(LONG_PTR lPlaybackHandle);
//���÷������Ƿ�֧�ֶ�·����,Ĭ��TRUE,����ý���������С��2017-06������ΪFALSE
NETMEDIA_API int	API_CALL	NETMEDIA_PBSetServerMulti(LONG_PTR lPlaybackHandle, BOOL bMulti);
//������¼���ļ�
NETMEDIA_API int	API_CALL	NETMEDIA_PBStartDown(LONG_PTR lPlaybackHandle, GPSFile_S* pFile, int nPlayChannel, int nBegMinSecond, int nEndMinSecond
													 , BOOL bPlayOnlyIFrame, const char* pSaveFile, BOOL bResumeDown=FALSE);
NETMEDIA_API int	API_CALL	NETMEDIA_PBStartDownW(LONG_PTR lPlaybackHandle, GPSFile_S* pFile, int nPlayChannel, int nBegMinSecond, int nEndMinSecond
													 , BOOL bPlayOnlyIFrame, const wchar_t* pSaveFile, BOOL bResumeDown=FALSE);
NETMEDIA_API int	API_CALL	NETMEDIA_PBStopDown(LONG_PTR lPlaybackHandle);
NETMEDIA_API int	API_CALL	NETMEDIA_PBAdjustedWndRect(LONG_PTR lPlaybackHandle);
//ȡ�ļ��������ݣ���λKByte
NETMEDIA_API int	API_CALL	NETMEDIA_PBGetFlowRate(LONG_PTR lPlaybackHandle, int* lpFlowRate);
//��������
NETMEDIA_API int	API_CALL	NETMEDIA_PBPlaySound(LONG_PTR lPlaybackHandle, long lPlay);
NETMEDIA_API int	API_CALL	NETMEDIA_PBPlaySoundEx(LONG_PTR lPlaybackHandle, int nFile, long lPlay);
NETMEDIA_API int	API_CALL	NETMEDIA_PBSetVolume(LONG_PTR lPlaybackHandle, WORD wVolume);
//��ͣ
NETMEDIA_API int	API_CALL	NETMEDIA_PBPause(LONG_PTR lPlaybackHandle, BOOL bPause);
//���ûط��ٶ�,nRate:��16λ(0��ʾ���,1��ʾ����)  ��16λ(�ط��ٶ�)
NETMEDIA_API int	API_CALL	NETMEDIA_PBSetPlayRate(LONG_PTR lPlaybackHandle, int nRate);
//�϶�
NETMEDIA_API int	API_CALL	NETMEDIA_PBSetPlayTime(LONG_PTR lPlaybackHandle, int nMinSecond);
//����ֻ��I֡
NETMEDIA_API int	API_CALL	NETMEDIA_PBSetPlayIFrame(LONG_PTR lPlaybackHandle, BOOL bIFrame);
//�ؼ�֡����
NETMEDIA_API int	API_CALL	NETMEDIA_PBSetPlayBackIFrame(LONG_PTR lPlaybackHandle, BOOL bBackIFrame);
//ȡ�ò��ŵ�����
NETMEDIA_API int	API_CALL	NETMEDIA_PBGetPlayTime(LONG_PTR lPlaybackHandle, int* lpMinSecond);
//ȡ����������
NETMEDIA_API int	API_CALL	NETMEDIA_PBGetDownTime(LONG_PTR lPlaybackHandle, int* lpMinSecond);
//ץ��ͼƬ
NETMEDIA_API int	API_CALL	NETMEDIA_PBCaptureBMP(LONG_PTR lPlaybackHandle, const char* szBmpFile);
NETMEDIA_API int	API_CALL	NETMEDIA_PBCaptureBMPEx(LONG_PTR lPlaybackHandle, int nFile, const char* szBmpFile);
//����һ֡����
NETMEDIA_API int	API_CALL	NETMEDIA_PBPlayOneFrame(LONG_PTR lPlaybackHandle, BOOL bBackward, BOOL bIFrame);

// �ط��ļ�ʱ¼��
NETMEDIA_API int	API_CALL	NETMEDIA_PBStartPlayRecord(LONG_PTR lPlaybackHandle, int nFile, const char* pSaveFile);
NETMEDIA_API int	API_CALL	NETMEDIA_PBStopPlayRecord(LONG_PTR lPlaybackHandle, int nFile);
NETMEDIA_API BOOL	API_CALL	NETMEDIA_PBIsPlayRecord(LONG_PTR lPlaybackHandle, int nFile);

//�ر�Զ�̻ط�
NETMEDIA_API int	API_CALL	NETMEDIA_PBClosePlayback(LONG_PTR lPlaybackHandle);


//͸����ѯ
NETMEDIA_API int	API_CALL	NETMEDIA_QTStartQueryTransparentMgr();
NETMEDIA_API int	API_CALL	NETMEDIA_QTStopQueryTransparentMgr();
NETMEDIA_API int	API_CALL	NETMEDIA_QTOpenQueryTransparent(LONG_PTR* lpQueryTransparent, const char* szDevIDNO);
NETMEDIA_API int	API_CALL	NETMEDIA_QTSetRealServer(LONG_PTR lQueryTransparent, const char* szIP, unsigned short usPort, const char* szSession);	
NETMEDIA_API int	API_CALL	NETMEDIA_QTSetQueryTransparentMsgCB(LONG_PTR lQueryTransparent, void* pUsr
														, void (CALLBACK *FUNMsgCB)(int nMsg, void* pUsr));
NETMEDIA_API int	API_CALL	NETMEDIA_QTSetQueryTransparentDataCB(LONG_PTR lQueryTransparent, void* pUsr
														 , void (CALLBACK *FUNQueryDataCB)(const char* pBuf, int nLen, void* pUsr));
NETMEDIA_API int	API_CALL	NETMEDIA_QTStartQueryTransparent(LONG_PTR lQueryTransparent, int nType, const char* szParam);
NETMEDIA_API int	API_CALL	NETMEDIA_QTStartQueryTransparentEX(LONG_PTR lQueryTransparent, int nType, const char* szParam);
NETMEDIA_API int	API_CALL	NETMEDIA_QTStopQueryTransparent(LONG_PTR lQueryTransparent);
NETMEDIA_API int	API_CALL	NETMEDIA_QTCloseQueryTransparent(LONG_PTR lQueryTransparent);	

//͸�����ڽӿ�
//TransparentPort
NETMEDIA_API int	API_CALL	NETMEDIA_TPOpenTransparentPort(LONG_PTR* lpTransportPort, const char* szDevIDNO);
NETMEDIA_API int	API_CALL	NETMEDIA_TPSetTranPortMsgCB(LONG_PTR lTransportPort, void* pUsr, void (CALLBACK *FUNMsgCB)(int nMsg, void* pUsr));
NETMEDIA_API int	API_CALL	NETMEDIA_TPSetTranPortDataCB(LONG_PTR lTransportPort, void* pUsr, void (CALLBACK *FUNPortDataCB)(int nType, const char* pBuf, int nLen, void* pUsr));
//���ݳ��Ȳ�Ҫ����1024
NETMEDIA_API int	API_CALL	NETMEDIA_TPSendTranPort(LONG_PTR lTransportPort, int nType, const char* pBuf, int nLen);
//ͨ��Ĭ�ϴ�0��ʼ��szParam��ʱ��Ч
NETMEDIA_API int	API_CALL	NETMEDIA_TPStartTran(LONG_PTR lTransportPort, int nChannel, const char* szParam);
NETMEDIA_API int	API_CALL	NETMEDIA_TPStopTran(LONG_PTR lTransportPort);
NETMEDIA_API int	API_CALL	NETMEDIA_TPCloseTransparentPort(LONG_PTR lTransportPort);

#ifdef __cplusplus
}
#endif

#endif
