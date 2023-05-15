#ifndef _WND_PUBLIC_H_
#define _WND_PUBLIC_H_

#ifndef __AFX_H__
#error Only for MFC project
#endif



template <class T>
void CustomCreateDlgBegin(T** pDlg)
{
	CustomCreateDlgBegin(*pDlg);
}

template <class T>
void CustomCreateDlgBegin(T*& pDlg)
{
	if (pDlg == NULL)
	{
		pDlg = new T;
	}
}

template <class T>
void CustomCreateDlgEnd(T** pDlg, CWnd* pParent, int nCmdShow = SW_HIDE, BOOL bCenter = FALSE)
{
	CustomCreateDlgEnd(*pDlg, pParent, nCmdShow, bCenter);
}

template <class T>
void CenterDlg(T* pDlg, CWnd* pAlternateOwner = NULL)
{
	if (pDlg)
	{
		if (pAlternateOwner)
		{
			pDlg->CenterWindow(pAlternateOwner);
		}
		else
		{
			pDlg->CenterWindow(CWnd::FromHandle(::GetDesktopWindow()));
		}
	}
}
template <class T>
void CustomCreateDlgEnd(T*& pDlg, CWnd* pParent, int nCmdShow = SW_HIDE, BOOL bCenter = FALSE)
{
	if (pDlg)
	{
		pDlg->Create(T::IDD, pParent);
		if (pDlg->GetSafeHwnd())
		{
			pDlg->ShowWindow(nCmdShow);
			if (bCenter)
			{
				CenterDlg(pDlg);
			}
		}
		else
		{
			SAFE_DELETE_OBJECT(pDlg);
		}
	}
}

template <class T>
void CustomCreateDlg(T** pDlg, CWnd* pParent, int nCmdShow = SW_HIDE, BOOL bCenter = FALSE)
{
	CustomCreateDlg(*pDlg, pParent, nCmdShow, bCenter);
}
template <class T>
void CustomCreateDlg(T*& pDlg, CWnd* pParent, int nCmdShow = SW_HIDE, BOOL bCenter = FALSE)
{
	if (pDlg == NULL)
	{
		CustomCreateDlgBegin(pDlg);
		CustomCreateDlgEnd(pDlg, pParent, nCmdShow, bCenter);
	}
}
template <class T>
void ShowDlg(T* pDlg, BOOL bCenter = TRUE, CWnd* pAlternateOwner = NULL)
{
	if (pDlg)
	{
		if (!pDlg->IsWindowVisible())
		{
			if (bCenter)
			{
				CenterDlg(pDlg, pAlternateOwner);
			}
		}
		pDlg->ShowWindow(SW_SHOW);
		pDlg->SetForegroundWindow();
	}
}

template <class T>
void DestroyDlg(T** pDlg)
{
	DestroyDlg(*pDlg);
}

template <class T>
void DestroyDlg(T*& pDlg)
{
	if (pDlg)
	{
		pDlg->DestroyWindow();
		ASSERT(NULL == pDlg->GetSafeHwnd());
		SAFE_DELETE_OBJECT(pDlg);
	}
}


void	CloseAllModalDialog(HWND hParent);
void	CloseProcessAllDialog();

void	SetForeground(HWND hWnd);

// �������Ϊ����
void	SetHandCursor();


namespace _nsCWnd
{
	// ��ȡ�ؼ����ı�(ID=-1��ʾ��ȡ�Լ����ı�),ɾ�����ҵĿո�
	CString GetCtrlText(CWnd* pParent, int nCtrl = -1);


	// ��ȡ�����ؼ����Ͻǵ������,��1Ϊ׼,2 �� 1
	BOOL GetPointDiff(CWnd* pParent, int nCtrlID1, int nCtrlID2, int& nX, int& nY);
	BOOL GetPointDiff(CWnd* pCtrlWnd1, CWnd* pCtrlWnd2, int& nX, int& nY);

	// �����ƶ��ؼ�,�ڵ�ǰλ�õĻ������ƶ�
	void BetchMoveCtrl(CWnd* pParent, int* pCtrlID, int nNum, int nX, int nY);

	BOOL CheckCtrlNumber(CWnd* pParent, int nCtrl = -1);

	//��Բ��
	void DrawRoundRectRgn(CWnd* pWnd);
	void DrawRoundRectRgn(HWND hWnd);

	// ������ǰ��,����������WS_POPUP���ԵĴ���
	// ǰ��ʱ��ȥ����������
	void WndTopMost(CWnd* pWnd);
	void WndTopMost(HWND hWnd);


