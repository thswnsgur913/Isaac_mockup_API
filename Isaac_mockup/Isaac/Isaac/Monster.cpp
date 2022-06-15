#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
	: baseShotAngle(0)
	, m_bAIStart(false)
	, m_fTemp(0)
	, m_eMonState(MONSTATE_END)
	, m_MonState(MONSTATE_END)
	, m_eDir(DIR_END)
{
}

CMonster::~CMonster()
{
}

int CMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_RenLeft = m_tInfo.fX - (m_tInfo.fRenX * 0.5f);
	m_RenTop = m_tInfo.fY - (m_tInfo.fRenY * 0.5f);
	Update_Rect();
	Update_TargetRect();

	BehaviorUpdate();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
	if (0 >= m_iLife)
	{
		Set_Dead();
	}

	Motion_Change();

	if (MONSTATE_HIT == m_MonState)
	{
		if (m_dwTime + 600 < GetTickCount())
		{
			m_MonState = MONSTATE_IDLE;
			m_dwTime = GetTickCount();
		}
	}
	
	Move_Frame();
}

void CMonster::BehaviorStart(CObj* _targetObj)
{
	m_targetObj = _targetObj;

	m_bAIStart = true;
	m_BehaviorState = Enter;
}

void CMonster::BehaviorUpdate()
{
	if (!m_bAIStart || !m_targetObj)
		return;

	switch (m_BehaviorState) {
	case Enter:
		BehaviorEnter();
		break;

	case Execute:
		BehaviorExecute();
		break;

	case Exit:
		BehaviorExit();
		break;
	}
}

void CMonster::Update_TargetRect(void)
{
	m_TargetRect.left = LONG(m_TargetInfo.fX - (m_TargetInfo.fCX * 0.5f));
	m_TargetRect.top = LONG(m_TargetInfo.fY - (m_TargetInfo.fCY * 0.5f));
	m_TargetRect.right = LONG(m_TargetInfo.fX + (m_TargetInfo.fCX * 0.5f));
	m_TargetRect.bottom = LONG(m_TargetInfo.fY + (m_TargetInfo.fCY * 0.5f));
}

void CMonster::TargetMove_V()
{
	if (!m_targetObj)
		return;

	if (0.2f * PLAYERCX < abs(m_tInfo.fX - m_TargetPosition.x))
	{
		m_fAngle = CosAngle();
		m_tInfo.fX -= m_fSpeed * cos(m_fAngle);
		if (m_tInfo.fX < m_TargetPosition.x)
		{
			m_eDir = DIR_RIGHT;
		}
		else if (m_tInfo.fX > m_TargetPosition.x)
		{
			m_eDir = DIR_LEFT;
		}
	}
	if (0.2f * PLAYERCY < abs(m_tInfo.fY - m_TargetPosition.y))
	{
		m_fAngle = SinAngle();
		m_tInfo.fY -= m_fSpeed * sin(m_fAngle);
	}
}

void CMonster::TargetMove_SD()
{
	if (!m_targetObj)
		return;

	if (0.2f * PLAYERCX < abs(m_TargetInfo.fX - m_TargetPosition.x))
	{
		m_fAngle = CosAngleSD();
		m_TargetInfo.fX -= m_fSpeed * cos(m_fAngle);
	}
	if (0.2f * PLAYERCY < abs(m_TargetInfo.fY - m_TargetPosition.y))
	{
		m_fAngle = SinAngleSD();
		m_TargetInfo.fY -= m_fSpeed * sin(m_fAngle);
	}
}

bool CMonster::TargetMove_B()
{
	if (!m_targetObj)
		return true;

	if (0.1f * PLAYERCX >= abs(m_tInfo.fX - m_TargetPosition.x) && 0.1f * PLAYERCY >= abs(m_tInfo.fY - m_TargetPosition.y))
	{
		return true;
	}
	else
	{
		if (0.1f * PLAYERCX < abs(m_tInfo.fX - m_TargetPosition.x))
		{
			m_fAngle = CosAngle();
			m_tInfo.fX -= m_fSpeed * cos(m_fAngle);
		}
		if (0.1f * PLAYERCY < abs(m_tInfo.fY - m_TargetPosition.y))
		{
			m_fAngle = SinAngle();
			m_tInfo.fY -= m_fSpeed * sin(m_fAngle);
		}
		return false;
	}
}

