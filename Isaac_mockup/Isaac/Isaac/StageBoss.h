#pragma once
#include "Scene.h"
class CStageBoss :
	public CScene
{
public:
	CStageBoss();
	~CStageBoss();

	// CScene을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	bool m_bEnding;
};

