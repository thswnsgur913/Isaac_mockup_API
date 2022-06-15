#pragma once

#include "Obj.h"
#include "SoundMgr.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual int	Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Set_Life(void) { ++m_iLife; CSoundMgr::Get_Instance()->PlaySoundW(L"Coin.wav", SOUND_EFFECT, g_fSound);}
	void Set_Coin(void) { ++m_iCoin; CSoundMgr::Get_Instance()->PlaySoundW(L"Coin.wav", SOUND_EFFECT, g_fSound);}
	void Minus_Coin() { --m_iCoin; }
	void Set_Boom(void) { ++m_iBoom; CSoundMgr::Get_Instance()->PlaySoundW(L"Coin.wav", SOUND_EFFECT, g_fSound);}
	void Set_Key(void) { ++m_iKey; CSoundMgr::Get_Instance()->PlaySoundW(L"Coin.wav", SOUND_EFFECT, g_fSound);}
	void Minus_Key() { --m_iKey; }
	void Set_ActiveA(void) { m_bActiveA = true; }
	void Set_PowerUp(void) { m_bPowerUp = true; }
	void Set_State(STATE _eCurState) { m_eCurState = _eCurState; }
	void Set_Bullet(BULLETTYPE _eBullet) { m_eBullet = _eBullet; }

	int Get_Life(void) { return m_iLife; }
	int Get_Coin(void) { return m_iCoin; }
	int Get_Boom(void) { return m_iBoom; }
	int Get_Key(void) { return m_iKey; }
	bool Get_ActiveA(void) { return m_bActiveA; }
	bool Get_CooldownA(void) { return m_CooldownA; }
	bool Get_GodMod(void) { return m_bGOD; }
	BULLETTYPE Get_BulletType(void) { return m_eBullet; }

private:
	void		Key_Input(void);
	void		Motion_Change(void);

private:
	float					m_fDiagonal;

	STATE					m_ePreState;
	STATE					m_eCurState;

	BULLETTYPE				m_eBullet;

	int m_iCoin;
	int m_iBoom;
	int m_iKey;
	bool m_bActiveA;
	bool m_CooldownA;
	bool m_bPowerUp;
	DWORD m_dwCool;
	DWORD m_dwCheak;

	bool m_bGOD;
};
