#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "ObjTestStageMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"


CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize(void)
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CSoundMgr::Get_Instance()->PlayBGM(L"Start.wav", g_fSoundBGM);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Button/Start.bmp", L"Start");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Back/BackGround.bmp", L"Menu");

	CObj* pButton = CAbstractFactory<CMyButton>::Create(400.f, 525.f);
	pButton->Set_FrameKey(L"Start");
	CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);
	
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
}

void CMyMenu::Update(void)
{
	CObjTestStageMgr::Get_Instance()->Update();
}

void CMyMenu::Late_Update(void)
{
	Move_Frame();

	CObjTestStageMgr::Get_Instance()->Late_Update();
}

void CMyMenu::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Menu");

	GdiTransparentBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, m_tFrame.iFrameStart * WINCX, m_tFrame.iMotion * WINCY, WINCX, WINCY, RGB(3, 36, 255));

	CObjTestStageMgr::Get_Instance()->Render(hDC);
}

void CMyMenu::Release(void)
{
	CObjTestStageMgr::Get_Instance()->Delete_ID(OBJ_BUTTON);
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
}