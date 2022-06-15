#pragma once

#include "Obj.h"

class CDoor :
	public CObj
{
//public:
//	enum DOOR { NEW, BACK, DOOR_END };

public:
	CDoor();
	~CDoor();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Set_ThisID(SCENEID _eThisID) { m_eThisID = _eThisID; }
	void Set_NestID(SCENEID _eNextID) { m_eNextID = _eNextID; }
	void Set_DoorDir(DIRECTION _DoorDir) { m_DoorDir = _DoorDir; }
	void Set_CheakMon() { m_bCheakMon = true; }
	void Set_ColCheak() { m_bColCheak = true; }
	void Set_KeyCheak() { m_bKeyCheak = true; }

	bool Get_CheakMon() { return m_bCheakMon; }
	bool Get_KeyCheak() { return m_bKeyCheak; }

	/*void Set_SCSAVEID_This(SCSAVEID _eSCSAVEID_This) { m_eSCSAVEID_This = _eSCSAVEID_This; }
	void Set_SCSAVEID_Next(SCSAVEID _eSCSAVEID_Next) { m_eSCSAVEID_Next = _eSCSAVEID_Next; }*/

private:
	bool m_bCheakMon;
	bool m_bColCheak;
	bool m_bKeyCheak;
	SCENEID m_eThisID;
	SCENEID m_eNextID;
	DIRECTION m_DoorDir;
	/*SCSAVEID m_eSCSAVEID_This;
	SCSAVEID m_eSCSAVEID_Next;*/
};

