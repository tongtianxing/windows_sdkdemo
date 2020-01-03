#ifndef _AVSHOW_API_H_
#define _AVSHOW_API_H_

#ifdef LIBAVSHOW_EXPORTS
#define AVSHOW_API __declspec(dllexport)
#else
#define AVSHOW_API __declspec(dllimport)
#endif

#define APICALL WINAPI

#include <mmsystem.h>

// 显示模式修改为镜像和翻转,使用标志位 [2016-12-21 ydl]
// 镜像和旋转只取一个标志位判断,优先判断(镜像:水平->垂直,旋转:90->180->270)
#define AVSHOW_MIRROR_MODE_NORMAL			0			//镜像正常
#define AVSHOW_MIRROR_MODE_LEFTRIGHT		1			//镜像左右翻转(应弃用)
#define AVSHOW_MIRROR_MODE_TOPBOTTOM		2			//镜像上下翻转(应弃用)

#define AVSHOW_MIRROR_MODE_ROTATE180		0x2			//旋转180度
#define AVSHOW_MIRROR_MODE_ROTATE90			0x4			//旋转90度
#define AVSHOW_MIRROR_MODE_ROTATE270		0x8			//旋转270度
#define AVSHOW_MIRROR_MODE_ROTATE			0xF			//旋转

#define AVSHOW_MIRROR_MODE_FLIP_H			0x1			//水平镜像
#define AVSHOW_MIRROR_MODE_FLIP_V			0x10		//垂直镜像
#define AVSHOW_MIRROR_MODE_FLIP				0x11		//水平和垂直镜像

#define AVSHOW_MIRROR_MODE_RATIO			0x20		//实际比例显示



#define AVSHOW_OSD_POS_TOP					0			//OSD顶部显示
#define AVSHOW_OSD_POS_BELOW				1			//OSD底部显示

#define AVSHOW_OSD_COUNT					6			//最多OSD数目


#define	AVSHOW_ZOOM_MAX						8			//图像放大的最大倍数
#define AVSHOW_ZOOM_MIN						1			//....	..	最小倍数

#define AVSHOW_ZOOM_MIN_EX					100			//图像放大倍数(长,宽等比例放大),除以100
#define	AVSHOW_ZOOM_MAX_EX					800		

#define AVSHOW_SPLITSCREEN_LEFT				0x1 //显示一半左边
#define AVSHOW_SPLITSCREEN_RIGHT			0x2 //显示一半右边
#define AVSHOW_SPLITSCREEN_TOP				0x4 //显示一半上边
#define AVSHOW_SPLITSCREEN_BOTTOM			0x8 //显示一半下边

//multiple
#define	AVSHOW_ZOOM_MULTIPLE				1000		//坐标放大倍数
#define AVSHOW_MASAIC_ULTIOPLE				1000		//马赛克区域放大倍数

// 画面色彩设置,暂仅支持D3D模式 [2017-5-8 ydl]
#define AVSHOW_DDCOLOR_BRIGHT_MIN			(-255) //亮度最小值(默认值0)
#define AVSHOW_DDCOLOR_BRIGHT_MAX			(255)
#define AVSHOW_DDCOLOR_CONTRAST_MIN			(-255) //对比度最小值(默认值0)
#define AVSHOW_DDCOLOR_CONTRAST_MAX			(255)
#define AVSHOW_DDCOLOR_SATURATION_MIN		(-255) //饱和度最小值(默认值0)
#define AVSHOW_DDCOLOR_SATURATION_MAX		(255)
#define AVSHOW_DDCOLOR_HUE_MIN				(0) //色度最小值(默认值0)
#define AVSHOW_DDCOLOR_HUE_MAX				(360)

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

	
AVSHOW_API int APICALL AVSHOW_Initialize();
AVSHOW_API int APICALL AVSHOW_UnInitialize();

//-----------------------------------------视频显示部分-------------------------------------//
//创建显示对象
AVSHOW_API int APICALL AVSHOW_DWOpenDraw(LONG_PTR* lpDrawHandle);
AVSHOW_API int APICALL AVSHOW_DWCloseDraw(LONG_PTR lDrawHandle);

//设置显示回调
AVSHOW_API int APICALL AVSHOW_DWSetDisplayCB(LONG_PTR lDrawHandle, void* pUsr, void (CALLBACK* FUNDisplayCB)(int nIndex, HDC hDc
											 , int nWidth, int nHeight, __int64 nStamp
											 , int nWndWidth, int nWndHeight, int nMirrorMode, void* pUsr));
AVSHOW_API int APICALL AVSHOW_DWSetDecCB(LONG_PTR lDrawHandle, void* pUsr, void (CALLBACK* FUNDisplayCB)(BYTE* pBuf, long nSize, long nWidth, long nHeight, 
										long nStamp, int nDecodeType, void* pUsr));

//设置显示窗口
AVSHOW_API int APICALL AVSHOW_DWSetHwnd(LONG_PTR lDrawHandle, HWND hWnd);
//设置显示窗口区域
AVSHOW_API int APICALL AVSHOW_DWSetHwndEx(LONG_PTR lDrawHandle, HWND hWnd, RECT* pstDisplayRect, BOOL bEnable);
//设置窗口序号
AVSHOW_API int APICALL AVSHOW_DWSetIndex(LONG_PTR lDrawHandle, int nIndex);
//
AVSHOW_API int APICALL AVSHOW_DWInitDraw(LONG_PTR lDrawHandle, int nWidth, int nHeight, BOOL bPriorRGB16=FALSE);
//
AVSHOW_API int APICALL AVSHOW_DWFreeDraw(LONG_PTR lDrawHandle);
//调整显示窗口位置
AVSHOW_API int APICALL AVSHOW_DWAdjustedWnd(LONG_PTR lDrawHandle);
//显示YUV420数据
AVSHOW_API int APICALL AVSHOW_DWDrawYUV420(LONG_PTR lDrawHandle, unsigned char* in_Y, int nYPitch, unsigned char* in_U, unsigned char* in_V, int nUVPitch
											, BOOL bZoomed, unsigned __int64 llStamp);  //Draw YUV to Window
