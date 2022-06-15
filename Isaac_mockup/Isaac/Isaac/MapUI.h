#pragma once

#include "UI.h"

class CMapUI :
	public CUI
{
public:
	CMapUI();
	~CMapUI();

	// CUI��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Set_SceneID(SCENEID _SceneID) { m_SceneID = _SceneID; }

private:
	SCENEID m_SceneID;
};

