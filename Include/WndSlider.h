#pragma once

class CImgBase;
class CWndSlider : public CWnd
{

public:
	CWndSlider();

public:
	virtual ~CWndSlider();

protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

protected:
	void	DrawSlider(HDC hDc, RECT rcClient);
	void	DrawSliderCompact(HDC hDc, RECT rcClient);
	void	UpdateThunmPos(int nX);
	void	NotifyMove();

public:
	void	SetBkColor(COLORREF clr);
	void	LoadBgImg(LPCTSTR lpszImage);
	void	LoadThumbNormalImg(LPCTSTR lpszImage);
	void	LoadThumbOverImg(LPCTSTR lpszImage);
	void	LoadChnUsedImg(LPCTSTR lpszImage);
	void	LoadChnBgImg(LPCTSTR lpszImage);
	void	SetRange(int nMax) {	m_nRangeMax = nMax;}
	void	SetTickCount(int nCount) {	m_nTickCount = nCount; }
	void	SetCurPos(int nPos);
	int		GetCurPos();
	void	SetChnOffset(int nLeft, int nRight) {	m_nLeftOffset = nLeft;	m_nRightOffset = nRight;	}
	void	SetChannelHeight(int nHeight)	{	m_nChannelHeight = nHeight; }
	void	SetTimeMode(BOOL bTime) {	m_bTimeMode = bTime; }
	void	SetSliderMsg(UINT nMsg)	{	m_nSliderMsg = nMsg; }
	void	SetSliderMsgMove(UINT nMsg)	{	m_nSliderMsgMove = nMsg; }
	void	SetThumbWidth(int nWidth)	{	m_nThumbWidth = nWidth; }
	void	SetDrawCompact(BOOL bEnabled) { m_bDrawCompact = bEnabled; }
		
private:
	COLORREF m_clrBK;
	COLORREF m_clrTick;
	CImgBase*	m_ImgBG;
	CImgBase*	m_ImgThumbNormal;
	CImgBase*	m_ImgThumbOver;
	CImgBase*	m_ImgChnUsed;
	CImgBase*	m_ImgChnBg;
	double	m_dwPosWidth;
	RECT	m_rcThumb;
	RECT	m_rcChannel;
	int		m_nLeftOffset;
	int		m_nRightOffset;
	int		m_nChannelHeight;
	int		m_nThumbWidth;

	CString	m_strTime;
	int		m_nRangeMax;
	int		m_nTickCount;
	int		m_nCurPos;
	BOOL	m_bMoveThumb;

	BOOL	m_bTimeMode;

	UINT	m_nSliderMsg;
	UINT	m_nSliderMsgMove;

	BOOL	m_bDrawCompact;
};