bool CMonster::TargetMove_Ball()
{
	if (!m_targetObj)
		return true;

	if (m_tRect.left < 52 || m_tRect.right > 747 || m_tRect.top < 146 || m_tRect.bottom > 550)
	{ // 충돌한 벽이 좌우인지 상하인지 판단해서 반환할 것.
		srand((unsigned int)time((nullptr)));
		// rand() % 90 + 1;
		// rand() % 90 + 91;

		if (m_tRect.left < 52)
		{
			m_tInfo.fX += m_fSpeed + 5;


			m_fAngle = float(rand() % 90 + 1);
			m_fAngleBack = m_fAngle * -1;
		}
		else if (m_tRect.right > 747)
		{
			m_tInfo.fX -= m_fSpeed + 5;

			m_fAngle = float(rand() % 90 + 91);
			m_fAngleBack = m_fAngle * -1;
		}
		if (m_tRect.top < 146)
		{
			m_tInfo.fY += m_fSpeed + 5;

			m_fAngle = -(float(rand() % 90 + 1));
			m_fAngleBack = -(90.f + (90.f + m_fAngle));
		}
		else if (m_tRect.bottom > 550)
		{
			m_tInfo.fY -= m_fSpeed + 5;

			m_fAngle = float(rand() % 90 + 1);
			m_fAngleBack = 90.f + (90.f - m_fAngle);
		}
		return true;
	}
	else
	{
		m_tInfo.fX += m_fSpeed * cosf(m_fAngle * DEGREE);
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * DEGREE);

		/*if (0.1f * PLAYERCX < abs(m_tInfo.fX - m_TargetPosition.x))
		{
			m_fAngle = CosAngle();
			m_tInfo.fX -= m_fSpeed * cos(m_fAngle);
		}
		if (0.1f * PLAYERCY < abs(m_tInfo.fY - m_TargetPosition.y))
		{
			m_fAngle = SinAngle();
			m_tInfo.fY -= m_fSpeed * sin(m_fAngle);
		}

		if ((WINCX / 2) > m_tInfo.fX)
		{
			if ((WINCX / 2) > m_TargetPosition.x)
			{
				if (m_tInfo.fX > m_TargetPosition.x)
				{
					if(0 < m_TargetPosition.x)
						m_TargetPosition.x -= m_fSpeed;
				}
				else
				{
					if (WINCX > m_TargetPosition.x)
						m_TargetPosition.x += m_fSpeed;
				}
			}
			else
			{
				if (WINCX > m_TargetPosition.x)
					m_TargetPosition.x += m_fSpeed;
			}
		}
		else
		{
			if ((WINCX / 2) > m_TargetPosition.x)
			{
				if (0 < m_TargetPosition.x)
					m_TargetPosition.x -= m_fSpeed;
			}
			else
			{
				if (m_tInfo.fX > m_TargetPosition.x)
				{
					if (0 < m_TargetPosition.x)
						m_TargetPosition.x -= m_fSpeed;
				}
				else
				{
					if (WINCX > m_TargetPosition.x)
						m_TargetPosition.x += m_fSpeed;
				}
			}
		}

		if ((WINCY / 2) > m_tInfo.fY)
		{
			if ((WINCY / 2) > m_TargetPosition.y)
			{
				if (m_tInfo.fY > m_TargetPosition.y)
				{
					if (0 < m_TargetPosition.y)
						m_TargetPosition.y -= m_fSpeed;
				}
				else
				{
					if (WINCY > m_TargetPosition.y)
						m_TargetPosition.y += m_fSpeed;
				}
			}
			else
			{
				if (WINCY > m_TargetPosition.y)
					m_TargetPosition.y += m_fSpeed;
			}
		}
		else
		{
			if ((WINCY / 2) > m_TargetPosition.y)
			{
				if (0 < m_TargetPosition.y)
					m_TargetPosition.y -= m_fSpeed;
			}
			else
			{
				if (m_tInfo.fY > m_TargetPosition.y)
				{
					if (0 < m_TargetPosition.y)
						m_TargetPosition.y -= m_fSpeed;
				}
				else
				{
					if (WINCY > m_TargetPosition.y)
						m_TargetPosition.y += m_fSpeed;
				}
			}
		}*/

		return false;
	}
}

