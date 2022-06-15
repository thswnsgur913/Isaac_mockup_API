#include "stdafx.h"
#include "Stage.h"
#include "BmpMgr.h"
#include "ObjTestStageMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "UIMgr.h"
#include "AbstractFactory.h"
#include "Stone.h"
#include "Wall.h"
#include "Fire.h"
#include "Poo.h"
#include "Item.h"
#include "ItemUI.h"
#include "MapUI.h"
#include "Door.h"
#include "SoundMgr.h"

// test stage

// 빽씬 구현, 맵 디자인 마무리, 사운드
// 문열림 코드 CObjMgr LateUpdate에 있음. 몬스터 추가 후 수정할 것.
// stage2 미로 제작 후 시간내에 열쇠 획득해야 함.
// stage3 열쇠로 문따고 아이템 먹는거 보여주고 기능 설명
// boss 전투 후 문열리면 엔딩

CStage::CStage()
{
}

CStage::~CStage()
{
	Release();
}

void CStage::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/UI/RoomBack.bmp", L"Ground");

	if (CObjTestStageMgr::Get_Instance()->Cheak_OBJ(OBJ_PLAYER))
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
		CSoundMgr::Get_Instance()->PlayBGM(L"StageBgm.wav", g_fSoundBGM);

		CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	}

	if (0 == CObjTestStageMgr::Get_Instance()->Get_Cheak_TestStage_In())
	{
		CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_LIFE, CAbstractFactory<CItem>::Create_Item(SC_TESTSTAGE, 300.f, 500.f, LIFE));
		CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_LIFE, CAbstractFactory<CItem>::Create_Item(SC_TESTSTAGE, 400.f, 500.f, LIFE));
		CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_LIFE, CAbstractFactory<CItem>::Create_Item(SC_TESTSTAGE, 500.f, 500.f, LIFE));
		CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_FIRE, CAbstractFactory<CFire>::Create_Object(SC_TESTSTAGE, 100.f, 490.f, 50.f, 69.f));
		CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_POO, CAbstractFactory<CPoo>::Create_Object(SC_TESTSTAGE, 705.f, 495.f, 49.f, 50.f));
	}
	else
	{
		CObjTestStageMgr::Get_Instance()->Set_DoRun(SC_TESTSTAGE, OBJ_ITEM);
		CObjTestStageMgr::Get_Instance()->Set_DoRun(SC_TESTSTAGE, OBJ_LIFE);
		CObjTestStageMgr::Get_Instance()->Set_DoRun(SC_TESTSTAGE, OBJ_FIRE);
		CObjTestStageMgr::Get_Instance()->Set_DoRun(SC_TESTSTAGE, OBJ_POO);
	}

	// 이하 죽여도 되는거(스테이지마다 할당 - 해제 해줘야하는거)
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
	CUIMgr::Get_Instance()->Add_UI(UI_MAP, CAbstractFactory<CMapUI>::Map_UI(150.f, 50.f, SC_TESTSTAGE));

	CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_DOOR, CAbstractFactory<CDoor>::Create_Door(400.f, 130.f, false, SC_TESTSTAGE, SC_STAGE1, DIR_UP));
	//CObjTestStageMgr::Get_Instance()->Open_Door();

	CObjTestStageMgr::Get_Instance()->Set_Cheak_TestStage_In(1);
}	


void CStage::Update(void)
{
		CObjTestStageMgr::Get_Instance()->Update();

		CUIMgr::Get_Instance()->Update();
}

void CStage::Late_Update(void)
{
	CObjTestStageMgr::Get_Instance()->Late_Update();

	CUIMgr::Get_Instance()->Late_Update();

	if (CObjTestStageMgr::Get_Instance()->Cheak_OBJ(OBJ_MONSTER))
	{
		CObjTestStageMgr::Get_Instance()->Open_Door();
	}
}

void CStage::Render(HDC hDC)
{
	HDC	hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hGroundMemDC, 0, 0, SRCCOPY);

	CObjTestStageMgr::Get_Instance()->Render(hDC);

	CUIMgr::Get_Instance()->Render(hDC);
}

void CStage::Release(void)
{
	CObjTestStageMgr::Get_Instance()->Set_DoNotRun(SC_TESTSTAGE, OBJ_FIRE);
	CObjTestStageMgr::Get_Instance()->Set_DoNotRun(SC_TESTSTAGE, OBJ_POO);
	CObjTestStageMgr::Get_Instance()->Set_DoNotRun(SC_TESTSTAGE, OBJ_ITEM);
	CObjTestStageMgr::Get_Instance()->Set_DoNotRun(SC_TESTSTAGE, OBJ_LIFE);

	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_WALL);
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_BULLET);
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_BOOM);
	CObjTestStageMgr::Get_Instance()->Set_TestObj_Dead(OBJ_DOOR);

	CUIMgr::Get_Instance()->Delete_ID(UI_ITEM);
	CUIMgr::Get_Instance()->Delete_ID(UI_MAP);

	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
}
