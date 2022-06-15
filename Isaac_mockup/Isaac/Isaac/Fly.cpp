#include "stdafx.h"
#include "Fly.h"
#include "BmpMgr.h"
#include "SoundMgr.h"


CFly::CFly()
{
}

CFly::~CFly()
{
	Release();
}

void CFly::Initialize(void)
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_fSpeed = 1.5f;

	m_iLife = 2;

	m_CurrentPattern = Create;

	m_dwTime = GetTickCount();

	m_eRender = RENDER_BOSSFLY;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Monster/Fly_.bmp", L"Fly");

	m_pFrameKey = L"Fly";

	m_MotionIdle = 1;
	m_MotionHit = 3;
	m_MonState = MONSTATE_IDLE;
}

void CFly::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 								// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left),							// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top),
		int(m_tInfo.fCX),							// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hMemDC,										// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,	// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,							// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));						// �����ϰ��� �ϴ� ����
}

void CFly::Release(void)
{
}

void CFly::Motion_Change(void)
{
	if (m_eMonState != m_MonState)
	{
		switch (m_MonState)
		{
		case MONSTATE_IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = m_MotionIdle;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case MONSTATE_HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = m_MotionHit;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			m_dwTime = GetTickCount();
			break;
		}
		m_eMonState = m_MonState;
	}
}

void CFly::BehaviorEnter()
{
	if (!m_targetObj)
		return;

	switch (m_CurrentPattern)
	{
	case Create:
		break;

	case Fly1:
		m_fSpeed = 2.f;
		break;

	case Fly2:
		break;
	}

	m_BehaviorState = Execute;
}

void CFly::BehaviorExecute()
{
	if (!m_targetObj)
		return;

	switch (m_CurrentPattern)
	{
	case Create:
		m_BehaviorState = Exit;
		break;

	case Fly1:
		if (TargetMove_B())
		{
			m_fSpeed = 1.5f;
			m_BehaviorState = Exit;
			break;
		}
		break;

	case Fly2:
	{
		m_TargetPosition.x = m_targetObj->Get_Info().fX;
		m_TargetPosition.y = m_targetObj->Get_Info().fY;
		TargetMove_V();
	}
	}
}

void CFly::BehaviorExit()
{
	switch (m_CurrentPattern)
	{
	case Create:
		m_CurrentPattern = Fly2;
		break;

	case Fly1:
		m_CurrentPattern = Fly2;
		break;

	case Fly2:
		m_CurrentPattern = Fly2;
		break;
	}

	m_BehaviorState = Enter;
}

bool CFly::Dir()
{
	return false;
}

float CFly::Fly_Player()
{
	// abs : ���밪�� �����ִ� �Լ�
	float	fWidth = fabs(m_tInfo.fX - m_targetObj->Get_Info().fX);
	float	fHeight = fabs(m_tInfo.fY - m_targetObj->Get_Info().fY);

	// sqrt : ��Ʈ�� �����ִ� �Լ�
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float fSound = 1.f;

	m_fMonsterSound = fSound - (0.001f * fDiagonal);

	return m_fMonsterSound;
}