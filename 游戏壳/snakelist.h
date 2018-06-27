
#ifndef TEST_SNAKELIST
#define TEST_SNAKELIST

#include "snake.h"
#include <Windows.h>
#include "bean.h"

// 蛇的方向
enum emDirectionType
{
	DT_Right = 1,	// 右
	DT_Left,		// 左
	DT_Up,			// 上
	DT_Down,		// 下
};

struct CSnakeList
{
public:
	CSnakeList();
	~CSnakeList();
public:
	void InitHDC(HDC hdc);
	// 创建蛇
	void CreateSnake();
	// 显示蛇
	void ShowSnake();
	// 移动蛇
	void Move();
	// 得到方向
	emDirectionType GetDirect();
	// 改变方向
	void ChangeDirection(emDirectionType dt);
	// 创建豆
	void CreateBean();
	// 显示豆
	void ShowBean();
	// 吃豆
	bool EatBean();
	// 判断能吃豆吗
	bool CanEat();
	// 显示分数
	void ShowScore();
	// 是否死亡
	bool CanDie();
	// 清空蛇
	void ClearSnake();
	
	int GetSpeed();

private:
	int m_nScore;			// 当前分数
	HDC m_hdc;				// 设备句柄
	CBean m_bean;			// 豆
	emDirectionType m_dt;	// 当前方向
	CSnakeInfo* m_pHead;	// 指向头的指针
	CSnakeInfo* m_pEnd;		// 指向尾的指针
	int m_nSpeed;			// 速度
};


#endif