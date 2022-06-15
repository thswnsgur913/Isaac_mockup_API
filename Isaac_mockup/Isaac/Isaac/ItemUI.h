#pragma once

#include "UI.h"

class CItemUI
	: public CUI
{
public:
	CItemUI();
	virtual ~CItemUI();

public:
	virtual		void	Initialize(void)	override;
	virtual		int		Update(void)		override;
	virtual		void	Late_Update(void)	override;
	virtual		void	Render(HDC hDC)		override;
	virtual		void	Release(void)		override;

	void Set_ItemType(ITEMTYPE _ItemID) { m_ItemID = _ItemID; }
	ITEMTYPE& Get_ItemType(void) { return m_ItemID; }

private:
	ITEMTYPE m_ItemID;

	int m_iLife;
	int m_iCoin;
	int m_iBoom;
	int m_iKey;
};

