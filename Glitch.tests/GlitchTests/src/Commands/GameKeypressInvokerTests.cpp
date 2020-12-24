#include "pch.h"
#include "CppUnitTest.h"
#include <Game/Commands/Builder/CommandBuilder.h>
#include <Game/Commands/GameKeypressInvoker.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsGlitch
{
	class MockCommand : public ICommand {
	private:
		std::size_t calls = 0;
	public:
		MockCommand() : ICommand("identifier") {}

		virtual void execute(EventDispatcher& dispatcher) { calls++; }
		std::size_t getCalls() const { return calls; }
	};
	TEST_CLASS(CommandTests)
	{
	public:
		TEST_METHOD(KeypressInvoker_Update_Command__Existing_Should_ThrowError)
		{
			// Arrange
			CommandBuilder commandBuilder;
			GameKeypressInvoker* result = commandBuilder.readBindingsAndCreateInvoker();
			MockCommand m;
			// Act
			try {
				result->updateCommand(KeyCode::KEY_G, m.getIdentifier());
			}
			catch (exception e) {
				Assert::AreEqual("KeypressInvoker: trying to update an unregistered command", e.what());
			}
			// Assert
			delete result;
		}

		TEST_METHOD(KeypressInvoker_Execute_Once_Should_Call_Command_Once)
		{
			// Arrange
			EventDispatcher dispatcher;
			CommandBuilder commandBuilder;
			GameKeypressInvoker* result = commandBuilder.readBindingsAndCreateInvoker();
			MockCommand m;
			// Act
			result->registerCommand(KeyCode::KEY_G, &m);
			result->enqueueCommand(KeyCode::KEY_G);
			result->executeCommandQueue(dispatcher);
			// Assert
			Assert::AreEqual((int)m.getCalls(), 1);
			delete result;
		}

		TEST_METHOD(KeypressInvoker_Execute_KeyA_ShouldNot_Call_Command)
		{
			// Arrange
			EventDispatcher dispatcher;
			CommandBuilder commandBuilder;
			GameKeypressInvoker* result = commandBuilder.readBindingsAndCreateInvoker();
			MockCommand m;
			// Act
			result->registerCommand(KeyCode::KEY_G, &m);
			result->enqueueCommand(KeyCode::KEY_A);
			result->executeCommandQueue(dispatcher);
			// Assert
			Assert::AreEqual((int)m.getCalls(), 0);
			delete result;
		}
	};
}