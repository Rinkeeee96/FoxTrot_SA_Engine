#include "pch.h"
#include "CppUnitTest.h"
#include <Game/States/IState.h>
#include <Game/States/StateMachine.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsGlitch
{
	class MockObj{ };

	class mockFirstState : public IState<MockObj> {
	private:
		int entryCalls = 0;
		int executeCalls = 0;
		int exitCalls = 0;
	public:
		~mockFirstState() {}
		int getEntryCalls() const { return this->entryCalls; }
		int getExecuteCalls() const { return this->executeCalls; }
		int getExitCalls() const { return this->exitCalls; }

		void entry(MockObj& entity) override {
			entryCalls++;
		}

		virtual void execute(MockObj& entity) override {
			executeCalls++;
		}

		virtual void exit(MockObj& entity) override {
			exitCalls++;
		}
	};

	class mockSecondState : public IState<MockObj> {
	private:
		int entryCalls = 0;
		int executeCalls = 0;
		int exitCalls = 0;
	public:
		~mockSecondState() {}
		int getEntryCalls() const { return this->entryCalls; }
		int getExecuteCalls() const { return this->executeCalls; }
		int getExitCalls() const { return this->exitCalls; }
		
		void entry(MockObj& entity) override {
			entryCalls++;
		}

		virtual void execute(MockObj& entity) override {
			executeCalls++;
		}

		virtual void exit(MockObj& entity) override {
			exitCalls++;
		}
	};

	class mockGlobalState : public IState<MockObj> {
	private:
		int entryCalls = 0;
		int executeCalls = 0;
		int exitCalls = 0;
	public:
		~mockGlobalState() {}
		int getCalls() const { return this->executeCalls; }

		void entry(MockObj& entity) override {
			entryCalls++;
		}

		virtual void execute(MockObj& entity) override {
			executeCalls++;
		}

		virtual void exit(MockObj& entity) override {
			exitCalls++;
		}
	};

	TEST_CLASS(StatesTests)
	{
	public:
		TEST_METHOD(StateMachine_ChangeState_Should_Call_Entry_Once)
		{
			// Arrange
			MockObj* obj = new MockObj;
			unique_ptr<mockFirstState> firstState = make_unique<mockFirstState>();
			unique_ptr<mockSecondState> secondState = make_unique<mockSecondState>();
			unique_ptr<mockGlobalState> globalState = make_unique<mockGlobalState>();

			mockSecondState* toCheck = secondState.get();

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
			unique_ptr<mockFirstState> firstState = make_unique<mockFirstState>();
			unique_ptr<mockSecondState> secondState = make_unique<mockSecondState>();
			unique_ptr<mockGlobalState> globalState = make_unique<mockGlobalState>();

			mockFirstState* toCheck1 = firstState.get();
			mockGlobalState* toCheck2 = globalState.get();

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
			unique_ptr<mockFirstState> firstState = make_unique<mockFirstState>();
			unique_ptr<mockSecondState> secondState = make_unique<mockSecondState>();
			unique_ptr<mockGlobalState> globalState = make_unique<mockGlobalState>();
			StateMachine<MockObj> statemachine;
			// Act
			statemachine.setCurrentState(std::move(firstState), *obj);
			statemachine.setGlobalState(std::move(globalState), *obj);

			IState<MockObj>& result = statemachine.getGlobalState();
			// Assert
			if (typeid(mockGlobalState) == typeid(result)) {
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
			unique_ptr<mockFirstState> firstState = make_unique<mockFirstState>();
			unique_ptr<mockSecondState> secondState = make_unique<mockSecondState>();
			unique_ptr<mockGlobalState> globalState = make_unique<mockGlobalState>();
			mockFirstState* toCheck = firstState.get();
			StateMachine<MockObj> statemachine;
			statemachine.setGlobalState(std::move(globalState), *obj);
			// Act
			statemachine.setCurrentState(std::move(firstState), *obj);
			// Assert
			Assert::AreEqual(toCheck->getEntryCalls(), 1);
		}
	};
}