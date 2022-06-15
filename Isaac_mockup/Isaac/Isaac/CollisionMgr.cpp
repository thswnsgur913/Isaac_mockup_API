#include "stdafx.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include "ObjTestStageMgr.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "Active.h"
#include "Poo.h"
#include "Door.h"
#include "Fire.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (!Sour->Get_DoNotRun())
			{
				if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
				{
					//Dest->Set_Dead();
					Sour->Set_Dead();
					return;
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Rect_Boom(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (!Sour->Get_DoNotRun())
			{
				if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
				{
					Sour->MinusLife();
					return;
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Monster(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (!Sour->Get_DoNotRun())
			{
				if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
				{
					Dest->MinusLife();
					dynamic_cast<CMonster*>(Dest)->Set_MonState(MONSTATE_HIT);
					Sour->Set_Dead();
					return;
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Door(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (dynamic_cast<CDoor*>(Sour)->Get_CheakMon())
			{
				float	fX = 0.f, fY = 0.f;

				if (Check_Rect(Dest, Sour, &fX, &fY))
				{
					// 상하 충돌
					if (fX > fY)
					{
						// 상 충돌
						if (Dest->Get_Info().fY > Sour->Get_Info().fY)
						{
							if (!Dest->Get_Dead())
							{
								if (dynamic_cast<CDoor*>(Sour)->Get_KeyCheak())
								{
									if (0 >= dynamic_cast<CPlayer*>(Dest)->Get_Key())
									{
										if (0 >= CObjTestStageMgr::Get_Instance()->Get_Cheak_KeyDoor())
										{
											return;
										}
									}
								}
								Sour->Set_Dead();
								dynamic_cast<CDoor*>(Sour)->Set_ColCheak();
								Dest->Set_Pos(400.f, 450.f);
							}
							else
								return;
						}

						else // 하 충돌
						{
							if (!Dest->Get_Dead())
							{
								if (dynamic_cast<CDoor*>(Sour)->Get_KeyCheak())
								{
									if (0 >= dynamic_cast<CPlayer*>(Dest)->Get_Key())
									{
										if (0 >= CObjTestStageMgr::Get_Instance()->Get_Cheak_KeyDoor())
										{
											return;
										}
									}
								}
								Sour->Set_Dead();
								dynamic_cast<CDoor*>(Sour)->Set_ColCheak();
								Dest->Set_Pos(400.f, 200.f);
							}
							else
								return;
						}
					}
					// 좌우 충돌
					else
					{
						// 좌 충돌
						if (Dest->Get_Info().fX > Sour->Get_Info().fX)
						{
							if (!Dest->Get_Dead())
							{
								if (dynamic_cast<CDoor*>(Sour)->Get_KeyCheak())
								{
									if (0 >= dynamic_cast<CPlayer*>(Dest)->Get_Key())
									{
										if (0 >= CObjTestStageMgr::Get_Instance()->Get_Cheak_KeyDoor())
										{
											return;
										}
									}
								}
								Sour->Set_Dead();
								dynamic_cast<CDoor*>(Sour)->Set_ColCheak();
								Dest->Set_Pos(650.f, 350.f);
							}
							else
								return;
						}

						// 우 충돌
						else
						{
							if (!Dest->Get_Dead())
							{
								if (dynamic_cast<CDoor*>(Sour)->Get_KeyCheak())
								{
									if (0 >= dynamic_cast<CPlayer*>(Dest)->Get_Key())
									{
										if (0 >= CObjTestStageMgr::Get_Instance()->Get_Cheak_KeyDoor())
										{
											return;
										}
									}
								}
								Sour->Set_Dead();
								dynamic_cast<CDoor*>(Sour)->Set_ColCheak();
								Dest->Set_Pos(150.f, 350.f);
							}
							else
								return;
						}
					}

				}
			}
		}
	}
}

void CCollisionMgr::Collision_Item(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (!Sour->Get_DoNotRun())
			{
				if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
				{
					if (dynamic_cast<CItem*>(Sour)->Get_ItemType() == LIFE)
					{
						if (6 > dynamic_cast<CPlayer*>(Dest)->Get_Life())
						{
							Sour->Set_Dead();
							dynamic_cast<CPlayer*>(Dest)->Set_Life();
						}
						else
							Collision_RectEx(_Dest, _Sour);
					}
					else if (dynamic_cast<CItem*>(Sour)->Get_ItemType() == COIN)
					{
						Sour->Set_Dead();
						dynamic_cast<CPlayer*>(Dest)->Set_Coin();
					}
					else if (dynamic_cast<CItem*>(Sour)->Get_ItemType() == BOOM)
					{
						Sour->Set_Dead();
						dynamic_cast<CPlayer*>(Dest)->Set_Boom();
					}
					else if (dynamic_cast<CItem*>(Sour)->Get_ItemType() == KEY)
					{
						Sour->Set_Dead();
						dynamic_cast<CPlayer*>(Dest)->Set_Key();
					}
					else if (dynamic_cast<CItem*>(Sour)->Get_ItemType() == TRIPLE)
					{
						Sour->Set_Dead();
						dynamic_cast<CPlayer*>(Dest)->Set_Bullet(BULLET_EYEBALL);
						dynamic_cast<CPlayer*>(Dest)->Set_State(GET_TRIPLE);
					}
					else if (dynamic_cast<CItem*>(Sour)->Get_ItemType() == ACTIVE_A)
					{
						if (1 <= dynamic_cast<CPlayer*>(Dest)->Get_Coin())
						{
							Sour->Set_Dead();
							dynamic_cast<CPlayer*>(Dest)->Set_ActiveA();
							dynamic_cast<CPlayer*>(Dest)->Set_State(GET_ACTIVE_A);
							dynamic_cast<CPlayer*>(Dest)->Minus_Coin();
						}
						else
							Collision_RectEx(_Dest, _Sour);
					}
					else
					{
						return;
					}
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Stone(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (!Dest->Get_DoNotRun())
			{
				if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
				{
					Sour->Set_Dead();
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Poo_B(list<CObj*> _Dest, list<CObj*> _Sour) // bullet
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (!Dest->Get_DoNotRun())
			{
				if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
				{
					if (!Dest->Get_Dead())
					{
						dynamic_cast<CPoo*>(Dest)->Set_ColCheak();
						//Dest->Set_Dead();
						Sour->Set_Dead();
					}
					else
						break;
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Fire_B(list<CObj*> _Dest, list<CObj*> _Sour) // bullet
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (!Dest->Get_DoNotRun())
			{
				if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
				{
					if (!Dest->Get_Dead())
					{
						Dest->Set_Dead();
						dynamic_cast<CFire*>(Dest)->Set_ColCheakFire();
						Sour->Set_Dead();
					}
					else
						break;
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Fire_P(list<CObj*> _Dest, list<CObj*> _Sour) // player
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (!Dest->Get_DoNotRun())
			{
				float	fX = 0.f, fY = 0.f;

				if (Check_Rect(Dest, Sour, &fX, &fY))
				{
					// 상하 충돌
					if (fX > fY)
					{
						// 상 충돌
						if (Dest->Get_Info().fY > Sour->Get_Info().fY)
						{
							if (!Dest->Get_Dead())
							{
								Sour->Set_PosY(-(fY + 18));
								Sour->MinusLife();
								dynamic_cast<CPlayer*>(Sour)->Set_State(HIT);
								if (0 >= dynamic_cast<CPlayer*>(Sour)->Get_Life())
								{
									Sour->Set_Dead();
								}
								CObjTestStageMgr::Get_Instance()->Set_Cheak();
								return;
							}
							else
								return;
						}

						else // 하 충돌
						{
							if (!Dest->Get_Dead())
							{
								Sour->Set_PosY(fY + 18);
								Sour->MinusLife();
								dynamic_cast<CPlayer*>(Sour)->Set_State(HIT);
								if (0 >= dynamic_cast<CPlayer*>(Sour)->Get_Life())
								{
									Sour->Set_Dead();
								}
								CObjTestStageMgr::Get_Instance()->Set_Cheak();
								return;
							}
							else
								return;
						}
					}
					// 좌우 충돌
					else
					{
						// 좌 충돌
						if (Dest->Get_Info().fX > Sour->Get_Info().fX)
						{
							if (!Dest->Get_Dead())
							{
								Sour->Set_PosX(-(fX + 18));
								Sour->MinusLife();
								dynamic_cast<CPlayer*>(Sour)->Set_State(HIT);
								if (0 >= dynamic_cast<CPlayer*>(Sour)->Get_Life())
								{
									Sour->Set_Dead();
								}
								CObjTestStageMgr::Get_Instance()->Set_Cheak();
								return;
							}
							else
								return;
						}

						// 우 충돌
						else
						{
							if (!Dest->Get_Dead())
							{
								Sour->Set_PosX(fX + 18);
								Sour->MinusLife();
								dynamic_cast<CPlayer*>(Sour)->Set_State(HIT);
								if (0 >= dynamic_cast<CPlayer*>(Sour)->Get_Life())
								{
									Sour->Set_Dead();
								}
								CObjTestStageMgr::Get_Instance()->Set_Cheak();
								return;
							}
							else
								return;
						}
					}

				}
			}
		}
	}
}
									// 고정되어 있는 물체  // 움직이는 물체		
void CCollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (!Dest->Get_DoNotRun())
			{
				float	fX = 0.f, fY = 0.f;

				if (Check_Rect(Dest, Sour, &fX, &fY))
				{
					// 상하 충돌
					if (fX > fY)
					{
						// 상 충돌
						if (Dest->Get_Info().fY > Sour->Get_Info().fY)
						{
							if (!Dest->Get_Dead())
							{
								Sour->Set_PosY(-fY);
							}
							else
								return;
						}

						else // 하 충돌
						{
							if (!Dest->Get_Dead())
							{
								Sour->Set_PosY(fY);
							}
							else
								return;
						}
					}
					// 좌우 충돌
					else
					{
						// 좌 충돌
						if (Dest->Get_Info().fX > Sour->Get_Info().fX)
						{
							if (!Dest->Get_Dead())
							{
								Sour->Set_PosX(-fX);
							}
							else
								return;
						}

						// 우 충돌
						else
						{
							if (!Dest->Get_Dead())
							{
								Sour->Set_PosX(fX);
							}
							else
								return;
						}
					}

				}
			}
		}
	}
}

bool CCollisionMgr::Check_Rect(CObj* pDest, CObj* pSour, float *pX, float* pY)
{
	float		fWidth = abs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float		fHeight = abs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	float		fCX = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;
	float		fCY = (pDest->Get_Info().fCY + pSour->Get_Info().fCY) * 0.5f;

	if ((fCX > fWidth) && (fCY > fHeight))
	{
		*pX = fCX - fWidth;
		*pY = fCY - fHeight;

		return true;
	}
	
	return false;
}

bool CCollisionMgr::Check_Sphere(CObj* pDest, CObj* pSour)
{
	
	// abs : 절대값을 구해주는 함수
	float	fWidth  = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float	fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	// sqrt : 루트를 씌워주는 함수
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;

	return fRadius > fDiagonal;
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour)
{

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{
				dynamic_cast<CMonster*>(Dest)->Set_MonState(MONSTATE_HIT);
				Dest->MinusLife();
				Sour->Set_Dead();
				return;
			}
		}
	}
}

void CCollisionMgr::Collision_Sphere_P(list<CObj*> _Dest, list<CObj*> _Sour)
{

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{
				dynamic_cast<CPlayer*>(Dest)->Set_State(HIT);
				Dest->MinusLife();
				if (0 >= dynamic_cast<CPlayer*>(Dest)->Get_Life())
				{
					Dest->Set_Dead();
				}
				CObjTestStageMgr::Get_Instance()->Set_Cheak();
				Sour->Set_Dead();
				return;
			}
		}
	}
}

void CCollisionMgr::Collision_Sphere_Player(list<CObj*> _Dest, list<CObj*> _Sour)
{

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{
				if (Return == dynamic_cast<CMonster*>(Dest)->Get_Pattern())
				{
					Sour->MinusLife();
					Sour->MinusLife();
					Sour->MinusLife();
					dynamic_cast<CPlayer*>(Sour)->Set_State(HIT);
					if (0 >= dynamic_cast<CPlayer*>(Sour)->Get_Life())
					{
						Sour->Set_Dead();
					}
					CObjTestStageMgr::Get_Instance()->Set_Cheak();
					return;
				}
				else
				{
					Sour->MinusLife();
					dynamic_cast<CPlayer*>(Sour)->Set_State(HIT);
					if (0 >= dynamic_cast<CPlayer*>(Sour)->Get_Life())
					{
						Sour->Set_Dead();
					}
					CObjTestStageMgr::Get_Instance()->Set_Cheak();
					return;
				}
			}
		}
	}
}