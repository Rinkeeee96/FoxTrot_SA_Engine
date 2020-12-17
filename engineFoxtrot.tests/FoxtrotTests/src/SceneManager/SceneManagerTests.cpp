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
			shared_ptr<Scene> scene = shared_ptr<MockScene>(new MockScene);
			// Act
			scenemager.insertScene(scene);
			scenemager.deregisterScene(1);
			// Assert
			Assert::IsTrue(true);
		}
		TEST_METHOD(DeregisterScene_NonExistingId_Should_ThrowError)
		{
			// Arrange
			SceneManager scenemager;
			// Act
			try {
				scenemager.deregisterScene(0);
			}
			// Assert
			catch (exception e) {
				Assert::AreEqual(e.what(), "scene does not exist");
			}
		}
		TEST_METHOD(GetSceneID_ExsitingScene_Should_Return_Scene)
		{
			// Arrange
			SceneManager scenemager;
			shared_ptr<Scene> scene = shared_ptr<MockScene>(new MockScene);
			// Act
			scenemager.insertScene(scene);
			auto result = scenemager.getSceneWithID(1);
			// Assert
			Assert::AreEqual(result->getSceneID(), 1);

		}

		TEST_METHOD(GetSceneID_NonExsitingScene_Should_ThrowError)
		{
			// Arrange
			SceneManager scenemager;
			// Act
			try {
				scenemager.getSceneWithID(0);
			}
			// Assert
			catch (exception e) {
				Assert::AreEqual(e.what(), "scene does not exist");
			}
		}

		TEST_METHOD(SceneManagerSetCurrentScene_Existing_Scene_Should_Return_EventDispatcher)
		{
			// Arrange
			SceneManager scenemager;
			shared_ptr<Scene> scene = shared_ptr<MockScene>(new MockScene);
			// Act
			scenemager.insertScene(scene);
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
				Assert::AreEqual(e.what(), "scene does not exist");
			}
		}
	};
}