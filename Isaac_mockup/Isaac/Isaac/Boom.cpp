#include "stdafx.h"
#include "Boom.h"
#include "BmpMgr.h"


CBoom::CBoom()
{
}


CBoom::~CBoom()
{
	Release();
}

void CBoom::Initialize(void)
{
	m_tInfo.fCX = 0.f;
	m_tInfo.fCY = 0.f;

	fRenCX = 200.f;
	fRenCY = 200.f;

	m_bDead = false;

	m_bBoom = false;

	m_dwCheck = GetTickCount();

	m_eRender = RENDER_PLAYER;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Obj/bomb2.bmp", L"Boom");

	m_pFrameKey = L"Boom";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iMotion = 1;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}

int CBoom::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	lRenLeft = LONG(m_tInfo.fX - (fRenCX * 0.5f));
	lRenTop = LONG(m_tInfo.fY - (fRenCY * 0.5f));

	return OBJ_NOEVENT;
}

void CBoom::Late_Update(void)
{
	if (m_tInfo.fX < 52 || m_tInfo.fX > 747 || m_tInfo.fY < 146 || m_tInfo.fY > 550)
	{
		Set_Dead();
	}

	Motion_Change();
}

void CBoom::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 							// ���� ����, ���������� �׸��� �׸� DC
		(int)lRenLeft,							// 2,3 ���� :  ������� ��ġ X, Y
		(int)lRenTop,
		(int)fRenCX,							// 4,5 ���� : ������� ����, ���� ����
		(int)fRenCY,
		hMemDC,										// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)fRenCX,	// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_tFrame.iMotion * (int)fRenCY,
		(int)fRenCX,							// ������ ��Ʈ���� ����, ���� ����
		(int)fRenCY,
		RGB(255, 255, 255));						// �����ϰ��� �ϴ� ����
}

void CBoom::Release(void)
{
}

void CBoom::Motion_Change(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		m_tFrame.iFrameStart++;

		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			if (1 == m_tFrame.iMotion)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iMotion = 2;
			}
			else if (2 == m_tFrame.iMotion)
			{
				m_tInfo.fCX = 150.f;
				m_tInfo.fCY = 150.f;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iMotion = 0;
				m_bBoom = true;
			}
			else if (0 == m_tFrame.iMotion)
			{
				Set_Dead();
			}
			else
				m_tFrame.iFrameStart = 0;
		}
	}
}
