#include "stdafx.h"
#include "Ending.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ObjTestStageMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CEnding::CEnding()
{
}


CEnding::~CEnding()
{
	Release();
}

void CEnding::Initialize(void)
{
	CSoundMgr::Get_Instance()->StopAll();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Stage/Ending.bmp", L"Ending");

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 400;
	m_tFrame.dwTime = GetTickCount();

	m_dwTime = GetTickCount();
}

void CEnding::Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
	}
}

void CEnding::Late_Update(void)
{
	if (6 > m_tFrame.iFrameStart)
	{
		Move_Frame();
	}
}

void CEnding::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ending");

	GdiTransparentBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, m_tFrame.iFrameStart * WINCX, m_tFrame.iMotion * WINCY, WINCX, WINCY, RGB(3, 36, 255));
}

void CEnding::Release(void)
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
