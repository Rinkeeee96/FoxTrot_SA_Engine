#pragma once
#define FRAME_VALUES 100
#define TIMESTEP 1.f

class FrameData
{
public:
	API FrameData();
	API ~FrameData();
	API double calculateAverageFps();
	API void updateFps();
	API void startTimer();
	API const double getFps() { return fps; };
	API const double getLastFrameFps() { return lastFrameFps; };

private:

	double fps = 0;

	list<chrono::duration<double>> frametimes;
	chrono::high_resolution_clock::time_point startTime;
	double framesPerSecond = 0;
	double lastFrameFps = 0;
	bool reset = true;
};
