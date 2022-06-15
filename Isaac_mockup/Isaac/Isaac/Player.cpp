#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "ObjTestStageMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "PBullet.h"
#include "Boom.h"
#include "Eyeball.h"

CPlayer::CPlayer()
	: m_eCurState(IDLE)
	, m_ePreState(END)
	, m_eBullet(BULLET_DEFULT)
	, m_iCoin(0)
	, m_iBoom(0)
	, m_iKey(0)
	, m_dwCheak(0)
	, m_dwCool(GetTickCount())
	, m_CooldownA(false)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 400.f;

	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;

	m_fSpeed = 3.5f;

	m_fDiagonal = 100.f;

	m_iLife = 4;

	m_eRender = RENDER_PLAYER;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Player/Isaac_.bmp", L"Player");

	m_pFrameKey = L"Player";
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Key_Input();

	if (m_CooldownA)
	{
		if (m_dwCool + 5000 < GetTickCount())
		{
			m_dwCool = GetTickCount();
			m_CooldownA = false;
		}
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	Motion_Change();

	Move_Frame();
}

void CPlayer::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 								// 복사 받을, 최종적으로 그림을 그릴 DC
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

void CPlayer::Release(void)
{
}

void CPlayer::Key_Input(void)
{
	if (HIT == m_eCurState)
	{
		if (m_dwCheak + 1000 < GetTickCount())
		{
			m_dwCheak = GetTickCount();
			m_eCurState = IDLE;
			return;
		}
	}
	else if (GET_TRIPLE == m_eCurState)
	{
		if (m_dwCheak + 1200 < GetTickCount())
		{
			m_dwCheak = GetTickCount();
			m_eCurState = IDLE;
			return;
		}
	}
	else if (GET_ACTIVE_A == m_eCurState)
	{
		if (m_dwCheak + 1200 < GetTickCount())
		{
			m_dwCheak = GetTickCount();
			m_eCurState = IDLE;
			return;
		}
	}
	else
	{
		m_dwCheak = GetTickCount();

		if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
		{
			if (CKeyMgr::Get_Instance()->Key_Pressing('W'))
			{
				m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
				m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
				m_eCurState = WALKL;
			}
			else if (CKeyMgr::Get_Instance()->Key_Pressing('S'))
			{
				m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
				m_tInfo.fY += m_fSpeed / sqrtf(2.f);
				m_eCurState = WALKL;
			}
			else
			{
				m_tInfo.fX -= m_fSpeed;
				m_eCurState = WALKL;
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
		{
			if (CKeyMgr::Get_Instance()->Key_Pressing('W'))
			{
				m_tInfo.fX += m_fSpeed / sqrtf(2.f);
				m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
				m_eCurState = WALKR;
			}
			else if (CKeyMgr::Get_Instance()->Key_Pressing('S'))
			{
				m_tInfo.fX += m_fSpeed / sqrtf(2.f);
				m_tInfo.fY += m_fSpeed / sqrtf(2.f);
				m_eCurState = WALKR;
			}
			else
			{
				m_tInfo.fX += m_fSpeed;
				m_eCurState = WALKR;
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing('W'))
		{
			m_tInfo.fY -= m_fSpeed;
			m_eCurState = WALKU;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing('S'))
		{
			m_tInfo.fY += m_fSpeed;
			m_eCurState = WALKD;
		}

		if (CKeyMgr::Get_Instance()->Key_Up('A'))
		{
			m_eCurState = IDLE;
		}
		else if (CKeyMgr::Get_Instance()->Key_Up('D'))
		{
			m_eCurState = IDLE;
		}
		else if (CKeyMgr::Get_Instance()->Key_Up('W'))
		{
			m_eCurState = IDLE;
		}
		else if (CKeyMgr::Get_Instance()->Key_Up('S'))
		{
			m_eCurState = IDLE;
		}

		if (CKeyMgr::Get_Instance()->Key_Up(VK_UP))
		{
			if (BULLET_DEFULT == m_eBullet)
			{
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CPBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_UP));
			}
			else if (BULLET_EYEBALL == m_eBullet)
			{
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CEyeball>::Create_TB(m_tInfo.fX + 5, m_tInfo.fY + 5, 88.f, DIR_UP, OBJ_BULLET));
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CEyeball>::Create_TB(m_tInfo.fX, m_tInfo.fY, 90.f, DIR_UP, OBJ_BULLET));
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CEyeball>::Create_TB(m_tInfo.fX - 5, m_tInfo.fY - 5, 92.f, DIR_UP, OBJ_BULLET));
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Up(VK_DOWN))
		{
			if (BULLET_DEFULT == m_eBullet)
			{
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CPBullet>::Create(m_tInfo.fX, m_tInfo.fY + 10, DIR_DOWN));
			}
			else if (BULLET_EYEBALL == m_eBullet)
			{
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CEyeball>::Create_TB(m_tInfo.fX + 5, m_tInfo.fY + 15, -88.f, DIR_DOWN, OBJ_BULLET));
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CEyeball>::Create_TB(m_tInfo.fX, m_tInfo.fY + 10, -90.f, DIR_DOWN, OBJ_BULLET));
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CEyeball>::Create_TB(m_tInfo.fX - 5, m_tInfo.fY + 5, -92.f, DIR_DOWN, OBJ_BULLET));
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Up(VK_LEFT))
		{
			if (BULLET_DEFULT == m_eBullet)
			{
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CPBullet>::Create(m_tInfo.fX - 20, m_tInfo.fY + 10, DIR_LEFT));
			}
			else if (BULLET_EYEBALL == m_eBullet)
			{
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CEyeball>::Create_TB(m_tInfo.fX - 15, m_tInfo.fY + 5, 178.f, DIR_LEFT, OBJ_BULLET));
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CEyeball>::Create_TB(m_tInfo.fX - 20, m_tInfo.fY + 10, 180.f, DIR_LEFT, OBJ_BULLET));
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CEyeball>::Create_TB(m_tInfo.fX - 25, m_tInfo.fY + 15, -178.f, DIR_LEFT, OBJ_BULLET));
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Up(VK_RIGHT))
		{
			if (BULLET_DEFULT == m_eBullet)
			{
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CPBullet>::Create(m_tInfo.fX + 20, m_tInfo.fY + 10, DIR_RIGHT));
			}
			else if (BULLET_EYEBALL == m_eBullet)
			{
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CEyeball>::Create_TB(m_tInfo.fX + 25, m_tInfo.fY + 5, 2.f, DIR_RIGHT, OBJ_BULLET));
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CEyeball>::Create_TB(m_tInfo.fX + 20, m_tInfo.fY + 10, 0.f, DIR_RIGHT, OBJ_BULLET));
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CEyeball>::Create_TB(m_tInfo.fX + 15, m_tInfo.fY + 15, -2.f, DIR_RIGHT, OBJ_BULLET));
			}
		}

		if (CKeyMgr::Get_Instance()->Key_Up(VK_SHIFT) || CKeyMgr::Get_Instance()->Key_Up('E'))
		{
			if (0 < m_iBoom)
			{
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_BOOM, CAbstractFactory<CBoom>::Create(m_tInfo.fX, m_tInfo.fY + 10, DIR_DOWN));
				--m_iBoom;
			}
		}
		if (CKeyMgr::Get_Instance()->Key_Up(VK_SPACE))
		{
			if (m_bActiveA && !m_CooldownA)
			{
				m_CooldownA = true;
				m_dwCool = GetTickCount();
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_BOOM, CAbstractFactory<CBoom>::Create(m_tInfo.fX - 100, m_tInfo.fY - 80, DIR_DOWN));
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_BOOM, CAbstractFactory<CBoom>::Create(m_tInfo.fX - 70, m_tInfo.fY + 50, DIR_DOWN));
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_BOOM, CAbstractFactory<CBoom>::Create(m_tInfo.fX, m_tInfo.fY + 10, DIR_DOWN));
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_BOOM, CAbstractFactory<CBoom>::Create(m_tInfo.fX + 70, m_tInfo.fY - 50, DIR_DOWN));
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_BOOM, CAbstractFactory<CBoom>::Create(m_tInfo.fX + 100, m_tInfo.fY + 80, DIR_DOWN));
			}
			else
			{

			}
		}
		if (CKeyMgr::Get_Instance()->Key_Up('N'))
		{
			m_iLife = 1;
		}
		if (CKeyMgr::Get_Instance()->Key_Up('B'))
		{
			++m_iBoom;
		}
		if (CKeyMgr::Get_Instance()->Key_Up('C'))
		{
			++m_iCoin;
		}
		if (CKeyMgr::Get_Instance()->Key_Up('V'))
		{
			if (m_bGOD)
			{
				m_iLife = 6;
				m_bGOD = false;
			}
			else if (!m_bGOD)
			{
				m_iLife = 12;
				m_bGOD = true;
			}
		}
		if (CKeyMgr::Get_Instance()->Key_Up(VK_F1))
		{
			g_fSoundBGM = 0.f;

			CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_BGM, g_fSoundBGM);
		}
		if (CKeyMgr::Get_Instance()->Key_Up(VK_F2))
		{
			g_fSoundBGM -= 0.1f;


			if (g_fSoundBGM < 0.f)
				g_fSoundBGM = 0.f;

			CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_BGM, g_fSoundBGM);
		}
		if (CKeyMgr::Get_Instance()->Key_Up(VK_F3))
		{
			g_fSoundBGM += 0.1f;

			if (g_fSoundBGM > 1.f)
				g_fSoundBGM = 1.f;

			CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_BGM, g_fSoundBGM);
		}
	}
}

