#include "stdafx.h"
#include "Mouse.h"

CMouse::CMouse()
{
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
}

int CMouse::Update(void)
{

	POINT	pt{};

	GetCursorPos(&pt);	// ���� ���콺�� ��ġ ��ǥ�� ������ �Լ�
	ScreenToClient(g_hWnd, &pt);	// ��ü ��ũ���������� ������ Ŭ���̾�Ʈ(â) ��ǥ�� ��ȯ

	m_tInfo.fX = (float)pt.x;
	m_tInfo.fY = (float)pt.y;
	
	Update_Rect();
	ShowCursor(false);		// ���콺 Ŀ���� ������� �ʰڴ�.

	return OBJ_NOEVENT;
}

void CMouse::Late_Update(void)
{
	

}

void CMouse::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMouse::Release(void)
{
	
}
