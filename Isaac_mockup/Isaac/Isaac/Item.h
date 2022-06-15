#pragma once

#include "Obj.h"

class CItem :
	public CObj
{
public:
	CItem();
	~CItem();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Set_ItemType(ITEMTYPE _ItemType) { m_ItemType = _ItemType; }
	ITEMTYPE& Get_ItemType(void) { return m_ItemType; }

	int Move_Frame_Item(void);

private:
	ITEMTYPE m_ItemType;
};