	// ʹ�ؼ����ڿ��(�߶�,��С)��ͬ,����һ�Ǳ�׼ֵ
	void ControlSameWidth(CWnd* pWnd, CWnd* pChangeWnd);
	void ControlSameWidthMutli(CWnd* pWnd, CWnd** ppChangeWnd, int nCount);
	void ControlSameHeight(CWnd* pWnd, CWnd* pChangeWnd);
	void ControlSameHeightMutli(CWnd* pWnd, CWnd** ppChangeWnd, int nCount);
	void ControlSameSize(CWnd* pWnd, CWnd* pChangeWnd, BOOL bChangeWidth, BOOL bChangeHeight);
	void ControlSameSizeMutli(CWnd* pWnd, CWnd** ppChangeWnd, int nCount, BOOL bChangeWidth, BOOL bChangeHeight);

};
using namespace _nsCWnd;



namespace _nsCEdit
{
	// ���ý��㵽Edit�ؼ�
	void	SetEditCtrlFocus(CWnd* pParent, int nEditID);
	void	SetEditCtrlFocus(CWnd* pEditWnd);
	// ���ý��㵽Edit�ؼ�����λ������ͷ��
	void	SetEditCtrlFocusSeekBegin(CWnd* pParent, int nEditID);
	void	SetEditCtrlFocusSeekBegin(CWnd* pEditWnd);
	// ���ý��㵽Edit�ؼ�����λ������β��
	void	SetEditCtrlFocusSeekEnd(CWnd* pParent, int nEditID);
	void	SetEditCtrlFocusSeekEnd(CWnd* pEditWnd);

	// ��CEdit�ؼ����渽���ı�,������:Ԥ���ǰ�ȸ����ַ���(��Ҫ��������)
	void	EditCtrlAddText(CWnd* pParent, int nEditID, LPCTSTR lpszText, LPCTSTR lpszAdd = NULL);
	void	EditCtrlAddText(CWnd* pEditWnd, LPCTSTR lpszText, LPCTSTR lpszAdd = NULL);
	// ��ͷ�������ı�
	void	EditCtrlAddTextToHead(CWnd* pParent, int nEditID, LPCTSTR lpszText, LPCTSTR lpszAdd = NULL);
	void	EditCtrlAddTextToHead(CWnd* pEditWnd, LPCTSTR lpszText, LPCTSTR lpszAdd = NULL);

	// ���ؼ��Ƿ�Ϊ��
	BOOL	CheckEditEmpty(CWnd* pParent, int nCtrl);
	BOOL	CheckEditEmpty(CWnd* pEditWnd);

	// ����ı��Ƿ�Ϊ����,�����Ƿ���ָ����Χ��
	// ���ַ�����0����,���ܰ���������
	BOOL	CheckEditNumber(CWnd* pParent, int nCtrl, int nMin, int nMax);
	BOOL	CheckEditNumber(CWnd* pEditWnd, int nMin, int nMax);

	BOOL	CheckEditNumber64(CWnd* pParent, int nCtrl, __int64 nMin, __int64 nMax);
	BOOL	CheckEditNumber64(CWnd* pEditWnd, __int64 nMin, __int64 nMax);

	// ����ַ
	BOOL	CheckIPValid(CWnd* pParent, int nCtrl = -1);

	// ���˿���Ч��
	BOOL	CheckPortValid(CWnd* pParent, int nCtrl);
	BOOL	CheckPortValid(CWnd* pEditWnd);

	// EMAIL��Ч����֤
	BOOL	CheckEditEmail(CWnd* pParent, int nCtrl);
	BOOL	CheckEditEmail(CWnd* pEditWnd);


	// ���edit�ؼ������ַ�Χ
	void	CheckEditNumberRange(CWnd* pParent, int nEditID, int nOffest, int nMin, int nMax);
	void	CheckEditNumberRange(CWnd* pEditWnd, int nOffest, int nMin, int nMax);
	void	CheckEditNumberRange64(CWnd* pParent, int nEditID, __int64 nOffest, __int64 nMin, __int64 nMax);
	void	CheckEditNumberRange64(CWnd* pEditWnd, __int64 nOffest, __int64 nMin, __int64 nMax);

	// ���Ʊ༭��ؼ�������ַ���
	BOOL	EditCtrlLimitText(CWnd* pParent, int nEditID, int nChars);
	BOOL	EditCtrlLimitText(CWnd* pEditWnd, int nChars);

	// ����ֻ������
	BOOL	SetEditCtrlReadOnly(CWnd* pParent, int nEditID, BOOL bReadOnly);
	BOOL	SetEditCtrlReadOnly(CWnd* pEditWnd, BOOL bReadOnly = TRUE);
};
using namespace _nsCEdit;



namespace _nsCComboBox
{
	// ��CComboBox�ؼ���������
	void	InsertCComboBoxData(CComboBox& cmb, int nIndex, LPCTSTR lpszStr, DWORD_PTR dwData);
	void	InsertCComboBoxData(CComboBox& cmb, LPCTSTR lpszStr, DWORD_PTR dwData);
	void	InsertCComboBoxPtrData(CComboBox& cmb, int nIndex, LPCTSTR lpszStr, LPVOID pData);
	void	InsertCComboBoxPtrData(CComboBox& cmb, LPCTSTR lpszStr, LPVOID pData);

