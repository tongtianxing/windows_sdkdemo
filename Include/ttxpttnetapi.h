#ifndef _TTX_PTT_NET_API_H_
#define _TTX_PTT_NET_API_H_

#include "ttxdvrnetdef.h"
#include "ttxpttnetdef.h"

/******************************************************************************
  Author        : afu
  Created       : 2017/08/30
  Last Modified :
  Description   : PTT集群对讲接口定义
  History       :
	  1.	Date        : 2017/08/30
		Author      : afu
		Modification: Created file
		
******************************************************************************/

/*
* 注意事项
*   
* 	1、ptt集群对讲库与dvrnet合并一起使用，不能单独使用。在dvrnet的Makefile增加 _TTX_ENABLE_PTT_ 宏，CFLAGS += -D _TTX_ENABLE_PTT_，则为增加集群对讲的功能
*/

/*
1、	版本：	6.1.0.1
		日期：	20170830	
		修改：	创建
*/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @Description: 设置适配层，此接口必须在TTXPTT_StartWork前调用
 * @param: 上层应用需要从CTTXPttWork继承子类，实现相应的接口
 * @return: 0表示成功 
 * @Author: afu	2017-08-30
 */
LIBTTXPTT_API int TTXPTT_SetPttAdapter(CTTXPttWork* pPttWork);


//启动或者停止工作
LIBTTXPTT_API int TTXPTT_StartWork();
LIBTTXPTT_API int TTXPTT_StopWork();


