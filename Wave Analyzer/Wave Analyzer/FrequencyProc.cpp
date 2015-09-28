#include<windows.h>
#include<math.h>
#include "winproc.h"

LRESULT CALLBACK FreqWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC         hdc;
	PAINTSTRUCT ps;
	RECT        rect;

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

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rect);

		DrawText(hdc, TEXT("Frequency"), -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);



		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		ShowWindow(hwnd, 0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

