#include "stdafx.h"
#include "Trash.h"
#include "BmpMgr.h"
#include "ObjTestStageMgr.h"
#include "AbstractFactory.h"
#include "Eyeball.h"
#include "SoundMgr.h"
#include "BossBall.h"

CTrash::CTrash()
{
}


CTrash::~CTrash()
{
	Release();
}

void CTrash::Initialize(void)
{
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 150.f;

	m_tInfo.fRenX = 150.f;
	m_tInfo.fRenY = 150.f;

	m_TargetInfo.fCX = 150.f;
	m_TargetInfo.fCY = 50.f;

	m_fSpeed = 0.8f;

	m_iLife = 297;

	m_CurrentPattern = Create;

	m_dwTime = GetTickCount();
	m_dwWait = GetTickCount();

	m_eRender = RENDER_BOSS;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Monster/Trash.bmp", L"Trash");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Monster/SD.bmp", L"SD");

	m_pFrameKey = L"Trash";

	m_MotionIdle = 1;
	m_MotionHit = 4;
	m_MonState = MONSTATE_IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_pMonster = nullptr;
}

void CTrash::Render(HDC hDC)
{
	HDC		hSDDC = CBmpMgr::Get_Instance()->Find_Image(L"SD");

	if (m_bTargetRenderOn)
	{
		GdiTransparentBlt(hDC, 							// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_TargetRect.left),								// 2,3 인자 :  복사받을 위치 X, Y
			int(m_TargetRect.top),
			int(m_TargetInfo.fCX),							// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_TargetInfo.fCY),
			hSDDC,										// 비트맵을 가지고 있는 DC
			0,	// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)m_TargetInfo.fCX,							// 복사할 비트맵의 가로, 세로 길이
			(int)m_TargetInfo.fCY,
			RGB(255, 255, 255));						// 제거하고자 하는 색상
	}

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 							// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_RenLeft),								// 2,3 인자 :  복사받을 위치 X, Y
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

void CTrash::Release(void)
{
}

void CTrash::Motion_Change(void)
{
	if (m_eMonState != m_MonState)
	{
		switch (m_MonState)
		{
		case MONSTATE_IDLE:
			m_tFrame.iMotion = m_MotionIdle;
			break;

		case MONSTATE_HIT:
			m_tFrame.iMotion = m_MotionHit;
			m_dwTime = GetTickCount();
			break;
		}
		m_eMonState = m_MonState;
	}
}

void CTrash::BehaviorEnter()
{
	if (!m_targetObj)
		return;

	switch (m_CurrentPattern)
	{
	case Create:
		m_TargetPosition.x = m_targetObj->Get_Info().fX;
		m_TargetPosition.y = m_targetObj->Get_Info().fY;
		m_BehaviorState = Execute;
		break;

	case Trash1:
		m_tFrame.iFrameStart = 2;
		m_tFrame.iFrameEnd = 8;
		m_BehaviorState = Execute;
		break;

	case Trash2:
		m_tFrame.iFrameStart = 2;
		m_tFrame.iFrameEnd = 8;
		m_BehaviorState = Execute;
		break;

	case Trash3:
		m_dwWait = GetTickCount();
		m_tFrame.iFrameStart = 1;
		m_tFrame.iFrameEnd = 1;
		m_BehaviorState = Execute;
		break;

	case Return:
		m_dwWait = GetTickCount();
		m_TargetInfo.fX = m_targetObj->Get_Info().fX;
		m_TargetInfo.fY = (m_targetObj->Get_Info().fY - 25.f);
		m_fSpeed = 2.f;
		m_BehaviorState = Execute;
		break;

	case Idle:
		m_BehaviorState = Execute;
		break;
	}
}

void CTrash::BehaviorExecute()
{
	if (!m_targetObj)
		return;

	switch (m_CurrentPattern)
	{
	case Create:
		m_dwWait = GetTickCount();
		m_BehaviorState = Exit;
		break;

	case Trash1:
		if (5 == m_tFrame.iFrameStart)
		{
			m_dwWait = GetTickCount();
			CSoundMgr::Get_Instance()->PlaySoundW(L"BossWing.wav", SOUND_EFFECT, g_fSound);
			CObjTestStageMgr::Get_Instance()->CreateMonster(BOSSFLY, m_tInfo.fX, m_tInfo.fY);
			m_BehaviorState = Exit;
			break;
		}
		break;


	case Trash2:
		if (5 == m_tFrame.iFrameStart)
		{
			m_dwWait = GetTickCount();
			CSoundMgr::Get_Instance()->PlaySoundW(L"BossWing.wav", SOUND_EFFECT, g_fSound);

			m_pMonster = CAbstractFactory<CBossBall>::Create_BossBall(m_tInfo.fX, m_tInfo.fY, 100.f, 100.f, 30.f);
			dynamic_cast<CMonster*>(m_pMonster)->BehaviorStart(m_targetObj);
			CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pMonster);
			m_pMonster = nullptr;

			m_pMonster = CAbstractFactory<CBossBall>::Create_BossBall(m_tInfo.fX, m_tInfo.fY, 100.f, 100.f, 120.f);
			dynamic_cast<CMonster*>(m_pMonster)->BehaviorStart(m_targetObj);
			CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pMonster);
			m_pMonster = nullptr;

			m_pMonster = CAbstractFactory<CBossBall>::Create_BossBall(m_tInfo.fX, m_tInfo.fY, 100.f, 100.f, -30.f);
			dynamic_cast<CMonster*>(m_pMonster)->BehaviorStart(m_targetObj);
			CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pMonster);
			m_pMonster = nullptr;

			m_pMonster = CAbstractFactory<CBossBall>::Create_BossBall(m_tInfo.fX, m_tInfo.fY, 100.f, 100.f, -120.f);
			dynamic_cast<CMonster*>(m_pMonster)->BehaviorStart(m_targetObj);
			CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pMonster);
			m_pMonster = nullptr;

			m_BehaviorState = Exit;
			break;
		}
		break;

	case Trash3:
		if (m_dwWait + 3000 < GetTickCount())
		{
			m_tInfo.fCX = 0.f;
			m_tInfo.fCY = 0.f;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_fSpeed = 30.f;

			if (TargetMove_Jump())
			{
				m_dwWait = GetTickCount();
				m_BehaviorState = Exit;
				break;
			}
		}
		else
		{
			m_TargetPosition.x = m_tInfo.fX;
			m_TargetPosition.y = -200;
		}
		break;

	case Return:
		if (m_dwWait + 5000 < GetTickCount())
		{
			m_tInfo.fCX = 0.f;
			m_tInfo.fCY = 0.f;
			m_fSpeed = 20.f;
			m_tInfo.fX = m_TargetInfo.fX;
			m_TargetPosition.y = m_TargetInfo.fY;
			if (TargetMove_Return())
			{
				m_OriginPosition.x=m_tInfo.fX;
				m_OriginPosition.y=m_tInfo.fY;
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_MONBUL, CAbstractFactory<CEyeball>::Create_TB(m_OriginPosition.x, m_OriginPosition.y + 50.f, 0.f, DIR_LEFT, OBJ_MONBUL));
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_MONBUL, CAbstractFactory<CEyeball>::Create_TB(m_OriginPosition.x, m_OriginPosition.y + 50.f, 30.f, DIR_LEFT, OBJ_MONBUL));
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_MONBUL, CAbstractFactory<CEyeball>::Create_TB(m_OriginPosition.x, m_OriginPosition.y + 50.f, 60.f, DIR_LEFT, OBJ_MONBUL));
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_MONBUL, CAbstractFactory<CEyeball>::Create_TB(m_OriginPosition.x, m_OriginPosition.y + 50.f, 90.f, DIR_LEFT, OBJ_MONBUL));
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_MONBUL, CAbstractFactory<CEyeball>::Create_TB(m_OriginPosition.x, m_OriginPosition.y + 50.f, 120.f, DIR_LEFT, OBJ_MONBUL));
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_MONBUL, CAbstractFactory<CEyeball>::Create_TB(m_OriginPosition.x, m_OriginPosition.y + 50.f, 150.f, DIR_LEFT, OBJ_MONBUL));
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_MONBUL, CAbstractFactory<CEyeball>::Create_TB(m_OriginPosition.x, m_OriginPosition.y + 50.f, 180.f, DIR_LEFT, OBJ_MONBUL));
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_MONBUL, CAbstractFactory<CEyeball>::Create_TB(m_OriginPosition.x, m_OriginPosition.y + 50.f, -30.f, DIR_LEFT, OBJ_MONBUL));
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_MONBUL, CAbstractFactory<CEyeball>::Create_TB(m_OriginPosition.x, m_OriginPosition.y + 50.f, -60.f, DIR_LEFT, OBJ_MONBUL));
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_MONBUL, CAbstractFactory<CEyeball>::Create_TB(m_OriginPosition.x, m_OriginPosition.y + 50.f, -90.f, DIR_LEFT, OBJ_MONBUL));
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_MONBUL, CAbstractFactory<CEyeball>::Create_TB(m_OriginPosition.x, m_OriginPosition.y + 50.f, -120.f, DIR_LEFT, OBJ_MONBUL));
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_MONBUL, CAbstractFactory<CEyeball>::Create_TB(m_OriginPosition.x, m_OriginPosition.y + 50.f, -150.f, DIR_LEFT, OBJ_MONBUL));
				m_bTargetRenderOn = false;
				m_tInfo.fCX = 150.f;
				m_tInfo.fCY = 150.f;
				m_dwWait = GetTickCount();
				m_BehaviorState = Exit;
				break;
			}
		}
		else
		{
			m_TargetPosition.x = m_targetObj->Get_Info().fX;
			m_TargetPosition.y = m_targetObj->Get_Info().fY;
			TargetMove_SD();
			m_bTargetRenderOn = true;
		}
		break;

	case Idle:
		m_dwWait = GetTickCount();
		m_BehaviorState = Exit;
		break;
	}
}

void CTrash::BehaviorExit()
{
	if (m_tFrame.iFrameStart > (m_tFrame.iFrameEnd - 1))
	{
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 0;
		m_fSpeed = 0.8f;
	}

	if (m_dwWait + 2000 < GetTickCount())
	{
		switch (m_CurrentPattern)
		{
		case Create:
			m_CurrentPattern = Idle;
			break;

		case Trash1:
			m_CurrentPattern = Idle;
			break;

		case Trash2:
			m_CurrentPattern = Idle;
			break;

		case Trash3:
			m_CurrentPattern = Return;
			break;

		case Return:
			m_CurrentPattern = Idle;
			break;

		case Idle:
			RandomPattern();
			break;
		}

		m_BehaviorState = Enter;
	}
}

bool CTrash::Dir()
{
	return false;
}

void CTrash::RandomPattern()
{
	srand((unsigned int)time((nullptr)));

	int RandomPattern = rand() % 3 + 1;

	switch (RandomPattern)
	{
	case 1:
		m_CurrentPattern = Trash1;
		return;

	case 2:
		m_CurrentPattern = Trash2;
		return;

	case 3:
		m_CurrentPattern = Trash3;
		return;
	}
}