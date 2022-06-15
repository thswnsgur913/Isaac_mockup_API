#pragma once

#include "UI.h"

class CUIMgr
{
private:
	CUIMgr();
	~CUIMgr();

public:
	void		Add_UI(UIID eID, CUI* pObj);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	void		Delete_ID(UIID eID);

	bool Cheak_List(UIID _UIID) { if (m_UIList[_UIID].empty()) { return true; } else { return false; } }

private:
	list<CUI*>	m_UIList[UI_END];

public:
	static		CUIMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CUIMgr;
		}

		return m_pInstance;
	}

	static	void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CUIMgr*			m_pInstance;
	list<CUI*>				m_RenderSort[RENDER_END];
};

