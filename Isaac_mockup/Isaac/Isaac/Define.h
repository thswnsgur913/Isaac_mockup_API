#pragma once

#define WINCX 800
#define WINCY 600

#define BallCX 150
#define BallCY 150

#define PURE = 0

#define PI 3.1415926535f
#define DEGREE (PI / 180.f)

#define PLAYERCX 64.f
#define PLAYERCY 64.f

#define ACOSF(x,y) acosf(x / sqrtf((x * x) + (y * y)))
#define ASINF(x,y) asinf(y / sqrtf((x * x) + (y * y)))

#define		OBJ_NOEVENT  0
#define		OBJ_DEAD	 1

#define		VK_MAX		 0xff

extern HWND	g_hWnd;