#include "stdafx.h"
#include "Fire.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "ObjTestStageMgr.h"
#include "Item.h"
#include "SoundMgr.h"


CFire::CFire()
{
}


CFire::~CFire()
{
	Release();
}

void CFire::Initialize(void)
{
	m_eRender = RENDER_FIELDOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Obj/Fire_1.bmp", L"Fire");

	m_pFrameKey = L"Fire";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_bDead = false;
}

int CFire::Update(void)
{
	if (m_bDoNotRun)
	{
		return OBJ_NOEVENT;
	}
	else
	{
		if (m_bDead)
		{
			if (m_bColCheakFire)
			{
				srand((unsigned int)time((nullptr)));

				int iRanDrop = rand() % 100 + 1;
				int iRanItem = rand() % 100 + 1;

				switch (iRanDrop % 4 + 1)
				{
				case 1:
				{
					if (0 < iRanItem && 100 >= iRanItem)
					{
						CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItem>::Create_Item(m_eSceneID, m_tInfo.fX - 5, m_tInfo.fY, COIN));
					}
				}
				break;
				}
				CSoundMgr::Get_Instance()->PlaySoundW(L"FireEnd.wav", SOUND_FIRE, g_fSound);
				m_bColCheakFire = false;
			}

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 0;
			m_tFrame.dwTime = GetTickCount();
		}

		Update_Rect();

		return OBJ_NOEVENT;
	}
}

void CFire::Late_Update(void)
{
	if (m_bDoNotRun)
	{
		return;
	}
	else
	{
		Move_Frame();
	}
}

void CFire::Render(HDC hDC)
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

void CFire::Release(void)
{
}
