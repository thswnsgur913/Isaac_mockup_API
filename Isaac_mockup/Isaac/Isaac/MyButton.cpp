#include "stdafx.h"
#include "MyButton.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CMyButton::CMyButton()
	: m_iDrawID(0)
{
}


CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize(void)
{
	m_tInfo.fCX = 170.f;
	m_tInfo.fCY = 70.f;

	m_eRender = RENDER_UI;
}

int CMyButton::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMyButton::Late_Update(void)
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tRect, pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (!lstrcmp(L"Start", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_TESTSTAGE);

			return;
		}
		if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
		{
			if (!lstrcmp(L"Start", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_TESTSTAGE);

			return;
		}

		m_iDrawID = 1;
	}

	else
		m_iDrawID = 0;


}

void CMyButton::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 				// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left),				// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top),
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		int(m_tInfo.fCX) * m_iDrawID,	// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));			// �����ϰ��� �ϴ� ����

}

void CMyButton::Release(void)
{

}
