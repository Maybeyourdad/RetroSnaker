
#ifndef TEST_SNAKE
#define TEST_SNAKE
#include <Windows.h>

struct CSnakeInfo
{
public:
	CSnakeInfo();
	~CSnakeInfo();
public:
	int m_nX;				// x����
	int m_nY;				// y����
	CSnakeInfo* m_pNext;	// ָ���һ�ڵ�ָ��
	CSnakeInfo* m_pPre;		// ָ��ǰһ�ڵ�ָ��
	COLORREF m_color;		// �ߵ���ɫ
};

#endif