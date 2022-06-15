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
	int		iFrameStart;		// ���ϴ� �������� ��������Ʈ �̹��� ���� ����
	int		iFrameEnd;			// ��������Ʈ�� ������ ������ ����
	int		iMotion;			// ��� �ε���

	DWORD	dwSpeed;			// ��������Ʈ�� ���ư��� �ӵ�
	DWORD	dwTime;				// ��������Ʈ ��ġ�� ����Ǵ� �ð� 

}FRAME;