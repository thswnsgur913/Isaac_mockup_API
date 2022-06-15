#pragma once

typedef	struct tagInfo
{
	float	fX;
	float	fY;

	float	fCX;
	float	fCY;

	float	fRenX;
	float	fRenY;
}INFO;

struct Vector2D
{
	float x;
	float y;
};

typedef struct tagFrame
{
	int		iFrameStart;		// 원하는 지점부터 스프라이트 이미지 구동 시작
	int		iFrameEnd;			// 스프라이트가 끝나는 지점을 지정
	int		iMotion;			// 모션 인덱스

	DWORD	dwSpeed;			// 스프라이트가 돌아가는 속도
	DWORD	dwTime;				// 스프라이트 위치가 변경되는 시간 

}FRAME;