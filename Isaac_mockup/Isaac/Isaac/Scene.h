#pragma once

#include "Include.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void	Initialize(void) PURE;
	virtual void	Update(void) PURE;
	virtual void	Late_Update(void) PURE;
	virtual void	Render(HDC hDC) PURE;
	virtual void	Release(void) PURE;

	/*void Set_Run() { m_bRun = true; }
	void Set_RunStop() { m_bRun = false; }

	bool Get_RunCheak() { return m_bRun; }*/

protected:
	//bool m_bRun;

	// frame test

	FRAME m_tFrame;

	void Move_Frame(void)
	{
		if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
		{
			m_tFrame.iFrameStart++;

			m_tFrame.dwTime = GetTickCount();

			if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
				m_tFrame.iFrameStart = 0;
		}
	}
};

