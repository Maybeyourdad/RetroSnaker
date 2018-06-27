#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include "snakelist.h"

/*  函数声明 */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
void InitGame();		//游戏的初始化
int gettimeofday(timeval* tv);	// 获取当前时间戳（到毫秒）
void SetDirect(emDirectionType type);


/*  定义全局变量 */
char szClassName[ ] = "WindowsApp";
timeval oldTime;
static bool bStart = false;
static emDirectionType nOldDirection = DT_Right;


CSnakeList snakeList;

/*主函数入口*/
int WINAPI
	WinMain (HINSTANCE hThisInstance,					/*当前实例句柄*/
	HINSTANCE hPrevInstance,					/*前一个实例句柄*/ 
	LPSTR lpszArgument,						/*命令行字符串*/
	int nFunsterStil)							/*窗口显示方式*/

{
	HWND hwnd;               /* 主窗体句柄 */
	MSG messages;            /* 主窗体向应用程序发送的消息 */
	WNDCLASSEX wincl;        /* 主窗体的结构 */

	/* 填写窗口结构，使得其参数描述主窗口各个方面的属性 */
	wincl.hInstance = hThisInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = WindowProcedure;      /* 注册回调函数 */
	wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
	wincl.cbSize = sizeof (WNDCLASSEX);

	/* 使用缺省的图标和鼠标指针样式 */ 
	wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;                 /* 没有注册菜单 */
	wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
	wincl.cbWndExtra = 0;                      /* structure or the window instance */
	/* windows缺省的背景色 */
	wincl.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

	/* 对窗口进行注册 */
	if (!RegisterClassEx (&wincl))
		return 0;

	/* 创建一个窗口*/
	hwnd = CreateWindowEx (
		0,                   /* 指定窗口的扩展风格 */
		szClassName,         /* 指定窗体类名 */
		"Game", 				/* 窗口标题*/
		WS_OVERLAPPEDWINDOW, /* 指定创建窗口的风格 */
		CW_USEDEFAULT,       /* Windows decides the position */
		CW_USEDEFAULT,       /* where the window ends up on the screen */
		608,                 /* The programs width */
		550,                 /* and height in pixels */
		HWND_DESKTOP,        /* The window is a child-window to desktop */
		NULL,                /* No menu */
		hThisInstance,       /* Program Instance handler */
		NULL                 /* No Window Creation data */
		);

	/* 让窗口显示出来 */
	ShowWindow (hwnd, nFunsterStil);


	HDC hdc = GetDC(hwnd);
	/* 从应用程序进行必要的初始化 */

	snakeList.InitHDC(hdc);

	/* 进入消息循环；当得到的消息是一条WM_OUIT消息时，就退出消息循环 */
	while (GetMessage (&messages, NULL, 0, 0))
	{
		/* 把虚拟键消息翻译为字符消息 */
		TranslateMessage(&messages);
		/* 把消息分配到相应的窗口过程中去 */
		DispatchMessage(&messages);
	}

	/* The program return-value is 0 - The value that PostQuitMessage() gave */
	return (int)messages.wParam;
}


/*  回调函数，处理主窗口消息  */

