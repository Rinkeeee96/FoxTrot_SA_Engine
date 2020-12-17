#include "pch.h"
#include "CppUnitTest.h"
#include "Engine/Physics/PhysicsFacade.h"
#include "../mocks/MockScene.h"
#include "../mocks/MockObject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsEngine
{
	TEST_CLASS(PhysicsFacadeTest)
	{
	public:
		TEST_METHOD(JumpTests_NonExistingObject_Should_Not_Move_Object)
		{
			// Arrange
			unique_ptr<FrameData> frameData = make_unique<FrameData>();
			EventDispatcher dispatcher = EventDispatcher();
			PhysicsFacade facade = PhysicsFacade(dispatcher, frameData);

			Object* object = new MockObject();
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
			PhysicsBody b{ object };

			facade.addDynamicObject(&b);
			// Act
			auto oldY = object->getPositionY();
			facade.Jump(0);
			// Assert
			Assert::AreEqual(oldY, object->getPositionY());
		}

		TEST_METHOD(JumpTests_ExistingObject_Should_Move_Object)
		{
			// Arrange
			unique_ptr<FrameData> frameData = make_unique<FrameData>();
			EventDispatcher dispatcher = EventDispatcher();
			PhysicsFacade facade = PhysicsFacade(dispatcher, frameData);

			Object* object = new MockObject();
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
			PhysicsBody b{ object };

			facade.addDynamicObject(&b);
			// Act
			auto oldY = object->getPositionY();
			facade.Jump(1);
			facade.update();
			// Assert
			Assert::AreNotEqual(oldY, object->getPositionY());
		}

		TEST_METHOD(MoveRightTests_NonExistingObject_Should_Not_Move_Object)
		{
			// Arrange
			unique_ptr<FrameData> frameData = make_unique<FrameData>();
			EventDispatcher dispatcher = EventDispatcher();
			PhysicsFacade facade = PhysicsFacade(dispatcher, frameData);

			Object* object = new MockObject();
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
			PhysicsBody b{ object };

			facade.addDynamicObject(&b);
			// Act
			frameData->startTimer();
			frameData->calculateAverageFps();
			auto oldX = object->getPositionX();
			facade.MoveRight(0);
			facade.update();
			// Assert
			Assert::AreEqual(oldX, object->getPositionX());
		}

		TEST_METHOD(MoveRightTests_ExistingObject_Should_Move_Object)
		{
			// Arrange
			unique_ptr<FrameData> frameData = make_unique<FrameData>();
			EventDispatcher dispatcher = EventDispatcher();
			PhysicsFacade facade = PhysicsFacade(dispatcher, frameData);

			Object* object = new MockObject();
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
			PhysicsBody b{ object };

			facade.addDynamicObject(&b);
			// Act
			auto oldX = object->getPositionX();
			facade.MoveRight(1);
			facade.update();
			// Assert
			Assert::AreNotEqual(oldX, object->getPositionX());
		}

		TEST_METHOD(MoveLeftTests_NonExistingObject_Should_Not_Move_Object)
		{
			// Arrange
			unique_ptr<FrameData> frameData = make_unique<FrameData>();
			EventDispatcher dispatcher = EventDispatcher();
			PhysicsFacade facade = PhysicsFacade(dispatcher, frameData);

			Object* object = new MockObject();
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
			PhysicsBody b{ object };

			facade.addDynamicObject(&b);
			// Act
			frameData->startTimer();
			frameData->calculateAverageFps();
			auto oldX = object->getPositionX();
			facade.MoveLeft(0);
			facade.update();
			// Assert
			Assert::AreEqual(oldX, object->getPositionX());
		}

		TEST_METHOD(MoveLeftTests_ExistingObject_Should_Move_Object)
		{
			// Arrange
			unique_ptr<FrameData> frameData = make_unique<FrameData>();
			EventDispatcher dispatcher = EventDispatcher();
			PhysicsFacade facade = PhysicsFacade(dispatcher, frameData);

			Object* object = new MockObject();
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
			PhysicsBody b{ object };

			facade.addDynamicObject(&b);
			// Act
			auto oldX = object->getPositionX();
			facade.MoveLeft(1);
			facade.update();
			// Assert
			Assert::AreNotEqual(oldX, object->getPositionX());
		}
	};
}
