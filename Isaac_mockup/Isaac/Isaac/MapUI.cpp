#include "stdafx.h"
#include "MapUI.h"
#include "BmpMgr.h"


CMapUI::CMapUI()
	: m_SceneID(SC_END)
{
}


CMapUI::~CMapUI()
{
}

void CMapUI::Initialize(void)
{
	m_tInfo.fCX = 255.f;
	m_tInfo.fCY = 85.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/UI/Map_Test.bmp", L"Map_Test");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/UI/Map_Stage1.bmp", L"Map_Stage1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/UI/Map_Stage2.bmp", L"Map_Stage2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/UI/Map_Stage3.bmp", L"Map_Stage3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/UI/Map_StageBoss.bmp", L"Map_StageBoss");

	m_eRender = RENDER_UI;

	switch (m_SceneID)
	{
	case SC_TESTSTAGE:
		m_pFrameKey = L"Map_Test";
		break;

	case SC_STAGE1:
		m_pFrameKey = L"Map_Stage1";
		break;

	case SC_STAGE2:
		m_pFrameKey = L"Map_Stage2";
		break;

	case SC_STAGE3:
		m_pFrameKey = L"Map_Stage3";
		break;

	case SC_STAGEBOSS:
		m_pFrameKey = L"Map_StageBoss";
		break;
	}
}

int CMapUI::Update(void)
{
	Update_Rect();

	return 0;
}

void CMapUI::Late_Update(void)
{
}

void CMapUI::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void CMapUI::Release(void)
{
}
