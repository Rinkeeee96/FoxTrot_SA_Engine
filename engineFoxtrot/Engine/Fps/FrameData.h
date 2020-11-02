#pragma once
#define FRAME_VALUES 100
#define TIMESTEP 1.f

class DLLEXPORT FrameData
{
public:
	// Todo getters and Setters
	double gameFps = 0;
	double renderFps = 0;
	FrameData();
	~FrameData();
	double calculateAverageFps();
	void startTimer();

private:
	list<chrono::duration<double>> frametimes;
	chrono::high_resolution_clock::time_point startTime;
	double framesPerSecond = 0;

};
