
#ifndef TEST_SNAKELIST
#define TEST_SNAKELIST

#include "snake.h"
#include <Windows.h>
#include "bean.h"

// �ߵķ���
enum emDirectionType
{
	DT_Right = 1,	// ��
	DT_Left,		// ��
	DT_Up,			// ��
	DT_Down,		// ��
};

struct CSnakeList
{
public:
	CSnakeList();
	~CSnakeList();
public:
	void InitHDC(HDC hdc);
	// ������
	void CreateSnake();
	// ��ʾ��
	void ShowSnake();
	// �ƶ���
	void Move();
	// �õ�����
	emDirectionType GetDirect();
	// �ı䷽��
	void ChangeDirection(emDirectionType dt);
	// ������
	void CreateBean();
	// ��ʾ��
	void ShowBean();
	// �Զ�
	bool EatBean();
	// �ж��ܳԶ���
	bool CanEat();
	// ��ʾ����
	void ShowScore();
	// �Ƿ�����
	bool CanDie();
	// �����
	void ClearSnake();
	
	int GetSpeed();

private:
	int m_nScore;			// ��ǰ����
	HDC m_hdc;				// �豸���
	CBean m_bean;			// ��
	emDirectionType m_dt;	// ��ǰ����
	CSnakeInfo* m_pHead;	// ָ��ͷ��ָ��
	CSnakeInfo* m_pEnd;		// ָ��β��ָ��
	int m_nSpeed;			// �ٶ�
};


#endif