#pragma once
#include "Obj.h"
class CPoo :
	public CObj
{
public:
	CPoo();
	~CPoo();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Set_ColCheak(void) { m_bColCheak = true; }

private:
	bool m_bColCheak;
};

