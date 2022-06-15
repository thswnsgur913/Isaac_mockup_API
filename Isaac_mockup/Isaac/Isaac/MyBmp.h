#pragma once

#include "Include.h"

class CMyBmp
{
public:
	CMyBmp();
	~CMyBmp();

public:
	HDC			Get_MemDC() { return m_hMemDC; }
public:
	void		Load_Bmp(const TCHAR* pFilePath);
	void		Release(void);

private:
	HDC			m_hMemDC;

	HBITMAP		m_hBitMap;
	HBITMAP		m_hOldMap;
};

// DDB : ��ġ�� �������� ��Ʈ�� ���� ����, �̹����� ũ��, ���� �� �⺻���� ������ �̹��� �����䷯ �����Ǿ� �־� �پ��� �ػ��� ��ġ�� �������ϰ� ������ ���Ѵ�.
//		 ��� ��Ʈ���� ��� ��ġ�� �÷� ��Ʈ���� �÷� ��ġ�θ� ����� �� �ִ�.

// DIB : ��ġ�� �������� ��Ʈ�� ���� ����, DDB�� ���� ���� ���̺�, �ػ� ���� ���� �߰� ������ �����Ƿ�, ��ġ�� ���ӵ��� �ʾ� Ȱ�뵵�� �� �������ϰ� ȣȯ���� �پ��.