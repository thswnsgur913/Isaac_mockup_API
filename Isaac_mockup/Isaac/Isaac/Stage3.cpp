#include "stdafx.h"
#include "Stage3.h"
#include "BmpMgr.h"
#include "ObjTestStageMgr.h"
#include "SoundMgr.h"
#include "UIMgr.h"
#include "AbstractFactory.h"
#include "Item.h"
#include "ItemUI.h"
#include "Door.h"
#include "Wall.h"
#include "Fire.h"

CStage3::CStage3()
{
}


CStage3::~CStage3()
{
	Release();
}

void CStage3::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/UI/Defult.bmp", L"Stage");

	if (0 == CObjTestStageMgr::Get_Instance()->Get_Cheak_Stage3_In())
	{
		CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_FIRE, CAbstractFactory<CFire>::Create_Object(SC_STAGE3, 100.f, 490.f, 50.f, 69.f));
		CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_FIRE, CAbstractFactory<CFire>::Create_Object(SC_STAGE3, 700.f, 490.f, 50.f, 69.f));
		CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_FIRE, CAbstractFactory<CFire>::Create_Object(SC_STAGE3, 100.f, 180.f, 50.f, 69.f));
		CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_FIRE, CAbstractFactory<CFire>::Create_Object(SC_STAGE3, 700.f, 180.f, 50.f, 69.f));

		CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItem>::Create_Item(SC_STAGE3, 350.f, 300.f, TRIPLE));
		CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItem>::Create_Item(SC_STAGE3, 450.f, 300.f, ACTIVE_A));
	}
	else
	{
		CObjTestStageMgr::Get_Instance()->Set_DoRun(SC_STAGE3, OBJ_FIRE);
		CObjTestStageMgr::Get_Instance()->Set_DoRun(SC_STAGE3, OBJ_ITEM);
		CObjTestStageMgr::Get_Instance()->Set_DoRun(SC_STAGE3, OBJ_LIFE);
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
	CUIMgr::Get_Instance()->Add_UI(UI_MAP, CAbstractFactory<CMapUI>::Map_UI(150.f, 50.f, SC_STAGE3));

	CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_DOOR, CAbstractFactory<CDoor>::Create_Door(38.f, 350.f, false, SC_STAGE3, SC_STAGE1, DIR_LEFT));
}

void CStage3::Update(void)
{
	CObjTestStageMgr::Get_Instance()->Update();

	CUIMgr::Get_Instance()->Update();
}

void CStage3::Late_Update(void)
{
	CObjTestStageMgr::Get_Instance()->Late_Update();

	CUIMgr::Get_Instance()->Late_Update();

	if (0 == CObjTestStageMgr::Get_Instance()->Get_Cheak_Stage3_In())
	{
		CObjTestStageMgr::Get_Instance()->Cheak_Open_Door(SC_STAGE3, OBJ_FIRE);
	}
	else
	{
		CObjTestStageMgr::Get_Instance()->Open_Door();
	}
}

void CStage3::Render(HDC hDC)
{
	HDC	hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Stage");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hGroundMemDC, 0, 0, SRCCOPY);

	CObjTestStageMgr::Get_Instance()->Render(hDC);

	CUIMgr::Get_Instance()->Render(hDC);
}

void CStage3::Release(void)
{
	CObjTestStageMgr::Get_Instance()->Set_DoNotRun(SC_STAGE3, OBJ_FIRE);
	CObjTestStageMgr::Get_Instance()->Set_DoNotRun(SC_STAGE3, OBJ_ITEM);
	CObjTestStageMgr::Get_Instance()->Set_DoNotRun(SC_STAGE3, OBJ_LIFE);

	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_WALL);
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_BULLET);
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_BOOM);
	CObjTestStageMgr::Get_Instance()->Set_TestObj_Dead(OBJ_DOOR);

	CUIMgr::Get_Instance()->Delete_ID(UI_ITEM);
	CUIMgr::Get_Instance()->Delete_ID(UI_MAP);

	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
}
