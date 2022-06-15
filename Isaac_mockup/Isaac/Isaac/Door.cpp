#include "stdafx.h"
#include "Door.h"
#include "BmpMgr.h"
#include "ObjTestStageMgr.h"
#include "SceneMgr.h"
#include "Player.h"


CDoor::CDoor()
{
}


CDoor::~CDoor()
{
}

void CDoor::Initialize(void)
{
	m_eRender = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Door/DoorL.bmp", L"Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Door/DoorR.bmp", L"Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Door/DoorT.bmp", L"Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Door/DoorD.bmp", L"Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Door/DoorRT.bmp", L"Boss");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Door/DoorEnd.bmp", L"End");

	if (DIR_LEFT == m_DoorDir)
	{
		m_tInfo.fCX = 80.f;
		m_tInfo.fCY = 120.f;

		m_pFrameKey = L"Left";

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 5;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 200;
		m_tFrame.dwTime = GetTickCount();
	}
	else if (DIR_RIGHT == m_DoorDir)
	{
		m_tInfo.fCX = 80.f;
		m_tInfo.fCY = 120.f;

		m_pFrameKey = L"Right";

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 5;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 200;
		m_tFrame.dwTime = GetTickCount();
	}
	else if (DIR_UP == m_DoorDir)
	{
		m_tInfo.fCX = 120.f;
		m_tInfo.fCY = 80.f;

		m_pFrameKey = L"Up";

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 5;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 200;
		m_tFrame.dwTime = GetTickCount();
	}
	else if (DIR_DOWN == m_DoorDir)
	{
		m_tInfo.fCX = 120.f;
		m_tInfo.fCY = 80.f;

		m_pFrameKey = L"Down";

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 5;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 200;
		m_tFrame.dwTime = GetTickCount();
	}
	else if (DIR_UP_BOSS == m_DoorDir)
	{
		m_tInfo.fCX = 120.f;
		m_tInfo.fCY = 80.f;

		m_pFrameKey = L"Up";

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 5;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 200;
		m_tFrame.dwTime = GetTickCount();
	}
	else if (DIR_UP_END == m_DoorDir)
	{
		m_tInfo.fCX = 100.f;
		m_tInfo.fCY = 100.f;

		m_pFrameKey = L"End";

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 3;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 200;
		m_tFrame.dwTime = GetTickCount();
	}
}

int CDoor::Update(void)
{
	if (m_bDead)
	{
		if (m_bColCheak)
		{
			switch (m_bKeyCheak)
			{
			case true:
				if (0 < dynamic_cast<CPlayer*>(CObjTestStageMgr::Get_Instance()->Get_Player())->Get_Key())
				{
					if (1 == CObjTestStageMgr::Get_Instance()->Get_Cheak_KeyDoor())
					{
						CSceneMgr::Get_Instance()->Scene_Change(m_eNextID);
					}
					else
					{
						dynamic_cast<CPlayer*>(CObjTestStageMgr::Get_Instance()->Get_Player())->Minus_Key();
						CObjTestStageMgr::Get_Instance()->Set_Cheak_KeyDoor(1);
						CSceneMgr::Get_Instance()->Scene_Change(m_eNextID);
					}
				}
				else if (1 == CObjTestStageMgr::Get_Instance()->Get_Cheak_KeyDoor())
				{
					CSceneMgr::Get_Instance()->Scene_Change(m_eNextID);
				}
				else
				{
					m_bDead = false;
					m_bColCheak = false;
				}
				break;

			case false:
				CSceneMgr::Get_Instance()->Scene_Change(m_eNextID);
				break;
			}
		}
		return OBJ_DEAD;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CDoor::Late_Update(void)
{
	if (m_bKeyCheak)
	{
		if (0 < dynamic_cast<CPlayer*>(CObjTestStageMgr::Get_Instance()->Get_Player())->Get_Key())
		{
			if (m_tFrame.iFrameStart < m_tFrame.iFrameEnd)
			{
				Move_Frame();
			}
		}
		else if (1 == CObjTestStageMgr::Get_Instance()->Get_Cheak_KeyDoor())
		{
			if (m_tFrame.iFrameStart < m_tFrame.iFrameEnd)
			{
				Move_Frame();
			}
		}
	}
	else
	{
		if (m_bCheakMon)
		{
			if (m_tFrame.iFrameStart < m_tFrame.iFrameEnd)
			{
				Move_Frame();
			}
			if (DIR_UP_BOSS == m_DoorDir)
			{
				if (m_tFrame.iFrameStart < m_tFrame.iFrameEnd)
				{
					Move_Frame();
				}
				else
				{
					m_tInfo.fCX = 120.f;
					m_tInfo.fCY = 120.f;

					m_pFrameKey = L"Boss";

					m_tFrame.iFrameStart = 1;
					m_tFrame.iFrameEnd = 1;
					m_tFrame.iMotion = 0;
					m_tFrame.dwSpeed = 200;
					m_tFrame.dwTime = GetTickCount();
				}
			}
		}
	}
}

void CDoor::Render(HDC hDC)
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

void CDoor::Release(void)
{
}
