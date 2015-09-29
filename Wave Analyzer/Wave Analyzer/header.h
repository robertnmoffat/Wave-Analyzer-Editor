#pragma once

#define XPOS 400
#define YPOS 100
#define DEFAULTWIDTH 400
#define DEFAULTHEIGHT 400
#define HEIGHTOFFSET 100

#define AMPS 10

typedef struct windowStruct {
	HWND hFreqWnd;
	HWND hTemWnd;

	double samples[1024];
	int samplesUsed;

	int sampleAmount;

	int amplitude;
	int frequency;
	int phase;
	int sampleRate;
}WINDOWSTRUCT, *PWINDOWSTRUCT;