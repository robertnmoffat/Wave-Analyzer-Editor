#include<windows.h>
#include<math.h>
#include "winproc.h"
#include "header.h"



LRESULT CALLBACK TemporalWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC         hdc;
	PAINTSTRUCT ps;
	RECT        rect;

	PWINDOWSTRUCT pwdata;

	pwdata = (PWINDOWSTRUCT)GetWindowLongPtr(hwnd, 0);

	double startx = 120;
	double starty = 100;
	double positionx;
	long double positiony;
	double oldx = startx;
	double oldy = starty;
	double scale = 10;
	double samples;

	switch (message)
	{
	case WM_CREATE:
		//PlaySound(TEXT("hellowin.wav"), NULL, SND_FILENAME | SND_ASYNC);
		return 0;

	case WM_PAINT:

		samples = (double)pwdata->sampleAmount;

		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rect);

		DrawText(hdc, TEXT("Temporal"), -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		HPEN hPenOld;
		HPEN hLinePen;
		COLORREF qLineColor;
		qLineColor = RGB(255, 0, 0);
		hLinePen = CreatePen(PS_SOLID, 1, qLineColor);
		hPenOld = (HPEN)SelectObject(hdc, hLinePen);



		for (int i = 0; i < samples*scale; i++) {
			double t = (double)i / scale;
			positionx = startx + (t*scale);
			double insideSine = 2 * PI * 5 * t / samples;
			double sined = sin(2 * PI * 5 * t / samples)+ sin(2 * PI * 2 * t / samples)+ sin(2 * PI * 7 * t / samples);
			double scaledSine = sined*scale;
			positiony = starty + scaledSine;//+ sin(2 * PI * 7 * (i) / 30))*scale;

			if (i % (int)scale == 0) {
				int tmp = pwdata->samplesUsed++;
				pwdata->samples[tmp] = positiony;
			}

			MoveToEx(hdc, (int)oldx, (int)oldy, NULL);
			LineTo(hdc, (int)positionx, (int)positiony);
			oldx = positionx;
			oldy = positiony;
		}


		SelectObject(hdc, hPenOld);
		DeleteObject(hLinePen);

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		ShowWindow(hwnd, 0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

