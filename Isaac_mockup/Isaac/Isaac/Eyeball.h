#pragma once
#include "Bullet.h"
class CEyeball :
	public CBullet
{
public:
	CEyeball();
	~CEyeball();

	// CBullet��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Motion_Change(void) override;

private:
	float m_fTemp;
};

