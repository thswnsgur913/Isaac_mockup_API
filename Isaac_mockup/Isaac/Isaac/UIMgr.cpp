#include "stdafx.h"
#include "UIMgr.h"

CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr()
{
}


CUIMgr::~CUIMgr()
{
}

void CUIMgr::Add_UI(UIID eID, CUI* pObj)
{
	if ((eID >= UI_END) || (nullptr == pObj))
		return;

	m_UIList[eID].push_back(pObj);
}

int CUIMgr::Update(void)
{
	for (int i = 0; i < UI_END; ++i)
	{
		for (auto& iter = m_UIList[i].begin();
			iter != m_UIList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CUI*>(*iter);
				iter = m_UIList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return 0;
}

void CUIMgr::Late_Update(void)
{
	for (int i = 0; i < UI_END; ++i)
	{
		for (auto& iter : m_UIList[i])
		{
			iter->Late_Update();

			if (m_UIList[i].empty())
				break;

			RENDERID eRender = iter->Get_RenderID();
			m_RenderSort[eRender].push_back(iter);
		}
	}
}

template<typename T>
bool		CompareY(T Dest, T Sour)
{
	return Dest->Get_Info().fY < Sour->Get_Info().fY;
}

void CUIMgr::Render(HDC hDC)
{
	for (int i = 0; i < RENDER_END; ++i)
	{
		m_RenderSort[i].sort(CompareY<CUI*>);

		for (auto& iter : m_RenderSort[i])
			iter->Render(hDC);

		m_RenderSort[i].clear();
	}
}

void CUIMgr::Release(void)
{
	for (int i = 0; i < UI_END; ++i)
	{
		for (auto& iter : m_UIList[i])
			Safe_Delete<CUI*>(iter);

		m_UIList[i].clear();
	}
}

void CUIMgr::Delete_ID(UIID eID)
{
	for (auto& iter : m_UIList[eID])
		Safe_Delete(iter);

	m_UIList[eID].clear();
}