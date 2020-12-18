#pragma once
#include <Game/States/IState.h>
#include "./MockObj.h"

class MockState : public IState<MockObj> {
private:
	int entryCalls = 0;
	int executeCalls = 0;
	int exitCalls = 0;
public:
	~MockState() {}
	int getCalls() const { return this->executeCalls; }

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