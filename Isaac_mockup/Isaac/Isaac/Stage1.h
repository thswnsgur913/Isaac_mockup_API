#pragma once

#include "Scene.h"

class CStage1 :
	public CScene
{
public:
	CStage1();
	~CStage1();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

