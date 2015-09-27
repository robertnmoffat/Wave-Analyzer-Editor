/*------------------------------------------------------------
HELLOWIN.C -- Displays "Hello, Windows 98!" in client area
(c) Charles Petzold, 1998
------------------------------------------------------------*/

#include <windows.h>
#include "winproc.h"
#include "header.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("HelloWin");
	HWND         hwnd;
	HWND	     hwnd2;
	MSG          msg;
	WNDCLASS     wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName,                  // window class name
		TEXT("The Hello Program"), // window caption
		WS_OVERLAPPEDWINDOW,        // window style
		XPOS,              // initial x position
		YPOS,              // initial y position
		DEFAULTHEIGHT*2,              // initial x size
		DEFAULTWIDTH*2,              // initial y size
		NULL,                       // parent window handle
		NULL,                       // window menu handle
		hInstance,                  // program instance handle
		NULL);                     // creation parameters

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	hwnd2 = CreateWindow(szAppName,                  // window class name
		TEXT("Temporal"), // window caption
		WS_OVERLAPPEDWINDOW,        // window style
		XPOS,              // initial x position
		YPOS,              // initial y position
		DEFAULTWIDTH,              // initial x size
		DEFAULTHEIGHT,              // initial y size
		hwnd,                       // parent window handle
		NULL,                       // window menu handle
		hInstance,                  // program instance handle
		NULL);                     // creation parameters

	ShowWindow(hwnd2, iCmdShow);
	UpdateWindow(hwnd);

	hwnd2 = CreateWindow(szAppName,                  // window class name
		TEXT("Frequency"), // window caption
		WS_OVERLAPPEDWINDOW,        // window style
		XPOS+DEFAULTWIDTH,              // initial x position
		YPOS,              // initial y position
		DEFAULTWIDTH,              // initial x size
		DEFAULTHEIGHT,              // initial y size
		hwnd,                       // parent window handle
		NULL,                       // window menu handle
		hInstance,                  // program instance handle
		NULL);                     // creation parameters

	ShowWindow(hwnd2, iCmdShow);
	UpdateWindow(hwnd);



	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

