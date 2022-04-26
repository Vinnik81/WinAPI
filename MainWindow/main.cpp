#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include"resource.h"

#define IDC_STATIC 1000		//

CONST CHAR g_szClassName[] = "MyWindowClass"; //Имя класса окна
CONST CHAR g_szWindowTitle[] = "My First Window";

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//1)
	WNDCLASSEX wc; //wc - Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_DOCUM));
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_TXT));
	//wc.hIcon = (HICON)LoadImage(hInstance, "txt_file.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wc.hIconSm = (HICON)LoadImage(hInstance, "document_contract.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(hInstance, (LPCSTR)IDC_CURSOR1);
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = (WNDPROC)WndProc;	//
	wc.lpszClassName = g_szClassName;
	wc.lpszMenuName = NULL;
	wc.style = 0;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed :-(", "Error", MB_OK | MB_ICONERROR);
		return NULL;
	}
	//2)

	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);
	int window_width = screen_width * .75;
	int window_height = screen_height * .75;
	int start_x = screen_width * .125;
	int start_y = screen_height * .125;

	HWND hwnd = CreateWindowEx
	(
		NULL,	//
		g_szClassName,
		g_szWindowTitle,
		WS_OVERLAPPEDWINDOW,	//
		start_x, start_y,	//
		window_width, window_height,	//
		NULL,	//
		NULL,	//
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creator failed!", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);	//
	UpdateWindow(hwnd);	//
	//3)
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
	return 0;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		//
		HWND hStatic = CreateWindowEx
		(
			0,
			"Static",
			"Эта статическая строка будет отображать размер окна, и его положение на экране",
			WS_CHILD | WS_VISIBLE,
			10, 10,
			800,
			50,
			hwnd,
			(HMENU)IDC_STATIC,
			GetModuleHandle(NULL),	//
			0
		);
	}
		break;
	case WM_COMMAND: break;
	case WM_SIZE:
	case WM_MOVE:
	{
		CONST INT SIZE = 256;
		CHAR sz_msg[SIZE] = {};
		RECT rect;	//
		GetWindowRect(hwnd, &rect);
		int window_width = rect.right - rect.left;
		int window_height = rect.bottom - rect.top;
		sprintf(sz_msg, "%s - Size: %ix%i, Position: %ix%i", g_szWindowTitle, window_width, window_height, rect.left, rect.top);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_msg);
		SendMessage(GetDlgItem(hwnd, IDC_STATIC), WM_SETTEXT, 0, (LPARAM)sz_msg);
	}
	break;
	case WM_CLOSE: 
		if(MessageBox(hwnd, "Вы действительно хотите закрыть окно?", "Question", MB_YESNO | MB_ICONQUESTION) == IDYES)
			DestroyWindow(hwnd);
		break;
	case WM_DESTROY:	//
		PostQuitMessage(NULL);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}