#include "stdafx.h"
#include "BossBall.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "ObjTestStageMgr.h"


CBossBall::CBossBall()
{
}


CBossBall::~CBossBall()
{
	Release();
}

void CBossBall::Initialize(void)
{
	m_tInfo.fRenX = 100.f;
	m_tInfo.fRenY = 100.f;

	m_fSpeed = 4.f;

	m_CurrentPattern = Create;

	m_dwTime = GetTickCount();
	//m_dwWait = GetTickCount();

	m_eRender = RENDER_BOSSFLY;

	CSoundMgr::Get_Instance()->StopSound(SOUND_MBUL);
	CSoundMgr::Get_Instance()->PlaySound(L"Bullet.wav", SOUND_MBUL, g_fSound);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/MonsterBullet/BossBall.bmp", L"BossBall");

	m_pFrameKey = L"BossBall";

	m_MonState = MONSTATE_IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();

	if (100 == m_tInfo.fCX)
	{
		m_tFrame.iMotion = 0;
		m_iLife = 5;
	}
	else if (80 == m_tInfo.fCX)
	{
		m_tFrame.iMotion = 1;
		m_iLife = 4;
	}
	else if (60 == m_tInfo.fCX)
	{
		m_tFrame.iMotion = 2;
		m_iLife = 3;
	}
	else if (40 == m_tInfo.fCX)
	{
		m_tFrame.iMotion = 3;
		m_iLife = 2;
	}
	else if (20 == m_tInfo.fCX)
	{
		m_tFrame.iMotion = 4;
		m_iLife = 1;
	}
}

void CBossBall::Render(HDC hDC)
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

void CBossBall::Release(void)
{
}

void CBossBall::Motion_Change(void)
{
}

void CBossBall::BehaviorEnter()
{
	if (!m_targetObj)
		return;

	switch (m_CurrentPattern)
	{
	case Create:
		break;
	}

	m_BehaviorState = Execute;
}

void CBossBall::BehaviorExecute()
{
	if (!m_targetObj)
		return;

	switch (m_CurrentPattern)
	{
	case Create:
		if (TargetMove_Ball())
		{
			if (20 < m_tInfo.fCX)
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_BULLET_END);
				CSoundMgr::Get_Instance()->PlaySound(L"BulletEnd.wav", SOUND_BULLET_END, g_fSound);

				CObj* m_pMonster = CAbstractFactory<CBossBall>::Create_BossBall(m_tInfo.fX, m_tInfo.fY, (m_tInfo.fCX - 20.f), (m_tInfo.fCY - 20.f), m_fAngle);
				dynamic_cast<CMonster*>(m_pMonster)->BehaviorStart(m_targetObj);
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pMonster);

				m_pMonster = CAbstractFactory<CBossBall>::Create_BossBall(m_tInfo.fX, m_tInfo.fY, (m_tInfo.fCX - 20.f), (m_tInfo.fCY - 20.f), m_fAngleBack);
				dynamic_cast<CMonster*>(m_pMonster)->BehaviorStart(m_targetObj);
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pMonster);
			}
			m_BehaviorState = Exit;
			Set_Dead();
			break;
		}
	}
}

void CBossBall::BehaviorExit()
{
	switch (m_CurrentPattern)
	{
	case Create:
		break;
	}

	m_BehaviorState = Enter;
}

bool CBossBall::Dir()
{
	return false;
}
