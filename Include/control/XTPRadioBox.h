#pragma once


class CXTPRadioBox : public CXTPButton
{
public:
	CXTPRadioBox();


	virtual COLORREF GetButtonTextColor() override;
	virtual COLORREF GetButtonBackColor() override;
	virtual void OnDraw(CDC* pDC) override;

	void SetButtonTextColor(COLORREF color);
	void SetButtonBackColor(COLORREF color);
private:
	COLORREF m_clrButtonText;
	COLORREF m_clrButtonBack;
};

