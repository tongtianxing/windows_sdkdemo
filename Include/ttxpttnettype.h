#ifndef _TTX_PTT_NET_TYPE_H_
#define _TTX_PTT_NET_TYPE_H_

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


#define TTX_PTT_GROUP_TYPE_NORMAL					1	//普通小组
#define TTX_PTT_GROUP_TYPE_TEMPORARY				2	//临时小组

#define TTX_PTT_STATUS_LEAVE						0	//不处在当前的小组上
#define TTX_PTT_STATUS_ENTER						1	//处于当前小组上

#define TTX_PTT_TALK_MAX_SECOND						30	//每次讲话最长30秒
#define TTX_PTT_TALK_MAX_MIN_SECOND					30000	//每次讲话最长30秒

//PTT相关的结构体定义
//_T_表示设备上报的，通过MDVRPTT_RegPttMessageCB接口返回的
#define TTX_PTT_MESSAGE_T_CHECK_PWD					101	//校验密码，inParam的szParam1为md5值的密码, outParam无内容
#define TTX_PTT_MESSAGE_T_LOGIN						102	//终端登录，inParam无内容, outParam, szParam1返回用户服务器IP(IP1|IP2|IP3)
//nParam1返回群组ID, nParam2返回终端ID, nParam3返回用户服务器端口
#define TTX_PTT_MESSAGE_T_LOGOUT						103	//终端注销，inParam无内容, outParam无内容
#define TTX_PTT_MESSAGE_T_REQUIRE_TALK				104	//请求对讲，inParam：nParam1=0表示停止，1表示开始讲话, nParam2表示终端ID, outParam无内容
#define TTX_PTT_MESSAGE_T_SWITCH_GROUP				105	//切换群组, inParam：nParam1表示群组ID, nParam2表示终端ID, nParam3表示进入或者离开 
//nTerminalID为0时为自己切换群组(只有进入某个群组，没有离开某个群组)
#define TTX_PTT_MESSAGE_T_CREATE_TEMP_GROUP			106	//创建临时群组，inParam：nParam1表示终端ID（和某个终端建立临时群组）,nParam2表示群组名称是否为utf8格式,szParam1临时群组的名字，outParam：nParam1表示群组ID
#define TTX_PTT_MESSAGE_T_ADD_TEMP_GROUP_NEMBER		107	//添加临时小组成员，inParam：szParam1为终端ID列表（ 1234|1235）, 最多128个群组，nParam1表示群组ID, nParam2表示终端数目
#define TTX_PTT_MESSAGE_T_DEL_TEMP_GROUP_NEMBER		108	//移除临时小组成员，inParam：szParam1为终端ID列表（ 1234|1235）, 最多128个群组，nParam1表示群组ID, nParam2表示终端数目
#define TTX_PTT_MESSAGE_T_REMOVE_TEMP_GROUP			109	//移除临时群组，inParam：nParam1为群组ID
#define TTX_PTT_MESSAGE_T_TALK_AUDIO				110	//接收到讲话数据，inParam：szParam1为音频数据，nParam1为音频帧序号，nParam2为数据长度, outParam无内容
#define TTX_PTT_MESSAGE_T_TTS						111	//接收TTS文字，inParam：szParam1为文字数据，nParam1群组ID(不为0表示对某个群组消息消息),nParam2终端id(nParam1为0时有效，表示1对1发送文字信息),nParam3类型

//_S_表示服务器下发的，通过MDVRPTT_SendPttMessage下发给设备
#define TTX_PTT_MESSAGE_S_TALK_EVENT				201	//通知某个用户讲话事件，inParam：nParam1表示群组ID，nParam2表示终端ID，nParam3=0表示停止，1表示开始讲话, outParam无内容
#define TTX_PTT_MESSAGE_S_SWITCH_GROUP				202	//切换群组, inParam：nParam1表示群组ID, nParam2表示终端ID, nParam3表示进入或者离开, nParam4=1强拉强拆或0进入离开  
#define TTX_PTT_MESSAGE_S_TALK_AUDIO				203	//接收到讲话数据，inParam：szParam1为音频数据，nParam1为音频帧序号，nParam2为数据长度, nParam3为群组ID, nParam4为终端ID, outParam无内容
#define TTX_PTT_MESSAGE_S_UPDATE_GROUP_INFO			204	//协同小组信息（如名称）发生变化，inParam：nParam1为群组ID，szParam1为utf8群组名称，szParam2为ansi群组名称, outParam无内容
#define TTX_PTT_MESSAGE_S_UPDATE_GROUP_MEMBER		205	//协同成员变化（增加、删除成员），inParam：nParam1为群组ID, outParam无内容
#define TTX_PTT_MESSAGE_S_APPEND_TO_GROUP			206	//用户添加到协同小组，inParam：nParam1为群组ID, nParam2表示是否为临时群组
#define TTX_PTT_MESSAGE_S_REMOVE_FROM_GROUP			207	//从协同小组中移除，inParam：nParam1为群组ID, nParam2表示为临时群组，nParam3表示操作的终端id
#define TTX_PTT_MESSAGE_S_TTS						208	//发送TTS文字，inParam：szParam1为文字数据，nParam1群组ID(不为0表示对某个群组消息消息),nParam2终端id(nParam1为0时有效，表示1对1发送文字信息),nParam3类型
#define TTX_PTT_MESSAGE_S_UPLOAD_FILE				209	//上传文件，inParam：szParam1为url地址，nParam1群组ID(不为0表示对某个群组消息消息),nParam2终端id(nParam1为0时有效，表示1对1发送文字信息),nParam3类型

#define TTX_PTT_SUC								0	//成功
#define TTX_PTT_ERR_PASSWORD					200	//密码错误
#define TTX_PTT_ERR_ALREADY_LOGIN				201	//已经登录
#define TTX_PTT_ERR_NETWORK						202	//网络错误
#define TTX_PTT_ERR_NO_TALK_RIGHT				203	//未取得讲话权
#define TTX_PTT_ERR_OTHER_TALKING				204	//其它用户正在讲话
#define TTX_PTT_ERR_GROUP_IDLE					205	//没有处于某个群组(空闲状态)
#define TTX_PTT_ERR_GROUP_NO_EXIST				206	//群组不存在
#define TTX_PTT_ERR_NO_GROUP_MEMBER				207	//非群组成员
#define TTX_PTT_ERR_TEMP_GROUP_EXIST			208	//已经存在临时小组（用户同时只能建立一个临时群组）
#define TTX_PTT_ERR_NO_TEMP_GROUP				209	//非临时群组（目前只有临时群组才能添加成员）
#define TTX_PTT_ERR_NO_RIGHT					210	//无权限
#define TTX_PTT_ERR_DATABASE					211	//操作数据库
#define TTX_PTT_ERR_UNKOWN						212	//未知错误
#define TTX_PTT_ERR_OFFLINE						213	//离线状态
#define TTX_PTT_ERR_TERMINAL_NO_EXIST			214	//终端不存在
#define TTX_PTT_ERR_TERMINAL_OFFLINE			215	//终端不在线
#define TTX_PTT_ERR_TERMINAL_TALKING			216	//终端正在讲话，强拉或者强拆会失败
#define TTX_PTT_ERR_IN_TEMP_GROUP				217	//终端处在临时群组中

//PTT相关的结构体定义
typedef struct _tagPTTMsgParam
{
	int		nParam[8];		//参数
	char	szParam1[2048];	//参数1
	char	szParam2[512];	//参数2
	char	szParam3[512];	//参数2
	char	szParam4[1024];	//参数2
}PTTMsgParam_S;


#endif

