#include "stdafx.h"
#include "Item.h"
#include "BmpMgr.h"


CItem::CItem()
	: m_ItemType(ITEM_END)
{
}


CItem::~CItem()
{
}

void CItem::Initialize(void)
{
	m_eRender = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Obj/item3.bmp", L"Item");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Stage/eyeball.bmp", L"Active");

	

	if (LIFE == m_ItemType)
	{
		m_tInfo.fCX = 54.f;
		m_tInfo.fCY = 58.f;

		m_pFrameKey = L"Item";

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 4;
		m_tFrame.iMotion = 3;
		m_tFrame.dwSpeed = 130;
		m_tFrame.dwTime = GetTickCount();
	}
	else if (COIN == m_ItemType)
	{
		m_tInfo.fCX = 54.f;
		m_tInfo.fCY = 58.f;

		m_pFrameKey = L"Item";

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 5;
		m_tFrame.iMotion = 1;
		m_tFrame.dwSpeed = 130;
		m_tFrame.dwTime = GetTickCount();
	}
	else if (BOOM == m_ItemType)
	{
		m_tInfo.fCX = 54.f;
		m_tInfo.fCY = 58.f;

		m_pFrameKey = L"Item";

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 3;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 130;
		m_tFrame.dwTime = GetTickCount();
	}
	else if (KEY == m_ItemType)
	{
		m_tInfo.fCX = 54.f;
		m_tInfo.fCY = 58.f;

		m_pFrameKey = L"Item";

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 4;
		m_tFrame.iMotion = 5;
		m_tFrame.dwSpeed = 130;
		m_tFrame.dwTime = GetTickCount();
	}
	else if (TRIPLE == m_ItemType)
	{
		m_tInfo.fCX = 70.f;
		m_tInfo.fCY = 70.f;

		m_pFrameKey = L"Active";

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 4;
		m_tFrame.iMotion = 1;
		m_tFrame.dwSpeed = 130;
		m_tFrame.dwTime = GetTickCount();
	}
	else if (ACTIVE_A == m_ItemType)
	{
		m_tInfo.fCX = 70.f;
		m_tInfo.fCY = 70.f;

		m_pFrameKey = L"Active";

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 4;
		m_tFrame.iMotion = 3;
		m_tFrame.dwSpeed = 130;
		m_tFrame.dwTime = GetTickCount();
	}
}

int CItem::Update(void)
{
	if (m_bDoNotRun)
	{
		return OBJ_NOEVENT;
	}
	else
	{
		if (m_bDead)
		{
			return OBJ_DEAD;
		}

		Update_Rect();

		return OBJ_NOEVENT;
	}
}

void CItem::Late_Update(void)
{
	if (m_bDoNotRun)
	{
		return;
	}
	else
	{
		if (m_tRect.left < 52 || m_tRect.right > 747 || m_tRect.top < 146 || m_tRect.bottom > 550)
		{
			Set_Dead();
		}

		if (1 == Move_Frame_Item())
		{
			if (m_pFrameKey == L"Item")
			{
				if (0 == m_tFrame.iMotion) // boom
				{
					m_tFrame.iFrameStart = 2;
				}

				else if (1 == m_tFrame.iMotion) // coin
				{
					m_tFrame.iMotion++;
					m_tFrame.iFrameEnd = 1;
				}
				else if (3 == m_tFrame.iMotion) // life
				{
					m_tFrame.iMotion++;
					m_tFrame.iFrameEnd = 1;
				}
				else if (5 == m_tFrame.iMotion) // key
				{
					m_tFrame.iMotion++;
					m_tFrame.iFrameEnd = 1;
				}
			}
			else
			{
				if (1 == m_tFrame.iMotion)
				{
					m_tFrame.iFrameEnd = 1;
					m_tFrame.iMotion--;
				}
				else if (3 == m_tFrame.iMotion)
				{
					m_tFrame.iFrameEnd = 1;
					m_tFrame.iMotion--;
				}
			}
		}
	}
}

void CItem::Render(HDC hDC)
{
	if (m_bDoNotRun)
	{
		return;
	}
	else
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

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
}

void CItem::Release(void)
{
}

int CItem::Move_Frame_Item(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		m_tFrame.iFrameStart++;

		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = 0;
			return 1;
		}
	}
	return 0;
}