/**
 * @Description:判断是否连接成功
 * @return: 0表示成功 
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_IsLoginSuc();

/**
 * @Description:设置请求超时时间
 * @param: lMinSecond毫秒，默认是5000毫秒
 * @return: 0表示成功 
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_SetRequireTimeout(long lMinSecond);

/**
 * @Description:请求讲话权限, TTXPTT_RequestTalk，sdk会调用InitAudioReader获取音频对象
			InitAudioReader接口可以不实现，此时上层要调用TTXPTT_SendAudio发送音频数据
 * @param:	bTalk: 是否讲话，true为请求讲话权限，false为释放讲话权限
 * @return: 0表示成功，接口同步返回，最多2秒超时。
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_RequestTalk(bool bTalk);

/**
 * @Description:发送音频数据，在TTXPTT_RequestTalk后获取到讲话权限再调用才有效
			发送音频，上层有两种方式
				a、调用TTXPTT_SendAudio, b，重载InitAudioReader接口进行发送数据
					TTXPTT_RequestTalk，sdk会调用InitAudioReader获取音频对象
 * @param: 	pAudio: 音频数据
 			nLength: 数据长度
 * @return: 0表示成功 
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_SendAudio(const char* pAudio, int nLength, _u64long u64Stamp);

/**
 * @Description:发送TTS
 * @param: 	nGroupID: 群组ID(为0时，表示对某个终端发送文字)
 			nTerminalID: 终端ID，群组为0时有效，表示对某个终端发送文字
			nType: 类型（暂时无效）
			szUtf8Text：文字信息, 长度不超过512
 * @return: 0表示成功 
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_SendTts(int nGroupID, int nTerminalID, int nType, const char* szUtf8Text);

/**
 * @Description:切换群组，强拉，强拆
 * @param: nGroupID: 群组ID
 * @param: nTerminalID:终端ID，如果nTerminalID为0表示将自己换组
 * @param: nEnter    1为进入群组(强拉), 0为离开群组(强拆)
 				nTerminalID为0时为自己切换群组(只有进入某个群组，没有离开某个群组)
 * @return: 0表示成功，接口同步返回，最多2秒超时。
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_SwitchGroup(int nGroupID, int nTerminalID, int nEnter);

/**
 * @Description: 创建临时群组，调用接口用用户进入到临时群组中
 * @param: szName: 群组名称,暂时无效
 * @param: bNameUtf8 =1为utf格式的名称，=0为ansi
 * @param: nTerminalID: 终端ID, 与某个终端一起创建群组，单呼
 * @param: nGroupID: 返回临时群组ID
 * @return: 0表示成功，接口同步返回，最多2秒超时。
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_CreateTempGroup(const char* szName, int bNameUtf8, int nTerminalID, int& nGroupID);

/**
 * @Description: 增加群组成员，调用接口用用户进入到临时群组中
 * @param: nGroupID: 群组ID
 * @param: pArrTerminalID: 添加成员到群组中，并将成员切换到此群组
 * @param: nTerminalCount: 终端数目
 * @return: 0表示成功，接口同步返回，最多2秒超时
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_AddTempGroupMember(int nGroupID, int* pArrTerminalID, int nTerminalCount);

/**
 * @Description: 删除群组成员，调用接口用用户进入到临时群组中
 * @param: nGroupID: 群组ID
 * @param: pArrTerminalID: 添加成员到群组中，并将成员切换到此群组
 * @param: nTerminalCount: 终端数目
 * @return: 0表示成功，接口同步返回，最多2秒超时
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_DelTempGroupMember(int nGroupID, int* pArrTerminalID, int nTerminalCount);

/**
 * @Description: 移除临时群组
 * @param: nGroupID: 群组ID
 * @return: 0表示成功，接口同步返回，最多2秒超时
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_RemoveTempGroup(int nGroupID);

/**
 * @Description:获取用户的群组列表, 异步接口
 * @  先 TTXPTT_ReadGroupList，数据等待TTXPTTPfnReadInformationCB返回，再TTXPTT_CloseReadHandle
 * @param: lpReadHandle返回读取对象句柄，TTXPTT_CloseReadHandle使用
 * @param: pUsr: 用户自定义数据
 * @param: pfnReadInfoCB: 回调函数
 * @return: 0表示成功
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_ReadGroupList(long* lpReadHandle, void* pUsr, TTXPTTPfnReadInformationCB pfnReadInfoCB);

/**
 * @Description:获取群组成员列表，可以一次获取多个群组的成员
 * @param: lpReadHandle返回读取对象句柄，TTXPTT_CloseReadHandle使用
 * @param: pArrGroupID群组ID列表
 * @param: nGroupCount群组数目
 * @param: pUsr: 用户自定义数据
 * @param: pfnReadInfoCB: 回调函数
 * @return: 0表示成功
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_ReadGroupMember(long* lpReadHandle, int* pArrGroupID, int nGroupCount, void* pUsr, TTXPTTPfnReadInformationCB pfnReadInfoCB);

/**
 * @Description: 
 * @  先 TTXPTT_UploadFile，数据等待TTXPTTPfnReadInformationCB返回，再TTXPTT_CloseReadHandle
 * @param: lpReadHandle返回读取对象句柄，TTXPTT_CloseReadHandle使用
 * @param: nGroupID表示向某个群组的用户发音频文件，当为0时nTerminalID有效表示向某个终端发
 * @param: nFileType文件类型  TTX_FILE_AUDIO(4)表示音频文件
 * @param: szFile: 文件绝对路径
 * @param: nTotalSecond: 文件总时长
 * @param: pUsr: 用户自定义数据
 * @param: pfnReadInfoCB: 回调函数
 * @return: 0表示成功
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_UploadFile(long* lpReadHandle, int nGroupID, int nTerminalID, int nFileType, const char* szFile, int nTotalSecond, void* pUsr, TTXPTTPfnReadInformationCB pfnReadInfoCB);
//上传音频到缓存
LIBTTXPTT_API int TTXPTT_UploadBuffer(long* lpReadHandle, int nGroupID, int nTerminalID, int nFileType, const char* pBuffer, int nBufLen, int nTotalSecond, void* pUsr, TTXPTTPfnReadInformationCB pfnReadInfoCB);

/**
 * @Description: 
 * @  先 TTXPTT_ReadGroupList，数据等待TTXPTTPfnReadInformationCB返回，再TTXPTT_CloseReadHandle
 * @param: lpReadHandle返回读取对象句柄，TTXPTT_CloseReadHandle使用
 * @param: szUrl文件路径，通过CTTXPttWork的DoFile接口返回
 * @param: szSavePath: 文件的存储路径
 * @param: pUsr: 用户自定义数据
 * @param: pfnReadInfoCB: 回调函数
 * @return: 0表示成功
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_DownFile(long* lpReadHandle, const char* szUrl, const char* szSavePath, void* pUsr, TTXPTTPfnReadInformationCB pfnReadInfoCB);
//下载音频到缓存中
//通过回调的nDataType == TTX_PTT_READ_DATA_TYPE_AUDIO_FILE_BUFFER 和 (TTXPttAudioFileBuffer_S*)pData返回
LIBTTXPTT_API int TTXPTT_DownBuffer(long* lpReadHandle, const char* szUrl, void* pUsr, TTXPTTPfnReadInformationCB pfnReadInfoCB);

/**
 * @Description:关闭获取对象
 * @param: lReadHandle: 用户读取对象句柄
 * @return: 0表示成功
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_CloseReadHandle(long lReadHandle);

/**
 * @Description:获取多少毫秒无数据
 * @return: 返回时间差(毫秒) 
 * @Author: 
 */
LIBTTXPTT_API _u64long TTXPTT_GetTimeNoRecvData();


#ifdef __cplusplus
}
#endif 


#endif

