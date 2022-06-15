#include "stdafx.h"
#include "Stage2.h"
#include "BmpMgr.h"
#include "ObjTestStageMgr.h"
#include "UIMgr.h"
#include "AbstractFactory.h"
#include "Item.h"
#include "ItemUI.h"
#include "Door.h"
#include "Wall.h"
#include "Stone.h"
#include "ColorStone.h"
#include "Poo.h"
#include "SoundMgr.h"

CStage2::CStage2()
{
}


CStage2::~CStage2()
{
	Release();
}

void CStage2::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/UI/Defult.bmp", L"Stage");

	if (0 == CObjTestStageMgr::Get_Instance()->Get_Cheak_Stage2_In())
	{
		CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_POO, CAbstractFactory<CPoo>::Create_Object(SC_STAGE2, 100.f, 200.f, 49.f, 50.f));
		CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_POO, CAbstractFactory<CPoo>::Create_Object(SC_STAGE2, 100.f, 495.f, 49.f, 50.f));

		CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_STONE, CAbstractFactory<CStone>::Create_Stone(SC_STAGE2, 700.f, 200.f, 1, 1, 0));
		CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_STONE, CAbstractFactory<CStone>::Create_Stone(SC_STAGE2, 100.f, 345.f, 0, 0, 1));
		CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_STONE, CAbstractFactory<CColorStone>::Create_Stone(SC_STAGE2, 250.f, 345.f, 1, 1, 1));
		CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_STONE, CAbstractFactory<CStone>::Create_Stone(SC_STAGE2, 550.f, 345.f, 1, 1, 0));		
		CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_STONE, CAbstractFactory<CStone>::Create_Stone(SC_STAGE2, 400.f, 495.f, 0, 0, 1));	
		CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_STONE, CAbstractFactory<CStone>::Create_Stone(SC_STAGE2, 700.f, 495.f, 0, 0, 1));
	}
	else
	{
		CObjTestStageMgr::Get_Instance()->Set_DoRun(SC_STAGE2, OBJ_LIFE);
		CObjTestStageMgr::Get_Instance()->Set_DoRun(SC_STAGE2, OBJ_ITEM);
		CObjTestStageMgr::Get_Instance()->Set_DoRun(SC_STAGE2, OBJ_POO);
		CObjTestStageMgr::Get_Instance()->Set_DoRun(SC_STAGE2, OBJ_STONE);
	}

	CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create_Wall(400.f, 165.f, 650.f, 2.f)); // top
	CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create_Wall(400.f, 530.f, 650.f, 2.f)); // bottom
	CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create_Wall(68.f, 350.f, 2.f, 355.f)); // left
	CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create_Wall(735.f, 350.f, 2.f, 355.f)); // right

	CUIMgr::Get_Instance()->Add_UI(UI_ITEM, CAbstractFactory<CItemUI>::Item_UI(675.f, 35.f, LIFE));
	CUIMgr::Get_Instance()->Add_UI(UI_ITEM, CAbstractFactory<CItemUI>::Item_UI(360.f, 20.5f, COIN));
	CUIMgr::Get_Instance()->Add_UI(UI_ITEM, CAbstractFactory<CItemUI>::Item_UI(360.f, 45.5f, BOOM));
	CUIMgr::Get_Instance()->Add_UI(UI_ITEM, CAbstractFactory<CItemUI>::Item_UI(360.f, 71.f, KEY));
	CUIMgr::Get_Instance()->Add_UI(UI_ITEM, CAbstractFactory<CItemUI>::Item_UI(435.f, 45.f, TRIPLE));
	CUIMgr::Get_Instance()->Add_UI(UI_ITEM, CAbstractFactory<CItemUI>::Item_UI(510.f, 40.f, ACTIVE_A));
	CUIMgr::Get_Instance()->Add_UI(UI_MAP, CAbstractFactory<CMapUI>::Map_UI(150.f, 50.f, SC_STAGE2));

	CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_DOOR, CAbstractFactory<CDoor>::Create_Door(765.f, 350.f, false, SC_STAGE2, SC_STAGE1, DIR_RIGHT));
	CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_DOOR, CAbstractFactory<CDoor>::Create_Door(400.f, 130.f, false, SC_STAGE2, SC_STAGEBOSS, DIR_UP_BOSS));

	m_dwCount = GetTickCount();

	Cheak_BossD = false;
}

void CStage2::Update(void)
{
	CObjTestStageMgr::Get_Instance()->Update();

	CUIMgr::Get_Instance()->Update();
}

