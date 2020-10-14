#include "glpch.h"
#include "FrameData.h"

using namespace std;

FrameData::FrameData() {
	memset(frametimes, 0, sizeof(frametimes));
	framecount = 0;
	framespersecond = 0;
	frametimelast = SDL_GetTicks();
}

FrameData::~FrameData() {
	delete frametimes;
}

/// @brief
/// Calculates the average fps of the last few ticks
int FrameData::calculateAverageFps()
{
	int frametimesindex;
	int getticks;
	int count;
	int i;

	frametimesindex = framecount % FRAME_VALUES;

	getticks = SDL_GetTicks();

	frametimes[frametimesindex] = getticks - frametimelast;

	frametimelast = getticks;

	framecount++;

	if (framecount < FRAME_VALUES) {
		count = framecount;
	}
	else {
		count = FRAME_VALUES;
	}

	framespersecond = 0;
	for (i = 0; i < count; i++) {

		framespersecond += frametimes[i];

	}

	framespersecond /= count;

	framespersecond = ONE_SECOND / framespersecond;
	return framespersecond;
}