#include "stdafx.h"
#include "ObjTestStageMgr.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"
#include "Item.h"
#include "Fly.h"
#include "Envy.h"
#include "Hopper.h"
#include "Trash.h"

CObjTestStageMgr* CObjTestStageMgr::m_pInstance = nullptr;

int CObjTestStageMgr::Cheak_TestStage_In = 0;
int CObjTestStageMgr::Cheak_Stage1_In = 0;
int CObjTestStageMgr::Cheak_Stage2_In = 0;
int CObjTestStageMgr::Cheak_Stage3_In = 0;
int CObjTestStageMgr::Cheak_BossStage_In = 0;
int CObjTestStageMgr::Cheak_KeyDoor = 0;
int CObjTestStageMgr::Cheak_Drop = 0;


CObjTestStageMgr::CObjTestStageMgr()
	: m_bCheak(false)
	, m_dwCheak(GetTickCount())
{
}


CObjTestStageMgr::~CObjTestStageMgr()
{
	Release();
}

void CObjTestStageMgr::Cheak_Key(SCENEID _SceneID, OBJID _OBJID)
{
	for (auto& iter : m_ObjList[_OBJID])
		if (_SceneID == iter->Get_SceneID())
			if(KEY == dynamic_cast<CItem*>(iter)->Get_ItemType())
				if (iter->Get_Dead())
				{
					Set_Cheak_Stage2_In(1);
				}
}

bool CObjTestStageMgr::Cheak_Open_Poo(SCENEID _SceneID, OBJID _OBJID, float _fA)
{
	int iTemp = 0;
	for (auto& iter : m_ObjList[_OBJID])
		if (_SceneID == iter->Get_SceneID())
			if(_fA == iter->Get_Info().fY)
				if (iter->Get_Dead())
				{
					++iTemp;
				}

	if (1 == iTemp)
	{
		return false;
	}

	return true;
}

void CObjTestStageMgr::Cheak_Open_Door(SCENEID _SceneID, OBJID _OBJID)
{
	int iTemp = 0;
	for (auto& iter : m_ObjList[_OBJID])
		if (_SceneID == iter->Get_SceneID())
			if (iter->Get_Dead())
			{
				++iTemp;
			}

	if (4 == iTemp)
	{
		//Open_Door();
		Set_Cheak_Stage3_In(1);

		srand((unsigned int)time((nullptr)));

		int iRanDrop = rand() % 100 + 1;
		int iRanItem = rand() % 100 + 1;

		switch (iRanDrop % 2 + 1)
		{
		case 1:
		{
			if (0 < iRanItem && 25 >= iRanItem)
			{
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_LIFE, CAbstractFactory<CItem>::Create_Item(_SceneID, 400.f, 350.f, LIFE));
			}
			else if (25 < iRanItem && 67 >= iRanItem)
			{
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItem>::Create_Item(_SceneID, 400.f, 350.f, BOOM));
			}
			else if (67 < iRanItem && 100 >= iRanItem)
			{
				CObjTestStageMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItem>::Create_Item(_SceneID, 400.f, 350.f, COIN));
			}
		}
		break;
		}
	}
}

CObj* CObjTestStageMgr::Get_Target(OBJID eID, CObj* pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj*		pTarget = nullptr;
	float		fDistance = 0.f;
	
	for (auto& iter : m_ObjList[eID])
	{
		if (iter->Get_Dead())
			continue;

		float	fWidth = abs(pObj->Get_Info().fX - iter->Get_Info().fX);
		float	fHeight = abs(pObj->Get_Info().fY - iter->Get_Info().fY);

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if ((!pTarget) || (fDistance > fDiagonal))
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}
	}
		
	return pTarget;
}

void CObjTestStageMgr::Add_Object(OBJID eID, CObj * pObj)
{
	if ((eID >= OBJ_END) || (nullptr == pObj))
		return;

	m_ObjList[eID].push_back(pObj);
}

