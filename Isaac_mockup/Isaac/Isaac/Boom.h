#pragma once

#include "Bullet.h"

class CBoom :
	public CBullet
{
public:
	CBoom();
	~CBoom();

	// CBullet을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Motion_Change(void) override;

	bool Get_Boom(void) { return m_bBoom; }

private:
	float fRenCX;
	float fRenCY;

	long lRenLeft;
	long lRenTop;

	bool m_bBoom;
};

