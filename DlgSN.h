#pragma once


class CDlgSN : public CDialog
{
	DECLARE_DYNAMIC(CDlgSN)

public:
	CDlgSN(CWnd* pParent = NULL);
	virtual ~CDlgSN();

	enum { IDD = IDD_DIALOG_SN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	void SetFilePath(CString strFilePath, int nFileType);

private:
	CStPicture	m_stPic;
	CString m_strFilePath;
	int		m_nFileType;
};
