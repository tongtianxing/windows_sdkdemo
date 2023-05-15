#pragma once
#include <vector>


// ����:���д���Ի����еĿؼ�


typedef struct _tagCtrlData
{
	int nCtrlID;			//�ؼ�ID��
	int nInterval;			//������(�߶�)
	int	nCmdShow;			//�ؼ���ʾ״̬
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
	BOOL IsEmpty() const;

	void EnableCtrl(int nIndex, BOOL bEnable);
	void ShowCtrl(int nIndex, int nCmdShow);
	void ShowOneCtrl(int nIndex1, int nIndex2, int nCmdShow);
	// ����ĳһ�е�����һ���ؼ�ID,����һ��������
	void EnableCtrlFromCtrlID(int nCtrlID, BOOL bEnable);
	void ShowCtrlFromCtrlID(int nCtrlID, int nCmdShow);
	// ���ݿؼ�ID,�������˿ؼ�
	void ShowOneCtrlFromCtrlID(int nCtrlID, int nCmdShow);

	void ResetCtrl();
	void ResetCtrlFixed(int nIntervalCtrlX, int nIntervalCtrlY, int nIntervalGroup, int nGroupExStep = 1, int nIntervalGroupEx = 0);

	// ���ҿؼ�λ��
	BOOL FindCtrl(int nStart, int nCtrlID, int& nIndex1, int& nIndex2);
	BOOL FindCtrl(int nCtrlID, int& nIndex1, int& nIndex2);
	BOOL FindCtrlFromWnd(int nStart, CWnd* pWnd, int& nIndex1, int& nIndex2);
	BOOL FindCtrlFromWnd(CWnd* pWnd, int& nIndex1, int& nIndex2);

	void SameHeight(CWnd* pWnd, int nIndex = -1, int nIndex2 = -1);


	int GetSingleCount() const;
	void SetSingleCount(int nSingleCount);

	CSize GetSize() const { return m_size; }

protected:
	CCtrlSort::VecCtrl& GetVecCtrl(int nIndex);
private:
	CWnd* m_pParent;		//�Ի���Ĵ���ָ��
	CPoint m_StartPt;		//�ؼ��������
	MapVecCtrl m_mapVecCtrlData;	//�ؼ�����
	int m_nSingleCount;		//���пؼ�����,������ֵ�Զ�����
	CSize m_size;
};

