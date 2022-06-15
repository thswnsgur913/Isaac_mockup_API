#include "stdafx.h"
#include "GameClear.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ObjTestStageMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CGameClear::CGameClear()
{
}


CGameClear::~CGameClear()
{
	Release();
}

void CGameClear::Initialize(void)
{
	CSoundMgr::Get_Instance()->StopAll();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Logo/EndSCENE.bmp", L"ClearEnding");
}

void CGameClear::Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
	}
}

void CGameClear::Late_Update(void)
{
}

void CGameClear::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ClearEnding");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void CGameClear::Release(void)
{
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_BULLET);
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_BOOM);
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_MONSTER);
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_STONE);
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_FIRE);
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_POO);
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_WALL);
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_ITEM);
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_MOUSE);
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_BUTTON);
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_MONBUL);
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_FLY);
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_BOSS);

	CObjTestStageMgr::Get_Instance()->Set_TestObj_Dead(OBJ_DOOR);

	CObjTestStageMgr::Get_Instance()->Set_Cheak_TestStage_In(0);
	CObjTestStageMgr::Get_Instance()->Set_Cheak_Stage1_In(0);
	CObjTestStageMgr::Get_Instance()->Set_Cheak_Stage2_In(0);
	CObjTestStageMgr::Get_Instance()->Set_Cheak_Stage3_In(0);
	CObjTestStageMgr::Get_Instance()->Set_Cheak_BossStage_In(0);

	CSoundMgr::Get_Instance()->StopAll();
}
