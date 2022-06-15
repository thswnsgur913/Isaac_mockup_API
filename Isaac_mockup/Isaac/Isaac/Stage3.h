#pragma once
#include "Scene.h"
class CStage3 :
	public CScene
{
public:
	CStage3();
	~CStage3();

	// CScene을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

