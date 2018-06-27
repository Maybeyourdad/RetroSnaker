#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include "snakelist.h"

/*  �������� */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
void InitGame();		//��Ϸ�ĳ�ʼ��
int gettimeofday(timeval* tv);	// ��ȡ��ǰʱ����������룩
void SetDirect(emDirectionType type);


/*  ����ȫ�ֱ��� */
char szClassName[ ] = "WindowsApp";
timeval oldTime;
static bool bStart = false;
static emDirectionType nOldDirection = DT_Right;


CSnakeList snakeList;

/*���������*/
int WINAPI
	WinMain (HINSTANCE hThisInstance,					/*��ǰʵ�����*/
	HINSTANCE hPrevInstance,					/*ǰһ��ʵ�����*/ 
	LPSTR lpszArgument,						/*�������ַ���*/
	int nFunsterStil)							/*������ʾ��ʽ*/

{
	HWND hwnd;               /* �������� */
	MSG messages;            /* ��������Ӧ�ó����͵���Ϣ */
	WNDCLASSEX wincl;        /* ������Ľṹ */

	/* ��д���ڽṹ��ʹ����������������ڸ������������ */
	wincl.hInstance = hThisInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = WindowProcedure;      /* ע��ص����� */
	wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
	wincl.cbSize = sizeof (WNDCLASSEX);

	/* ʹ��ȱʡ��ͼ������ָ����ʽ */ 
	wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;                 /* û��ע��˵� */
	wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
	wincl.cbWndExtra = 0;                      /* structure or the window instance */
	/* windowsȱʡ�ı���ɫ */
	wincl.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

	/* �Դ��ڽ���ע�� */
	if (!RegisterClassEx (&wincl))
		return 0;

	/* ����һ������*/
	hwnd = CreateWindowEx (
		0,                   /* ָ�����ڵ���չ��� */
		szClassName,         /* ָ���������� */
		"Game", 				/* ���ڱ���*/
		WS_OVERLAPPEDWINDOW, /* ָ���������ڵķ�� */
		CW_USEDEFAULT,       /* Windows decides the position */
		CW_USEDEFAULT,       /* where the window ends up on the screen */
		608,                 /* The programs width */
		550,                 /* and height in pixels */
		HWND_DESKTOP,        /* The window is a child-window to desktop */
		NULL,                /* No menu */
		hThisInstance,       /* Program Instance handler */
		NULL                 /* No Window Creation data */
		);

	/* �ô�����ʾ���� */
	ShowWindow (hwnd, nFunsterStil);


	HDC hdc = GetDC(hwnd);
	/* ��Ӧ�ó�����б�Ҫ�ĳ�ʼ�� */

	snakeList.InitHDC(hdc);

	/* ������Ϣѭ�������õ�����Ϣ��һ��WM_OUIT��Ϣʱ�����˳���Ϣѭ�� */
	while (GetMessage (&messages, NULL, 0, 0))
	{
		/* ���������Ϣ����Ϊ�ַ���Ϣ */
		TranslateMessage(&messages);
		/* ����Ϣ���䵽��Ӧ�Ĵ��ڹ�����ȥ */
		DispatchMessage(&messages);
	}

	/* The program return-value is 0 - The value that PostQuitMessage() gave */
	return (int)messages.wParam;
}


/*  �ص�������������������Ϣ  */

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
		/* �������ʼ������ͼ�Ĵ��� */
		{
			snakeList.CreateSnake();
			snakeList.CreateBean();
		}
		break;
		//��ʾͼ��
	case WM_PAINT:
		{
			hdc = BeginPaint(hwnd, &ps);
			/* ��������ӻ�ͼ�Ĵ��� */

			// Rectangle(��ˢ�豸����� ��1 x���꣬��1y���꣬ ��2 x���꣬��2 y����)
			// ǽ��
			Rectangle(hdc, 0, 0, 500, 500);
			// ��ʾ��
			snakeList.ShowSnake();
			snakeList.ShowBean();
			snakeList.ShowScore();
			
			
			EndPaint(hwnd, &ps);
		}
		break;
		//������
	case WM_LBUTTONDOWN:
		{
			xPos = LOWORD(lParam);		//������ʱx����
			yPos = HIWORD(lParam);		//������ʱy����
			//������д����������
		}
		break;
		//����һ�
	case WM_RBUTTONDOWN:
		{
			xPos = LOWORD(lParam);		//����һ�ʱx����
			yPos = HIWORD(lParam);		//����һ�ʱy����
			//������д����һ�����
		}
		break;
		//������ĸ
	case WM_CHAR:
		{
			chCharCode = (char) wParam;	
			if ('A' == chCharCode)
			{
				//������д����'A'ʱ�Ĵ���

			}
			else if('a' == chCharCode)
			{

			}
		}
		break;
		//���̰����¼�
	case WM_KEYDOWN:
		switch(wParam)
		{
			/*����Enter*/
		case VK_RETURN:		
			//��������д����
			{
				SetTimer(hwnd, 0, snakeList.GetSpeed(), NULL);
			}
			break;
			/* ���ͷ */
		case VK_LEFT:
			//��������д����
			{
				if (snakeList.GetDirect() != DT_Right)
				{
					SetDirect(DT_Left);
				}
			}
			break;
			/* �Ҽ�ͷ */
		case VK_RIGHT:		
			//��������д����
			{
				if (snakeList.GetDirect() != DT_Left)
				{
					SetDirect(DT_Right);
				}
			}
			break;
			/* �ϼ�ͷ */
		case VK_UP:	
			//��������д����
			{
				if (snakeList.GetDirect() != DT_Down)
				{
					SetDirect(DT_Up);
				}
			}
			break;
			/* �¼�ͷ */
		case VK_DOWN:
			//��������д����
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
		//���̵����¼�
	case WM_KEYUP:
		switch(wParam)
		{
			/*����Enter*/
		case VK_RETURN:		
			//��������д����
			{

			}
			break;
			/*���� ���ͷ */
		case VK_LEFT:
			//��������д����
			{
				
				
			}
			break;
			/* �����Ҽ�ͷ */
		case VK_RIGHT:		
			//��������д����
			{
				
			}
			break;
			/* �����ϼ�ͷ */
		case VK_UP:	
			//��������д����
			{
				
			}
			break;
			/* �����¼�ͷ */
		case VK_DOWN:
			//��������д����
			{
				
			}
			break;
		}
		break;
		/*ʱ���¼�*/
	case WM_TIMER:
		//��������д����
		{
			Rectangle(GetDC(hwnd), 0, 0, 500, 500);

			if (snakeList.CanDie())
			{
				KillTimer(hwnd, NULL);
				snakeList.ShowSnake();
				snakeList.ShowBean();
				snakeList.ShowScore();
				//snakeList.ClearSnake();
				if (MessageBox(hwnd, "�Ƿ����¿�ʼ", "game over", MB_YESNO) == IDYES)
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

			// ����Զ��ɹ��ҾͲ��ƶ�����
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
		PostQuitMessage (0);       /* ����Ϣ�����з���һ��WM_OUIT��Ϣ */
		break;
	default:                      /* ����Ĭ�ϴ��ڹ��̶�δ�������Ϣ���б�Ҫ�Ĵ��� */
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
