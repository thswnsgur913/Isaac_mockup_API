#include "stdafx.h"
#include "ColorStone.h"
#include "BmpMgr.h"
#include "ObjTestStageMgr.h"
#include "AbstractFactory.h"
#include "Item.h"


CColorStone::CColorStone()
{
}


CColorStone::~CColorStone()
{
	Release();
}

void CColorStone::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_eRender = RENDER_FIELDOBJECT;

	m_bDead = false;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Obj/Colorstone.bmp", L"ColorStone");

	m_pFrameKey = L"ColorStone";
}

int CColorStone::Update(void)
{
	if (m_bDoNotRun)
	{
		return OBJ_NOEVENT;
	}
	else
	{
		if (m_bDead)
		{
			CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItem>::Create_Item(m_eSceneID, m_tInfo.fX, m_tInfo.fY, KEY));
			return OBJ_DEAD;
		}
		else
		{
			Update_Rect();

			return OBJ_NOEVENT;
		}
	}
}

void CColorStone::Late_Update(void)
{
}

void CColorStone::Render(HDC hDC)
{
	if (m_bDoNotRun)
	{
		return;
	}
	else
	{
		if (m_bDead)
		{
			return;
		}
		else
		{
			HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

			GdiTransparentBlt(hDC, 							// ���� ����, ���������� �׸��� �׸� DC
				int(m_tRect.left),							// 2,3 ���� :  ������� ��ġ X, Y
				int(m_tRect.top),
				int(m_tInfo.fCX),							// 4,5 ���� : ������� ����, ���� ����
				int(m_tInfo.fCY),
				hMemDC,										// ��Ʈ���� ������ �ִ� DC
				m_tFrame.iFrameStart * (int)m_tInfo.fCX,	// ��Ʈ�� ��� ���� ��ǥ, X,Y
				m_tFrame.iMotion * (int)m_tInfo.fCY,
				(int)m_tInfo.fCX,							// ������ ��Ʈ���� ����, ���� ����
				(int)m_tInfo.fCY,
				RGB(255, 255, 255));						// �����ϰ��� �ϴ� ����
		}
	}
}

void CColorStone::Release(void)
{
}
