// VoiceBroadcast.h: interface for the CVoiceBroadcast class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VOICEBROADCAST_H__DEDD57BF_04E9_40F2_9E3A_C242DC287648__INCLUDED_)
#define AFX_VOICEBROADCAST_H__DEDD57BF_04E9_40F2_9E3A_C242DC287648__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*===========================================================================

��Ȩ���� (c) 2009, 

V 1.0

���ߣ�	afu	(imafu@hotmail.com)

������	CVoiceBroadcast

������	�����㲥�࣬����ʵ����

��ƣ�	

��ʷ��	1���������ڣ�2013-06-25

δʵ�֣�
		����㲥��Ϣ�����Խ�ʱ���ڶԽ�λ����ʾ�Խ��¼�
					���㲥ʱ���ڹ㲥λ����ʾ�㲥�¼�
					
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
	LONG_PTR	m_lVoiceCom;
	HWND	m_hVoiceHwnd;
	UINT	m_uiVoiceMsg;
};

#endif // !defined(AFX_VOICEBROADCAST_H__DEDD57BF_04E9_40F2_9E3A_C242DC287648__INCLUDED_)
