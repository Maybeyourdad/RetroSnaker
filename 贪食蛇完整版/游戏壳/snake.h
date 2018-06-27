
#ifndef TEST_SNAKE
#define TEST_SNAKE
#include <Windows.h>

struct CSnakeInfo
{
public:
	CSnakeInfo();
	~CSnakeInfo();
public:
	int m_nX;				// x坐标
	int m_nY;				// y坐标
	CSnakeInfo* m_pNext;	// 指向后一节的指针
	CSnakeInfo* m_pPre;		// 指向前一节的指针
	COLORREF m_color;		// 蛇的颜色
};

#endif