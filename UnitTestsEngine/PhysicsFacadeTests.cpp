#include "pch.h"
#include "CppUnitTest.h"
#include "../api.h"
#include <Physics\ContactListenerAdapter.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsEngine
{

	TEST_CLASS(PhysicsFacadeTests)
	{
	public:
		TEST_METHOD(GetStaticPhysicsBodyByObjectId_Should_Return_NewlyCreatedObject)
		{
			// Arrange
			IPhysicsFacade* physicsFacade = new PhysicsFacade();

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
			PhysicsBody* physicsBody = new PhysicsBody(object);
			physicsFacade->addStaticObject(physicsBody);
			// Act
			auto result = physicsFacade->getPhysicsObject(1);
			// Assert
			Assert::AreEqual(result->getObjectId(), 1);
			Assert::AreEqual(result->getHeight(), 100.0f);
		};

		TEST_METHOD(GetDynamicPhysicsBodyByObjectId_Should_Return_NewlyCreatedObject)
		{
			// Arrange
			IPhysicsFacade* physicsFacade = new PhysicsFacade();

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
			PhysicsBody* physicsBody = new PhysicsBody(object);
			physicsFacade->addDynamicObject(physicsBody);
			// Act
			auto result = physicsFacade->getPhysicsObject(1);
			// Assert
			Assert::AreEqual(result->getObjectId(), 1);
			Assert::AreEqual(result->getHeight(), 100.0f);
		};

		TEST_METHOD(ObjectJump_Existing_Object_Should_Change_YVelocity)
		{
			// Arrange
			IPhysicsFacade* physicsFacade = new PhysicsFacade();

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
			PhysicsBody* physicsBody = new PhysicsBody(object);

			physicsFacade->addDynamicObject(physicsBody);
			// Act
			auto oldY = object->getYAxisVelocity();
			physicsFacade->Jump(1);
			physicsFacade->update();
			// Assert
			Assert::AreNotEqual(oldY, object->getYAxisVelocity());
		}

		TEST_METHOD(ObjectMoveLeft_Existing_Object_Should_Change_YVelocity)
		{
			// Arrange
			IPhysicsFacade* physicsFacade = new PhysicsFacade();

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
			PhysicsBody* physicsBody = new PhysicsBody(object);

			physicsFacade->addDynamicObject(physicsBody);
			// Act
			auto oldX = object->getPositionX();
			physicsFacade->MoveLeft(1);
			physicsFacade->update();
			// Assert
			Assert::AreNotEqual(oldX, object->getPositionX());
		}

		TEST_METHOD(ObjectMoveRight_Existing_Object_Should_Change_YVelocity)
		{
			// Arrange
			IPhysicsFacade* physicsFacade = new PhysicsFacade();

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
			PhysicsBody* physicsBody = new PhysicsBody(object);

			physicsFacade->addDynamicObject(physicsBody);
			// Act
			auto oldX = object->getPositionX();
			physicsFacade->MoveRight(1);
			physicsFacade->update();
			// Assert
			Assert::AreNotEqual(oldX, object->getPositionX());
		}

		TEST_METHOD(ObjectJump_Invalid_Object_Should_Change_YVelocity)
		{
			// Arrange
			IPhysicsFacade* physicsFacade = new PhysicsFacade();
			// Act
			try
			{
				physicsFacade->Jump(1);
			}
			// Assert
			catch (int e)
			{
				Assert::AreEqual(e, PHYSICS_FACADE_BODY_DOESNT_EXIST);
			}
		}

		TEST_METHOD(ObjectMoveRight_Invalid_Object_Should_Change_YVelocity)
		{
			// Arrange
			IPhysicsFacade* physicsFacade = new PhysicsFacade();
			// Act
			try
			{
				physicsFacade->MoveRight(1);
			}
			// Assert
			catch (int e)
			{
				Assert::AreEqual(e, PHYSICS_FACADE_BODY_DOESNT_EXIST);
			}
		}

		TEST_METHOD(ObjectMoveLeft_Invalid_Object_Should_Change_YVelocity)
		{
			// Arrange
			IPhysicsFacade* physicsFacade = new PhysicsFacade();
			// Act
			try
			{
				physicsFacade->MoveLeft(1);
			}
			// Assert
			catch (int e)
			{
				Assert::AreEqual(e, PHYSICS_FACADE_BODY_DOESNT_EXIST);
			}
		}

		TEST_METHOD(ObjectCleanMap_OnExistingObjects_Should_Remove_Existing_Bodies)
		{
			// Arrange
			IPhysicsFacade* physicsFacade = new PhysicsFacade();

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
			PhysicsBody* physicsBody = new PhysicsBody(object);
			physicsFacade->addDynamicObject(physicsBody);
			// Act
			physicsFacade->cleanMap();
			try
			{
				physicsFacade->MoveLeft(1);
			}
			// Assert
			catch (int e)
			{
				Assert::AreEqual(e, PHYSICS_FACADE_BODY_DOESNT_EXIST);
			}
		}

		TEST_METHOD(ObjectCleanMap_OnEmptyArray_Should_Not_Throw_Any_Array)
		{
			// Arrange
			IPhysicsFacade* physicsFacade = new PhysicsFacade();

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
			PhysicsBody* physicsBody = new PhysicsBody(object);
			physicsFacade->addDynamicObject(physicsBody);
			// Act
			physicsFacade->cleanMap();
			try
			{
				physicsFacade->MoveLeft(1);
			}
			// Assert
			catch (int e)
			{
				Assert::AreEqual(e, PHYSICS_FACADE_BODY_DOESNT_EXIST);
			}
		}

		TEST_METHOD(UpdateDynamicBody_Should_Update_Body)
		{
			// Arrange
			IPhysicsFacade* physicsFacade = new PhysicsFacade();

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
			PhysicsBody* physicsBody = new PhysicsBody(object);

			physicsFacade->addDynamicObject(physicsBody);
			// Act
			auto oldY = object->getYAxisVelocity();
			physicsFacade->Jump(1);
			physicsFacade->update();
			// Assert
			Assert::AreNotEqual(oldY, object->getYAxisVelocity());
		}

		TEST_METHOD(UpdateStaticBody_Should_Not_Update_Body)
		{
			// Arrange
			IPhysicsFacade* physicsFacade = new PhysicsFacade();

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
			object->setStatic(true);
			PhysicsBody* physicsBody = new PhysicsBody(object);

			physicsFacade->addStaticObject(physicsBody);
			// Act
			auto oldY = object->getYAxisVelocity();
			physicsFacade->Jump(1);
			physicsFacade->update();
			// Assert
			Assert::AreEqual(oldY, object->getYAxisVelocity());
		}
	};
}