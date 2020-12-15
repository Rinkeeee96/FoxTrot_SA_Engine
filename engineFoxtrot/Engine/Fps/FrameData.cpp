#include "stdafx.h"
#include "FrameData.h"


FrameData::FrameData() {
}

FrameData::~FrameData() {
}

/// @brief
/// Sets the start time for the fps counter (use at beginning of loop)
void FrameData::startTimer() {
	startTime = chrono::high_resolution_clock::now();
}

/// @brief
/// returns the current deltaTime (1 / fps of the last frame)
/// @param timeStep
/// The timestep to use when calculating deltaTime
/// @returns const float
const float FrameData::calculateDeltaTime(int timeStep)
{
	return static_cast<const float>(timeStep / lastFrameFps);
}

/// @brief
/// Calculates the average fps of the last few ticks
double FrameData::calculateAverageFps()
{
	chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
	chrono::duration<double> diff = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
	double avgFps = 0;

	if (frametimes.size() >= FRAME_VALUES) {
		frametimes.pop_front();
	}
	frametimes.push_back(diff);

	for (auto const &time : frametimes) {
		avgFps += time.count();
	}

	avgFps /= frametimes.size();

	lastFrameFps = TIMESTEP / diff.count();
	framesPerSecond = TIMESTEP / avgFps;
	return framesPerSecond;
}

/// @brief
/// Determines when to update the fps
void FrameData::updateFps()
{
	if (reset)
		this->startTimer();
	else
		this->fps = this->calculateAverageFps();
	reset = !reset;
}
