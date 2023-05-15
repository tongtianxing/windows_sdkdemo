// GlobalFont.h: interface for the CGlobalFont class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLOBALFONT_H__F08343DE_09B8_430B_8A54_9AEF1AACC6D7__INCLUDED_)
#define AFX_GLOBALFONT_H__F08343DE_09B8_430B_8A54_9AEF1AACC6D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGlobalFont : public CStaticObject<CGlobalFont>
{
public:
	CGlobalFont();
	virtual ~CGlobalFont();

public:
	void SetTextFont(BYTE lfCharSet, long lHeight, long lWeight, LPCTSTR lpFaceName);
	void SetBoldTextFont(BYTE lfCharSet, long lHeight, long lWeight, LPCTSTR lpFaceName);
	void SetSystemNameTextFont(BYTE lfCharSet, long lHeight, long lWeight, LPCTSTR lpFaceName);
	HGDIOBJ	GetTextFontHandle();
	HGDIOBJ	GetBoldTextFontHandle();
	HGDIOBJ	GetSystemNameTextFontHandle();
	HGDIOBJ	GetLegacyFontHandle();

	void InitDPIFont(BOOL bIsDPI = TRUE);
protected:
	void InitFont();
	void ReleaseFont();

private:
	BOOL	m_bInit;
	CFont	m_fntText;	//全局字体
	CFont	m_fntBoldText; //粗体
	CFont	m_fntSystemName;
	CFont	m_fntLegacyText;
};

#endif // !defined(AFX_GLOBALFONT_H__F08343DE_09B8_430B_8A54_9AEF1AACC6D7__INCLUDED_)
