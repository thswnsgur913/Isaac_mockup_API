#pragma once

#include "Obj.h"
#include "UI.h"
#include "ItemUI.h"
#include "MapUI.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory(){}
	~CAbstractFactory(){}

public:
	static CObj*	Create(void)
	{
		CObj*	pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj*	Create_Door(float _fX, float _fY, bool _KeyCheak, SCENEID _ThisID = SC_END, SCENEID _NextID = SC_END, DIRECTION _DoorDir = DIR_END)
	{
		CObj*	pObj = new T;

		if (SC_END >= _ThisID)
			dynamic_cast<CDoor*>(pObj)->Set_ThisID(_ThisID);

		if (SC_END >= _NextID)
			dynamic_cast<CDoor*>(pObj)->Set_NestID(_NextID);

		if (DIR_END >= _DoorDir)
			dynamic_cast<CDoor*>(pObj)->Set_DoorDir(_DoorDir);

		if(_KeyCheak)
			dynamic_cast<CDoor*>(pObj)->Set_KeyCheak();

		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		

		return pObj;
	}

	static CObj*	Create_Item(SCENEID _eSceneID, float _fX, float _fY, ITEMTYPE _type = ITEM_END) //item
	{
		CObj*	pObj = new T;

		if (ITEM_END >= _type)
			dynamic_cast<CItem*>(pObj)->Set_ItemType(_type);

		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_SceneID(_eSceneID);

		return pObj;
	}

	static CUI*	Create_UI(void)
	{
		CUI*	pUI = new T;
		pUI->Initialize();

		return pUI;
	}

	static CUI*	Item_UI(float _fX, float _fY, ITEMTYPE _type = END) //itemUI
	{
		CUI*	pUI = new T;

		if (END >= _type)
			dynamic_cast<CItemUI*>(pUI)->Set_ItemType(_type);

		pUI->Initialize();
		pUI->Set_Pos(_fX, _fY);

		return pUI;
	}

	static CUI*	Map_UI(float _fX, float _fY, SCENEID _Scene = SC_END) // Map
	{
		CUI*	pMapUI = new T;

		if (SC_END >= _Scene)
			dynamic_cast<CMapUI*>(pMapUI)->Set_SceneID(_Scene);

		pMapUI->Initialize();
		pMapUI->Set_Pos(_fX, _fY);

		return pMapUI;
	}

	static CObj*	Create_Stone(SCENEID _eSceneID, float _fX, float _fY, int _iA, int _iB, int _iC) // stone
	{
		CObj*	pObj = new T;

		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Frame(_iA, _iB, _iC);
		pObj->Set_SceneID(_eSceneID);

		return pObj;
	}

	static CObj*	Create_Wall(float _fX, float _fY, float _fCX, float _fCY) // wall
	{
		CObj*	pObj = new T;

		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Size(_fCX, _fCY);

		return pObj;
	}

	static CObj*	Create_Object(SCENEID _eSceneID, float _fX, float _fY, float _fCX, float _fCY)
	{
		CObj*	pObj = new T;

		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Size(_fCX, _fCY);
		pObj->Set_SceneID(_eSceneID);

		return pObj;
	}

	static CObj*	Create(float _fX, float _fY, DIRECTION eDir = DIR_END) // bullet
	{
		CObj*	pObj = new T;

		if (DIR_END >= eDir)
			pObj->Set_Dir(eDir);

		pObj->Set_Pos(_fX, _fY);

		pObj->Initialize();

		return pObj;
	}

	static CObj*	Create_Angle_Bullet(float _fX, float _fY, float _fAngle, DIRECTION eDir = DIR_END)
	{
		CObj*	pObj = new T;

		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);

		if (DIR_END >= eDir)
			pObj->Set_Dir(eDir);

		return pObj;
	}

	static CObj*	Create_TB(float _fX, float _fY, float _fAngle, DIRECTION eDir = DIR_END, OBJID _eID = OBJ_END)
	{
		CObj*	pObj = new T;

		if (DIR_END >= eDir)
			pObj->Set_Dir(eDir);

		if (OBJ_END >= _eID)
			pObj->Set_BulID(_eID);

		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}

	static CObj*	Create_BossFly(float _fX1, float _fY1, float _fX2, float _fY2)
	{
		CObj*	pObj = new T;

		pObj->Initialize();

		pObj->Set_Pos(_fX1, _fY1);

		dynamic_cast<CMonster*>(pObj)->Set_Fly1();

		dynamic_cast<CMonster*>(pObj)->Set_TargetPosition(_fX2, _fY2);

		return pObj;
	}

	static CObj*	Create_BossBall(float _fX1, float _fY1, float _fX2, float _fY2, float _fAngle)
	{
		CObj*	pObj = new T;

		pObj->Set_Pos(_fX1, _fY1);

		pObj->Set_Size(_fX2, _fX2);

		dynamic_cast<CMonster*>(pObj)->Set_Angle(_fAngle);//Set_TargetPosition(_fX2, _fY2);

		pObj->Initialize();

		return pObj;
	}
};

