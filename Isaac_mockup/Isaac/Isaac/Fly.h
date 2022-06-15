#pragma once
#include "Monster.h"
class CFly :
	public CMonster
{
public:
	CFly();
	~CFly();

	// CMonster��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual void Motion_Change(void) override;

	virtual void BehaviorEnter() override;
	virtual void BehaviorExecute() override;
	virtual void BehaviorExit() override;

	virtual bool Dir() override;

	float Fly_Player();
};

