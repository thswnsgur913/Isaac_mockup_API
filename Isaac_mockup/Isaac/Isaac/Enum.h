#pragma once

enum DIRECTION { DIR_LEFT, DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_UP_BOSS, DIR_UP_END, DIR_END };

enum STATE { IDLE, WALKD, WALKU, WALKL, WALKR, ATTACK, HIT, GET_TRIPLE, GET_ACTIVE_A, END };

enum MONSTATE { MONSTATE_IDLE, MONSTATE_HIT, M0NSTER_JUMP, MONSTATE_END };

enum BULLETTYPE {BULLET_DEFULT, BULLET_EYEBALL, BULLET_END};

enum ITEMTYPE { COIN, BOOM, KEY, LIFE, TRIPLE, ACTIVE_A, ITEM_END };

enum MONTYPE { FLY, BOSSFLY, ENVY, HOPPER, TRASH, BOSSBALL, MON_END };

enum UIID { UI_MAP, UI_ITEM, UI_END };

enum OBJID { OBJ_PLAYER, OBJ_BULLET, OBJ_BOOM, OBJ_BOSS, OBJ_MONSTER, OBJ_STONE, OBJ_FIRE, OBJ_POO, OBJ_WALL, OBJ_DOOR, OBJ_ITEM, OBJ_LIFE, OBJ_MOUSE, OBJ_BUTTON, OBJ_MONBUL, OBJ_FLY, OBJ_END };

enum SCENEID { SC_MENU, SC_TESTSTAGE, SC_STAGE1, SC_STAGE2, SC_STAGE3, SC_STAGEBOSS, SC_ENDING, SC_CLEAR, SC_END };

enum RENDERID { RENDER_BACKGROUND, RENDER_FIELDOBJECT, RENDER_GAMEOBJECT, RENDER_UI, RENDER_BOSS, RENDER_BOSSFLY, RENDER_PLAYER, RENDER_END };

enum CHANNELID { SOUND_EFFECT, SOUND_BGM, SOUND_PLAYER, SOUND_MONSTER, SOUND_FLY, SOUND_BULLET, SOUND_BULLET_END, SOUND_PBUL, SOUND_MBUL, SOUND_EYE, SOUND_DOOR, SOUND_FIRE, MAXCHANNEL };

enum Pattern {
	Create,
	Fly1,
	Fly2,
	Envy,
	Hopper,
	Trash1, // Create Fly
	Trash2, // Create Big Bullet
	Trash3, // Jump and
	Return, // Shot Bullet
	Idle
};