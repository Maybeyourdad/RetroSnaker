#include "snakelist.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SNAKE_SIZE 20


CSnakeList::CSnakeList()
{
	srand((unsigned)time(NULL));
	m_dt = DT_Right;
	m_pHead = NULL;
	m_pEnd = NULL;
	m_nScore = 0;
	m_nSpeed = 100;
}

CSnakeList::~CSnakeList()
{
	
}

void CSnakeList::CreateSnake()
{
	for (int i = 0; i < 3; i++)
	{
		CSnakeInfo* p = (CSnakeInfo*)malloc(sizeof(CSnakeInfo));
		if (p == NULL)
		{
			return;
		}
		p->m_nX = i * SNAKE_SIZE;
		p->m_nY = 0;
		p->m_pNext = NULL;
		p->m_pPre = NULL;

		int nR = rand() % 256;
		int nG = rand() % 256;
		int nB = rand() % 256;
		p->m_color = RGB(nR, nG, nB);

		if (m_pHead == NULL)
		{
			m_pHead = p;
		}
		else
		{
			m_pEnd->m_pNext = p;
			p->m_pPre = m_pEnd;
		}
		m_pEnd = p;
	}
}

void CSnakeList::ShowSnake()
{
	CSnakeInfo* pTmp = m_pHead;
	while (pTmp != NULL)
	{
		// 画刷
		HBRUSH hBr = CreateSolidBrush(pTmp->m_color);
		// 关联hdc
		HBRUSH hOldBr = (HBRUSH)SelectObject(m_hdc, hBr);
		Rectangle(m_hdc, pTmp->m_nX, pTmp->m_nY, pTmp->m_nX + SNAKE_SIZE, pTmp->m_nY + SNAKE_SIZE);
		pTmp = pTmp->m_pNext;
		DeleteObject(hBr);
	}
}

void CSnakeList::InitHDC(HDC hdc)
{
	m_hdc = hdc;
}

void CSnakeList::Move()
{
	COLORREF nTmpColor = m_pHead->m_color;
	CSnakeInfo* pTmp = m_pHead;
	switch (m_dt)
	{
	case DT_Right:
		{
			if (m_pEnd->m_nX == 480)
			{
				pTmp->m_nX = 0;
			}
			else
			{
				pTmp->m_nX = m_pEnd->m_nX + SNAKE_SIZE;
			}
			pTmp->m_nY = m_pEnd->m_nY;
		}
		break;
	case DT_Left:
		{
			if (m_pEnd->m_nX == 0)
			{
				pTmp->m_nX = 480;
			}
			else
			{
				pTmp->m_nX = m_pEnd->m_nX - SNAKE_SIZE;
			}
			pTmp->m_nY = m_pEnd->m_nY;
		}
		break;
	case DT_Up:
		{
			if (m_pEnd->m_nY == 0)
			{
				pTmp->m_nY = 480;
			}
			else
			{
				pTmp->m_nY = m_pEnd->m_nY - SNAKE_SIZE;
			}
			pTmp->m_nX = m_pEnd->m_nX;
		}
		break;
	case DT_Down:
		{
			if (m_pEnd->m_nY == 480)
			{
				pTmp->m_nY = 0;
			}
			else
			{
				pTmp->m_nY = m_pEnd->m_nY + SNAKE_SIZE;
			}
			pTmp->m_nX = m_pEnd->m_nX;
		}
		break;
	}
	
	// pHead移到pEnd后
	m_pHead = m_pHead->m_pNext;
	m_pHead->m_pPre = NULL;
	pTmp->m_pNext = NULL;
	pTmp->m_pPre = m_pEnd;
	m_pEnd->m_pNext = pTmp;
	m_pEnd = pTmp;

	// 换颜色
	CSnakeInfo* p = m_pEnd;
	while (p->m_pPre != NULL)
	{
		p->m_color = p->m_pPre->m_color;
		p = p->m_pPre;
	}
	p->m_color = nTmpColor;
}

void CSnakeList::ChangeDirection(emDirectionType dt)
{
	m_dt = dt;
}

emDirectionType CSnakeList::GetDirect()
{
	return m_dt;
}

void CSnakeList::CreateBean()
{
	bool flag = true;
	while (true)
	{
		m_bean.m_nX = rand() % 25 * SNAKE_SIZE;
		m_bean.m_nY = rand() % 25 * SNAKE_SIZE;
		CSnakeInfo* pTmp = m_pHead;
		while (pTmp != NULL)
		{
			if (pTmp->m_nX == m_bean.m_nX && pTmp->m_nY == m_bean.m_nY)
			{
				flag = false;
				break;
			}
			pTmp = pTmp->m_pNext;
		}
		if (flag == true)
		{
			break;
		}
	}
	int nR = rand() % 256;
	int nG = rand() % 256;
	int nB = rand() % 256;
	m_bean.m_color = RGB(nR, nG, nB);
}

