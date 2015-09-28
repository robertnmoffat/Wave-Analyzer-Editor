#pragma once

#define XPOS 400
#define YPOS 100
#define DEFAULTWIDTH 400
#define DEFAULTHEIGHT 400
#define HEIGHTOFFSET 100

typedef struct windowStruct {
	HWND hFreqWnd;
	HWND hTemWnd;

	int amplitude;
	int frequency;
	int phase;
	int sampleRate;
}WINDOWSTRUCT, *PWINDOWSTRUCT;