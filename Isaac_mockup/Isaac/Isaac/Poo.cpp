#include "stdafx.h"
#include "Poo.h"
#include "Item.h"
#include "AbstractFactory.h"
#include "ObjTestStageMgr.h"
#include "BmpMgr.h"


CPoo::CPoo()
{
}


CPoo::~CPoo()
{
	Release();
}

void CPoo::Initialize(void)
{
	m_eRender = RENDER_FIELDOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Obj/Poo.bmp", L"Poo");

	m_pFrameKey = L"Poo";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 0;
	m_tFrame.dwTime = GetTickCount();

	m_bDead = false;

	m_bColCheak = false;
}

int CPoo::Update(void)
{
	if (m_bDoNotRun)
	{
		return OBJ_NOEVENT;
	}
	else
	{
		if (m_bDead)
		{
			if (m_bColCheak)
			{
				srand((unsigned int)time((nullptr)));

				int iRanDrop = rand() % 100 + 1;
				int iRanItem = rand() % 100 + 1;

				switch (iRanDrop % 1 + 1)
				{
				case 1:
				{
					if (0 < iRanItem && 25 >= iRanItem)
					{
						CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_LIFE, CAbstractFactory<CItem>::Create_Item(m_eSceneID, m_tInfo.fX, m_tInfo.fY, LIFE));
					}
					else if (25 < iRanItem && 67 >= iRanItem)
					{
						CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItem>::Create_Item(m_eSceneID, m_tInfo.fX, m_tInfo.fY, BOOM));
					}
					else if (67 < iRanItem && 100 >= iRanItem)
					{
						CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItem>::Create_Item(m_eSceneID, m_tInfo.fX - 5, m_tInfo.fY, COIN));
					}
				}
				break;
				}
				m_bColCheak = false;
			}
		}

		Update_Rect();

		return OBJ_NOEVENT;
	}
}

void CPoo::Late_Update(void)
{
	if (m_bDoNotRun)
	{
		return;
	}
	else
	{
		if (m_bColCheak)
		{
			if (3 == m_tFrame.iFrameStart)
			{
				Set_Dead();
			}
			else
			{
				m_tFrame.iFrameStart++;
				if (3 > m_tFrame.iFrameStart)
				{
					m_bColCheak = false;
				}
			}
		}
	}
}

void CPoo::Render(HDC hDC)
{
	if (m_bDoNotRun)
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

void CPoo::Release(void)
{
}