LRESULT CALLBACK
	WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	int xPos;
	int yPos;
	char chCharCode;

	switch (message)                  /* handle the messages */
	{
	case WM_CREATE:
		/* 在这里初始创建画图的代码 */
		{
			snakeList.CreateSnake();
			snakeList.CreateBean();
		}
		break;
		//显示图形
	case WM_PAINT:
		{
			hdc = BeginPaint(hwnd, &ps);
			/* 在这里添加画图的代码 */

			// Rectangle(画刷设备句柄， 点1 x坐标，点1y坐标， 点2 x坐标，点2 y坐标)
			// 墙壁
			Rectangle(hdc, 0, 0, 500, 500);
			// 显示蛇
			snakeList.ShowSnake();
			snakeList.ShowBean();
			snakeList.ShowScore();
			
			
			EndPaint(hwnd, &ps);
		}
		break;
		//鼠标左击
	case WM_LBUTTONDOWN:
		{
			xPos = LOWORD(lParam);		//鼠标左击时x坐标
			yPos = HIWORD(lParam);		//鼠标左击时y坐标
			//在这里写鼠标左击代码
		}
		break;
		//鼠标右击
	case WM_RBUTTONDOWN:
		{
			xPos = LOWORD(lParam);		//鼠标右击时x坐标
			yPos = HIWORD(lParam);		//鼠标右击时y坐标
			//在这里写鼠标右击代码
		}
		break;
		//按下字母
	case WM_CHAR:
		{
			chCharCode = (char) wParam;	
			if ('A' == chCharCode)
			{
				//在这里写按了'A'时的代码

			}
			else if('a' == chCharCode)
			{

			}
		}
		break;
		//键盘按下事件
	case WM_KEYDOWN:
		switch(wParam)
		{
			/*按下Enter*/
		case VK_RETURN:		
			//在这里填写代码
			{
				SetTimer(hwnd, 0, snakeList.GetSpeed(), NULL);
			}
			break;
			/* 左箭头 */
		case VK_LEFT:
			//在这里填写代码
			{
				if (snakeList.GetDirect() != DT_Right)
				{
					SetDirect(DT_Left);
				}
			}
			break;
			/* 右箭头 */
		case VK_RIGHT:		
			//在这里填写代码
			{
				if (snakeList.GetDirect() != DT_Left)
				{
					SetDirect(DT_Right);
				}
			}
			break;
			/* 上箭头 */
		case VK_UP:	
			//在这里填写代码
			{
				if (snakeList.GetDirect() != DT_Down)
				{
					SetDirect(DT_Up);
				}
			}
			break;
			/* 下箭头 */
		case VK_DOWN:
			//在这里填写代码
			{
				if (snakeList.GetDirect() != DT_Up)
				{
					SetDirect(DT_Down);
				}
			}

			break;
		case VK_SPACE:
			{
				KillTimer(hwnd, 0);
			}
			break;
		}
		break;
		//键盘弹起事件
	case WM_KEYUP:
		switch(wParam)
		{
			/*弹起Enter*/
		case VK_RETURN:		
			//在这里填写代码
			{

			}
			break;
			/*弹起 左箭头 */
		case VK_LEFT:
			//在这里填写代码
			{
				
				
			}
			break;
			/* 弹起右箭头 */
		case VK_RIGHT:		
			//在这里填写代码
			{
				
			}
			break;
			/* 弹起上箭头 */
		case VK_UP:	
			//在这里填写代码
			{
				
			}
			break;
			/* 弹起下箭头 */
		case VK_DOWN:
			//在这里填写代码
			{
				
			}
			break;
		}
		break;
		/*时间事件*/
	case WM_TIMER:
		//在这里填写代码
		{
			Rectangle(GetDC(hwnd), 0, 0, 500, 500);

			if (snakeList.CanDie())
			{
				KillTimer(hwnd, NULL);
				snakeList.ShowSnake();
				snakeList.ShowBean();
				snakeList.ShowScore();
				//snakeList.ClearSnake();
				if (MessageBox(hwnd, "是否重新开始", "game over", MB_YESNO) == IDYES)
				{
					snakeList.ClearSnake();
					snakeList.CreateSnake();
					snakeList.CreateBean();

					SetTimer(hwnd, 0, snakeList.GetSpeed(), NULL);
				}
				else
				{
					break;
				}
				
			}

			// 如果吃豆成功我就不移动蛇了
			bool b = snakeList.EatBean();
			if (!b)
			{
				snakeList.Move();
			}
			
			snakeList.ShowSnake();
			snakeList.ShowBean();
			snakeList.ShowScore();
		}
		break;
	case WM_DESTROY:
		PostQuitMessage (0);       /* 向消息队列中发送一个WM_OUIT消息 */
		break;
	default:                      /* 调用默认窗口过程对未处理的消息进行必要的处理 */
		return DefWindowProc (hwnd, message, wParam, lParam);
	}

	return 0;
}

void SetDirect(emDirectionType type)
{
	if (!bStart)
	{
		gettimeofday(&oldTime);
		bStart = !bStart;
		nOldDirection = snakeList.GetDirect();
		snakeList.ChangeDirection(type);
	}
	else
	{
		timeval newTime;
		gettimeofday(&newTime);
		long long t = (newTime.tv_sec * 1000 + newTime.tv_usec / 1000) - (oldTime.tv_sec * 1000 + oldTime.tv_usec / 1000); 
		if (t > snakeList.GetSpeed())
		{
			snakeList.ChangeDirection(type);
		}
		else
		{
			snakeList.ChangeDirection(nOldDirection);
		}
		bStart = !bStart;
	}
}


int gettimeofday(timeval* tv)
{
	union {
		long long ns100;
		FILETIME ft;
	} now;
	GetSystemTimeAsFileTime (&now.ft);
	tv->tv_usec = (long) ((now.ns100 / 10LL) % 1000000LL);
	tv->tv_sec = (long) ((now.ns100 - 116444736000000000LL) / 10000000LL);
	return 0;
}
