#include "pch.h"
#include "CppUnitTest.h"
#include "../api.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsEngine
{
	TEST_CLASS(UnitTestsFPS)
	{
	public:
		TEST_METHOD(TestAvgFpsFunction)
		{
			vector<double> avgFpsList;
			FrameData fps;

			for (int i = 0; i < 5; i++) {
				fps.startTimer();
				this_thread::sleep_for(chrono::milliseconds(1));
				avgFpsList.push_back(fps.calculateAverageFps());
			}

			list<chrono::duration<double>> frameTimes = fps.getFrameTimes();

			double calculatedFps = 0;
			for (auto const& time : frameTimes) {
				calculatedFps += time.count();
			}

			calculatedFps /= frameTimes.size();

			double framesPerSecond = TIMESTEP / calculatedFps;

			Assert::AreEqual(framesPerSecond, avgFpsList.back());
		}
	};
}
