#pragma once

#include "Obj.h"
#include "Player.h"
#include "Boom.h"
#include "Door.h"

class CObjTestStageMgr
{
private:
	CObjTestStageMgr();
	~CObjTestStageMgr();

public:
	bool		Cheak_OBJ(OBJID _OBJID) { if (m_ObjList[_OBJID].empty()) { return true; } else { return false; } }
	void		Cheak_Key(SCENEID _SceneID, OBJID _OBJID);
	bool		Cheak_Open_Poo(SCENEID _SceneID, OBJID _OBJID, float _fA);
	void		Cheak_Open_Door(SCENEID _SceneID, OBJID _OBJID);
	CObj*		Get_Player() { return m_ObjList[OBJ_PLAYER].front(); }
	CObj*		Get_Boss() { return m_ObjList[OBJ_BOSS].front(); }
	CObj*		Get_Target(OBJID eID, CObj* pObj);

public:
	void		Add_Object(OBJID eID, CObj* pObj);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	void		Delete_ID(OBJID eID);

	void		CreateMonster(MONTYPE _type, float _fXpoint, float _fYpoint);

	void		Set_TestObj_Dead(OBJID eID);
	void		Set_DoNotRun(SCENEID _SceneID, OBJID eID);
	void		Set_DoRun(SCENEID _SceneID, OBJID eID);
	void		Open_Door();

	void		Set_Cheak() { m_bCheak = true; }

private:
	list<CObj*>	m_ObjList[OBJ_END];

public:
	// 몬스터 혹은 아이템의 재할당을 막기위한 스태틱 변수
	int Get_Cheak_TestStage_In() { return Cheak_TestStage_In; }
	void Set_Cheak_TestStage_In(int _iA) { Cheak_TestStage_In = _iA; }
	static int Cheak_TestStage_In;

	int Get_Cheak_Stage1_In() { return Cheak_Stage1_In; }
	void Set_Cheak_Stage1_In(int _iA) { Cheak_Stage1_In = _iA; }
	static int Cheak_Stage1_In;

	int Get_Cheak_Stage2_In() { return Cheak_Stage2_In; }
	void Set_Cheak_Stage2_In(int _iA) { Cheak_Stage2_In = _iA; }
	static int Cheak_Stage2_In;

	int Get_Cheak_Stage3_In() { return Cheak_Stage3_In; }
	void Set_Cheak_Stage3_In(int _iA) { Cheak_Stage3_In = _iA; }
	static int Cheak_Stage3_In;

	int Get_Cheak_BossStage_In() { return Cheak_BossStage_In; }
	void Set_Cheak_BossStage_In(int _iA) { Cheak_BossStage_In = _iA; }
	static int Cheak_BossStage_In;

	// 열쇠문 열렸나 안열렸나
	int Get_Cheak_KeyDoor() { return Cheak_KeyDoor; }
	void Set_Cheak_KeyDoor(int _iA) { Cheak_KeyDoor = _iA; }
	static int Cheak_KeyDoor;

	// 아이템 드랍 확인
	int Get_Cheak_Drop() { return Cheak_Drop; }
	void Set_Cheak_Drop(int _iA) { Cheak_Drop = _iA; }
	static int Cheak_Drop;

public:
	static		CObjTestStageMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CObjTestStageMgr;
		}

		return m_pInstance;
	}

	static	void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CObjTestStageMgr*			m_pInstance;
	list<CObj*>				m_RenderSort[RENDER_END];

	CObj* m_pMonster;

	bool m_bCheak;
	DWORD m_dwCheak;
};

