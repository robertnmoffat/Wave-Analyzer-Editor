#include<windows.h>
#include<math.h>
#include "winproc.h"
#include "header.h"
#include <stdio.h>


LRESULT CALLBACK FreqWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
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
	const int samples = 20;

	double amplitudes[AMPS]{0,0,0,0,0,0,0,0,0,0};

	double cosAmps[samples];
	double sinAmps[samples];
	double cosProducts[samples];
	double sinProducts[samples];
	double cosSumOfProducts=0.0;
	double sinSumOfProducts = 0.0;

	for (int i = 0; i < samples; i++) {
		cosAmps[i] =0.0;
		sinAmps[i] = 0.0;
		cosProducts[i] = 0.0;
		sinProducts[i] = 0.0;
	}


	switch (message)
	{
	case WM_CREATE:
		//PlaySound(TEXT("hellowin.wav"), NULL, SND_FILENAME | SND_ASYNC);
		return 0;

	case WM_PAINT:
		double squaredCos;
		double squaredSin;

		pwdata = (PWINDOWSTRUCT)GetWindowLongPtr(hwnd, 0);
		
		

		for (int f = 1; f <= AMPS; f++) {
			cosSumOfProducts = 0.0;
			sinSumOfProducts = 0.0;
			for (int i = 0; i < samples; i++) {
				cosAmps[i] = cos(2 * PI*f*((double)i)/samples);
				sinAmps[i] = sin(2 * PI*f*((double)i) / samples);

				cosProducts[i] = cosAmps[i] * pwdata->samples[i];
				sinProducts[i] = sinAmps[i] * pwdata->samples[i];

				cosSumOfProducts += cosProducts[i];
				sinSumOfProducts += sinProducts[i];
			}
			printf("%d", sinAmps[2]);
			printf("%d", pwdata->samples[2]);
			squaredCos = cosSumOfProducts*cosSumOfProducts;
			squaredSin = sinSumOfProducts*sinSumOfProducts;

			amplitudes[f-1] = sqrt(squaredCos+squaredSin)/10;
		}



		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rect);

		DrawText(hdc, TEXT("Frequency"), -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		HPEN hPenOld;
		HPEN hLinePen;
		COLORREF qLineColor;
		qLineColor = RGB(255, 0, 0);
		hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
		hPenOld = (HPEN)SelectObject(hdc, hLinePen);

		for (int i = 0; i < 10; i++) {
			MoveToEx(hdc, (int)(105+(i*16)), (int)140, NULL);
			LineTo(hdc, (int)(105 + (i * 16)), (int)(140 - amplitudes[i]));
		}

		SelectObject(hdc, hPenOld);
		DeleteObject(hLinePen);

		rect.left = 100;
		rect.top = 150;

		DrawText(hdc, TEXT("1  2  3  4  5  6  7  8  9  10"), -1, &rect,
			DT_SINGLELINE);


		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		ShowWindow(hwnd, 0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
