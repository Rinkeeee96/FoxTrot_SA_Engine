#include "pch.h"
#include "CppUnitTest.h"
#include <Game/Triggers/BaseTrigger.h>
#include <Game/Factories/TriggerFactory.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsGlitch
{
	class MockTrigger : public BaseTrigger {
	public:
		MockTrigger(EventDispatcher& _dispatcher) : BaseTrigger(_dispatcher) { }
		MockTrigger(const int id, EventDispatcher& _dispatcher) : BaseTrigger(id, _dispatcher) { }

		bool onCollisionBegin(const Event& event)  override {
			return false;
		}

		shared_ptr<BaseTrigger> clone(int id) override {

			return make_shared<MockTrigger>(MockTrigger{ id + 1, this->dispatcher });
		}

		void onUpdate(float deltaTime) override {};
	};

	TEST_CLASS(FactoryTests)
	{
	public:
		TEST_METHOD(TriggerFactory_Create_Charactar_Return_Clone)
		{
			// Arrange
			EventDispatcher dispatcher;
			TriggerFactory factory;
			MockTrigger trigger{ dispatcher };
			// Act
			factory.registerTrigger("name", make_shared<MockTrigger>(trigger));
			auto result = factory.create("name", 1);
			// Assert
			Assert::AreEqual(result->getObjectId(), 2);
		}

		TEST_METHOD(TriggerFactory_Create_NonExisting_Identifier_Should_ThrowError)
		{
			// Arrange
			EventDispatcher dispatcher;
			TriggerFactory factory;
			MockTrigger trigger{ dispatcher };
			// Act
			try {
				factory.create("name", 1);
			}
			// Assert
			catch (exception e) {
				Assert::AreEqual(e.what(), "identifier does not exist");
			}
		}

		TEST_METHOD(TriggerFactory_Register_Charactar_Should_Add_Character)
		{
			// Arrange
			EventDispatcher dispatcher;
			TriggerFactory factory;
			MockTrigger trigger{ dispatcher };
			// Act
			factory.registerTrigger("name", make_shared<MockTrigger>(trigger));
			// Assert
			Assert::IsTrue(true);
		}
		TEST_METHOD(TriggerFactory_Register_ExistingCharactar_Should_ThrowError)
		{
			// Arrange
			EventDispatcher dispatcher;
			TriggerFactory factory;
			MockTrigger trigger{ dispatcher };
			MockTrigger trigger2{ dispatcher };
			// Act
			factory.registerTrigger("name", make_shared<MockTrigger>(trigger));
			try {
				factory.registerTrigger("name", make_shared<MockTrigger>(trigger2));
			}
			// Assert
			catch (exception e) {
				Assert::AreEqual(e.what(), "identifier already registered");
			}
		}
	};
}