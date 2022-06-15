#include "stdafx.h"
#include "Wall.h"


CWall::CWall()
{
}


CWall::~CWall()
{
}

void CWall::Initialize(void)
{
	m_bDead = false;
}

int CWall::Update(void)
{
	return 0;
}

void CWall::Late_Update(void)
{
	Update_Rect();
}

void CWall::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CWall::Release(void)
{
}
