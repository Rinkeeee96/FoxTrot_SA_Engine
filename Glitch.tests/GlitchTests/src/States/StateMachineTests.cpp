#include "pch.h"
#include "CppUnitTest.h"
#include <Game/States/IState.h>
#include <Game/States/StateMachine.h>
#include "../mocks/MockObj.h"
#include "../mocks/MockState.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsGlitch
{
	TEST_CLASS(StatesTests)
	{
	public:
		TEST_METHOD(StateMachine_ChangeState_Should_Call_Entry_Once)
		{
			// Arrange
			MockObj* obj = new MockObj;
			unique_ptr<MockState> firstState = make_unique<MockState>();
			unique_ptr<MockState> secondState = make_unique<MockState>();
			unique_ptr<MockState> globalState = make_unique<MockState>();

			MockState* toCheck = secondState.get();

			StateMachine<MockObj> statemachine;
			statemachine.setCurrentState(std::move(firstState), *obj);
			statemachine.setGlobalState(std::move(globalState), *obj);
			// ActB
			statemachine.changeState(std::move(secondState), *obj);
			// Assert
			Assert::AreEqual(1, toCheck->getEntryCalls());
		}

		TEST_METHOD(StateMachine_Update_Should_Call_GlobalState_And_CurrentState_Update_Once)
		{
			// Arrange
			MockObj* obj = new MockObj;
			unique_ptr<MockState> firstState = make_unique<MockState>();
			unique_ptr<MockState> secondState = make_unique<MockState>();
			unique_ptr<MockState> globalState = make_unique<MockState>();

			MockState* toCheck1 = firstState.get();
			MockState* toCheck2 = globalState.get();

			StateMachine<MockObj> statemachine;
			statemachine.setCurrentState(std::move(firstState), *obj);
			statemachine.setGlobalState(std::move(globalState), *obj);
			// Act
			statemachine.update(*obj);
			// Assert
			Assert::AreEqual(toCheck1->getExecuteCalls(), 1);
			Assert::AreEqual(toCheck2->getCalls(), 1);
		}

		TEST_METHOD(StateMachine_SetGlobalState_SetGlobalState)
		{
			// Arrange
			MockObj* obj = new MockObj;
			unique_ptr<MockState> firstState = make_unique<MockState>();
			unique_ptr<MockState> secondState = make_unique<MockState>();
			unique_ptr<MockState> globalState = make_unique<MockState>();
			StateMachine<MockObj> statemachine;
			// Act
			statemachine.setCurrentState(std::move(firstState), *obj);
			statemachine.setGlobalState(std::move(globalState), *obj);

			IState<MockObj>& result = statemachine.getGlobalState();
			// Assert
			if (typeid(MockState) == typeid(result)) {
				Assert::IsTrue(true);
			}
			else {
				Assert::IsTrue(false);
			}
		}

		TEST_METHOD(StateMachine_SetCurrentState_Should_CallEntry_Once)
		{
			// Arrange
			MockObj* obj = new MockObj;
			unique_ptr<MockState> firstState = make_unique<MockState>();
			unique_ptr<MockState> secondState = make_unique<MockState>();
			unique_ptr<MockState> globalState = make_unique<MockState>();
			MockState* toCheck = firstState.get();
			StateMachine<MockObj> statemachine;
			statemachine.setGlobalState(std::move(globalState), *obj);
			// Act
			statemachine.setCurrentState(std::move(firstState), *obj);
			// Assert
			Assert::AreEqual(toCheck->getEntryCalls(), 1);
		}
	};
}