#pragma once
#include <vector>


// 功能:按行处理对话框中的控件


typedef struct _tagCtrlData 
{
	int nCtrlID;		//控件ID号
	int nInterval;		//间隔宽度(高度)
	int	nCmdShow;		//控件显示状态
}CtrlData_S;

class CCtrlSort
{
protected:
	typedef std::vector<CtrlData_S> VecCtrl;
	typedef std::map<int, VecCtrl > MapVecCtrl;
public:
	CCtrlSort(void);
	~CCtrlSort(void);

	void SetParent(CWnd* pWnd) { m_pParent = pWnd; }
	void SetStartPt(CPoint pt) { m_StartPt = pt; }

	//int Insert(const CtrlData_S& CtrlInfo);
	void InsertChild(int nIndex, const CtrlData_S& CtrlInfo);
	void InsertChild(int nIndex, int nCtrlID, int nInterval, int nCmdShow = SW_SHOW);

	void Clear();

	void EnableCtrl(int nIndex, BOOL bEnable);
	void ShowCtrl(int nIndex, int nCmdShow);
	// 根据某一行的任意一个控件ID,操作一整行数据
	void EnableCtrlFromCtrlID(int nCtrlID, BOOL bEnable);
	void ShowCtrlFromCtrlID(int nCtrlID, int nCmdShow);

	void ResetCtrl();
	
	// 查找控件位置
	BOOL FindCtrl(int nStart, int nCtrlID, int& nIndex1, int& nIndex2);
	BOOL FindCtrl(int nCtrlID, int& nIndex1, int& nIndex2);
	BOOL FindCtrlFromWnd(int nStart, CWnd* pWnd, int& nIndex1, int& nIndex2);
	BOOL FindCtrlFromWnd(CWnd* pWnd, int& nIndex1, int& nIndex2);

	void SameHeight(CWnd* pWnd, int nIndex = -1, int nIndex2 = -1);
protected:
	CCtrlSort::VecCtrl& GetVecCtrl(int nIndex);
private:
	CWnd* m_pParent;		//对话框的窗口指针
	CPoint m_StartPt;		//控件起点坐标
	MapVecCtrl m_mapVecCtrlData;	//控件数据
};

