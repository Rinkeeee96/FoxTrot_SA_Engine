#include "pch.h"
#include "CppUnitTest.h"
#include "../api.h"
#include <Physics\ContactListenerAdapter.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsEngine
{

	class PhysicsFacadeMock : public IPhysicsFacade {
		void addStaticObject(PhysicsBody* object) override {
		}

		void addDynamicObject(PhysicsBody* object) override {
		}

		PhysicsBody* getPhysicsObject(const int objectId) override {
			return nullptr;
		}

		void MoveLeft(const int objectId) override {
		}

		void MoveRight(const int objectId) override {
		}

		void Jump(const int objectId) override {
		}

		CollisionStruct getObjectsByFixture(b2Fixture* fixture1, b2Fixture* fixture2) {
			return CollisionStruct();
		}

		void update() override {
		}

		void cleanMap() {
		}
	};

	TEST_CLASS(UnitTestsPhysicsCollisionAdapter)
	{
	public:
		TEST_METHOD(OnCollision_Bottom_Top_Should_Return_void)
		{
			IPhysicsFacade* mock = new PhysicsFacadeMock();
			ContactListenerAdapter contactListener = ContactListenerAdapter(mock);


			Assert::AreEqual(1, 1);
		}
	};
}