void CPlayer::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		if (BULLET_DEFULT == m_eBullet)
		{
			switch (m_eCurState)
			{
			case IDLE:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount();
				break;

			case WALKU:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 5;
				m_tFrame.iMotion = 3;
				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;

			case WALKD:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 9;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;

			case WALKL:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 1;
				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;

			case WALKR:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 8;
				m_tFrame.iMotion = 2;
				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;

			case HIT:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 6;
				m_tFrame.iMotion = 7;
				m_tFrame.dwSpeed = 150;
				m_tFrame.dwTime = GetTickCount();
				break;

			case GET_ACTIVE_A:
				CSoundMgr::Get_Instance()->PlaySoundW(L"ItemEat.wav", SOUND_EFFECT, g_fSound);
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.iMotion = 14;
				m_tFrame.dwSpeed = 300;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
		}
		else if (BULLET_EYEBALL == m_eBullet)
		{
			switch (m_eCurState)
			{
			case IDLE:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.iMotion = 9;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount();
				break;

			case WALKU:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 5;
				m_tFrame.iMotion = 12;
				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;

			case WALKD:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 9;
				m_tFrame.iMotion = 9;
				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;

			case WALKL:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 10;
				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;

			case WALKR:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 8;
				m_tFrame.iMotion = 11;
				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
				break;

			case HIT:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 6;
				m_tFrame.iMotion = 13;
				m_tFrame.dwSpeed = 150;
				m_tFrame.dwTime = GetTickCount();
				break;

			case GET_TRIPLE:
				CSoundMgr::Get_Instance()->PlaySoundW(L"ItemEat.wav", SOUND_EFFECT, g_fSound);
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.iMotion = 8;
				m_tFrame.dwSpeed = 300;
				m_tFrame.dwTime = GetTickCount();
				break;

			case GET_ACTIVE_A:
				CSoundMgr::Get_Instance()->PlaySoundW(L"ItemEat.wav", SOUND_EFFECT, g_fSound);
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.iMotion = 14;
				m_tFrame.dwSpeed = 300;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
		}
		m_ePreState = m_eCurState;
	}
}