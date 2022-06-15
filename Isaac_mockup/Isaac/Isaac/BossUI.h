#pragma once
#include "UI.h"
class CBossUI :
	public CUI
{
public:
	CBossUI();
	~CBossUI();

	// CUI��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void Bar_Update_Rect(void);

	INFO m_tBarInfo;
	RECT m_tBarRect;

	float m_fTemp;
};

