#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	CMonster();
	virtual ~CMonster();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) PURE;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) PURE;
	virtual void Release(void) PURE;

	virtual void Motion_Change(void) PURE;

	void BehaviorStart(CObj*);

	void Hit();

	float CosAngle(void);
	float CosAngleSD(void);
	float SinAngle(void);
	float SinAngleSD(void);

	void Set_MonState(MONSTATE _MonState) { m_MonState = _MonState; }
	void Set_Fly1(void) { m_CurrentPattern = Fly1; }
	void Set_TargetPosition(float _fX, float _fY) { m_TargetPosition.x = _fX; m_TargetPosition.y = _fY; }
	Pattern Get_Pattern() {	return m_CurrentPattern; }

	float Get_fMonsterSound() { return m_fMonsterSound; }

protected:
	

	const int baseShotAngle;

	void TargetMove_V();
	void TargetMove_SD();
	bool TargetMove_B();
	bool TargetMove_Ball();
	bool TargetMove_Jump();
	bool TargetMove_Return();
	void Fire(const int, DIRECTION);

	void BehaviorUpdate();

	virtual void BehaviorEnter() PURE;
	virtual void BehaviorExecute() PURE;
	virtual void BehaviorExit() PURE;

	virtual bool Dir() PURE;

	void Create_Ball();

protected:
	enum Behavior {
		Enter,
		Execute,
		Exit
	};

	Vector2D m_OriginPosition;
	Vector2D m_TargetPosition;

	Behavior m_BehaviorState;
	Pattern m_CurrentPattern;

	MONSTATE m_eMonState;
	MONSTATE m_MonState;

	DIRECTION m_eDir;

	DWORD m_dwTime;
	DWORD m_dwWait;

	bool m_bAIStart;

	float m_fTemp;

	float m_RenLeft;
	float m_RenTop;

	int m_MotionIdle;
	int m_MotionHit;

	void		Update_TargetRect(void);

	INFO		m_TargetInfo;
	RECT		m_TargetRect;

	float m_fMonsterSound;

	int iRanX;
	int iRanY;
	int iRanXX;
	int iRanYY;

	float m_fAngleBack;
};

