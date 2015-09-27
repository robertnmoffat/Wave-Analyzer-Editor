#include<windows.h>
#include<math.h>
#include "winproc.h"
#include "header.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC         hdc;
	PAINTSTRUCT ps;
	RECT        rect;

	PWINDOWSTRUCT pwdata;

	double startx = 100;
	double starty = 100;
	double positionx;
	double positiony;
	double oldx = 100;
	double oldy = 100;
	int scale = 10;
	int samples = 10;

	switch (message)
	{
	case WM_CREATE:
		//PlaySound(TEXT("hellowin.wav"), NULL, SND_FILENAME | SND_ASYNC);
		return 0;

	case WM_COMMAND:
		switch (HIWORD(wParam))
		{
			case BN_CLICKED:
				pwdata = (PWINDOWSTRUCT)GetWindowLongPtr(hwnd, 0);
				ShowWindow(pwdata->hFreqWnd, SW_SHOW);
				ShowWindow(pwdata->hTemWnd, SW_SHOW);
				break;
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rect);

		DrawText(hdc, TEXT("Hello, Windows 98!"), -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		
		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}