int CObjTestStageMgr::Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
				if (m_ObjList[OBJ_PLAYER].empty())
				{
					CSceneMgr::Get_Instance()->Scene_Change(SC_ENDING);
				}
			}
			else
				++iter;
		}
	}

	return 0;
}

void CObjTestStageMgr::Late_Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Late_Update();

			if (m_ObjList[i].empty())
				break;

			RENDERID eRender = iter->Get_RenderID();
			m_RenderSort[eRender].push_back(iter);
		}
	}
	// ÀÌÇÏ Ãæµ¹

	if (!m_ObjList[OBJ_PLAYER].empty())
	{
		if (!dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Get_GodMod())
		{

			if (m_bCheak) // player ¹«Àû½Ã°£ ºÎ¿©
			{
				if (m_dwCheak + 2000 < GetTickCount())
				{
					m_dwCheak = GetTickCount();
					m_bCheak = false;
				}
			}
			else
			{
				m_dwCheak = GetTickCount();
				CCollisionMgr::Collision_Fire_P(m_ObjList[OBJ_FIRE], m_ObjList[OBJ_PLAYER]);
				CCollisionMgr::Collision_Sphere_Player(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_PLAYER]);
				CCollisionMgr::Collision_Sphere_Player(m_ObjList[OBJ_FLY], m_ObjList[OBJ_PLAYER]);
				CCollisionMgr::Collision_Sphere_Player(m_ObjList[OBJ_BOSS], m_ObjList[OBJ_PLAYER]);
				CCollisionMgr::Collision_Sphere_P(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONBUL]);
			}
		}
	}

	if (!m_ObjList[OBJ_BOOM].empty())
	{
		for (auto& iter : m_ObjList[OBJ_BOOM])
		{
			if (dynamic_cast<CBoom*>(iter)->Get_Boom())
			{
				CCollisionMgr::Collision_Rect(m_ObjList[OBJ_BOOM], m_ObjList[OBJ_STONE]);
				CCollisionMgr::Collision_Rect_Boom(m_ObjList[OBJ_BOOM], m_ObjList[OBJ_MONSTER]);
				CCollisionMgr::Collision_Rect_Boom(m_ObjList[OBJ_BOOM], m_ObjList[OBJ_FLY]);
				break;
			}
		}
	}

	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_STONE], m_ObjList[OBJ_PLAYER]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_POO], m_ObjList[OBJ_PLAYER]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_WALL], m_ObjList[OBJ_PLAYER]);

	CCollisionMgr::Collision_Door(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_DOOR]);

	CCollisionMgr::Collision_Item(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_ITEM]);

	CCollisionMgr::Collision_Item(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_LIFE]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_WALL], m_ObjList[OBJ_LIFE]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_STONE], m_ObjList[OBJ_LIFE]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_FIRE], m_ObjList[OBJ_LIFE]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_POO], m_ObjList[OBJ_LIFE]);

	CCollisionMgr::Collision_Stone(m_ObjList[OBJ_STONE], m_ObjList[OBJ_BULLET]);
	CCollisionMgr::Collision_Fire_B(m_ObjList[OBJ_FIRE], m_ObjList[OBJ_BULLET]);
	CCollisionMgr::Collision_Poo_B(m_ObjList[OBJ_POO], m_ObjList[OBJ_BULLET]);
	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);
	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_FLY], m_ObjList[OBJ_BULLET]);
	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_BOSS], m_ObjList[OBJ_BULLET]);
}

template<typename T>
bool		CompareY(T Dest, T Sour)
{
	return Dest->Get_Info().fY < Sour->Get_Info().fY;
}

void CObjTestStageMgr::Render(HDC hDC)
{
	for (int i = 0; i < RENDER_END; ++i)
	{
		m_RenderSort[i].sort(CompareY<CObj*>);

		for (auto& iter : m_RenderSort[i])
			iter->Render(hDC);

		m_RenderSort[i].clear();
	}
}

