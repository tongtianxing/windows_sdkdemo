// Playback.h: interface for the CPlayback class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYBACK_H__6F400B06_15E6_4AC4_BEFC_40670EFBA3B3__INCLUDED_)
#define AFX_PLAYBACK_H__6F400B06_15E6_4AC4_BEFC_40670EFBA3B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MSG_PALYBACK_FINISHED	WM_USER+0x1
#define MSG_PALYBACK_FAILED		WM_USER+0x2
#define MSG_PALYBACK_DOWN_FINISHED	WM_USER+0x3

class CPlayback  
{
public:
	CPlayback();
	virtual ~CPlayback();

	void Init();
	void Uninit();
	void SetMsgWnd(HWND hWnd, UINT uiMsg);
	void SetProgressMax(int nProgressMax);

	int Play(GPSFile_S* pFile, int nChannel, int nBegMinSecond, int nEndMinSecond, BOOL bPlayOnlyIFrame, HWND hWnd);
	int Down(GPSFile_S* pFile, int nChannel, int nBegMinSecond, int nEndMinSecond, BOOL bPlayOnlyIFrame, const char* pSaveFile, BOOL bResumeDown);
	int Pause(BOOL bPause);
	int StopPlay();
	int StopDown();
	int GetFlowRate(int* lpFlowRate);
	int PlaySound(long lPlay);
	int SetVolume(WORD wVolume);
	int SetPlayProgress(int nProcess);
	int SetPlayIFrame(BOOL bIFrame);
	int GetPlayProgress(int& nProgress, CString& strTime);
	int GetDownProgress(int& nProgress);
	int GetDownTime(int& nDownMinSecond);
	int CaptureBMP(LPCTSTR szBmpFile);
	int AdjustedWndRect();

	//(s)
	int GetFileSecond();
	//(ms)
	int GetFileMinSecond();

	void GetFileDevAndChannel(TCHAR* szDevIDNO, int nSize, int& nChannel);
protected:
	static void CALLBACK FUNPlayMsgCB(int nMsg, void* pUsr);
	void	DoPlayMsgCB(int nMsg);

private:
	long m_lPlayback;
	HWND m_hWndMsg;
	HWND m_hWndViedo;
	UINT m_uiMsg;
	GPSFile_S m_File;
	int m_nChannel;
	int m_nProgressMax;
};

#endif // !defined(AFX_PLAYBACK_H__6F400B06_15E6_4AC4_BEFC_40670EFBA3B3__INCLUDED_)
