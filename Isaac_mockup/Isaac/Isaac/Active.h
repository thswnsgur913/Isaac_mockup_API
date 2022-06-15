#pragma once

#include "Obj.h"

class CActive :
	public CObj
{
public:
	CActive();
	~CActive();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Set_ActiveType(ITEMTYPE _ItemType) { m_ItemType = _ItemType; }
	ITEMTYPE& Get_ActiveType(void) { return m_ItemType; }

	void ActiveA_Render(HDC hDC);
	void ActiveB_Render(HDC hDC);

	int Move_Frame_Active(void);

private:
	ITEMTYPE m_ItemType;
};

