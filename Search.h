// RecSearch.h: interface for the CRecSearch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECSEARCH_H__9A48B06E_9E34_4F0D_8EF7_27E83EA0985A__INCLUDED_)
#define AFX_RECSEARCH_H__9A48B06E_9E34_4F0D_8EF7_27E83EA0985A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// #define RECORD_FILE_SERARCH_TYPE_LOCAL_DISK	0
// #define RECORD_FILE_SEARCH_TYPE_DEV_DIS		1
// #define RECORD_FILE_SEARCH_TYPE_DOWN_SERVER	2


class CSearch  
{
public:
	//Constructor and destructor
	CSearch(int nSrcType, int nFileType = GPS_FILE_ATTRIBUTE_RECORD);
	virtual ~CSearch();

protected:
	CSearch();

public:
	//Get variable
	static CSearch* GetNewRecSearch(int nSrcType, int nFileType = GPS_FILE_ATTRIBUTE_RECORD);
	void SetWndAndMsg(HWND hWnd, int nSearchMsgCB, int nSearchFileCB);
	long GetHandle() { return m_lHandle; }

public:
	//Search
	virtual void StartSearch(const char* szDevIDNO, int nChn, int nRecType, int nYear, int nMonth, int nDay, int nBegSec, int nEndSec) = 0;
	virtual void StartSearchEx(const char* szDevIDNO, int nChn, int nRecType, int nYear, int nMonth, int nDay, int nBegSec,
							   int nYearEnd, int nMonthEnd, int nDayEnd, int nEndSec) = 0;
	virtual void StopSearch() = 0;

protected:
	//call back function
	static void CALLBACK FUNSearchMsgCB(int nMsg, int nParam, void* pUsr);
	static void CALLBACK FUNSearchFileCB(GPSFile_S* pFile, void* pUsr);
	void	DoSearchMsgCB(int nMsg, int nParam);
	void	DoSearchFileCB(GPSFile_S* pFile);

protected:
	long	m_lHandle;
	int		m_nSearchType;
	HWND	m_hWnd;
	int		m_nSearchMsgCB;
	int		m_nSearchFileCB;
	int		m_nFileType;
};

class CNetSearch : public CSearch
{
public:
	CNetSearch(int nSrcType, int nFileType);
	virtual ~CNetSearch();

private:
	CNetSearch();

public:
	virtual void StartSearch(const char* szDevIDNO, int nChn, int nRecType, int nYear, int nMonth, int nDay, int nBegSec, int nEndSec);
	virtual void StartSearchEx(const char* szDevIDNO, int nChn, int nRecType, int nYear, int nMonth, int nDay, int nBegSec,
		int nYearEnd, int nMonthEnd, int nDayEnd, int nEndSec);
	virtual void StopSearch();

};

typedef void (CALLBACK* FUNDownFileMsgCB)(int nMsg, int nParam, void* pUsr);
class CDownFile
{
public:
	CDownFile(int nFileType);
	virtual ~CDownFile();
private:
	CDownFile();

public:
	int GetDownFlowRate();
	BOOL StartDownFile(GPSFile_S* pFile, char* szFilePath);
	BOOL StopDowndFile();
	void SetWndAndMsg(HWND hWnd, int nDownMsg);	
	void SetDownFileMsgCB(void* pUsr, FUNDownFileMsgCB pfDwonFileMsgCB);
	GPSFile_S* GetFileInfo() { return m_pFile; }

protected:
	static void CALLBACK FUNDownMsgCB(int nMsg, int nParam, void* pUsr);
	void	DoDownMsgCB(int nMsg, int nParam);
	
private:
	long	m_lDownHandle;
	int		m_nFileType;
	HWND	m_hWnd;
	int		m_nMsg;
	void*	m_pUser;
	FUNDownFileMsgCB m_pfDwonFileMsgCB;
	GPSFile_S* m_pFile;
};

#endif // !defined(AFX_RECSEARCH_H__9A48B06E_9E34_4F0D_8EF7_27E83EA0985A__INCLUDED_)
