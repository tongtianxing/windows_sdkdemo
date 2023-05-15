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

// 设置鼠标为手型
void	SetHandCursor();


namespace _nsCWnd
{
	// 获取控件的文本(ID=-1表示获取自己的文本),删除左右的空格
	CString GetCtrlText(CWnd* pParent, int nCtrl = -1);


	// 获取两个控件左上角的坐标差,以1为准,2 减 1
	BOOL GetPointDiff(CWnd* pParent, int nCtrlID1, int nCtrlID2, int& nX, int& nY);
	BOOL GetPointDiff(CWnd* pCtrlWnd1, CWnd* pCtrlWnd2, int& nX, int& nY);

	// 批量移动控件,在当前位置的基础上移动
	void BetchMoveCtrl(CWnd* pParent, int* pCtrlID, int nNum, int nX, int nY);

	BOOL CheckCtrlNumber(CWnd* pParent, int nCtrl = -1);

	//画圆角
	void DrawRoundRectRgn(CWnd* pWnd);
	void DrawRoundRectRgn(HWND hWnd);

	// 将窗口前置,仅操作带有WS_POPUP属性的窗口
	// 前置时会去掉隐藏属性
	void WndTopMost(CWnd* pWnd);
	void WndTopMost(HWND hWnd);


	// 使控件窗口宽度(高度,大小)相同,参数一是标准值
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
	// 设置焦点到Edit控件
	void	SetEditCtrlFocus(CWnd* pParent, int nEditID);
	void	SetEditCtrlFocus(CWnd* pEditWnd);
	// 设置焦点到Edit控件并定位到数据头部
	void	SetEditCtrlFocusSeekBegin(CWnd* pParent, int nEditID);
	void	SetEditCtrlFocusSeekBegin(CWnd* pEditWnd);
	// 设置焦点到Edit控件并定位到数据尾部
	void	SetEditCtrlFocusSeekEnd(CWnd* pParent, int nEditID);
	void	SetEditCtrlFocusSeekEnd(CWnd* pEditWnd);

	// 向CEdit控件后面附加文本,参数三:预添加前先附加字符串(主要用来换行)
	void	EditCtrlAddText(CWnd* pParent, int nEditID, LPCTSTR lpszText, LPCTSTR lpszAdd = NULL);
	void	EditCtrlAddText(CWnd* pEditWnd, LPCTSTR lpszText, LPCTSTR lpszAdd = NULL);
	// 从头部附加文本
	void	EditCtrlAddTextToHead(CWnd* pParent, int nEditID, LPCTSTR lpszText, LPCTSTR lpszAdd = NULL);
	void	EditCtrlAddTextToHead(CWnd* pEditWnd, LPCTSTR lpszText, LPCTSTR lpszAdd = NULL);

	// 检查控件是否为空
	BOOL	CheckEditEmpty(CWnd* pParent, int nCtrl);
	BOOL	CheckEditEmpty(CWnd* pEditWnd);

	// 检查文本是否为数字,并且是否在指定范围内
	// 空字符串按0计算,不能包含非数字
	BOOL	CheckEditNumber(CWnd* pParent, int nCtrl, int nMin, int nMax);
	BOOL	CheckEditNumber(CWnd* pEditWnd, int nMin, int nMax);

	BOOL	CheckEditNumber64(CWnd* pParent, int nCtrl, __int64 nMin, __int64 nMax);
	BOOL	CheckEditNumber64(CWnd* pEditWnd, __int64 nMin, __int64 nMax);

	// 检查地址
	BOOL	CheckIPValid(CWnd* pParent, int nCtrl = -1);

	// 检查端口有效性
	BOOL	CheckPortValid(CWnd* pParent, int nCtrl);
	BOOL	CheckPortValid(CWnd* pEditWnd);

	// EMAIL有效性验证
	BOOL	CheckEditEmail(CWnd* pParent, int nCtrl);
	BOOL	CheckEditEmail(CWnd* pEditWnd);


	// 检查edit控件的数字范围
	void	CheckEditNumberRange(CWnd* pParent, int nEditID, int nOffest, int nMin, int nMax);
	void	CheckEditNumberRange(CWnd* pEditWnd, int nOffest, int nMin, int nMax);
	void	CheckEditNumberRange64(CWnd* pParent, int nEditID, __int64 nOffest, __int64 nMin, __int64 nMax);
	void	CheckEditNumberRange64(CWnd* pEditWnd, __int64 nOffest, __int64 nMin, __int64 nMax);

