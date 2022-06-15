#include "stdafx.h"
#include "Envy.h"
#include "BmpMgr.h"


CEnvy::CEnvy()
	: m_iFTemp(0)
{
}


CEnvy::~CEnvy()
{
}

void CEnvy::Initialize(void)
{
	m_tInfo.fCX = 55.f;
	m_tInfo.fCY = 55.f;

	m_tInfo.fRenX = 76.f;
	m_tInfo.fRenY = 76.f;

	m_fSpeed = 1.5f;

	m_iLife = 4;

	m_CurrentPattern = Create;

	m_dwTime = GetTickCount();

	m_eRender = RENDER_PLAYER;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Monster/Envy.bmp", L"Envy");

	m_pFrameKey = L"Envy";

	m_MotionIdle = 0;
	m_MotionHit = 1;
	m_MonState = MONSTATE_IDLE;
}

void CEnvy::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 								// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_RenLeft),							// 2,3 인자 :  복사받을 위치 X, Y
		int(m_RenTop),
		int(m_tInfo.fRenX),							// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fRenY),
		hMemDC,										// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fRenX,	// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fRenY,
		(int)m_tInfo.fRenX,							// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fRenY,
		RGB(255, 255, 255));						// 제거하고자 하는 색상
}

void CEnvy::Release(void)
{
}

