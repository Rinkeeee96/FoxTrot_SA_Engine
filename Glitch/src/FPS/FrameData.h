#pragma once
#include <SDL.h>
#include <iostream>

#define FRAME_VALUES 10
#define ONE_SECOND 1000.f

using namespace std;

class FrameData
{
public:
	FrameData();
	~FrameData();
	int calculateAverageFps();

private:
	int framecount;
	int frametimes[FRAME_VALUES];
	int frametimelast;
	int framespersecond;
};

