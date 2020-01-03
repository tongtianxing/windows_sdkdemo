#ifndef _TTX_PTT_NET_DEF_H_
#define _TTX_PTT_NET_DEF_H_

/******************************************************************************
  Author        : afu
  Created       : 2017/08/30
  Last Modified :
  Description   : 集群对讲网络库通用信息定义
  History       :
	  1.	Date        : 2017/08/30
		Author      : leeafu
		Modification: Created file
******************************************************************************/

#ifdef WIN32

	#ifdef LIBTTXPTT_EXPORTS
	#define LIBTTXPTT_API __declspec(dllexport)
	#else
	#define LIBTTXPTT_API __declspec(dllimport)
	#endif

#else

	#define LIBTTXPTT_API

#endif

#include "ttxdvrnetdef.h"
#include "ttxpttnettype.h"

#define TTX_PTT_VERSION 		"V6.1.5 20180613"

#define TTX_PTT_READ_DATA_TYPE_FINISH			1	//数据读取结束
#define TTX_PTT_READ_DATA_TYPE_FAILED			2	//数据读取失败
#define TTX_PTT_READ_DATA_TYPE_GROUP_INFO		3	//群组信息
#define TTX_PTT_READ_DATA_TYPE_GROUP_MEMBER		4	//群组成员
#define TTX_PTT_READ_DATA_TYPE_AUDIO_FILE_BUFFER	5	//音频文件缓存数据


#pragma pack(4)

typedef struct _tagTTXPttGroupInfo
{
	int nGroupID;		//分组ID
	char szName[64];	//分组名称
	int nCompanyID;		//那个公司的群组
	char cType;			//类型1普通小组，2临时小组
	char cReserve[3];	//保留字段
	int nCreater;		//创建者
	char szRemarks[64];	//备注信息
}TTXPttGroupInfo_S, *LPTTXPttGroupInfo_S;

typedef struct _tagTTXPttGroupMember
{
	int nGroupID;		//属于那个群组
	int nTerminalID;	//成员ID
	char szDevIDNO[64];	//设备编号（如果为调度员，则为调度员的账号）
	char szName[64];	//成员名称
	char bDefault;		//是否为默认群组
	char cLevel;		//级别
	char cTerminaType;	//终端类型, 4警员，5调度用户，0为车载
	char cReserve[9];	//保留字段
}TTXPttGroupMember_S, *LPTTXPttGroupMember_S;

typedef struct _tagTTXPttAudioFileBuffer
{
	const char* pBuffer;
	int	nBufLen;
	char cReserve[32];
}TTXPttAudioFileBuffer_S, *LPTTXPttAudioFileBuffer_S;


#pragma pack()

//获取信息的数据回调，读取群组列表和群组成员时使用此回调
//TTXPTT_Read 开头的函数使用此回调
//@nDataType	TTX_PTT_READ_DATA_TYPE_GROUP_INFO 时pData = TTXPttGroupInfo_S
//				TTX_PTT_READ_DATA_TYPE_GROUP_MEMBER 时pData = TTXPttGroupMember_S
//				TTX_PTT_READ_DATA_TYPE_FINISH读取结束,可以调用TTXPTT_CloseReadHandle关闭获取对象
//				TTX_PTT_READ_DATA_TYPE_FAILED读取失败,可以调用TTXPTT_CloseReadHandle关闭获取对象
//@pUsr		用户自定义数据
typedef void(* TTXPTTPfnReadInformationCB)(int nDataType, void* pData, void* pUsr);

/**
 * @Description:网络服务基类
 * @Author: afu	2017-08-30
 */
class LIBTTXPTT_API CTTXPttWork
{
public:
	CTTXPttWork() 
	{
		m_nTerminalID = 0;
		m_nPttHeartInterval = 10;
	}
	virtual ~CTTXPttWork(){}

public:
	//
	//ptt 消息通知
	//@nMessage: 消息类型,不同的消息参数都不一样，具体见消息定义
	//@nParam1: 消息参数1
	//@nParam2: 消息参数2
	//@pParam3: 消息参数3
	//virtual void DoPttMsg(int nMessage, int nParam1, int nParam2, void* pParam3) {}

