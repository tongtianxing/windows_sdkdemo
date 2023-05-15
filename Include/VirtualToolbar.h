#pragma once
#include <functional>

// ��������������CWnd����
// ���ݿؼ��Ƿ�ɼ����ƶ��ؼ���λ�á���������Ȳ���ʱ�����Զ����ز��ֿؼ�
// ������ֻ�����ƶ��ؼ�/�����ؼ�����Ҫ�ڸ��Ի������д�����ť��Ա���󡢴���ť��Ϣ
class CVirtualToolbar
{
	struct Elem_S
	{
		enum {
			WND,
			SPACE
		} eType;
		std::vector<CWnd*> vecWnd;
		int nSpaceWidth;
		bool bVisible;
		Elem_S() : eType(WND), nSpaceWidth(0) {}
	};
	std::vector<Elem_S> m_vecWnd;
	int m_nAlign; // BF_TOPLEFT
	int m_nInterval;
	int m_nGapX;
	int m_nGapY;

	size_t m_nCandidateGroupCount;
	size_t m_nVisibleGroupCount;
	CMenu m_menuExpand;
	
	int m_nUsedWidth;
	BOOL m_bShowAll;
	int m_nFullWidth;

	struct SRect
	{
		int x, y, w, h;
		SRect(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}
		bool operator!=(const SRect& rhs) { return x != rhs.x && y != rhs.y && w != rhs.w && h != rhs.h; }
	} m_sRect;

public:
	CVirtualToolbar(int nAlign, int nInterval, int nGapX, int nGapY, BOOL bShowAll = FALSE);
	virtual ~CVirtualToolbar();

	// ���ఴť��δʵ��
private:
	CImgBase* m_pImageExpand;
public:
	void SetImage(LPCTSTR lpszExpand, LPCTSTR lpszColl);

public:
	bool AddWnd(std::vector<CWnd*>& vecBtn);
	template<size_t nCount>
	bool AddWnd(CWnd* (&ppBtn)[nCount])
	{
		std::vector<CWnd*> vecBtn;
		for (size_t i = 0; i < nCount; ++i)
			vecBtn.push_back(ppBtn[i]);
		return AddWnd(vecBtn);
	}
	bool AddWnd(CWnd* pBtn)
	{
		std::vector<CWnd*> vecBtn;
		vecBtn.push_back(pBtn);
		return AddWnd(vecBtn);
	}
	bool AddSpace(int nWidth);

public:
	// ����߿�ʼ��ӿؼ�
	int MoveCtrl();

private:
	// ���ұ߿�ʼ��ӿؼ�
	int MoveCtrlRight();

public:
	int Move(int x, int y);
	int Move(int x, int y, int w, int h);
	int Resize(int w, int h);

	// �������ĵ�ǰ���
	int GetUsedWidth() const { return m_nUsedWidth; }

	// ���пؼ��ɼ�ʱ�Ŀ��
	int GetFullWidth() const { return m_nFullWidth; }

	// ������λ�ô�С������Move(), Resize(), MoveCtrl()�����
	CRect GetRect() const { return CRect(m_sRect.x, m_sRect.y, m_sRect.x + m_sRect.w, m_sRect.y + m_sRect.h); }

	// ���»�ù�������ȫ��ʾʱ�Ŀ��
	int RecalcWidth(BOOL bVisible);

	void ForEach(std::function<void(CWnd* pWnd, void* pUsr)> pFn, void* pUsr = NULL)
	{ 
		for (auto it = m_vecWnd.begin(); it != m_vecWnd.end(); ++it)
		{
			if (it->eType == Elem_S::WND)
			{
				for (auto it1 = it->vecWnd.begin(); it1 != it->vecWnd.end(); ++it1)
					pFn(*it1, pUsr);
			}
		}
		m_nUsedWidth = RecalcWidth(TRUE);
		m_nFullWidth = RecalcWidth(FALSE);
	}

	// ��ÿؼ�������
	size_t GetGroupCount() const { return m_vecWnd.size(); }

	// ��ÿ��ÿؼ���������Ŀǰ��ͳ��Elem_S::WND���������
	size_t GetCandidateGroupCount() const { return m_nCandidateGroupCount; }

	// ������пɼ�������
	size_t GetVisibleGroupCount() const { return m_nVisibleGroupCount; }
};
