#pragma once
#include <functional>

// 工具栏，可容纳CWnd对象
// 根据控件是否可见，移动控件的位置。工具栏宽度不够时，会自动隐藏部分控件
// 工具栏只负责移动控件/显隐控件，需要在父对话框自行创建按钮成员对象、处理按钮消息
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

	// 更多按钮，未实现
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
	// 从左边开始添加控件
	int MoveCtrl();

private:
	// 从右边开始添加控件
	int MoveCtrlRight();

public:
	int Move(int x, int y);
	int Move(int x, int y, int w, int h);
	int Resize(int w, int h);

	// 工具栏的当前宽度
	int GetUsedWidth() const { return m_nUsedWidth; }

	// 所有控件可见时的宽度
	int GetFullWidth() const { return m_nFullWidth; }

	// 工具栏位置大小，调用Move(), Resize(), MoveCtrl()后更新
	CRect GetRect() const { return CRect(m_sRect.x, m_sRect.y, m_sRect.x + m_sRect.w, m_sRect.y + m_sRect.h); }

	// 重新获得工具栏完全显示时的宽度
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

	// 获得控件组数量
	size_t GetGroupCount() const { return m_vecWnd.size(); }

	// 获得可用控件组数量（目前仅统计Elem_S::WND组的数量）
	size_t GetCandidateGroupCount() const { return m_nCandidateGroupCount; }

	// 获得所有可见组数量
	size_t GetVisibleGroupCount() const { return m_nVisibleGroupCount; }
};
