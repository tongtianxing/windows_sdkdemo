#ifndef _IDECODER_H_
#define _IDECODER_H_

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the IDECODER_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// AVDECODER_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef LIBAVDECODER_EXPORTS
#define AVDECODER_API __declspec(dllexport)
#else
#define AVDECODER_API __declspec(dllimport)
#endif

#define  API_CALL	WINAPI


#ifdef __cplusplus
extern "C" {
#endif

#define AVDEC_OK		0
#define AVDEC_FALSE	1

#define AVDEC_TYPE_JS	0
#define AVDEC_TYPE_WKP	1

#define AVDEC_STREAM_MODE_FILE			1
#define AVDEC_STREAM_MODE_REAL			2	//ʵʱ��
#define AVDEC_STREAM_MODE_SMOOTH			3	//������

#define AVDEC_SEARCH_FIRST				-1

#define DECODER_FRAME_BUFF_FULL			-7			// ֡������������

#define AVDEC_FILE_NORMAL		0
#define AVDEC_FILE_ALARM			1
#define AVDEC_FILE_ALARM_MOTION	2
#define AVDEC_FILE_ALARM_IO		3
#define AVDEC_FILE_ALARM_IA		4
#define AVDEC_FILE_ALARM_OTHER	5

#define AVDEC_PLAY_FAST_MAX				4
#define AVDEC_PLAY_FAST_RATE				1
#define AVDEC_PLAY_SLOW_MAX				-4
#define AVDEC_PLAY_RATE_NORMAL			0
#define AVDEC_PLAY_RATE_IFRM				3

#define AVDEC_PLAY_END_TAIL				0
#define AVDEC_PLAY_END_HEAD				1

#define AVDEC_PLAY_A_TYPE_G726_40KBPS			1
#define AVDEC_PLAY_A_TYPE_ADPCM					2
#define AVDEC_PLAY_A_TYPE_G726_MEDIA_40KBPS		3
#define AVDEC_PLAY_A_TYPE_G726_MEDIA_32KBPS		4
#define AVDEC_PLAY_A_TYPE_G726_MEDIA_24KBPS		5
#define AVDEC_PLAY_A_TYPE_G726_MEDIA_16KBPS		6
#define AVDEC_PLAY_A_TYPE_G726_32KBPS			7
#define AVDEC_PLAY_A_TYPE_G726_24KBPS			8
#define AVDEC_PLAY_A_TYPE_G726_16KBPS			9
#define AVDEC_PLAY_A_TYPE_G711A					10
#define AVDEC_PLAY_A_TYPE_G711U					11
#define AVDEC_PLAY_A_TYPE_AAC_8KBPS				12
#define AVDEC_PLAY_A_TYPE_AAC_16KBPS			13
#define AVDEC_PLAY_A_TYPE_AMR					14
#define AVDEC_PLAY_A_TYPE_AAC_24KBPS			15
#define AVDEC_PLAY_A_TYPE_ADPCM_IMA				16		//ʹ�ú�˼��ʽ
#define AVDEC_PLAY_A_TYPE_G711A_EX				17		//�Ǻ�˼��ʽ
#define AVDEC_PLAY_A_TYPE_G711U_EX				18		//�Ǻ�˼��ʽ
#define AVDEC_PLAY_A_TYPE_NELLY_8KBPS			19		//Nellymoser

// �ļ����ͺ궨��
#define AVDEC_FILE_FORMAT_SEARCH_ALL			-2	//.*�ļ�,�������������ļ�
#define AVDEC_FILE_FORMAT_UNKNOWN				-1	//��ʶ����ļ�,���޸�
#define AVDEC_FILE_FORMAT_GREC					0	//.grec�ļ�
#define AVDEC_FILE_FORMAT_MP4					1	//.mp4�ļ�

// ��Ƶ�ļ����Żص�Msg
#define AVDEC_FILE_MSG_PROCESS				1	//���ڲ���
#define AVDEC_FILE_MSG_FINISH				2	//�������


#pragma pack(4)
typedef struct _tagIDECFileInfo
{
	SYSTEMTIME tmBeg;
	SYSTEMTIME tmEnd;
	int	nChn;
	int	nRecType;
	int	nTotalMinSecond;
}IDECFileInfo_S, *LPIDECFileInfo_S;

typedef struct _tagIDECParse
{
	long nOffset;
	unsigned __int64 u64Pts;
	long nFrmLen;
}IDECParse_S, *LPIDECParse_S;

typedef struct _tagIDECFrmInfo
{
	int		nMinSecond;
	int		nFrmPos;
	int		nFrmLen;
}IDECFrmInfo_S;

#pragma pack()

AVDECODER_API HANDLE	API_CALL	AVDEC_Initialize(long nType);
AVDECODER_API HANDLE	API_CALL	AVDEC_GetDecHandle();
AVDECODER_API void	API_CALL	AVDEC_UnInitialize(HANDLE hDec);
AVDECODER_API void	API_CALL	AVDEC_SetWaterEable(HANDLE hDec, BOOL bEnable);
AVDECODER_API void	API_CALL	AVDEC_SetAudioGain(HANDLE hDec, double lfGain);

/*-----------------------ȡ���ļ�ͷ�ĳ���------------------------------*/
AVDECODER_API int	API_CALL	AVDEC_GetFileHeadLength(HANDLE hDec, LONG_PTR* lpLength);
AVDECODER_API int   API_CALL	AVDEC_GetFileHead(HANDLE hDec, char* pHeadBuf, int& nLen);
AVDECODER_API int	API_CALL	AVDEC_SetDDrawParam(HANDLE hDec, BOOL bPriorRGB16);
AVDECODER_API int	API_CALL	AVDEC_GetFrmType(HANDLE hDec, int nInFrmType, int* nOutFrmType);


/*---------------------------����------------------------------*/
AVDECODER_API int	API_CALL	AVDEC_OpenPlayHandle(HANDLE hDec, LONG_PTR* lpHandle);
AVDECODER_API int	API_CALL	AVDEC_ClosePlayHandle(LONG_PTR lpHandle);
AVDECODER_API int	API_CALL	AVDEC_SetPlayWnd(LONG_PTR lHandle, HWND hWnd);
AVDECODER_API int	API_CALL	AVDEC_SetPlayWndEx(LONG_PTR lHandle, HWND hWnd, RECT* pstDisplayRect, BOOL bEnable);
AVDECODER_API int	API_CALL	AVDEC_AdjustedWndRect(LONG_PTR lHandle);

/*-----------------------I֡����ת����BMPͼƬ�ļ�------------------------------*/
AVDECODER_API int	API_CALL	AVDEC_IFrameToBMP(LONG_PTR lHandle, char* pIFrame, int nLen, char* szBMPFile);

/*---------------------------������------------------------------*/
AVDECODER_API int	API_CALL	AVDEC_OpenStream(LONG_PTR lHandle, char* pFileHeadBuf, unsigned int nSize, unsigned int nBufPoolSize, BOOL bPriorRGB16=FALSE);
AVDECODER_API int	API_CALL	AVDEC_StreamSetPlayBuffer(LONG_PTR lHandle, int nBufPoolSize);
AVDECODER_API int	API_CALL	AVDEC_SetStreamMode(LONG_PTR lHandle, unsigned int nMode);
AVDECODER_API int	API_CALL	AVDEC_SetStreamAttr(LONG_PTR lHandle, const char* pFileHeadBuf, unsigned int nSize);
AVDECODER_API int	API_CALL	AVDEC_InputStreamData(LONG_PTR lHandle, char* pBuf, unsigned int nSize);
AVDECODER_API int	API_CALL	AVDEC_InputFrameData(LONG_PTR lHandle, const char* pFrame, unsigned int lFrameLen, unsigned int lFrameType, unsigned __int64 u64Stamp);
AVDECODER_API int	API_CALL	AVDEC_CloseStream(LONG_PTR lHandle);
AVDECODER_API int	API_CALL	AVDEC_GetVideoFrameNum(LONG_PTR lHandle, long* lpNum);
AVDECODER_API int	API_CALL	AVDEC_GetSourceBufferRemain(LONG_PTR lHandle, long* lpRemain);
AVDECODER_API int	API_CALL	AVDEC_ResetStream(LONG_PTR lHandle);
AVDECODER_API int	API_CALL	AVDEC_SearchFrame(LONG_PTR lHandle, char* pBuf, int nLen, int nFrmType, IDECFrmInfo_S* pFrm);
AVDECODER_API int	API_CALL	AVDEC_SetDelayTime(LONG_PTR lHandle, DWORD dwMinMinsecond, DWORD dwMaxMinsecond);
AVDECODER_API int	API_CALL	AVDEC_PlayOneFrameData(LONG_PTR lHandle, BOOL bBackward, BOOL bIFrame);
AVDECODER_API int	API_CALL	AVDEC_StartPlayRecord(LONG_PTR lHandle, const void* pSaveFile, int nCoder);
AVDECODER_API int	API_CALL	AVDEC_StopPlayRecord(LONG_PTR lHandle);
AVDECODER_API int	API_CALL	AVDEC_GetPlayRecordStatus(LONG_PTR lHandle);

/*---------------------------�ļ�����------------------------------*/
AVDECODER_API int	API_CALL	AVDEC_OpenFile(LONG_PTR lHandle, const char* szFile, BOOL bPriorRGB16=FALSE);
AVDECODER_API int	API_CALL	AVDEC_CloseFile(LONG_PTR lHandle);
AVDECODER_API int	API_CALL	AVDEC_GetFileInfo(LONG_PTR lHandle, IDECFileInfo_S* pFileInfo);
AVDECODER_API int	API_CALL	AVDEC_Play(LONG_PTR lHandle);
AVDECODER_API int	API_CALL	AVDEC_Stop(LONG_PTR lHandle);
AVDECODER_API int	API_CALL	AVDEC_Pause(LONG_PTR lHandle, long nPause);
AVDECODER_API int	API_CALL	AVDEC_OneByOne(LONG_PTR lHandle);
AVDECODER_API int	API_CALL	AVDEC_PlayOneIFrame(LONG_PTR lHandle, BOOL bBackward);
AVDECODER_API int	API_CALL	AVDEC_SetPlayRate(LONG_PTR lHandle, int Rate);
AVDECODER_API int	API_CALL	AVDEC_GetPlayTime(LONG_PTR lHandle, long* lpMinSecond);
AVDECODER_API int	API_CALL	AVDEC_SetPlayTime(LONG_PTR lHandle, long nMinSecond);
AVDECODER_API int	API_CALL	AVDEC_SeekIFramStamp(LONG_PTR lHandle, unsigned __int64 u64Stamp);
AVDECODER_API int	API_CALL	AVDEC_SetEndCallBack(LONG_PTR lHandle, void* pUsr
													   , void (CALLBACK* EndCBFun)(int nMsg, void* pUsr));

/*---------------------------���ýӿ�------------------------------*/
AVDECODER_API int	API_CALL	AVDEC_PlaySound(LONG_PTR lHandle);
AVDECODER_API int	API_CALL	AVDEC_StopSound(LONG_PTR lHandle);
AVDECODER_API int	API_CALL	AVDEC_SetVolume(LONG_PTR lHandle, WORD nVolume);
AVDECODER_API int	API_CALL	AVDEC_SetGain(LONG_PTR lHandle, double lfGain);
AVDECODER_API int	API_CALL	AVDEC_SetDecCallBack(LONG_PTR lHandle, void* pUsr
														  , void (CALLBACK* DecCBFun)(unsigned char* pY, int nYStride, unsigned char* pU, unsigned char* pV, int nUVStride, 
														  int nWidth, int nHeight, unsigned __int64 nStamp, int nType, void* pUsr));
// �˽ӿڻص������������ [2017-2-9 ydl]
AVDECODER_API int	API_CALL	AVDEC_SetUsrDataBack(LONG_PTR lHandle, void* pUsr
														  , void (CALLBACK *FUNUsrDataCB)(const char* pUsrData
														  , int nDataLen, int nDataType, void* pUsr));
// 
AVDECODER_API int	API_CALL	AVDEC_SetUsrDataBackEx(LONG_PTR lHandle, void* pUsr
									, void (CALLBACK *FUNUsrDataCB)(const char* pUsrData
									, int nDataLen, int nDataType, unsigned __int64 u64Pts, void* pUsr));
AVDECODER_API int	API_CALL	AVDEC_SetDisplayCallBack(LONG_PTR lHandle, void* pUsr
															  , void (CALLBACK* DisplayCBFun)(HDC hDc
															  , int nWidth, int nHeight, unsigned __int64 nStamp
															  , int nWndWidth, int nWndHeight, void* pUsr));
AVDECODER_API int   API_CALL	AVDEC_SetDecCBEx(LONG_PTR lHandle, void* pUsr, void (CALLBACK* DecCBFunEx)(BYTE* pBuf, long nSize, long nWidth, long nHeight, 
												  long nStamp, int nDecodeType, void* pUsr));
AVDECODER_API int	API_CALL    AVDEC_SetSourceBufCallBack(LONG_PTR lHandle, DWORD dwThreShold
															, void (CALLBACK * SourceBufCBFun)(DWORD dwBufSize, DWORD dwUser,void*pResvered)
															, DWORD dwUser, void *pReserved);

AVDECODER_API int	API_CALL	AVDEC_CaptureBMP(LONG_PTR lHandle, const char* szBMPFile);
AVDECODER_API int	API_CALL	AVDEC_CaptureJPEG(LONG_PTR lHandle, const char* szJPGFile);
AVDECODER_API int	API_CALL	AVDEC_FlashWnd(LONG_PTR lHandle);
AVDECODER_API int	API_CALL	AVDEC_SetPlayIFrame(LONG_PTR lHandle, BOOL bIFrame);
AVDECODER_API int	API_CALL	AVDEC_SetPlayBackIFrame(LONG_PTR lHandle, BOOL bIFrame);
AVDECODER_API int	API_CALL	AVDEC_GetPlayStamp(LONG_PTR lHandle, unsigned __int64* u64Stamp);
//����ͼ��ɫ�ʲ���
AVDECODER_API int	API_CALL	AVDEC_SetColorParams (LONG_PTR lHandle, long nBrightness, long nContrast, long nSaturation, long nHue, BOOL bDefault);
//��ȡͼ��ɫ�ʲ���
AVDECODER_API int	API_CALL	AVDEC_GetColorParams(LONG_PTR lHandle, long* pBrightness, long* pContrast, long* pSaturation, long* pHue);
AVDECODER_API int	API_CALL	AVDEC_ShowOSDText(LONG_PTR lHandle, int nOsdIndex, const char* szText, int nLeft, int nTop, int nPos, COLORREF clr);
AVDECODER_API int	API_CALL	AVDEC_SetMirrorMode(LONG_PTR lHandle, int nMode);
AVDECODER_API int	API_CALL	AVDEC_SetZoom(LONG_PTR lHandle, int x, int y, int nZoom);
AVDECODER_API int	API_CALL	AVDEC_SetOffsetStart(LONG_PTR lHandle, BOOL bIsOffset, POINT ptStart);
AVDECODER_API int	API_CALL	AVDEC_SetOffsetEnd(LONG_PTR lHandle, POINT ptEnd);
//=============================¼��洢====================================//
AVDECODER_API int	API_CALL	AVDEC_MakeRecName(HANDLE hDec, SYSTEMTIME* lpBeg, SYSTEMTIME* lpEnd, int nChn, int nRecType, char* szName);
AVDECODER_API int	API_CALL	AVDEC_MakeRecNameEx(HANDLE hDec, const char* szPlate, const char* szAlarmString, SYSTEMTIME* lpBeg, SYSTEMTIME* lpEnd, int nChn, int nRecType, char* szName);
// �޸��ļ���չ��,�ο�AVDEC_FILE_FORMAT_UNKNOWN
AVDECODER_API int	API_CALL	AVDEC_ChangeFileExtension(HANDLE hDec, char* szFile, int nFileFormat = AVDEC_FILE_FORMAT_UNKNOWN);
AVDECODER_API int	API_CALL	AVDEC_MakeRecFind(HANDLE hDec, char* szFind);
AVDECODER_API int	API_CALL	AVDEC_GetRecFileInfo(HANDLE hDec, const char* szFileName, IDECFileInfo_S* lpFileInfo);

//�½��ļ�
// ���ȵ���AVDEC_ChangeFileExtension,�޸��ļ���׺�� [2017-6-16 ydl]
AVDECODER_API int	API_CALL	AVDEC_OpenWriter(HANDLE hDec, LONG_PTR* lpWriter, const char* szFile);
AVDECODER_API int	API_CALL	AVDEC_OpenWriterW(HANDLE hDec, LONG_PTR* lpWriter, const wchar_t* tszFile);
//֧�ֶϵ����� nMinSecond(�ļ�ʱ�� ��λ����)
AVDECODER_API int	API_CALL	AVDEC_OpenWriterEx(HANDLE hDec, LONG_PTR* lpWriter, const char* szFile, int& nMinSecond);
AVDECODER_API int	API_CALL	AVDEC_OpenWriterWEx(HANDLE hDec, LONG_PTR* lpWriter, const wchar_t* tszFile, int& nMinSecond);
AVDECODER_API int	API_CALL	AVDEC_SetFileBeginTime(LONG_PTR lWriter, BOOL bIsCustomBegTime, int nYear, int nMonth, int nDay, int nBegTime );
AVDECODER_API int	API_CALL	AVDEC_SetFileHead(LONG_PTR lWriter, char* pHead, int nLen);
AVDECODER_API int	API_CALL	AVDEC_WriteFrame(LONG_PTR lWriter, const char* pFrame, int nFrmLen, int nFrmType, __int64 ulPts, long* lpBegPos, long* lpEndPos);
AVDECODER_API int	API_CALL	AVDEC_CloseWriter(LONG_PTR lWriter);

//=============================¼�����====================================//
AVDECODER_API int	API_CALL	AVDEC_OpenReader(HANDLE hDec, LONG_PTR* lpReader, const char* szFile);
AVDECODER_API int	API_CALL	AVDEC_ReadFileInfo(LONG_PTR lReader, IDECFileInfo_S* pFileInfo);
AVDECODER_API int	API_CALL	AVDEC_ReadTimeOffset(LONG_PTR lReader, long nMinSecond, long* lpOffset);
AVDECODER_API int	API_CALL	AVDEC_CloseReader(LONG_PTR lReader);

//=============================��Ƶ����====================================//
AVDECODER_API int	API_CALL	AVDEC_OpenAudioCapture(HANDLE hDec, LONG_PTR* lpAudioHandle, void* pUsr
	, void (CALLBACK* FUNAudioDataCB)(char* pAudioData, int nDataLen, void* pUsr));
AVDECODER_API int	API_CALL	AVDEC_OpenAudioCaptureEx(HANDLE hDec, LONG_PTR* lpAudioHandle, int nSampleRate, void* pUsr
	, void (CALLBACK* FUNAudioDataCB)(char* pAudioData, int nDataLen, void* pUsr));
AVDECODER_API int	API_CALL	AVDEC_CloseAudioCapture(LONG_PTR lAudioHandle);

// ��Ƶ���񲢱���
AVDECODER_API int	API_CALL	AVDEC_ACEOpen(HANDLE hDec, LONG_PTR* lpAudioHandle, int nEncType, void* pUsr
	, void (CALLBACK* FUNAudioDataCB)(char* pAudioData, int nDataLen, void* pUsr));
AVDECODER_API int	API_CALL	AVDEC_ACEStartSaveToFile(LONG_PTR lAudioHandle);
AVDECODER_API int	API_CALL	AVDEC_ACEStopSaveToFile(LONG_PTR lAudioHandle);
// ��ȡ������Ƶ������ļ�·��
AVDECODER_API int	API_CALL	AVDEC_ACEGetSavePath(LONG_PTR lAudioHandle, char* szSavePath);
AVDECODER_API int	API_CALL	AVDEC_ACEGetSavePathW(LONG_PTR lAudioHandle, wchar_t* wszSavePath);
// ��ȡ��¼�Ƶ�ʱ��(��λ:����)
AVDECODER_API int	API_CALL	AVDEC_ACEGetTime(LONG_PTR lAudioHandle, int& nMillSecond);
AVDECODER_API int	API_CALL	AVDEC_ACEClose(LONG_PTR lAudioHandle);

//=============================��Ƶ����====================================//
AVDECODER_API int	API_CALL	AVDEC_OpenAudioDecoder(HANDLE hDec, LONG_PTR* lpAudioDecoder);
AVDECODER_API int	API_CALL	AVDEC_AudioDecoderHead(LONG_PTR lAudioDecoder, char *pInBuffer, int nInLen);
AVDECODER_API int	API_CALL	AVDEC_AudioDecoderWaveFormat(LONG_PTR lAudioDecoder, int* lpChannel, int* lpSamplesPerSec, int* lpAvgBytesPerSec, int* lpBitsPerSample);
AVDECODER_API int	API_CALL	AVDEC_AudioDecoderFrame(LONG_PTR lAudioDecoder, char *pInBuffer, int nInLen, char *pOutBuffer, int* lpOutLen);
AVDECODER_API int	API_CALL	AVDEC_CloseAudioDecoder(LONG_PTR lAudioDecoder);

//=============================��Ƶ����====================================//
AVDECODER_API int	API_CALL	AVDEC_OpenAudioEncoder(HANDLE hDec, LONG_PTR* lpAudioEncoder, int nEncType);
AVDECODER_API int	API_CALL	AVDEC_AudioEncoderHead(LONG_PTR lAudioEncoder, char *pOutBuffer, int* lpOutLen);
AVDECODER_API int	API_CALL	AVDEC_AudioEncoderFrame(LONG_PTR lAudioEncoder, char *pInBuffer, int nInLen, char *pOutBuffer, int* lpOutLen);
AVDECODER_API int	API_CALL	AVDEC_AudioEncOneFrame(LONG_PTR lAudioEncoder, char *pInBuffer, int* lpInLen, char *pOutBuffer, int* lpOutLen);
AVDECODER_API int	API_CALL	AVDEC_CloseAudioEncoder(LONG_PTR lAudioEncoder);

//=============================��Ƶ����====================================//
AVDECODER_API int	API_CALL	AVDEC_OpenAudioPlayer(HANDLE hDec, LONG_PTR* lpAudioPlayer);
AVDECODER_API int	API_CALL	AVDEC_SetAudioDelay(LONG_PTR lAudioPlayer, int nMinSecond);
AVDECODER_API int	API_CALL	AVDEC_SetNoDataEmptyCount(LONG_PTR lAudioPlayer, int nCount);
AVDECODER_API int	API_CALL	AVDEC_InputAudioHead(LONG_PTR lAudioPlayer, const char* pAudioData, int nDataLen);
AVDECODER_API int	API_CALL	AVDEC_InputAudioData(LONG_PTR lAudioPlayer, const char *pAudioData, int nDataLen, unsigned __int64 u64Stamp);
AVDECODER_API int	API_CALL	AVDEC_InputAudioFrame(LONG_PTR lAudioPlayer, const char* pFrame, int lFrameLen, unsigned __int64 u64Stamp);
AVDECODER_API int	API_CALL	AVDEC_SetAudioVolume(LONG_PTR lAudioPlayer, WORD wVolume);
AVDECODER_API int	API_CALL	AVDEC_SetAudioPlayerGain(LONG_PTR lAudioPlayer, double lfGain);
AVDECODER_API int	API_CALL	AVDEC_PlayAudioSound(LONG_PTR lAudioPlayer, BOOL bOpen);
AVDECODER_API int	API_CALL	AVDEC_ResetAudioPlayer(LONG_PTR lAudioPlayer);
AVDECODER_API int	API_CALL	AVDEC_CloseAudioPlayer(LONG_PTR lAudioPlayer);

//=============================��·�ط�====================================//
AVDECODER_API int	API_CALL	AVDEC_MPBSetUsrDataBack(LONG_PTR lHandle, int nFile, void* pUsr
	, void (CALLBACK *FUNUsrDataCB)(const char* pUsrData
	, int nDataLen, int nDataType, unsigned __int64 u64Pts, void* pUsr));


AVDECODER_API int	API_CALL	AVDEC_MPBOpenPlayHandle(HANDLE hDec, LONG_PTR* lpHandle, int nFileNum);
AVDECODER_API int	API_CALL	AVDEC_MPBClosePlayHandle(LONG_PTR lHandle);
AVDECODER_API int	API_CALL	AVDEC_MPBSetPlayWnd(LONG_PTR lHandle, HWND* pHwnd);
AVDECODER_API int	API_CALL	AVDEC_MPBAdjustedWndRect(LONG_PTR lHandle);
AVDECODER_API int	API_CALL	AVDEC_MPBPause(LONG_PTR lHandle, BOOL bPause);
AVDECODER_API int	API_CALL	AVDEC_MPBPlayOneFrame(LONG_PTR lHandle, int nFile, BOOL bBackward, BOOL bIFrame);
AVDECODER_API int	API_CALL	AVDEC_MPBSetPlayRate(LONG_PTR lHandle, int nRate);
AVDECODER_API int	API_CALL	AVDEC_MPBGetPlayTime(LONG_PTR lHandle, long* lpMinSecond);
AVDECODER_API int	API_CALL	AVDEC_MPBSeekIFramStamp(LONG_PTR lHandle, unsigned __int64 u64Stamp);

AVDECODER_API int	API_CALL	AVDEC_MPBOpenStream(LONG_PTR lHandle, int* pChn, const char* pFileHeadBuf, int nSize, int nBufPoolSize, BOOL bPriorRGB16);
AVDECODER_API int	API_CALL	AVDEC_MPBStreamSetPlayBuffer(LONG_PTR lHandle, int nBufPoolSize);
AVDECODER_API int	API_CALL	AVDEC_MPBSetStreamAttr(LONG_PTR lHandle, int nFile, const char* pFileHeadBuf, unsigned int nSize);
AVDECODER_API int	API_CALL	AVDEC_MPBInputFrameData(LONG_PTR lHandle, int nChn, const char* pFrame, int lFrameLen, int lFrameType, unsigned __int64 u64Stamp);
AVDECODER_API int	API_CALL	AVDEC_MPBCloseStream(LONG_PTR lHandle);
AVDECODER_API int	API_CALL	AVDEC_MPBGetVideoFrameNum(LONG_PTR lHandle, int nFile, long* lpNum);
AVDECODER_API int	API_CALL	AVDEC_MPBGetVideoFrameMaxSecond(LONG_PTR lHandle, long* lpSecond);
AVDECODER_API int	API_CALL	AVDEC_MPBResetStream(LONG_PTR lHandle, int nFile);
AVDECODER_API int	API_CALL	AVDEC_MPBGetSourceBufferRemain(LONG_PTR lHandle, int nFile, long* lpRemain);

AVDECODER_API int	API_CALL	AVDEC_MPBPlaySound(LONG_PTR lHandle, int nFile);
AVDECODER_API int	API_CALL	AVDEC_MPBStopSound(LONG_PTR lHandle, int nFile);
AVDECODER_API int	API_CALL	AVDEC_MPBSetVolume(LONG_PTR lHandle, WORD nVolume, int nFile);

AVDECODER_API int	API_CALL	AVDEC_MPBCaptureBMP(LONG_PTR lHandle, int nFile, const char* szBMPFile);
AVDECODER_API int	API_CALL	AVDEC_MPBCaptureJPEG(LONG_PTR lHandle, int nFile, const char* szJPGFile);
AVDECODER_API int	API_CALL	AVDEC_MPBFlashWnd(LONG_PTR lHandle, int nFile);
AVDECODER_API int	API_CALL	AVDEC_MPBSetPlayIFrame(LONG_PTR lHandle, BOOL bPlayIFrame);
AVDECODER_API int	API_CALL	AVDEC_MPBSetPlayBackIFrame(LONG_PTR lHandle, BOOL bPlayIFrame);
AVDECODER_API int	API_CALL	AVDEC_MPBGetPlayStamp(LONG_PTR lHandle, unsigned __int64* u64Stamp);
AVDECODER_API int	API_CALL	AVDEC_MPBSetPlayStamp(LONG_PTR lHandle, unsigned __int64 u64Stamp);
AVDECODER_API int	API_CALL	AVDEC_MPBSetColorParams (LONG_PTR lHandle, int nFile, long nBrightness, long nContrast, long nSaturation, long nHue, BOOL bDefault);
AVDECODER_API int	API_CALL	AVDEC_MPBGetColorParams(LONG_PTR lHandle, int nFile, long* pBrightness, long* pContrast, long* pSaturation, long* pHue);
AVDECODER_API int	API_CALL	AVDEC_MPBSetMirrorMode(LONG_PTR lHandle, int nFile, int nMode);
AVDECODER_API int	API_CALL	AVDEC_MPBStartPlayRecord(LONG_PTR lHandle, int nFile, const void* pSaveFile, int nCoder);
AVDECODER_API int	API_CALL	AVDEC_MPBStopPlayRecord(LONG_PTR lHandle, int nFile);
AVDECODER_API int	API_CALL	AVDEC_MPBGetPlayRecordStatus(LONG_PTR lHandle, int nFile);


//=============================��Ƶ�ļ�====================================//
AVDECODER_API int	API_CALL	AVDEC_AFPOpen(HANDLE hDec, LONG_PTR* lpAudioFilePlayer);
AVDECODER_API int	API_CALL	AVDEC_AFPSetFUNMsgCB(LONG_PTR lAudioFilePlayer, void* pUsr, void (CALLBACK* FUNCMsgCB)(int nMsg, int nSecond, void* pUsr));
AVDECODER_API int	API_CALL	AVDEC_AFPStartPlay(LONG_PTR lAudioFilePlayer, const char* szFile);
AVDECODER_API int	API_CALL	AVDEC_AFPStartPlayW(LONG_PTR lAudioFilePlayer, const wchar_t* wszFile);
// ��ȡ�ļ�ʱ��,��λ(����)
AVDECODER_API int	API_CALL	AVDEC_AFPGetTotalTime(LONG_PTR lAudioFilePlayer, int& nTotalMillSeconds);
// ��ȡ�Ѳ��ŵ�ʱ��,��λ(����)
AVDECODER_API int	API_CALL	AVDEC_AFPGetPlayTime(LONG_PTR lAudioFilePlayer, int& nPlayMillSeconds);
AVDECODER_API int	API_CALL	AVDEC_AFPPause(LONG_PTR lAudioFilePlayer, BOOL bPause);
AVDECODER_API int	API_CALL	AVDEC_AFPStopPlay(LONG_PTR lAudioFilePlayer);
AVDECODER_API int	API_CALL	AVDEC_AFPClose(LONG_PTR lAudioFilePlayer);

#ifdef __cplusplus
}
#endif

#endif

