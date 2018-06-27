
#ifndef TEST_BEAN
#define TEST_BEAN

#include <Windows.h>

// 豆
struct CBean
{
public:
	CBean();
	~CBean();
public:
	int m_nX;	// x坐标
	int m_nY;	// y坐标
	COLORREF m_color;	// 豆的颜色
};

#endif

