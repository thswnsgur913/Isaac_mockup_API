#pragma once
#include "Monster.h"
class CHopper :
	public CMonster
{
public:
	CHopper();
	~CHopper();

	// CMonster��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual void Motion_Change(void) override;

	virtual void BehaviorEnter() override;
	virtual void BehaviorExecute() override;
	virtual void BehaviorExit() override;

	virtual bool Dir() override;
};