void CSnakeList::ShowBean()
{
	// 画刷
	HBRUSH hBr = CreateSolidBrush(m_bean.m_color);
	// 关联hdc
	HBRUSH hOldBr = (HBRUSH)SelectObject(m_hdc, hBr);

	Ellipse(m_hdc, m_bean.m_nX, m_bean.m_nY, m_bean.m_nX + SNAKE_SIZE, m_bean.m_nY + SNAKE_SIZE);

	DeleteObject(hBr);
}

bool CSnakeList::EatBean()
{
	// 判断能吃到豆吗
	if (CanEat())
	{
		CSnakeInfo* p = (CSnakeInfo*)malloc(sizeof(CSnakeInfo));
		if (p == NULL)
		{
			return false;
		}

		p->m_color = m_bean.m_color;

		p->m_nX = m_bean.m_nX;
		p->m_nY = m_bean.m_nY;

		// 连接到蛇头
		p->m_pNext = NULL;
		p->m_pPre = m_pEnd;
		m_pEnd->m_pNext = p;
		m_pEnd = p;

		// 修改颜色，将吃的豆颜色放最后
		CSnakeInfo* pTmp = m_pEnd;
		while (pTmp->m_pPre != NULL)
		{
			pTmp->m_color = pTmp->m_pPre->m_color;
			pTmp = pTmp->m_pPre;
		}
		pTmp->m_color = m_bean.m_color;

		// 吃完豆再创建一个新的
		CreateBean();
		// 分数+1
		m_nScore++;
		return true;
	}
	return false;
}

bool CSnakeList::CanEat()
{
	switch (m_dt)
	{
	case DT_Right:
		{
			bool bNomal = (m_pEnd->m_nX + SNAKE_SIZE == m_bean.m_nX && m_pEnd->m_nY == m_bean.m_nY);
			bool bSpecial = (m_pEnd->m_nY == m_bean.m_nY && m_pEnd->m_nX == 480 && m_bean.m_nX == 0);
			if (bNomal || bSpecial)
			{
				return true;
			}
		}
		break;
	case DT_Left:
		{
			if ((m_pEnd->m_nX - SNAKE_SIZE == m_bean.m_nX &&
				m_pEnd->m_nY == m_bean.m_nY) ||
				(m_pEnd->m_nY == m_bean.m_nY &&
				m_pEnd->m_nX == 0 &&
				m_bean.m_nX == 480))
			{
				return true;
			}
		}
		break;
	case DT_Up:
		{
			if ((m_pEnd->m_nX == m_bean.m_nX &&
				m_pEnd->m_nY - SNAKE_SIZE == m_bean.m_nY) ||
				(m_pEnd->m_nX == m_bean.m_nX &&
				m_pEnd->m_nY == 0 &&
				m_bean.m_nY == 480))
			{
				return true;
			}
		}
		break;
	case DT_Down:
		{
			if ((m_pEnd->m_nX == m_bean.m_nX &&
				m_pEnd->m_nY + SNAKE_SIZE == m_bean.m_nY) ||
				(m_pEnd->m_nX == m_bean.m_nX &&
				m_pEnd->m_nY == 480 &&
				m_bean.m_nY == 0))
			{
				return true;
			}
		}
		break;
	}
	return false;
}

void CSnakeList::ShowScore()
{
	char szScore[20] = "分数：";
	char szNum[10];
	// 将int转换为字符串
	itoa(m_nScore, szNum, 10);
	strcat(szScore, szNum);
	TextOut(m_hdc, 510, 400, szScore, strlen(szScore));
}

bool CSnakeList::CanDie()
{
	CSnakeInfo* pTmp = m_pEnd->m_pPre;
	while (pTmp != NULL)
	{
		if (m_pEnd->m_nX == pTmp->m_nX && m_pEnd->m_nY == pTmp->m_nY)
		{
			return true;
		}
		pTmp = pTmp->m_pPre;
	}

	return false;
}

void CSnakeList::ClearSnake()
{
	CSnakeInfo* pTmp;
	while (m_pHead != NULL)
	{
		pTmp = m_pHead;
		m_pHead = m_pHead->m_pNext;
		free(pTmp);
	}
	m_pHead = NULL;
	m_pEnd = NULL;
	m_nScore = 0;
	m_dt = DT_Right;
}

int CSnakeList::GetSpeed()
{
	return m_nSpeed;
}