#include "stdafx.h"
#include "Stage1.h"
#include "BmpMgr.h"
#include "ObjTestStageMgr.h"
#include "UIMgr.h"
#include "AbstractFactory.h"
#include "Item.h"
#include "ItemUI.h"
#include "Door.h"
#include "Wall.h"
#include "Fly.h"
#include "Stone.h"
#include "SoundMgr.h"

CStage1::CStage1()
{
}


CStage1::~CStage1()
{
	Release();
}

void CStage1::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/UI/Defult.bmp", L"Stage");

	if (0 == CObjTestStageMgr::Get_Instance()->Get_Cheak_Stage1_In())
	{
		CObjTestStageMgr::Get_Instance()->CreateMonster(ENVY, 400.f, 200.f);
		CObjTestStageMgr::Get_Instance()->CreateMonster(HOPPER, 150.f, 200.f);
		CObjTestStageMgr::Get_Instance()->CreateMonster(HOPPER, 650.f, 200.f);
		CObjTestStageMgr::Get_Instance()->CreateMonster(HOPPER, 150.f, 450.f);
		CObjTestStageMgr::Get_Instance()->CreateMonster(HOPPER, 650.f, 450.f);

		//CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_STONE, CAbstractFactory<CStone>::Create_Stone(SC_STAGE1, 250.f, 350.f, 1, 1, 1));
		//CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_STONE, CAbstractFactory<CStone>::Create_Stone(SC_STAGE1, 550.f, 350.f, 1, 1, 1));
	}
	else
	{
		CObjTestStageMgr::Get_Instance()->Set_DoRun(SC_STAGE1, OBJ_STONE);
		CObjTestStageMgr::Get_Instance()->Set_DoRun(SC_STAGE1, OBJ_ITEM);
		CObjTestStageMgr::Get_Instance()->Set_DoRun(SC_STAGE1, OBJ_LIFE);
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
	CUIMgr::Get_Instance()->Add_UI(UI_MAP, CAbstractFactory<CMapUI>::Map_UI(150.f, 50.f, SC_STAGE1));

	CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_DOOR, CAbstractFactory<CDoor>::Create_Door(400.f, 560.f, false, SC_STAGE1, SC_TESTSTAGE, DIR_DOWN));
	CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_DOOR, CAbstractFactory<CDoor>::Create_Door(38.f, 350.f, false, SC_STAGE1, SC_STAGE2, DIR_LEFT));
	CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_DOOR, CAbstractFactory<CDoor>::Create_Door(765.f, 350.f, true, SC_STAGE1, SC_STAGE3, DIR_RIGHT));
}

void CStage1::Update(void)
{
	CObjTestStageMgr::Get_Instance()->Update();

	CUIMgr::Get_Instance()->Update();
}

void CStage1::Late_Update(void)
{
	CObjTestStageMgr::Get_Instance()->Late_Update();

	CUIMgr::Get_Instance()->Late_Update();

	if (!CObjTestStageMgr::Get_Instance()->Cheak_OBJ(OBJ_FLY))
	{
		CSoundMgr::Get_Instance()->PlaySoundW(L"Wing.wav", SOUND_FLY, g_fSound);
	}
	else
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_FLY);
	}

	if (CObjTestStageMgr::Get_Instance()->Cheak_OBJ(OBJ_MONSTER) && CObjTestStageMgr::Get_Instance()->Cheak_OBJ(OBJ_FLY) && (0 == CObjTestStageMgr::Get_Instance()->Get_Cheak_Stage1_In()))
	{
		CObjTestStageMgr::Get_Instance()->Open_Door();
		CObjTestStageMgr::Get_Instance()->Set_Cheak_Stage1_In(1);

		srand((unsigned int)time((nullptr)));

		int iRanDrop = rand() % 100 + 1;
		int iRanItem = rand() % 100 + 1;

		switch (iRanDrop % 2 + 1)
		{
		case 1:
		{
			if (0 < iRanItem && 25 >= iRanItem)
			{
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_LIFE, CAbstractFactory<CItem>::Create_Item(SC_STAGE1, 400.f, 350.f, LIFE));
			}
			else if (25 < iRanItem && 67 >= iRanItem)
			{
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItem>::Create_Item(SC_STAGE1, 400.f, 350.f, BOOM));
			}
			else if (67 < iRanItem && 100 >= iRanItem)
			{
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItem>::Create_Item(SC_STAGE1, 400.f, 350.f, COIN));
			}
		}
		break;
		}
	}
	else if(1 == CObjTestStageMgr::Get_Instance()->Get_Cheak_Stage1_In())
	{
		CObjTestStageMgr::Get_Instance()->Open_Door();
	}
}

void CStage1::Render(HDC hDC)
{
	HDC	hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Stage");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hGroundMemDC, 0, 0, SRCCOPY);

	CObjTestStageMgr::Get_Instance()->Render(hDC);

	CUIMgr::Get_Instance()->Render(hDC);
}

void CStage1::Release(void)
{
	CObjTestStageMgr::Get_Instance()->Set_DoNotRun(SC_STAGE1, OBJ_STONE);
	CObjTestStageMgr::Get_Instance()->Set_DoNotRun(SC_STAGE1, OBJ_ITEM);
	CObjTestStageMgr::Get_Instance()->Set_DoNotRun(SC_STAGE1, OBJ_LIFE);

	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_WALL);
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_BULLET);
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_BOOM);
	CObjTestStageMgr::Get_Instance()->Set_TestObj_Dead(OBJ_DOOR);

	CUIMgr::Get_Instance()->Delete_ID(UI_ITEM);
	CUIMgr::Get_Instance()->Delete_ID(UI_MAP);

	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
}
