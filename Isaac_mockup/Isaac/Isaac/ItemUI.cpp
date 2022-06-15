#include "stdafx.h"
#include "ItemUI.h"
#include "ObjTestStageMgr.h"
#include "BmpMgr.h"

CItemUI::CItemUI()
	: m_ItemID(ITEM_END)
{
}

CItemUI::~CItemUI()
{
}

void CItemUI::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/UI/UI_count.bmp", L"UI_count");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/UI/UI_hp.bmp", L"UI_hp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/UI/UI_bt.bmp", L"UI_bt");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/UI/UI_at.bmp", L"UI_at");

	m_eRender = RENDER_UI;

	if (LIFE == m_ItemID)
	{
		m_tInfo.fCX = 204.f;
		m_tInfo.fCY = 29.f;

		m_pFrameKey = L"UI_hp";

		m_iLife = dynamic_cast<CPlayer*>(CObjTestStageMgr::Get_Instance()->Get_Player())->Get_Life();

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 0;
		m_tFrame.iMotion = m_iLife;
		m_tFrame.dwSpeed = 0;
		m_tFrame.dwTime = GetTickCount();
	}
	else if (COIN == m_ItemID)
	{
		m_tInfo.fCX = 12.f;
		m_tInfo.fCY = 27.f;

		m_pFrameKey = L"UI_count";

		m_iCoin = dynamic_cast<CPlayer*>(CObjTestStageMgr::Get_Instance()->Get_Player())->Get_Coin();

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 0;
		m_tFrame.iMotion = m_iCoin;
		m_tFrame.dwSpeed = 0;
		m_tFrame.dwTime = GetTickCount();
	}
	else if (BOOM == m_ItemID)
	{
		m_tInfo.fCX = 12.f;
		m_tInfo.fCY = 27.f;

		m_pFrameKey = L"UI_count";

		m_iBoom = dynamic_cast<CPlayer*>(CObjTestStageMgr::Get_Instance()->Get_Player())->Get_Boom();

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 0;
		m_tFrame.iMotion = m_iBoom;
		m_tFrame.dwSpeed = 0;
		m_tFrame.dwTime = GetTickCount();
	}
	else if (KEY == m_ItemID)
	{
		m_tInfo.fCX = 12.f;
		m_tInfo.fCY = 27.f;

		m_pFrameKey = L"UI_count";

		m_iKey = dynamic_cast<CPlayer*>(CObjTestStageMgr::Get_Instance()->Get_Player())->Get_Key();

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 0;
		m_tFrame.iMotion = m_iKey;
		m_tFrame.dwSpeed = 0;
		m_tFrame.dwTime = GetTickCount();
	}
	else if (TRIPLE == m_ItemID)
	{
		m_tInfo.fCX = 64.f;
		m_tInfo.fCY = 70.f;

		m_pFrameKey = L"UI_bt";

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 0;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 0;
		m_tFrame.dwTime = GetTickCount();
	}
	else if (ACTIVE_A == m_ItemID)
	{
		m_tInfo.fCX = 45.f;
		m_tInfo.fCY = 50.f;

		m_pFrameKey = L"UI_at";

		m_tFrame.iFrameStart = 2;
		m_tFrame.iFrameEnd = 2;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 0;
		m_tFrame.dwTime = GetTickCount();
	}
}

int CItemUI::Update(void)
{
	Update_Rect();

	return 0;
}

void CItemUI::Late_Update(void)
{
	if (LIFE == m_ItemID)
	{
		m_iLife = dynamic_cast<CPlayer*>(CObjTestStageMgr::Get_Instance()->Get_Player())->Get_Life();

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 0;
		m_tFrame.iMotion = m_iLife;
		m_tFrame.dwSpeed = 0;
		m_tFrame.dwTime = GetTickCount();
	}
	else if (COIN == m_ItemID)
	{
		m_iCoin = dynamic_cast<CPlayer*>(CObjTestStageMgr::Get_Instance()->Get_Player())->Get_Coin();

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 0;
		m_tFrame.iMotion = m_iCoin;
		m_tFrame.dwSpeed = 0;
		m_tFrame.dwTime = GetTickCount();
	}
	else if (BOOM == m_ItemID)
	{
		m_iBoom = dynamic_cast<CPlayer*>(CObjTestStageMgr::Get_Instance()->Get_Player())->Get_Boom();

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 0;
		m_tFrame.iMotion = m_iBoom;
		m_tFrame.dwSpeed = 0;
		m_tFrame.dwTime = GetTickCount();
	}
	else if (KEY == m_ItemID)
	{
		m_iKey = dynamic_cast<CPlayer*>(CObjTestStageMgr::Get_Instance()->Get_Player())->Get_Key();

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 0;
		m_tFrame.iMotion = m_iKey;
		m_tFrame.dwSpeed = 0;
		m_tFrame.dwTime = GetTickCount();
	}
	else if (TRIPLE == m_ItemID)
	{
		if (BULLET_DEFULT == dynamic_cast<CPlayer*>(CObjTestStageMgr::Get_Instance()->Get_Player())->Get_BulletType())
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 0;
			m_tFrame.dwTime = GetTickCount();
		}
		else
		{
			m_tFrame.iFrameStart = 1;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 0;
			m_tFrame.dwTime = GetTickCount();
		}
	}
	else if (ACTIVE_A == m_ItemID)
	{
		if (dynamic_cast<CPlayer*>(CObjTestStageMgr::Get_Instance()->Get_Player())->Get_ActiveA())
		{
			if (dynamic_cast<CPlayer*>(CObjTestStageMgr::Get_Instance()->Get_Player())->Get_CooldownA())
			{
				m_tFrame.iFrameStart = 1;
				m_tFrame.iFrameEnd = 1;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 0;
				m_tFrame.dwTime = GetTickCount();
			}
			else
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 0;
				m_tFrame.dwTime = GetTickCount();
			}
		}
		else
		{
			m_tFrame.iFrameStart = 2;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 0;
			m_tFrame.dwTime = GetTickCount();
		}
	}

	Move_Frame();
}

void CItemUI::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	if (TRIPLE == m_ItemID)
	{
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
	else if(ACTIVE_A == m_ItemID)
	{
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
	else
	{
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
			RGB(0, 0, 255));						// 제거하고자 하는 색상
	}
}

void CItemUI::Release(void)
{
}
