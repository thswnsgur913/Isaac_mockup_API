#include "stdafx.h"
#include "Hopper.h"
#include "BmpMgr.h"
#include "SoundMgr.h"


CHopper::CHopper()
{
}


CHopper::~CHopper()
{
	Release();
}

void CHopper::Initialize(void)
{
	m_tInfo.fCX = 76.3f;
	m_tInfo.fCY = 50.f;

	m_tInfo.fRenX = 76.3f;
	m_tInfo.fRenY = 97.f;

	m_fSpeed = 5.f;

	m_iLife = 3;

	m_CurrentPattern = Create;

	m_dwTime = GetTickCount();
	m_dwWait = GetTickCount();

	m_eRender = RENDER_PLAYER;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Monster/Hopper.bmp", L"Hopper");

	m_pFrameKey = L"Hopper";

	m_MotionIdle = 0;
	m_MotionHit = 1;
	m_MonState = MONSTATE_IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.dwSpeed = 300;
	m_tFrame.dwTime = GetTickCount();
}

void CHopper::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 								// ���� ����, ���������� �׸��� �׸� DC
		int(m_RenLeft),							// 2,3 ���� :  ������� ��ġ X, Y
		int(m_RenTop),
		int(m_tInfo.fRenX),							// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fRenY),
		hMemDC,										// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fRenX,	// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fRenY,
		(int)m_tInfo.fRenX,							// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fRenY,
		RGB(255, 255, 255));						// �����ϰ��� �ϴ� ����
}

void CHopper::Release(void)
{
}

void CHopper::Motion_Change(void)
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

void CHopper::BehaviorEnter()
{
	if (!m_targetObj)
		return;

	switch (m_CurrentPattern)
	{
	case Create:
		break;

	case Hopper:
		m_TargetPosition.x = m_targetObj->Get_Info().fX;
		m_TargetPosition.y = m_targetObj->Get_Info().fY;
		break;
	}

	m_BehaviorState = Execute;
}

void CHopper::BehaviorExecute()
{
	if (!m_targetObj)
		return;

	switch (m_CurrentPattern)
	{
	case Create:
		m_dwWait = GetTickCount();
		m_BehaviorState = Exit;
		break;

	case Hopper:
		if (TargetMove_B())
		{
			if (5 == m_tFrame.iFrameStart)
			{
				CSoundMgr::Get_Instance()->PlaySoundW(L"Monster3.wav", SOUND_EFFECT, g_fSound);
				m_dwWait = GetTickCount();
				m_BehaviorState = Exit;
				break;
			}
		}
	}
}

void CHopper::BehaviorExit()
{
	m_tFrame.iFrameEnd = 0;

	if (m_dwWait + 1000 < GetTickCount())
	{
		m_tFrame.iFrameEnd = 5;

		if (2 == m_tFrame.iFrameStart)
		{
			switch (m_CurrentPattern)
			{
			case Create:
				m_CurrentPattern = Hopper;
				break;

			case Hopper:
				m_CurrentPattern = Hopper;
				break;
			}

			m_BehaviorState = Enter;
		}
	}
}

bool CHopper::Dir()
{
	return false;
}