//设置OSD
AVSHOW_API int APICALL AVSHOW_DWSetOSDText(LONG_PTR lDrawHandle, int nOsdIndex, const char* szText, int nLeft, int nTop, int nPos, COLORREF clr);
//设置播放区域，进行局部显示
AVSHOW_API int APICALL AVSHOW_DWSetPlayRect(LONG_PTR lDrawHandle, LPRECT lpRect);
//局部放大显示，放大倍数 0 - 增长显示 1 - 1倍 依次增加
AVSHOW_API int APICALL AVSHOW_DWSetZoom(LONG_PTR lDrawHandle, int x, int y, int nZoom);
//设置镜像模式
AVSHOW_API int APICALL AVSHOW_DWSetMirrorMode(LONG_PTR lDrawHandle, int nMode);
//设置图像色彩参数
AVSHOW_API int APICALL AVSHOW_SetColorParams (LONG_PTR lDrawHandle, long nBrightness, long nContrast, long nSaturation, long nHue, BOOL bDefault);
//获取图像色彩参数
AVSHOW_API int APICALL AVSHOW_GetColorParams(LONG_PTR lDrawHandle, long* pBrightness, long* pContrast, long* pSaturation, long* pHue);
//设置马赛克，参数三非零表示增加,否则为删除
AVSHOW_API int APICALL AVSHOW_DWSetMosaics(LONG_PTR lDrawHandle, RECT rcMosaics);
//设置右键点击的坐标
AVSHOW_API int APICALL AVSHOW_DWSetRClickPt(LONG_PTR lDrawHandle, POINT ptRClick);
//添加或删除马赛克区域UpdateMosaics
AVSHOW_API int APICALL AVSHOW_DWUpdateMosaics(LONG_PTR lDrawHandle, BOOL bMode);
//记录图像偏移的起点,参数二表示是否偏移
AVSHOW_API int APICALL AVSHOW_DWSetOffsetStart(LONG_PTR lDrawHandle, BOOL bIsOffset, POINT ptStart);
//记录图像偏移的终点
AVSHOW_API int APICALL AVSHOW_DWSetOffsetEnd(LONG_PTR lDrawHandle, POINT ptEnd);
//可指定播放模式是否强制使用Ddraw
AVSHOW_API int APICALL AVSHOW_SetDdrawMode(BOOL bDdraw);
//获取是否支持D3D
AVSHOW_API BOOL APICALL AVSHOW_IsSupport();
// 获取对象是否为D3D显示
AVSHOW_API BOOL APICALL AVSHOW_IsDrawD3D(LONG_PTR lDrawHandle);

// 初始化硬解码数据(数据为:D3D Device)
AVSHOW_API int APICALL AVSHOW_InitDxva2Device(LONG_PTR lDrawHandle, void** ppD3dDevice);
// 显示硬解码数据,设备无效后,需要重新
AVSHOW_API int APICALL AVSHOW_Dxva2RetrieveData(LONG_PTR lDrawHandle, void* pD3dDevice, void* pSurface);
//设置窗口分屏显示
AVSHOW_API BOOL APICALL AVSHOW_SplitScreen(LONG_PTR lDrawHandle, int nMode);


//-----------------------------------------音频播放-------------------------------------//
AVSHOW_API int APICALL AVSHOW_WVOpenWave(LONG_PTR* lpWaveHandle);
AVSHOW_API int APICALL AVSHOW_WVCloseWave(LONG_PTR lWaveHandle);
//设置音频编码参数
AVSHOW_API int APICALL AVSHOW_WVSetWaveFormat(LONG_PTR lWaveHandle, const WAVEFORMATEX* wfxFormat, int nSize);
//设置填充音频数据回调
AVSHOW_API int APICALL AVSHOW_WVSetWriteWaveCB(LONG_PTR lWaveHandle, void* pUsr, int (CALLBACK* FUNWriteWaveCB)(char* pData, int nSize, void* pUsr));
//开始播放
AVSHOW_API int APICALL AVSHOW_WVPlayWave(LONG_PTR lWaveHandle);
//停止播放
AVSHOW_API int APICALL AVSHOW_WVStopWave(LONG_PTR lWaveHandle);
//停止播放
AVSHOW_API int APICALL AVSHOW_WVPauseWave(LONG_PTR lWaveHandle, BOOL bPause);
//设置音量
AVSHOW_API int APICALL AVSHOW_WVSetVolume(LONG_PTR lWaveHandle, WORD wVolume);

//-----------------------------------------通用函数-------------------------------------//
AVSHOW_API int APICALL AVSHOW_yv12_to_rgb24_c(unsigned char *dst, int dst_stride,
					 const unsigned char *y_src,const unsigned char *u_src,const unsigned char * v_src, 
					 int y_stride, int uv_stride,
					 int width, int height);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _AVSHOW_API_H_ */

