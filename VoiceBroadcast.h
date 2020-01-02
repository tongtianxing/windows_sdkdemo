// VoiceBroadcast.h: interface for the CVoiceBroadcast class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VOICEBROADCAST_H__DEDD57BF_04E9_40F2_9E3A_C242DC287648__INCLUDED_)
#define AFX_VOICEBROADCAST_H__DEDD57BF_04E9_40F2_9E3A_C242DC287648__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*===========================================================================

版权所有 (c) 2009, 

V 1.0

作者：	afu	(imafu@hotmail.com)

类名：	CVoiceBroadcast

描述：	语音广播类，单个实例类

设计：	

历史：	1、生成日期：2013-06-25

未实现：
		处理广播消息，当对讲时，在对讲位置显示对讲事件
					当广播时，在广播位置显示广播事件
					
===========================================================================*/

class CVoiceBroadcast  : public CStaticObject<CVoiceBroadcast>
{
public:
	CVoiceBroadcast();
	virtual ~CVoiceBroadcast();

public:
	int		StartVoiceCom(std::list<int>& lstDev);
	int		StopVoiceCom();
	BOOL	IsBroadcast();
	void	SetVoiceMsg(HWND hVoice, UINT uiMsg);

protected:
	static void CALLBACK FUNVoiceComMsgCB(int nMsg, void* pUsr);
	void	DoVoiceComMsg(int nMsg);	

private:
	long	m_lVoiceCom;
	HWND	m_hVoiceHwnd;
	UINT	m_uiVoiceMsg;
};

#endif // !defined(AFX_VOICEBROADCAST_H__DEDD57BF_04E9_40F2_9E3A_C242DC287648__INCLUDED_)