	// 限制编辑框控件的最大字符数
	BOOL	EditCtrlLimitText(CWnd* pParent, int nEditID, int nChars);
	BOOL	EditCtrlLimitText(CWnd* pEditWnd, int nChars);

	// 设置只读属性
	BOOL	SetEditCtrlReadOnly(CWnd* pParent, int nEditID, BOOL bReadOnly);
	BOOL	SetEditCtrlReadOnly(CWnd* pEditWnd, BOOL bReadOnly = TRUE);
};
using namespace _nsCEdit;



namespace _nsCComboBox
{
	// 向CComboBox控件插入数据
	void	InsertCComboBoxData(CComboBox& cmb, int nIndex, LPCTSTR lpszStr, DWORD_PTR dwData);
	void	InsertCComboBoxData(CComboBox& cmb, LPCTSTR lpszStr, DWORD_PTR dwData);
	void	InsertCComboBoxPtrData(CComboBox& cmb, int nIndex, LPCTSTR lpszStr, LPVOID pData);
	void	InsertCComboBoxPtrData(CComboBox& cmb, LPCTSTR lpszStr, LPVOID pData);

	// 通过比较ITEMDATA选择相应的item,返回选择的索引bSel:搜索成功是否选中
	int		SearchCmbData(CComboBox& cmb, DWORD_PTR dwData, BOOL bSel);

	// 搜索项值并选中,如果选择失败则默认选中参数3
	BOOL	SelectComboxByItemData(CComboBox& box, DWORD_PTR dwData, int nDefault = 0);

	// 获取当前选择的项值
	DWORD_PTR GetComboBoxData(CComboBox& cmb);

};
using namespace _nsCComboBox;



namespace _nsCDateTimeCtrl //时间控件操作的名字空间
{
	// 从两个时间控件获取时间,前面是日期,后面为时间
	BOOL GetTimeFromDateTimeCtrl(CWnd* pParent, int nCtrlID1, int nCtrlID2, SYSTEMTIME& stTime);
	BOOL GetTimeFromDateTimeCtrl(CWnd* pWnd1, CWnd* pWnd2, SYSTEMTIME& stTime);

	// 设置日期控件(年月日)的默认格式化字符串,空值表示不修改,默认为_T("yyyy'-'MM'-'dd")
	void SetDateCtrlFormatStr(LPCTSTR lpszFormat);
	// 设置时间控件(时分秒)的默认格式化字符串,空值表示不修改,默认为_T("HH':'mm':'ss")
	void SetTimeCtrlFormatStr(LPCTSTR lpszFormat);

	//
	BOOL SetDateCtrlFormat(CWnd* pParent, int nDateID);
	BOOL SetDateCtrlFormat(CWnd* pDateWnd);
	BOOL SetTimeCtrlFormat(CWnd* pParent, int nTimeID);
	BOOL SetTimeCtrlFormat(CWnd* pTimeWnd);
	BOOL SetDateTimeCtrlFormat(CWnd* pParent, int nDateID, int nTimeID);
	BOOL SetDateTimeCtrlFormat(CWnd* pDateWnd, CWnd* pTimeWnd);

	// 按照开始日期的格式初始化数据,time=00:00:00
	BOOL InitTimeCtrlAsBegin(CWnd* pParent, int nTimeID);
	BOOL InitTimeCtrlAsBegin(CWnd* pTimeWnd);
	// 按照开始日期的格式初始化数据,time=23:59:59
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
	//添加菜单分隔行
	void AddSeparatorMenu(CMenu* pMenu, int& nIndex);

	// 增加灰色无效菜单
	void AddDisableMenu(CMenu* pMenu, int& nIndex, LPCTSTR lpszTip);

	// 以右键鼠标为准,显示菜单
	void ShowMenu(CMenu* pPopup, int nIndex, CWnd* pWnd);
};
using namespace _nsCMenu;



namespace _nsCListCtrl
{
	// 删除全部列
	void DeleteAllColumn(CWnd* pListWnd);

	// 计算CListCtrl控件中被选择的项数
	int TotalListSelectCount(CWnd* pListWnd);

	// 重新设置某列的宽度
	void ResizeListCtrl(CWnd* pListWnd, int nIndex);
	void ResizeListCtrlMulti(CWnd* pListWnd, int& nMaxWidth, int* pIndex, int nCount);
	// 获取当前选择的第一项索引
	int GetCurListSelectedItem(CWnd* pListWnd);
};
using namespace _nsCListCtrl;


#endif