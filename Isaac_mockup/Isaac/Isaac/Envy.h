#pragma once
#include "Monster.h"
class CEnvy :
	public CMonster
{
public:
	CEnvy();
	~CEnvy();

	// CMonster을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual void Motion_Change(void) override;

	virtual void BehaviorEnter() override;
	virtual void BehaviorExecute() override;
	virtual void BehaviorExit() override;

	virtual bool Dir() override;

private:
	int m_iFTemp;
	DIRECTION m_eNowDir;
};