bool CMonster::TargetMove_Jump()
{
	if (!m_targetObj)
		return true;

	if (PLAYERCY >= abs(m_tInfo.fY - m_TargetPosition.y))
	{
		return true;
	}
	else
	{
		if (PLAYERCY < abs(m_tInfo.fY - m_TargetPosition.y))
		{
			m_tInfo.fY -= m_fSpeed;
		}
		return false;
	}
}

bool CMonster::TargetMove_Return()
{
	if (!m_targetObj)
		return true;

	if (PLAYERCY >= abs(m_tInfo.fY - m_TargetPosition.y))
	{
		return true;
	}
	else
	{
		if (PLAYERCY < abs(m_tInfo.fY - m_TargetPosition.y))
		{
			m_tInfo.fY += m_fSpeed;
		}
		return false;
	}
}

void CMonster::Fire(const int _degree, DIRECTION _Dir)
{
}

void CMonster::Hit()
{
	--m_iLife;

	if (!m_bDead && (m_iLife <= 0))
	{
		Set_Dead();
	}
}

float CMonster::CosAngle(void)
{
	float fAngle;
	float fXX = 0.f, fYY = 0.f;

	fXX = m_tInfo.fX - m_TargetPosition.x;//m_targetObj->Get_Info().fX;
	fYY = m_tInfo.fY - m_TargetPosition.y;//m_targetObj->Get_Info().fY;

	fAngle = ACOSF(fXX, fYY);

	return fAngle;
}

float CMonster::CosAngleSD(void)
{
	float fAngle;
	float fXX = 0.f, fYY = 0.f;

	fXX = m_TargetInfo.fX - m_TargetPosition.x;//m_targetObj->Get_Info().fX;
	fYY = m_TargetInfo.fY - m_TargetPosition.y;//m_targetObj->Get_Info().fY;

	fAngle = ACOSF(fXX, fYY);

	return fAngle;
}

float CMonster::SinAngle(void)
{
	float fAngle;
	float fXX = 0.f, fYY = 0.f;

	fXX = m_tInfo.fX - m_TargetPosition.x;//m_targetObj->Get_Info().fX;
	fYY = m_tInfo.fY - m_TargetPosition.y;//m_targetObj->Get_Info().fY;

	fAngle = ASINF(fXX, fYY);

	return fAngle;
}

float CMonster::SinAngleSD(void)
{
	float fAngle;
	float fXX = 0.f, fYY = 0.f;

	fXX = m_TargetInfo.fX - m_TargetPosition.x;//m_targetObj->Get_Info().fX;
	fYY = m_TargetInfo.fY - m_TargetPosition.y;//m_targetObj->Get_Info().fY;

	fAngle = ASINF(fXX, fYY);

	return fAngle;
}

void CMonster::Create_Ball()
{
	if ((WINCX / 2) > m_tInfo.fX)
	{
		if ((WINCY / 2) > m_tInfo.fY)
		{
			iRanX = rand() % (WINCX - BallCX) + (BallCX + 1);
			iRanY = rand() % (WINCY - BallCY) + (BallCY + 1);
		}
		else
		{
			iRanX = rand() % (WINCX - BallCX) + (BallCX + 1);
			iRanY = rand() % (WINCY - BallCY) + 1;
		}
	}
	else
	{
		if ((WINCY / 2) > m_tInfo.fY)
		{
			iRanX = rand() % (WINCX - BallCX) + 1;
			iRanY = rand() % (WINCY - BallCY) + (BallCY + 1);
		}
		else
		{
			iRanX = rand() % (WINCX - BallCX) + 1;
			iRanY = rand() % (WINCY - BallCY) + 1;
		}
	}

	//iRanXX = abs((WINCX / 2) - iRanX);
	//iRanYY = abs((WINCY / 2) - iRanY);

	if (400 < iRanX)
	{
		iRanXX = abs(400 - iRanX);

	}
	else if (400 > iRanX)
	{
		iRanXX = abs(400 + iRanX);
	}
	else
	{
		iRanX += 200;
		iRanXX -= 200;
	}

	if (400 < iRanY)
	{
		iRanYY = abs(400 - iRanY);

	}
	else if (400 > iRanY)
	{
		iRanYY = abs(400 + iRanY);
	}
	else
	{
		iRanY += 150;
		iRanYY -= 150;
	}
}