void CStage2::Late_Update(void)
{
	CObjTestStageMgr::Get_Instance()->Late_Update();

	CUIMgr::Get_Instance()->Late_Update();

	if (!CObjTestStageMgr::Get_Instance()->Cheak_OBJ(OBJ_FLY))
	{
		CSoundMgr::Get_Instance()->PlayFLY(L"Wing.wav", SOUND_FLY, g_fSound);
	}
	else
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_FLY);
	}

	if (0 == CObjTestStageMgr::Get_Instance()->Get_Cheak_Stage2_In())
	{
		CObjTestStageMgr::Get_Instance()->Cheak_Key(SC_STAGE2, OBJ_ITEM);

		if (CObjTestStageMgr::Get_Instance()->Cheak_Open_Poo(SC_STAGE2, OBJ_POO, 200.f))
		{
			if (CObjTestStageMgr::Get_Instance()->Cheak_Open_Poo(SC_STAGE2, OBJ_POO, 495.f))
			{
				if (m_dwCount + 3000 < GetTickCount())
				{
					CObjTestStageMgr::Get_Instance()->CreateMonster(FLY, 100.f, 200.f);
					CObjTestStageMgr::Get_Instance()->CreateMonster(FLY, 100.f, 495.f);
					m_dwCount = GetTickCount();
				}
			}
			else
			{
				if (m_dwCount + 3000 < GetTickCount())
				{
					CObjTestStageMgr::Get_Instance()->CreateMonster(FLY, 100.f, 200.f);
					m_dwCount = GetTickCount();
				}
			}
		}
		else if (CObjTestStageMgr::Get_Instance()->Cheak_Open_Poo(SC_STAGE2, OBJ_POO, 495.f))
		{
			if (m_dwCount + 3000 < GetTickCount())
			{
				CObjTestStageMgr::Get_Instance()->CreateMonster(FLY, 100.f, 495.f);
				m_dwCount = GetTickCount();
			}
		}
	}
	else
	{
		if (!CObjTestStageMgr::Get_Instance()->Cheak_OBJ(OBJ_FLY))
		{
			if (CObjTestStageMgr::Get_Instance()->Cheak_Open_Poo(SC_STAGE2, OBJ_POO, 200.f))
			{
				if (CObjTestStageMgr::Get_Instance()->Cheak_Open_Poo(SC_STAGE2, OBJ_POO, 495.f))
				{
					if (m_dwCount + 3000 < GetTickCount())
					{
						CObjTestStageMgr::Get_Instance()->CreateMonster(FLY, 100.f, 200.f);
						CObjTestStageMgr::Get_Instance()->CreateMonster(FLY, 100.f, 495.f);
						m_dwCount = GetTickCount();
					}
				}
				else
				{
					if (m_dwCount + 3000 < GetTickCount())
					{
						CObjTestStageMgr::Get_Instance()->CreateMonster(FLY, 100.f, 200.f);
						m_dwCount = GetTickCount();
					}
				}
			}
			else if (CObjTestStageMgr::Get_Instance()->Cheak_Open_Poo(SC_STAGE2, OBJ_POO, 495.f))
			{
				if (m_dwCount + 3000 < GetTickCount())
				{
					CObjTestStageMgr::Get_Instance()->CreateMonster(FLY, 100.f, 495.f);
					m_dwCount = GetTickCount();
				}
			}
		}
		else
		{
			if (0 == CObjTestStageMgr::Get_Instance()->Get_Cheak_Drop())
			{
				srand((unsigned int)time((nullptr)));

				int iRanDrop = rand() % 100 + 1;
				int iRanItem = rand() % 100 + 1;

				switch (iRanDrop % 2 + 1)
				{
				case 1:
				{
					if (0 < iRanItem && 25 >= iRanItem)
					{
						CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_LIFE, CAbstractFactory<CItem>::Create_Item(SC_STAGE2, 400.f, 350.f, LIFE));
					}
					else if (25 < iRanItem && 67 >= iRanItem)
					{
						CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItem>::Create_Item(SC_STAGE2, 400.f, 350.f, BOOM));
					}
					else if (67 < iRanItem && 100 >= iRanItem)
					{
						CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItem>::Create_Item(SC_STAGE2, 400.f, 350.f, COIN));
					}
				}
				break;
				}
				CObjTestStageMgr::Get_Instance()->Set_Cheak_Drop(1);
			}
			CObjTestStageMgr::Get_Instance()->Open_Door();

			if (!Cheak_BossD)
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_DOOR);
				CSoundMgr::Get_Instance()->PlaySound(L"BossDoor.wav", SOUND_DOOR, g_fSound);
				Cheak_BossD = true;
			}
		}
	}
}

void CStage2::Render(HDC hDC)
{
	HDC	hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Stage");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hGroundMemDC, 0, 0, SRCCOPY);

	CObjTestStageMgr::Get_Instance()->Render(hDC);

	CUIMgr::Get_Instance()->Render(hDC);
}

void CStage2::Release(void)
{
	CObjTestStageMgr::Get_Instance()->Set_DoNotRun(SC_STAGE2, OBJ_LIFE);
	CObjTestStageMgr::Get_Instance()->Set_DoNotRun(SC_STAGE2, OBJ_ITEM);
	CObjTestStageMgr::Get_Instance()->Set_DoNotRun(SC_STAGE2, OBJ_POO);
	CObjTestStageMgr::Get_Instance()->Set_DoNotRun(SC_STAGE2, OBJ_STONE);

	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_WALL);
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_BULLET);
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_BOOM);
	CObjTestStageMgr::Get_Instance()->Set_TestObj_Dead(OBJ_DOOR);

	CUIMgr::Get_Instance()->Delete_ID(UI_ITEM);
	CUIMgr::Get_Instance()->Delete_ID(UI_MAP);

	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
}
