#include "pch.h"
#include "CppUnitTest.h"
#include "../api.h"
#include <Physics\ContactListenerAdapter.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsEngine
{
	class TestScene : public Scene {
	public:
		TestScene() : Scene(1) { }
		void OnAttach() override { }
		void Start() override { }
		void OnDetach() override { }
	};

	TEST_CLASS(PhysicsEngineTest)
	{
	public:
		TEST_METHOD(RegisterCurrentScene_Should_Set_Bodies)
		{
			// Arrange
			PhysicsEngine engine = PhysicsEngine();

			Scene* testScene = new TestScene();
			Scene** pptr;

			Object* object = new Object(1);
			object->setName("person1");
			object->setHeight(100);
			object->setWidth(100);
			object->setPositionX(30);
			object->setPositionY(300);
			object->setSpeed(100);
			object->setJumpHeight(400);
			object->setDensity(1000000);
			object->setFriction(0);
			object->setRestitution(0);
			object->setStatic(false);
			testScene->addNewObjectToLayer(1, object);
			pptr = &testScene;

			// Act
			engine.pointerToCurrentScene = pptr;
			engine.registerObjectInCurrentVectorWithPhysicsEngine();
			// Assert
			Assert::IsTrue(true);
		}

		TEST_METHOD(HandleActionEvent_With_Update_Direction_Up_Should_Call_Jump)
		{
			// Arrange
			PhysicsEngine engine = PhysicsEngine();
			Scene* testScene = new TestScene();
			Scene** pptr;
			Object* object = new Object(1);
			object->setName("person1");
			object->setHeight(100);
			object->setWidth(100);
			object->setPositionX(30);
			object->setPositionY(300);
			object->setSpeed(100);
			object->setJumpHeight(400);
			object->setDensity(1000000);
			object->setFriction(0);
			object->setRestitution(0);
			object->setStatic(false);
			testScene->addNewObjectToLayer(1, object);
			pptr = &testScene;
			engine.pointerToCurrentScene = pptr;
			engine.registerObjectInCurrentVectorWithPhysicsEngine();
			// Act
			auto oldY = object->getPositionY();
			ActionEvent x = ActionEvent(Direction::UP, object->getObjectId());
			engine.handleAction((Event&)x);
			// Assert
			Assert::AreEqual(oldY, object->getPositionY());
		}

		TEST_METHOD(HandleActionEvent_Without_Update_Direction_Up_Should_Call_Jump)
		{
			// Arrange
			PhysicsEngine engine = PhysicsEngine();
			Scene* testScene = new TestScene();
			Scene** pptr;
			Object* object = new Object(1);
			object->setName("person1");
			object->setHeight(100);
			object->setWidth(100);
			object->setPositionX(30);
			object->setPositionY(300);
			object->setSpeed(100);
			object->setJumpHeight(400);
			object->setDensity(1000000);
			object->setFriction(0);
			object->setRestitution(0);
			object->setStatic(false);
			testScene->addNewObjectToLayer(1, object);
			pptr = &testScene;
			engine.pointerToCurrentScene = pptr;
			engine.registerObjectInCurrentVectorWithPhysicsEngine();
			// Act
			auto oldX = object->getPositionX();
			ActionEvent x = ActionEvent(Direction::LEFT, object->getObjectId());
			engine.handleAction((Event&)x);
			// Assert
			Assert::AreEqual(oldX, object->getPositionX());
		}
		TEST_METHOD(HandleActionEvent_With_Update_Direction_Up_Should_Call_Right)
		{
			// Arrange
			PhysicsEngine engine = PhysicsEngine();
			Scene* testScene = new TestScene();
			Scene** pptr;
			Object* object = new Object(1);
			object->setName("person1");
			object->setHeight(100);
			object->setWidth(100);
			object->setPositionX(30);
			object->setPositionY(300);
			object->setSpeed(100);
			object->setJumpHeight(400);
			object->setDensity(1000000);
			object->setFriction(0);
			object->setRestitution(0);
			object->setStatic(false);
			testScene->addNewObjectToLayer(1, object);
			pptr = &testScene;
			engine.pointerToCurrentScene = pptr;
			engine.registerObjectInCurrentVectorWithPhysicsEngine();
			// Act
			auto oldX = object->getPositionX();
			ActionEvent x = ActionEvent(Direction::RIGHT, object->getObjectId());
			engine.handleAction((Event&)x);
			engine.physicsFacade->update();
			// Assert
			Assert::AreNotEqual(oldX, object->getPositionX());
		}

		TEST_METHOD(HandleActionEvent_Without_Update_Direction_Up_Should_Call_Right)
		{
			// Arrange
			PhysicsEngine engine = PhysicsEngine();
			Scene* testScene = new TestScene();
			Scene** pptr;
			Object* object = new Object(1);
			object->setName("person1");
			object->setHeight(100);
			object->setWidth(100);
			object->setPositionX(30);
			object->setPositionY(300);
			object->setSpeed(100);
			object->setJumpHeight(400);
			object->setDensity(1000000);
			object->setFriction(0);
			object->setRestitution(0);
			object->setStatic(false);
			testScene->addNewObjectToLayer(1, object);
			pptr = &testScene;
			engine.pointerToCurrentScene = pptr;
			engine.registerObjectInCurrentVectorWithPhysicsEngine();
			// Act
			auto oldX = object->getPositionX();
			ActionEvent x = ActionEvent(Direction::RIGHT, object->getObjectId());
			engine.handleAction((Event&)x);
			// Assert
			Assert::AreEqual(oldX, object->getPositionX());
		}

		TEST_METHOD(HandleActionEvent_Without_Update_Direction_Up_Should_Call_Left)
		{
			// Arrange
			PhysicsEngine engine = PhysicsEngine();
			Scene* testScene = new TestScene();
			Scene** pptr;
			Object* object = new Object(1);
			object->setName("person1");
			object->setHeight(100);
			object->setWidth(100);
			object->setPositionX(30);
			object->setPositionY(300);
			object->setSpeed(100);
			object->setJumpHeight(400);
			object->setDensity(1000000);
			object->setFriction(0);
			object->setRestitution(0);
			object->setStatic(false);
			testScene->addNewObjectToLayer(1, object);
			pptr = &testScene;
			engine.pointerToCurrentScene = pptr;
			engine.registerObjectInCurrentVectorWithPhysicsEngine();
			// Act
			auto oldX = object->getPositionX();
			ActionEvent x = ActionEvent(Direction::LEFT, object->getObjectId());
			engine.handleAction((Event&)x);
			// Assert
			Assert::AreEqual(oldX, object->getPositionX());
		}

		TEST_METHOD(HandleActionEvent_With_Update_Direction_Up_Should_Call_Left)
		{
			// Arrange
			PhysicsEngine engine = PhysicsEngine();
			Scene* testScene = new TestScene();
			Scene** pptr;
			Object* object = new Object(1);
			object->setName("person1");
			object->setHeight(100);
			object->setWidth(100);
			object->setPositionX(30);
			object->setPositionY(300);
			object->setSpeed(100);
			object->setJumpHeight(400);
			object->setDensity(1000000);
			object->setFriction(0);
			object->setRestitution(0);
			object->setStatic(false);
			testScene->addNewObjectToLayer(1, object);
			pptr = &testScene;
			engine.pointerToCurrentScene = pptr;
			engine.registerObjectInCurrentVectorWithPhysicsEngine();
			// Act
			auto oldX = object->getPositionX();
			ActionEvent x = ActionEvent(Direction::LEFT, object->getObjectId());
			engine.handleAction((Event&)x);
			engine.physicsFacade->update();
			// Assert
			Assert::AreNotEqual(oldX, object->getPositionX());
		}
	};
}
