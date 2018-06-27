#include "snake.h"
#include <stdio.h>

CSnakeInfo::CSnakeInfo()
{
	m_nX = 0;
	m_nY = 0;
	m_pNext = NULL;
	m_pPre = NULL;
	m_color = RGB(0, 0, 0);
}

CSnakeInfo::~CSnakeInfo()
{

}