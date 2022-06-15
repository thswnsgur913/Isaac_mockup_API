#include "stdafx.h"
#include "BossUI.h"
#include "BmpMgr.h"
#include "ObjTestStageMgr.h"
#include "Trash.h"


CBossUI::CBossUI()
{
}


CBossUI::~CBossUI()
{
}

void CBossUI::Initialize(void)
{
	m_tInfo.fCX = 334.f;
	m_tInfo.fCY = 38.f;

	m_tInfo.fX = 400.f;
	m_tInfo.fY = 130.f;

	m_tBarInfo.fCX = 297.f;
	m_tBarInfo.fCY = 16.f;

	m_tBarInfo.fX = 416.f;
	m_tBarInfo.fY = 130.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Monster/TrashHp.bmp", L"TrashHp");
	
	m_pFrameKey = L"TrashHp";
}

int CBossUI::Update(void)
{
	Update_Rect();
	Bar_Update_Rect();
	if (!CObjTestStageMgr::Get_Instance()->Cheak_OBJ(OBJ_BOSS))
	{
		if (0 <= CObjTestStageMgr::Get_Instance()->Get_Boss()->Get_Life())
		{
			m_tBarInfo.fCX = (float)(CObjTestStageMgr::Get_Instance()->Get_Boss()->Get_Life());

		}
	}
	return 0;
}

void CBossUI::Late_Update(void)
{
	if (!CObjTestStageMgr::Get_Instance()->Cheak_OBJ(OBJ_BOSS))
	{
		if (m_tBarInfo.fCX != (float)CObjTestStageMgr::Get_Instance()->Get_Boss()->Get_Life())
		{
			m_tBarInfo.fX -= 0.5f;
		}
	}
}

void CBossUI::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	HDC	hBarDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	//17, 16, 351, 54 / 51, 99, 348, 115 = 334, 38
	//BitBlt(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom, hMemDC, 17, 16, SRCCOPY);
	//BitBlt(hDC, m_tBarRect.left, m_tBarRect.top, m_tBarRect.right, m_tBarRect.bottom, hBarDC, 51, 99, SRCCOPY);

	GdiTransparentBlt(hDC, 							// ���� ����, ���������� �׸��� �׸� DC
		int(m_tBarRect.left),							// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tBarRect.top),
		int(m_tBarInfo.fCX),							// 4,5 ���� : ������� ����, ���� ����
		int(m_tBarInfo.fCY),
		hBarDC,										// ��Ʈ���� ������ �ִ� DC
		51,	// ��Ʈ�� ��� ���� ��ǥ, X,Y
		99,
		(int)m_tBarInfo.fCX,							// ������ ��Ʈ���� ����, ���� ����
		(int)m_tBarInfo.fCY,
		RGB(255, 255, 255));						// �����ϰ��� �ϴ� ����

	GdiTransparentBlt(hDC, 							// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left),							// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top),
		int(m_tInfo.fCX),							// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hMemDC,										// ��Ʈ���� ������ �ִ� DC
		17,	// ��Ʈ�� ��� ���� ��ǥ, X,Y
		16,
		(int)m_tInfo.fCX,							// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));						// �����ϰ��� �ϴ� ����
}

void CBossUI::Release(void)
{
}

void CBossUI::Bar_Update_Rect(void)
{
	m_tBarRect.left = LONG(m_tBarInfo.fX - (m_tBarInfo.fCX * 0.5f));
	m_tBarRect.top = LONG(m_tBarInfo.fY - (m_tBarInfo.fCY * 0.5f));
	m_tBarRect.right = LONG(m_tBarInfo.fX + (m_tBarInfo.fCX * 0.5f));
	m_tBarRect.bottom = LONG(m_tBarInfo.fY + (m_tBarInfo.fCY * 0.5f));
}
