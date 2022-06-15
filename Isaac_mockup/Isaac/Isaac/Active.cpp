#include "stdafx.h"
#include "Active.h"
#include "BmpMgr.h"


CActive::CActive()
	: m_ItemType(ITEM_END)
{
}


CActive::~CActive()
{
	Release();
}

void CActive::Initialize(void)
{
	m_tInfo.fCX = 70.f;
	m_tInfo.fCY = 70.f;

	m_eRender = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Stage/eyeball.bmp", L"Active_A");

	else if (ACTIVE_A == m_ItemType)
	{
		m_tInfo.fCX = 70.f;
		m_tInfo.fCY = 70.f;

		m_pFrameKey = L"Active_A";

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 4;
		m_tFrame.iMotion = 1;
		m_tFrame.dwSpeed = 130;
		m_tFrame.dwTime = GetTickCount();
	}
	else if (ACTIVE_B == m_ItemType)
	{
		m_tInfo.fCX = 70.f;
		m_tInfo.fCY = 70.f;

		m_pFrameKey = L"Active_B";

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 5;
		m_tFrame.iMotion = 1;
		m_tFrame.dwSpeed = 130;
		m_tFrame.dwTime = GetTickCount();
	}
}

int CActive::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CActive::Late_Update(void)
{
	if (1 == Move_Frame_Active())
	{
		if (1 == m_tFrame.iMotion)
		{
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion--;
		}
	}
}

void CActive::Render(HDC hDC)
{
	switch (m_ItemType)
	{
	case ACTIVE_A:
		ActiveA_Render(hDC);
		break;

	case ACTIVE_B:
		ActiveB_Render(hDC);
		break;
	}
}

void CActive::Release(void)
{
}

void CActive::ActiveA_Render(HDC hDC)
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

void CActive::ActiveB_Render(HDC hDC)
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

int CActive::Move_Frame_Active(void)
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