	//登录消息
	//@bSuc: 登录成功或者失败
	//@nGroupID：对应的当前的群组ID
	//@nTerminalID: 当为登录成功时, 为本终端自身的ID
	//@nError: 表示出错原因，当为出错时有效TTX_PTT_ERR_PASSWORD\TTX_PTT_ERR_NETWORK\TTX_PTT_ERR_ALREADY_LOGIN
	virtual void DoLogin(bool bSuc, int nGroupID, int nTerminalID, int nError) {}


	//接收到讲话音频
	//@nTerminalID: 终端ID，表示那个终端在讲话
	//@bStart: true表示开始,false表示停止
	virtual void DoTalk(int nGroupID, int nTerminalID, bool bStart) {}

	//接收到讲话音频
	//@nGroupID: 群组ID
	//@nTerminalID: 终端ID
	//@nAudioIndex: 音频索引，每次讲话时，从0开始
	//@pAudio: 音频数据
	//@nLength: 音频长度
	virtual void DoRecvAudio(int nGroupID, int nTerminalID, int nAudioIndex, const char* pAudio, int nLength, _u64long u64Stamp) {}

	//切换群组(被强拉或者强拆)
	//@nGroupID: 群组ID
	//@nTerminalID: 终端ID，如果终端ID为0表示本终端切换群组
	//@nEnter: 进入或者离开
	//@bForce: 1为强拉强拆，0为进入离开
	virtual void DoSwitchGroup(int nGroupID, int nTerminalID, int nEnter, int bForce) {}
	
	//群组信息更新
	//@nGroupID: 群组ID
	//@szUtf8Name: 群组名称
	virtual void DoUpdateGroupInfo(int nGroupID, const char* szUtf8Name, const char* szAnsiName) {}

	//群组成员发生变化，需要重新去后台获取群组成员信息
	//如果群组ID不存在，则需要去服务器上把群组信息整个刷新回来，新增临时群组时，会出现这个情况
	//@nGroupID: 群组ID
	virtual void DoUpdateGroupMember(int nGroupID) {}

	//把用户添加到某个小组 ，需要重新去后台获取群组成员信息
	//@nGroupID: 群组ID
	//@bTempGroup: 是否为临时群组
	virtual void DoAppendToGroup(int nGroupID, int bTempGroup) {}

	//从协同小组中移除，将群组结点删除
	//@nGroupID: 群组ID
	//@bTempGroup: 是否为临时群组
	//@nTerminalID: 那个终端删除了群组
	virtual void DoRemoveFromGroup(int nGroupID, int bTempGroup, int nTerminalID) {}

	//接收到文字信息
	//@nGroupID: 为0时表示1对1发送消息，不为0时，表示给某个群组的用户发送消息
	//@nTerminalID: 当群组ID为0时有效，表示给此终端发送文字信息
	//@nType: 暂时无效
	//@nSendTerID: 表示发送文字的用户
	//@szUtf8Text: 语言内容
	virtual void DoTts(int nGroupID, int nTerminalID, int nType, int nSendTerID, const char* szUtf8Text) {}

	//接收到文件，目前只支持音频文件
	//@pTm：发送时间
	//@nTotalSecond：文件时长
	//@nGroupID：为0时表示1对1发送消息，不为0时，表示给某个群组的用户发送消息
	//@nTerminalID：表示发送文字的用户
	//@nType：文件类型，4（TTX_FILE_AUDIO）表示音频文件
	//@nSendTerID：发送者ID
	//@szUrl：文件链接
	virtual void DoFile(const struct tm* pTm, int nTotalSecond, int nGroupID, int nTerminalID, int nType, int nSendTerID, const char* szUrl) {}

public:
	int 	GetTerminalID() {		return m_nTerminalID;	}
	
	//获取ptt心跳间隔(秒)
	int		GetPttHeartInterval() {	return m_nPttHeartInterval;	}
	//设置ptt心跳间隔
	void	SetPttHeartInterval(int nSecond) {	m_nPttHeartInterval = nSecond;	}
	
protected:
	int		m_nTerminalID;	//本终端自身的ID
	int				m_nPttHeartInterval;	//心跳发送间隔, 单位秒
};

#endif

