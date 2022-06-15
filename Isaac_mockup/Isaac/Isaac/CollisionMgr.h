#pragma once

#include "Obj.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static bool		Check_Sphere(CObj* pDest, CObj* pSour);
	static bool		Check_Rect(CObj* pDest, CObj* pSour, float *pX, float* pY);
	static void		Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_Rect_Boom(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_Monster(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_Door(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_Item(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_Stone(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_Poo_B(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_Fire_B(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_Fire_P(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_Sphere_P(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_Sphere_Player(list<CObj*> _Dest, list<CObj*> _Sour);
};

