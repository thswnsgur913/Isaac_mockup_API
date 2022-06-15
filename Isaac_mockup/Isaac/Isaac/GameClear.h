#pragma once

#include "Scene.h"

class CGameClear
	: public CScene
{
public:
	CGameClear();
	~CGameClear();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	DWORD m_dwTime;
};

