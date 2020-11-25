#include "pch.h"
#include "CppUnitTest.h"
#include "Video/VideoFacade.h"

#ifdef BUILD_DLL
	#define API __declspec(dllexport)
	#define EXPIMP_TEMPLATE
#else
	#define API __declspec(dllimport)
	#define EXPIMP_TEMPLATE extern
#endif // BUILD_DLL

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsEngine
{
	TEST_CLASS(UnitTestsEngine)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(1, 1);
		}
	};
}
