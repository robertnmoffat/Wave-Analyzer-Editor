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
	static TCHAR szAppName2[] = TEXT("HelloWin2");
	static TCHAR szAppName3[] = TEXT("HelloWin3");
	HWND         hwnd;
	HWND	     hwnd2;
	HWND	     hbutton;
	MSG          msg;
	WNDCLASS     wndclass;
	WNDCLASS     wndclass2;

	PWINDOWSTRUCT pwdata;

	pwdata = (PWINDOWSTRUCT)malloc(sizeof(WINDOWSTRUCT));
	pwdata->amplitude = 0;
	pwdata->frequency = 5;
	pwdata->sampleRate = 10;
	pwdata->phase = 0;
	pwdata->samplesUsed = 0;
	pwdata->sampleAmount = 20;

	for (int i = 0; i < 1024; i++) {
		pwdata->samples[i] = 0.0;
	}


	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = sizeof(WINDOWSTRUCT);
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	wndclass2.style = CS_HREDRAW | CS_VREDRAW;
	wndclass2.lpfnWndProc = TemporalWndProc;
	wndclass2.cbClsExtra = 0;
	wndclass2.cbWndExtra = sizeof(WINDOWSTRUCT);
	wndclass2.hInstance = hInstance;
	wndclass2.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass2.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass2.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass2.lpszMenuName = NULL;
	wndclass2.lpszClassName = szAppName2;


	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}


	hwnd = CreateWindow(szAppName,                  // window class name
		TEXT("Wave Analyzer"), // window caption
		WS_OVERLAPPEDWINDOW,        // window style
		XPOS,              // initial x position
		YPOS,              // initial y position
		DEFAULTHEIGHT,              // initial x size
		DEFAULTWIDTH,              // initial y size
		NULL,                       // parent window handle
		NULL,                       // window menu handle
		hInstance,                  // program instance handle
		NULL);                     // creation parameters

	SetWindowLongPtr(hwnd, 0, (LONG)pwdata);

	hbutton = CreateWindow("BUTTON", TEXT("Generate"), WS_CHILD|WS_VISIBLE, 70, 70, 80, 25, hwnd, NULL, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), 0);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	wndclass.lpfnWndProc = TemporalWndProc;
	wndclass.lpszClassName = szAppName2;

	if (!RegisterClass(&wndclass))
	{

		
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName2, MB_ICONERROR);
		return 0;
	}


	hwnd2 = CreateWindow(szAppName2,                  // window class name
		TEXT("Temporal"), // window caption
		WS_OVERLAPPEDWINDOW,        // window style
		XPOS-(DEFAULTWIDTH/2),              // initial x position
		YPOS+HEIGHTOFFSET,              // initial y position
		DEFAULTWIDTH,              // initial x size
		DEFAULTHEIGHT,              // initial y size
		NULL,                       // parent window handle
		NULL,                       // window menu handle
		hInstance,                  // program instance handle
		NULL);                     // creation parameters

	SetWindowLongPtr(hwnd2, 0, (LONG)pwdata);

	ShowWindow(hwnd2, 0);
	UpdateWindow(hwnd2);

	pwdata->hTemWnd = hwnd2;	//setting temporal distplay window in the window data struct


	wndclass.lpfnWndProc = FreqWndProc;
	wndclass.lpszClassName = szAppName3;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName3, MB_ICONERROR);
		return 0;
	}

	hwnd2 = CreateWindow(szAppName3,                  // window class name
		TEXT("Frequency"), // window caption
		WS_OVERLAPPEDWINDOW,        // window style
		XPOS+(DEFAULTWIDTH/2),              // initial x position
		YPOS+HEIGHTOFFSET,              // initial y position
		DEFAULTWIDTH,              // initial x size
		DEFAULTHEIGHT,              // initial y size
		NULL,                       // parent window handle
		NULL,                       // window menu handle
		hInstance,                  // program instance handle
		NULL);                     // creation parameters

	SetWindowLongPtr(hwnd2, 0, (LONG)pwdata);

	ShowWindow(hwnd2, 0);
	UpdateWindow(hwnd2);

	pwdata->hFreqWnd = hwnd2;

	SetWindowLongPtr(hwnd, 0, (LONG)pwdata);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}