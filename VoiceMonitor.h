// VoiceMonitor.h: interface for the CVoiceMonitor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VOICEMONITOR_H__FE424848_AAF8_47C2_9747_B59AB70D55B3__INCLUDED_)
#define AFX_VOICEMONITOR_H__FE424848_AAF8_47C2_9747_B59AB70D55B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVoiceMonitor  
{
private:
	static CVoiceMonitor*		g_pVoiceMonitor;
	friend CVoiceMonitor*		VOICEMonitor();

	friend void	DELMonitor();
private:
	CVoiceMonitor();
	virtual ~CVoiceMonitor();

public:
	int		StartMonitor(int nDevID, int nChan);
	int		StopMonitor();
	int		PlayMonitorSound(long bPlay);
	void	SetMonitorMsg(HWND hMonitor, UINT uiMsg);
	void	ChangeVolume(WORD wVolume);

	BOOL	IsMonitor();
	BOOL	IsDevMonitor();

	int		GetMonitorDevID();
	BOOL	CheckDevMonitor(int nDevID, int nChan);

protected:
	static void CALLBACK FUNMonitorMsgCB(int nMsg, void* pUsr);
	void	DoMonitorMsg(int nMsg);

private:
	int		m_nMonitorDevID;
	int		m_nMonitorChan;
	
	long	m_lMonitor;
	HWND	m_hMonitorHwnd;
	UINT	m_uiMonitorMsg;
};

CVoiceMonitor*		VOICEMonitor();
void	DELMonitor();

#endif // !defined(AFX_VOICEMONITOR_H__FE424848_AAF8_47C2_9747_B59AB70D55B3__INCLUDED_)
