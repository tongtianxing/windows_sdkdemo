// DownSnapshot.h: interface for the CDownSnapshot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOWNSNAPSHOT_H__CB2B636B_CFC6_48B1_B4D5_D68D677007F8__INCLUDED_)
#define AFX_DOWNSNAPSHOT_H__CB2B636B_CFC6_48B1_B4D5_D68D677007F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DownObject.h"

class CDownSnapshot : public CDownObject
{
public:
	CDownSnapshot();
	virtual ~CDownSnapshot();

public:
	virtual	BOOL StartDown();
	virtual	BOOL StopDown();
	virtual CString	GetDownTitle();

protected:
	static void CALLBACK FUNRealMsgCB(int nMsg, void* pUsr);
	void	DoRealMsgCB(int nMsg);

	void DoFinished();
	BOOL DecodeI2JPG(FILE* pFile, CString& strJPGFile);

};

#endif // !defined(AFX_DOWNSNAPSHOT_H__CB2B636B_CFC6_48B1_B4D5_D68D677007F8__INCLUDED_)
