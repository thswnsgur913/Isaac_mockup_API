#pragma once

#include "Include.h"

class CUI
{
public:
	CUI();
	virtual ~CUI();

public:
	virtual		void	Initialize(void)	PURE;
	virtual		int		Update(void)		PURE;
	virtual		void	Late_Update(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;

	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

	const INFO&		Get_Info(void) const { return m_tInfo; }
	const RECT&		Get_Rect(void) const { return m_tRect; }

	const RENDERID	Get_RenderID(void) const { return m_eRender; }

protected:
	void		Update_Rect(void);
	void		Move_Frame(void);

	INFO m_tInfo;
	RECT m_tRect;

	FRAME m_tFrame;
	TCHAR* m_pFrameKey;
	RENDERID m_eRender;
};