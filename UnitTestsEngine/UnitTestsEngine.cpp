#include "pch.h"
#include "CppUnitTest.h"
#include "../api.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsEngine
{
	TEST_CLASS(UnitTestsEngine)
	{
	public:
		Object *obj = new Object(1);
		TEST_METHOD(TestMethod1)
		{
			obj->setName("test1");
			Assert::AreEqual(1, 1);
		}
	};
}
