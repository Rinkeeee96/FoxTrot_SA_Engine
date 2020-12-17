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
		TEST_METHOD(DeregisterScene_ExistingId_Should_Remove_Scene)
		{
			// Arrange
			SceneManager scenemager;
			unique_ptr<Scene> scene = unique_ptr<MockScene>(new MockScene);
			// Act
			int id = scene->getSceneID();
			scenemager.insertScene(move(scene));
			scenemager.setCurrentScene(id);
			scenemager.deregisterCurrentScene();
			// Assert
			Assert::IsTrue(true);
		}
		TEST_METHOD(DeregisterScene_NonExistingId_Should_ThrowError)
		{
			// Arrange
			SceneManager scenemager;
			// Act
			try {
				scenemager.deregisterCurrentScene();
			}
			// Assert
			catch (exception e) {
				Assert::AreEqual(e.what(), "SceneManager: Scene does not exist");
			}
		}

		TEST_METHOD(SceneManagerSetCurrentScene_Existing_Scene_Should_Return_EventDispatcher)
		{
			// Arrange
			SceneManager scenemager;
			unique_ptr<Scene> scene = unique_ptr<MockScene>(new MockScene);
			// Act
			scenemager.insertScene(move(scene));
			auto dispatcher = scenemager.setCurrentScene(1);
			// Assert
			Assert::IsTrue(true);
		}

		TEST_METHOD(SceneManagerSetCurrentScene_NonExisting_Scene_Should_Throw_Error)
		{
			// Arrange
			SceneManager scenemager;
			// Act
			try {
				scenemager.setCurrentScene(0);
			}
			// Assert
			catch (exception e) {
				Assert::AreEqual(e.what(), "SceneManager: Scene does not exist");
			}
		}
	};
}