	// ͨ���Ƚ�ITEMDATAѡ����Ӧ��item,����ѡ�������bSel:�����ɹ��Ƿ�ѡ��
	int		SearchCmbData(CComboBox& cmb, DWORD_PTR dwData, BOOL bSel);

	// ������ֵ��ѡ��,���ѡ��ʧ����Ĭ��ѡ�в���3
	BOOL	SelectComboxByItemData(CComboBox& box, DWORD_PTR dwData, int nDefault = 0);

	// ��ȡ��ǰѡ�����ֵ
	DWORD_PTR GetComboBoxData(CComboBox& cmb);

};
using namespace _nsCComboBox;



namespace _nsCDateTimeCtrl //ʱ��ؼ����������ֿռ�
{
	// ������ʱ��ؼ���ȡʱ��,ǰ��������,����Ϊʱ��
	BOOL GetTimeFromDateTimeCtrl(CWnd* pParent, int nCtrlID1, int nCtrlID2, SYSTEMTIME& stTime);
	BOOL GetTimeFromDateTimeCtrl(CWnd* pWnd1, CWnd* pWnd2, SYSTEMTIME& stTime);

	// �������ڿؼ�(������)��Ĭ�ϸ�ʽ���ַ���,��ֵ��ʾ���޸�,Ĭ��Ϊ_T("yyyy'-'MM'-'dd")
	void SetDateCtrlFormatStr(LPCTSTR lpszFormat);
	// ����ʱ��ؼ�(ʱ����)��Ĭ�ϸ�ʽ���ַ���,��ֵ��ʾ���޸�,Ĭ��Ϊ_T("HH':'mm':'ss")
	void SetTimeCtrlFormatStr(LPCTSTR lpszFormat);

	//
	BOOL SetDateCtrlFormat(CWnd* pParent, int nDateID);
	BOOL SetDateCtrlFormat(CWnd* pDateWnd);
	BOOL SetTimeCtrlFormat(CWnd* pParent, int nTimeID);
	BOOL SetTimeCtrlFormat(CWnd* pTimeWnd);
	BOOL SetDateTimeCtrlFormat(CWnd* pParent, int nDateID, int nTimeID);
	BOOL SetDateTimeCtrlFormat(CWnd* pDateWnd, CWnd* pTimeWnd);

	// ���տ�ʼ���ڵĸ�ʽ��ʼ������,time=00:00:00
	BOOL InitTimeCtrlAsBegin(CWnd* pParent, int nTimeID);
	BOOL InitTimeCtrlAsBegin(CWnd* pTimeWnd);
	// ���տ�ʼ���ڵĸ�ʽ��ʼ������,time=23:59:59
	BOOL InitTimeCtrlAsEnd(CWnd* pParent, int nTimeID);
	BOOL InitTimeCtrlAsEnd(CWnd* pTimeWnd);

	BOOL SetDateTimeCtrlTime(CWnd* pParent, int nCtrlID, SYSTEMTIME& stTime);
	BOOL SetDateTimeCtrlTime(CWnd* pCtrlWnd, SYSTEMTIME& stTime);
};
using namespace _nsCDateTimeCtrl;




namespace _nsCSpinButtonCtrl
{
	void SetSpinCtrlBuddy(CWnd* pParent, int nSpinID, int nEditID);
	void SetSpinCtrlBuddy(CWnd* pSpinWnd, CWnd* pEditWnd);

	void SetSpinCtrlRange(CWnd* pParent, int nSpinID, int nLower, int nUpper);
	void SetSpinCtrlRange(CWnd* pSpinWnd, int nLower, int nUpper);

};
using namespace _nsCSpinButtonCtrl;



namespace _nsCMenu
{
	//��Ӳ˵��ָ���
	void AddSeparatorMenu(CMenu* pMenu, int& nIndex);

	// ���ӻ�ɫ��Ч�˵�
	void AddDisableMenu(CMenu* pMenu, int& nIndex, LPCTSTR lpszTip);

	// ���Ҽ����Ϊ׼,��ʾ�˵�
	void ShowMenu(CMenu* pPopup, int nIndex, CWnd* pWnd);
};
using namespace _nsCMenu;



namespace _nsCListCtrl
{
	// ɾ��ȫ����
	void DeleteAllColumn(CWnd* pListWnd);

	// ����CListCtrl�ؼ��б�ѡ�������
	int TotalListSelectCount(CWnd* pListWnd);

	// ��������ĳ�еĿ��
	void ResizeListCtrl(CWnd* pListWnd, int nIndex);
	void ResizeListCtrlMulti(CWnd* pListWnd, int& nMaxWidth, int* pIndex, int nCount);
	// ��ȡ��ǰѡ��ĵ�һ������
	int GetCurListSelectedItem(CWnd* pListWnd);
};
using namespace _nsCListCtrl;


#endif