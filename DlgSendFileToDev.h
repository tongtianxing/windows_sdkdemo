#pragma once
#include "afxwin.h"


// CDlgSendFileToDev �Ի���

class CDlgSendFileToDev : public CDialog
{
	DECLARE_DYNAMIC(CDlgSendFileToDev)

public:
	CDlgSendFileToDev(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSendFileToDev();

// �Ի�������
	enum { IDD = IDD_DIALOG_SEND_FILE_TO_DEV };
	CListCtrl	m_lstEquipPromote;
	//CBitmap m_ListBmp;
	CString	m_strFilePath;
	CButton m_btnFileDown;
	CButton m_btnPromote;
	CButton m_btnCancel;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual void OnCancel();
	afx_msg void OnBtnFileDown();
	afx_msg void OnBtnPromote();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnMsgUpload(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgPromote(WPARAM wParam, LPARAM lParam);

protected:
	void	LoadLanguage();
	HICON   m_hIcon;
	

	static void CALLBACK FUNUploadMsgCB(int nMsg, int nParam, void* pUsr);
	void	DoUploadMsgCB(int nMsg, int nParam);

	static void CALLBACK FUNPromoteMsgCB(int nMsg, int nParam, void* pUsr);
	void	DoPromoteMsgCB(int nMsg, int nParam);


	void	StopUpload();
	void	StartPromote();
	void    StopPromote();
	void	PromoteNextDevice();
	void    StartContinuePromote();
	void    PromoteContinueNext();
	void	SetUploadProcess(int nProcess);
	void	SetUploadProcessTip(LPCTSTR lpszTip);

	BOOL	CheckFile();
	BOOL	CheckFilePic();

	//void	AddDevList( LongVehicleBase* pVehicle, int nCount );
public:
	void	OnDropDevNode(int nType, int nID);
	void	AddRootNode();
	void	AddGroupNode(int nGroupID);
	//void	AddDevList(mapDevice& mapDev);
	BOOL    FindDeviceItem(int nDevID);
	void    InsertDevItem(int nDevID);
	void    SetCtrlEnable(BOOL bFlag);
	void	SetDevID(int nDevID);

	int m_nDevType;			//�豸�ͺţ�����
	int m_nDevSubType;		//�豸������
	CString m_strVersion;	//�汾��Ϣ
	CString m_strDevType;	//�豸�ͺ�,�ַ�
	CString m_strCurNote;

	CString m_strOldVersion;//������һ�ΰ汾��Ϣ
	CString m_strOldDevType;//������һ���豸�ͺ�,�ַ�

private:
	LONG_PTR	m_lUploadHandle;
	BOOL	m_bUploadSuc;
	BOOL    m_bPromoteSuc;
	GPSDEVUpgradeFile_S m_FileInfo;
	TCHAR	m_szUploadDestFile[MAX_PATH];
	int     m_nlpSvrID;
	LONG_PTR	m_lPromoteHanle;
	BOOL    m_bContinuePromote;
	int     m_nCurRow;
	int		m_nFailCount;
	LONG_PTR    m_lOldUploadHandle;
	BOOL    m_bContinueUpload;
	CComboBox m_cmbFlieType;

	int m_nDevID;


public:
};
