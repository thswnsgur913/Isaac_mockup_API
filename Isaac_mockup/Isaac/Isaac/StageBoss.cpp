#include "stdafx.h"
#include "StageBoss.h"
#include "BmpMgr.h"
#include "ObjTestStageMgr.h"
#include "UIMgr.h"
#include "AbstractFactory.h"
#include "Item.h"
#include "ItemUI.h"
#include "Door.h"
#include "Stone.h"
#include "Wall.h"
#include "SoundMgr.h"
#include "BossUI.h"

CStageBoss::CStageBoss()
	: m_bEnding(false)
{
}


CStageBoss::~CStageBoss()
{
	Release();
}

void CStageBoss::Initialize(void)
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CSoundMgr::Get_Instance()->PlayBGM(L"BossStart.wav", g_fSoundBGM);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/UI/Defult.bmp", L"Stage");

	if (0 == CObjTestStageMgr::Get_Instance()->Get_Cheak_BossStage_In())
	{
		CObjTestStageMgr::Get_Instance()->CreateMonster(TRASH, 400.f, 250.f);
	}
	else
	{

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
	CUIMgr::Get_Instance()->Add_UI(UI_MAP, CAbstractFactory<CMapUI>::Map_UI(150.f, 50.f, SC_STAGEBOSS));
	CUIMgr::Get_Instance()->Add_UI(UI_MAP, CAbstractFactory<CBossUI>::Create_UI());
}

void CStageBoss::Update(void)
{
	CObjTestStageMgr::Get_Instance()->Update();

	CUIMgr::Get_Instance()->Update();
}

void CStageBoss::Late_Update(void)
{
	if (!CObjTestStageMgr::Get_Instance()->Cheak_OBJ(OBJ_FLY))
	{
		CSoundMgr::Get_Instance()->PlayFLY(L"Wing.wav", SOUND_FLY, g_fSound);
	}
	else
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_FLY);
	}

	if (0 == CObjTestStageMgr::Get_Instance()->Get_Cheak_BossStage_In())
	{
		if (CObjTestStageMgr::Get_Instance()->Cheak_OBJ(OBJ_BOSS))
		{
			if (!m_bEnding)
			{
				CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_FLY);
				CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_MONSTER);
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_DOOR, CAbstractFactory<CDoor>::Create_Door(400.f, 200.f, false, SC_STAGEBOSS, SC_CLEAR, DIR_UP_END));
				CObjTestStageMgr::Get_Instance()->Open_Door();
				CObjTestStageMgr::Get_Instance()->Set_Cheak_BossStage_In(1);
				m_bEnding = true;
			}
		}
	}
	else
	{
		CObjTestStageMgr::Get_Instance()->Open_Door();
	}

	CObjTestStageMgr::Get_Instance()->Late_Update();

	CUIMgr::Get_Instance()->Late_Update();
}

void CStageBoss::Render(HDC hDC)
{
	HDC	hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Stage");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hGroundMemDC, 0, 0, SRCCOPY);

	CUIMgr::Get_Instance()->Render(hDC);

	CObjTestStageMgr::Get_Instance()->Render(hDC);
}

void CStageBoss::Release(void)
{
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_WALL);
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_BULLET);
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_BOOM);
	CObjTestStageMgr::Get_Instance()->Set_TestObj_Dead(OBJ_DOOR);

	CUIMgr::Get_Instance()->Delete_ID(UI_ITEM);
	CUIMgr::Get_Instance()->Delete_ID(UI_MAP);

	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
}
