// DownObject.h: interface for the CDownObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOWNOBJECT_H__82E5D145_7573_4AB1_B4D8_63E3986E06EC__INCLUDED_)
#define AFX_DOWNOBJECT_H__82E5D145_7573_4AB1_B4D8_63E3986E06EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDownObject  
{
public:
	CDownObject();
	virtual ~CDownObject();

public:
	void	SetDownFileName(const TCHAR* szName) {	_tcsnccpy(m_szDownFileName, szName, sizeof(m_szDownFileName)/sizeof(TCHAR) - 1);	}	
	const TCHAR* GetDownFileName() const	{	return m_szDownFileName;}

public:
	virtual	BOOL StartDown();
	virtual	BOOL StopDown();
	virtual CString	GetDownTitle();

public:
	void	SetDownMsg(HWND hWND, UINT nMsg) {	m_hDownHwnd = hWND; m_uDownMsg = nMsg; }
	void	SetDevInfo(int nDevID, int nChn) {	m_nDevID = nDevID; m_nChn = nChn; }
	int		GetDevID()	{	return m_nDevID; }
	int		GetDevChn()	{	return m_nChn; }

protected:
	static void CALLBACK FUNMsgCB(int nMsg, int nParam, void* pUsr);
	void	DoMsgCB(int nMsg, int nParam);
	static void CALLBACK FUNDataCB(const char* pData, int nDataLen, long nPos, void* pUsr);
	void	DoDataCB(const char* pData, int nDataLen, long nPos);

protected:
	void	PostDownMsg(int wParam, int lParam);
	void	OpenDownFile();
	void	CloseDownFile();

protected:
	TCHAR	m_szDownFileName[MAX_PATH];
	FILE*	m_pFile;
	
	int		m_nDevID;
	int		m_nChn;
	long	m_lHandle;

	HWND	m_hDownHwnd;
	UINT	m_uDownMsg;
};

#endif // !defined(AFX_DOWNOBJECT_H__82E5D145_7573_4AB1_B4D8_63E3986E06EC__INCLUDED_)