void CObjTestStageMgr::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			Safe_Delete<CObj*>(iter);

		m_ObjList[i].clear();
	}
}

void CObjTestStageMgr::Delete_ID(OBJID eID)
{
	for (auto& iter : m_ObjList[eID])
		Safe_Delete(iter);

	m_ObjList[eID].clear();
}

void CObjTestStageMgr::CreateMonster(MONTYPE _type, float _fXpoint, float _fYpoint)
{
	if (m_ObjList[OBJ_PLAYER].empty())
		return;

	switch (_type)
	{
	case FLY:
		m_pMonster = CAbstractFactory<CFly>::Create(_fXpoint, _fYpoint);
		dynamic_cast<CMonster*>(m_pMonster)->BehaviorStart(m_ObjList[OBJ_PLAYER].front());
		Add_Object(OBJ_FLY, m_pMonster);
		return;

	case BOSSFLY:
	{
		m_pMonster = CAbstractFactory<CFly>::Create_BossFly(_fXpoint, _fYpoint, (_fXpoint - 25.f), (_fYpoint - 75.f)); // ÁÂ»ó
		dynamic_cast<CMonster*>(m_pMonster)->BehaviorStart(m_ObjList[OBJ_PLAYER].front());
		Add_Object(OBJ_FLY, m_pMonster);
		m_pMonster = nullptr;
		m_pMonster = CAbstractFactory<CFly>::Create_BossFly(_fXpoint, _fYpoint, (_fXpoint - 55.f), (_fYpoint - 55.f)); // ÁÂ»ó
		dynamic_cast<CMonster*>(m_pMonster)->BehaviorStart(m_ObjList[OBJ_PLAYER].front());
		Add_Object(OBJ_FLY, m_pMonster);
		m_pMonster = nullptr;
		m_pMonster = CAbstractFactory<CFly>::Create_BossFly(_fXpoint, _fYpoint, (_fXpoint - 75.f), (_fYpoint - 25.f)); // ÁÂ»ó
		dynamic_cast<CMonster*>(m_pMonster)->BehaviorStart(m_ObjList[OBJ_PLAYER].front());
		Add_Object(OBJ_FLY, m_pMonster);
		m_pMonster = nullptr;

		m_pMonster = CAbstractFactory<CFly>::Create_BossFly(_fXpoint, _fYpoint, (_fXpoint + 25.f), (_fYpoint + 75.f)); // ¿ìÇÏ
		dynamic_cast<CMonster*>(m_pMonster)->BehaviorStart(m_ObjList[OBJ_PLAYER].front());
		Add_Object(OBJ_FLY, m_pMonster);
		m_pMonster = nullptr;
		m_pMonster = CAbstractFactory<CFly>::Create_BossFly(_fXpoint, _fYpoint, (_fXpoint + 55.f), (_fYpoint + 55.f)); // ÁÂ»ó
		dynamic_cast<CMonster*>(m_pMonster)->BehaviorStart(m_ObjList[OBJ_PLAYER].front());
		Add_Object(OBJ_FLY, m_pMonster);
		m_pMonster = nullptr;
		m_pMonster = CAbstractFactory<CFly>::Create_BossFly(_fXpoint, _fYpoint, (_fXpoint + 75.f), (_fYpoint + 25.f)); // ¿ìÇÏ
		dynamic_cast<CMonster*>(m_pMonster)->BehaviorStart(m_ObjList[OBJ_PLAYER].front());
		Add_Object(OBJ_FLY, m_pMonster);
		m_pMonster = nullptr;

		m_pMonster = CAbstractFactory<CFly>::Create_BossFly(_fXpoint, _fYpoint, (_fXpoint + 25.f), (_fYpoint - 75.f)); // ¿ì»ó
		dynamic_cast<CMonster*>(m_pMonster)->BehaviorStart(m_ObjList[OBJ_PLAYER].front());
		Add_Object(OBJ_FLY, m_pMonster);
		m_pMonster = nullptr;
		m_pMonster = CAbstractFactory<CFly>::Create_BossFly(_fXpoint, _fYpoint, (_fXpoint + 55.f), (_fYpoint - 55.f)); // ÁÂ»ó
		dynamic_cast<CMonster*>(m_pMonster)->BehaviorStart(m_ObjList[OBJ_PLAYER].front());
		Add_Object(OBJ_FLY, m_pMonster);
		m_pMonster = nullptr;
		m_pMonster = CAbstractFactory<CFly>::Create_BossFly(_fXpoint, _fYpoint, (_fXpoint + 75.f), (_fYpoint - 25.f)); // ¿ì»ó
		dynamic_cast<CMonster*>(m_pMonster)->BehaviorStart(m_ObjList[OBJ_PLAYER].front());
		Add_Object(OBJ_FLY, m_pMonster);
		m_pMonster = nullptr;

		m_pMonster = CAbstractFactory<CFly>::Create_BossFly(_fXpoint, _fYpoint, (_fXpoint - 25.f), (_fYpoint + 75.f)); // ÁÂÇÏ
		dynamic_cast<CMonster*>(m_pMonster)->BehaviorStart(m_ObjList[OBJ_PLAYER].front());
		Add_Object(OBJ_FLY, m_pMonster);
		m_pMonster = nullptr;
		m_pMonster = CAbstractFactory<CFly>::Create_BossFly(_fXpoint, _fYpoint, (_fXpoint - 55.f), (_fYpoint + 55.f)); // ÁÂ»ó
		dynamic_cast<CMonster*>(m_pMonster)->BehaviorStart(m_ObjList[OBJ_PLAYER].front());
		Add_Object(OBJ_FLY, m_pMonster);
		m_pMonster = nullptr;
		m_pMonster = CAbstractFactory<CFly>::Create_BossFly(_fXpoint, _fYpoint, (_fXpoint - 75.f), (_fYpoint + 25.f)); // ÁÂÇÏ
		dynamic_cast<CMonster*>(m_pMonster)->BehaviorStart(m_ObjList[OBJ_PLAYER].front());
		Add_Object(OBJ_FLY, m_pMonster);
		m_pMonster = nullptr;
		return;
	}

	case ENVY:
		m_pMonster = CAbstractFactory<CEnvy>::Create(_fXpoint, _fYpoint);
		break;

	case HOPPER:
		m_pMonster = CAbstractFactory<CHopper>::Create(_fXpoint, _fYpoint);
		break;

	case TRASH:
		m_pMonster = CAbstractFactory<CTrash>::Create(_fXpoint, _fYpoint);
		dynamic_cast<CMonster*>(m_pMonster)->BehaviorStart(m_ObjList[OBJ_PLAYER].front());
		Add_Object(OBJ_BOSS, m_pMonster);
		return;
	}
	dynamic_cast<CMonster*>(m_pMonster)->BehaviorStart(m_ObjList[OBJ_PLAYER].front());
	Add_Object(OBJ_MONSTER, m_pMonster);
}

void CObjTestStageMgr::Set_TestObj_Dead(OBJID eID)
{
	for (auto& iter : m_ObjList[eID])
		iter->Set_Dead();
}

void CObjTestStageMgr::Set_DoNotRun(SCENEID _SceneID, OBJID eID)
{
	for (auto& iter : m_ObjList[eID])
		if(_SceneID == iter->Get_SceneID())
			iter->Set_DoNotRun();
}

void CObjTestStageMgr::Set_DoRun(SCENEID _SceneID, OBJID eID)
{
	for (auto& iter : m_ObjList[eID])
		if (_SceneID == iter->Get_SceneID())
			iter->Set_DoRun();
}

void CObjTestStageMgr::Open_Door()
{
	for (auto& iter : m_ObjList[OBJ_DOOR])
		dynamic_cast<CDoor*>(iter)->Set_CheakMon();
}