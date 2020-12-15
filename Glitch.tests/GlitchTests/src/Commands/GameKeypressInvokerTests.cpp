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
		TEST_METHOD(KeypressInvoker_Init_Should_InitializeCorrectly)
		{
			// Arrange
			CommandBuilder commandBuilder;
			// Act
			GameKeypressInvoker* result = commandBuilder.readBindingsAndCreateInvoker();
			// Assert
			Assert::AreEqual((int)result->getGlobalCommands().count(KeyCode::KEY_P), 1);
			Assert::AreEqual((int)result->getGlobalCommands().count(KeyCode::KEY_I), 1);

			Assert::AreEqual((int)result->getPlayerCommands().count(KeyCode::KEY_G), 1);
			Assert::AreEqual((int)result->getPlayerCommands().count(KeyCode::KEY_A), 1);
			Assert::AreEqual((int)result->getPlayerCommands().count(KeyCode::KEY_D), 1);
			Assert::AreEqual((int)result->getPlayerCommands().count(KeyCode::KEY_SPACE), 1);
			delete result;
		}

		TEST_METHOD(KeypressInvoker_Update_Command__Existing_Should_ThrowError)
		{
			// Arrange
			CommandBuilder commandBuilder;
			GameKeypressInvoker* result = commandBuilder.readBindingsAndCreateInvoker();
			MockCommand m;
			// Act
			try {
				result->updateCommand(KeyCode::KEY_G, &m);
			}
			catch (exception e) {
				Assert::AreEqual(e.what(), "trying to update an unregistered command");
			}
			// Assert
			delete result;
		}

		TEST_METHOD(KeypressInvoker_Update_Command_ShouldUpdateCommand)
		{
			// Arrange
			CommandBuilder commandBuilder;
			GameKeypressInvoker* result = commandBuilder.readBindingsAndCreateInvoker();
			// Act
			// TODO
			//result->updateCommand(KeyCode::KEY_O, result->getGlobalCommands()[KeyCode::KEY_G]);
			// Assert
			Assert::IsTrue(false);
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