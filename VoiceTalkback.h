// VoiceTalkback.h: interface for the CVoiceTalkback class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VOICETALKBACK_H__6A6CB4A6_53C9_4BE6_B4EE_492CD21C5535__INCLUDED_)
#define AFX_VOICETALKBACK_H__6A6CB4A6_53C9_4BE6_B4EE_492CD21C5535__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVoiceTalkback  
{
private:
	static CVoiceTalkback*		g_pVoiceTalkback;
	friend CVoiceTalkback*		VOICETalkback();
	friend void	DELTalkback();

private:
	CVoiceTalkback();
	virtual ~CVoiceTalkback();

public:
	int		StartTalkback(LPCTSTR szDevIDNO, int nChn, bool bTBTrac);
	int		StopTalkback();
	int		OpenSound();
	int		CloseSound();
	void	SetTalkbackMsg(HWND hTback, UINT uiMsg);
	void	ChangeVolume(WORD wVolume);

	BOOL	IsTalkback();
	BOOL	CheckDevTalkback(LPCTSTR szDevIDNO);

	static void CALLBACK FUNAudioDataCB(const char* pFrameBuf, int nFrameLen, int nFrameType, unsigned __int64 llFrameStamp, void* pUsr);
	void	DoAudioData(const char* pFrameBuf, int nFrameLen, int nFrameType, unsigned __int64 llFrameStamp);
	void	OpenAudioFile();
	void	CloseAudioFile();
	void	WriteAudioData(const char* pBuf, int nLen);

protected:
	static void CALLBACK FUNTalkbackMsgCB(int nMsg, void* pUsr);
	void	DoTalkbackMsg(int nMsg);

private:
	TCHAR	m_szDevIDNO[32];
	long	m_lTalkback;
	HWND	m_hTalkHwnd;
	UINT	m_uiTalkMsg;
	bool	m_bTBTrac;
	FILE*	m_pFile;
	long	m_lAudioDec;
};

CVoiceTalkback*		VOICETalkback();
void	DELTalkback();

#endif // !defined(AFX_VOICETALKBACK_H__6A6CB4A6_53C9_4BE6_B4EE_492CD21C5535__INCLUDED_)
