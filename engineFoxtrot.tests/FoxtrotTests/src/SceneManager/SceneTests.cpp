#include "pch.h"
#include "CppUnitTest.h"
#include <api.h>
#include "../mocks/MockScene.h"
#include "../mocks/MockObject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsEngine
{
	TEST_CLASS(SceneManagerTests)
	{
	public:
		TEST_METHOD(GetSceneID_ExsitingScene_Should_Return_Scene)
		{
			// Arrange

			// Act

			// Assert

		}

		TEST_METHOD(SceneManagerSetCurrentScene_Existing_Scene_Should_Return_EventDispatcher)
		{
			// Arrange

			// Act

			// Assert

		}

		TEST_METHOD(SceneManagerSetCurrentScene_NonExisting_Scene_Should_Throw_Error)
		{
			// Arrange

			// Act

			// Assert

		}
	};
}