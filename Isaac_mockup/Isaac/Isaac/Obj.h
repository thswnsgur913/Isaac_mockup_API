#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void		Set_Size(float _fCX, float _fCY)
	{
		m_tInfo.fCX = _fCX;
		m_tInfo.fCY = _fCY;
	}
	void		Set_Frame(int _iA, int _iB, int _iC)
	{
		m_tFrame.iFrameStart = _iA;
		m_tFrame.iFrameEnd = _iB;
		m_tFrame.iMotion = _iC;
		m_tFrame.dwSpeed = 0;
		m_tFrame.dwTime = GetTickCount();
	}
	void		Set_Dir(DIRECTION eDir) { m_eDir = eDir; }
	void		Set_Dead()				{ m_bDead = true; }
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void		Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }

	void MinusLife() { --m_iLife; }

	void		Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void		Set_PosY(float _fY) { m_tInfo.fY += _fY; }

	void		Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }

	void		Set_SceneID(SCENEID _eSceneID) { m_eSceneID = _eSceneID; }
	SCENEID		Get_SceneID() { return m_eSceneID; }
	void		Set_DoNotRun() { m_bDoNotRun = true; }	// »ª¾À Å×½ºÆ®
	void		Set_DoRun() { m_bDoNotRun = false; }	// »ª¾À Å×½ºÆ®
	bool		Get_DoNotRun() { return m_bDoNotRun; }	// »ª¾À Å×½ºÆ®

	void		Set_BulID(OBJID _eID) { m_GetBulID = _eID; }

	int			Get_Life() { return m_iLife; }
	bool		Get_Dead() { return m_bDead; }


	const INFO&		Get_Info(void) const { return m_tInfo; }
	const RECT&		Get_Rect(void) const { return m_tRect; }

	const RENDERID	Get_RenderID(void) const { return m_eRender;  }

public:
	virtual		void	Initialize(void)	PURE;
	virtual		int		Update(void)		PURE;
	virtual		void	Late_Update(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;

protected:
	void		Update_Rect(void);
	void		Move_Frame(void);

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	FRAME		m_tFrame;

	float		m_fSpeed;
	float		m_fAngle;

	DIRECTION	m_eDir;
	int			m_iLife;
	bool		m_bDead;

	SCENEID		m_eSceneID;
	bool		m_bDoNotRun; // »ª¾À Å×½ºÆ®

	CObj*		m_pTarget;
	TCHAR*		m_pFrameKey;

	RENDERID	m_eRender;

	CObj* m_targetObj;

	OBJID m_GetBulID;
};

