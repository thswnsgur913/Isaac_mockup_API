#include "stdafx.h"
#include "Stone.h"
#include "BmpMgr.h"


CStone::CStone()
{
}


CStone::~CStone()
{
	Release();
}

void CStone::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_eRender = RENDER_FIELDOBJECT;

	m_bDead = false;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Obj/stone.bmp", L"Stone");

	m_pFrameKey = L"Stone";
}

int CStone::Update(void)
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
		else
		{
			Update_Rect();

			return OBJ_NOEVENT;
		}
	}
}

void CStone::Late_Update(void)
{
}

void CStone::Render(HDC hDC)
{
	if (m_bDoNotRun)
	{
		return;
	}
	else
	{
		if (m_bDead)
		{
			return;
		}
		else
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
	}
}

void CStone::Release(void)
{
}
