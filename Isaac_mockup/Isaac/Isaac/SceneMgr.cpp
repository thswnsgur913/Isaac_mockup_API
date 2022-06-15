#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr*	CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_eCurScene(SC_END), m_ePreScene(SC_END)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

// FSM(finite state machine) : 유한 상태 기계, 자신이 취할 수 있는 유한한 개수의 상태

void CSceneMgr::Scene_Change(SCENEID eNextID)
{
	m_eCurScene = eNextID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SC_MENU:
			m_pScene = new CMyMenu;
			m_pScene->Initialize();
			break;

		case SC_TESTSTAGE:
			m_pScene = new CStage;
			m_pScene->Initialize();
			break;

		case SC_STAGE1:
			m_pScene = new CStage1;
			m_pScene->Initialize();
			break;

		case SC_STAGE2:
			m_pScene = new CStage2;
			m_pScene->Initialize();
			break;

		case SC_STAGE3:
			m_pScene = new CStage3;
			m_pScene->Initialize();
			break;

		case SC_STAGEBOSS:
			m_pScene = new CStageBoss;
			m_pScene->Initialize();
			break;

		case SC_ENDING:
			m_pScene = new CEnding;
			m_pScene->Initialize();
			break;

		case SC_CLEAR:
			m_pScene = new CGameClear;
			m_pScene->Initialize();
			break;
		}
		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::Update(void)
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update(void)
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release(void)
{
	Safe_Delete(m_pScene);
}
