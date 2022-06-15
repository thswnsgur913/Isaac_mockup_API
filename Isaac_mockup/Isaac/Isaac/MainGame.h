#pragma once

#include "Include.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void	Initialize(void);
	void	Update(void);
	void	Late_Update(void);
	void	Render(void);
	void	Release(void);

private:
	HDC		m_hDC;
	TCHAR	m_szFPS[64];
	int		m_iFPS;
	DWORD	m_dwTime;
};