void CEnvy::Motion_Change(void)
{
	if (m_eMonState != m_MonState)
	{
		m_dwTime = GetTickCount();
		m_eMonState = m_MonState;
	}

	switch (m_iLife)
	{
	case 0:
		m_tInfo.fRenX = 0.f;
		m_tInfo.fRenY = 0.f;
		break;

	case 1:
		m_tInfo.fCX = 22.f;
		m_tInfo.fCY = 22.f;
		m_fSpeed = 0.8f;
		if (DIR_LEFT == m_eDir)
		{
			m_iFTemp = 6;
			switch (m_MonState)
			{
			case MONSTATE_IDLE:
				m_tFrame.iFrameStart = m_iFTemp;
				m_tFrame.iFrameEnd = m_iFTemp;
				m_tFrame.iMotion = m_MotionIdle;
				m_tFrame.dwSpeed = 0;
				m_tFrame.dwTime = GetTickCount();
				break;

			case MONSTATE_HIT:
				m_tFrame.iFrameStart = m_iFTemp;
				m_tFrame.iFrameEnd = m_iFTemp;
				m_tFrame.iMotion = m_MotionHit;
				m_tFrame.dwSpeed = 0;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
		}
		else if (DIR_RIGHT == m_eDir)
		{
			m_iFTemp = 6;
			switch (m_MonState)
			{
			case MONSTATE_IDLE:
				m_tFrame.iFrameStart = m_iFTemp;
				m_tFrame.iFrameEnd = m_iFTemp;
				m_tFrame.iMotion = m_MotionIdle;
				m_tFrame.dwSpeed = 0;
				m_tFrame.dwTime = GetTickCount();
				break;

			case MONSTATE_HIT:
				m_tFrame.iFrameStart = m_iFTemp;
				m_tFrame.iFrameEnd = m_iFTemp;
				m_tFrame.iMotion = m_MotionHit;
				m_tFrame.dwSpeed = 0;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
		}
		break;

	case 2:
		m_tInfo.fCX = 33.f;
		m_tInfo.fCY = 33.f;
		m_fSpeed = 1.f;
		if (DIR_LEFT == m_eDir)
		{
			m_iFTemp = 4;
			switch (m_MonState)
			{
			case MONSTATE_IDLE:
				m_tFrame.iFrameStart = m_iFTemp;
				m_tFrame.iFrameEnd = m_iFTemp;
				m_tFrame.iMotion = m_MotionIdle;
				m_tFrame.dwSpeed = 0;
				m_tFrame.dwTime = GetTickCount();
				break;

			case MONSTATE_HIT:
				m_tFrame.iFrameStart = m_iFTemp;
				m_tFrame.iFrameEnd = m_iFTemp;
				m_tFrame.iMotion = m_MotionHit;
				m_tFrame.dwSpeed = 0;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
		}
		else if (DIR_RIGHT == m_eDir)
		{
			m_iFTemp = 5;
			switch (m_MonState)
			{
			case MONSTATE_IDLE:
				m_tFrame.iFrameStart = m_iFTemp;
				m_tFrame.iFrameEnd = m_iFTemp;
				m_tFrame.iMotion = m_MotionIdle;
				m_tFrame.dwSpeed = 0;
				m_tFrame.dwTime = GetTickCount();
				break;

			case MONSTATE_HIT:
				m_tFrame.iFrameStart = m_iFTemp;
				m_tFrame.iFrameEnd = m_iFTemp;
				m_tFrame.iMotion = m_MotionHit;
				m_tFrame.dwSpeed = 0;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
		}
		break;

	case 3:
		m_tInfo.fCX = 44.f;
		m_tInfo.fCY = 44.f;
		m_fSpeed = 1.2f;
		if (DIR_LEFT == m_eDir)
		{
			m_iFTemp = 2;
			switch (m_MonState)
			{
			case MONSTATE_IDLE:
				m_tFrame.iFrameStart = m_iFTemp;
				m_tFrame.iFrameEnd = m_iFTemp;
				m_tFrame.iMotion = m_MotionIdle;
				m_tFrame.dwSpeed = 0;
				m_tFrame.dwTime = GetTickCount();
				break;

			case MONSTATE_HIT:
				m_tFrame.iFrameStart = m_iFTemp;
				m_tFrame.iFrameEnd = m_iFTemp;
				m_tFrame.iMotion = m_MotionHit;
				m_tFrame.dwSpeed = 0;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
		}
		else if (DIR_RIGHT == m_eDir)
		{
			m_iFTemp = 3;
			switch (m_MonState)
			{
			case MONSTATE_IDLE:
				m_tFrame.iFrameStart = m_iFTemp;
				m_tFrame.iFrameEnd = m_iFTemp;
				m_tFrame.iMotion = m_MotionIdle;
				m_tFrame.dwSpeed = 0;
				m_tFrame.dwTime = GetTickCount();
				break;

			case MONSTATE_HIT:
				m_tFrame.iFrameStart = m_iFTemp;
				m_tFrame.iFrameEnd = m_iFTemp;
				m_tFrame.iMotion = m_MotionHit;
				m_tFrame.dwSpeed = 0;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
		}
		break;

	case 4:
		if (DIR_LEFT == m_eDir)
		{
			m_iFTemp = 0;
			switch (m_MonState)
			{
			case MONSTATE_IDLE:
				m_tFrame.iFrameStart = m_iFTemp;
				m_tFrame.iFrameEnd = m_iFTemp;
				m_tFrame.iMotion = m_MotionIdle;
				m_tFrame.dwSpeed = 0;
				m_tFrame.dwTime = GetTickCount();
				break;

			case MONSTATE_HIT:
				m_tFrame.iFrameStart = m_iFTemp;
				m_tFrame.iFrameEnd = m_iFTemp;
				m_tFrame.iMotion = m_MotionHit;
				m_tFrame.dwSpeed = 0;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
		}
		else if (DIR_RIGHT == m_eDir)
		{
			m_iFTemp = 1;
			switch (m_MonState)
			{
			case MONSTATE_IDLE:
				m_tFrame.iFrameStart = m_iFTemp;
				m_tFrame.iFrameEnd = m_iFTemp;
				m_tFrame.iMotion = m_MotionIdle;
				m_tFrame.dwSpeed = 0;
				m_tFrame.dwTime = GetTickCount();
				break;

			case MONSTATE_HIT:
				m_tFrame.iFrameStart = m_iFTemp;
				m_tFrame.iFrameEnd = m_iFTemp;
				m_tFrame.iMotion = m_MotionHit;
				m_tFrame.dwSpeed = 0;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
		}
		break;
	}
}

void CEnvy::BehaviorEnter()
{
	if (!m_targetObj)
		return;

	switch (m_CurrentPattern)
	{
	case Create:
		break;

	case Envy:
		break;
	}

	m_BehaviorState = Execute;
}

void CEnvy::BehaviorExecute()
{
	if (!m_targetObj)
		return;

	switch (m_CurrentPattern)
	{
	case Create:
		m_BehaviorState = Exit;
		break;

	case Envy:
	{
		m_TargetPosition.x = m_targetObj->Get_Info().fX;
		m_TargetPosition.y = m_targetObj->Get_Info().fY;
		TargetMove_V();
	}
	}
}

void CEnvy::BehaviorExit()
{
	switch (m_CurrentPattern)
	{
	case Create:
		m_CurrentPattern = Envy;
		break;

	case Envy:
		m_CurrentPattern = Envy;
		break;
	}

	m_BehaviorState = Enter;
}

bool CEnvy::Dir()
{
	return false;
}