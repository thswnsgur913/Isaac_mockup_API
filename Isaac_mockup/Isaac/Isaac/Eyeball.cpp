#include "stdafx.h"
#include "Eyeball.h"
#include "BmpMgr.h"
#include "SoundMgr.h"

CEyeball::CEyeball()
{
}


CEyeball::~CEyeball()
{
	Release();
}

void CEyeball::Initialize(void)
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_fSpeed = 5.5f;

	m_dwCheck = GetTickCount();

	m_fTemp = 0.f;

	m_eRender = RENDER_PLAYER;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Player/Bullet.bmp", L"Bullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Player/MonBul.bmp", L"MonBul");

	switch (m_GetBulID)
	{
	case OBJ_BULLET:
		CSoundMgr::Get_Instance()->StopSound(SOUND_EYE);
		CSoundMgr::Get_Instance()->PlaySound(L"Bullet.wav", SOUND_EYE, g_fSound);
		m_pFrameKey = L"Bullet";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 1;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 100;
		m_tFrame.dwTime = GetTickCount();
		break;

	case OBJ_MONBUL:
		CSoundMgr::Get_Instance()->StopSound(SOUND_MBUL);
		CSoundMgr::Get_Instance()->PlaySound(L"Bullet.wav", SOUND_MBUL, g_fSound);
		m_pFrameKey = L"MonBul";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 2;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 100;
		m_tFrame.dwTime = GetTickCount();
		break;
	}
}

int CEyeball::Update(void)
{
	if (m_bDead)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_BULLET_END);
		CSoundMgr::Get_Instance()->PlaySound(L"BulletEnd.wav", SOUND_BULLET_END, g_fSound);
		return OBJ_DEAD;
	}

	switch (m_eDir)
	{
	case DIR_LEFT:
		m_tInfo.fX += (m_fSpeed - m_fTemp) * cosf(m_fAngle * DEGREE);
		m_tInfo.fY -= (m_fSpeed - m_fTemp) * sinf(m_fAngle * DEGREE);
		m_fTemp += 0.05f;
		if (m_dwCheck + 1500 < GetTickCount())
		{
			Set_Dead();
			m_dwCheck = GetTickCount();
			m_fTemp = 0.f;
		}
		break;

	case DIR_UP:
		m_tInfo.fX += (m_fSpeed - m_fTemp) * cosf(m_fAngle * DEGREE);
		m_tInfo.fY -= (m_fSpeed - m_fTemp) * sinf(m_fAngle * DEGREE);
		m_fTemp += 0.07f;
		if (m_dwCheck + 1200 < GetTickCount())
		{
			Set_Dead();
			m_dwCheck = GetTickCount();
			m_fTemp = 0.f;
		}
		break;

	case DIR_RIGHT:
		m_tInfo.fX += (m_fSpeed - m_fTemp) * cosf(m_fAngle * DEGREE);
		m_tInfo.fY -= (m_fSpeed - m_fTemp) * sinf(m_fAngle * DEGREE);
		m_fTemp += 0.05f;
		if (m_dwCheck + 1500 < GetTickCount())
		{
			Set_Dead();
			m_dwCheck = GetTickCount();
			m_fTemp = 0.f;
		}
		break;

	case DIR_DOWN:
		m_tInfo.fX += (m_fSpeed - m_fTemp) * cosf(m_fAngle * DEGREE);
		m_tInfo.fY -= (m_fSpeed - m_fTemp) * sinf(m_fAngle * DEGREE);
		m_fTemp += 0.07f;
		if (m_dwCheck + 1200 < GetTickCount())
		{
			Set_Dead();
			m_dwCheck = GetTickCount();
			m_fTemp = 0.f;
		}
		break;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CEyeball::Late_Update(void)
{
	if (m_tRect.left < 52 || m_tRect.right > 747 || m_tRect.top < 146 || m_tRect.bottom > 550)
	{
		Set_Dead();
	}

	Move_Frame();
}

void CEyeball::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 							// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left),							// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top),
		int(m_tInfo.fCX),							// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,										// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,	// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,							// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));						// 제거하고자 하는 색상
}

void CEyeball::Release(void)
{
}

void CEyeball::Motion_Change(void)
{
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 1000;
	m_tFrame.dwTime = GetTickCount();
}
