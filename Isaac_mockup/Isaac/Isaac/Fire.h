#pragma once
#include "Obj.h"
class CFire :
	public CObj
{
public:
	CFire();
	~CFire();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Set_ColCheakFire(void) { m_bColCheakFire = true; }

private:
	bool m_bColCheakFire;
};

