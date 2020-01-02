// DlgSN.cpp : 实现文件
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSN.h"
#include "afxdialogex.h"


IMPLEMENT_DYNAMIC(CDlgSN, CDialogEx)

CDlgSN::CDlgSN(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSN::IDD, pParent)
{

}

CDlgSN::~CDlgSN()
{
}

void CDlgSN::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ST_PIC, m_stPic);

}


BEGIN_MESSAGE_MAP(CDlgSN, CDialog)
END_MESSAGE_MAP()




BOOL CDlgSN::OnInitDialog()
{
	CDialog::OnInitDialog();


	m_stPic.LoadPic(m_strFilePath);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlgSN::SetFilePath(CString strFilePath, int nFileType)
{
	m_strFilePath = strFilePath;
	m_nFileType = nFileType;
}
