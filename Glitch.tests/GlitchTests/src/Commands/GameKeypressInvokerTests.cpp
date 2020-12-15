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

		TEST_METHOD(KeypressInvoker_Delete_Global_Commands_Should_Remove_GlobalCommands)
		{
			// Arrange
			CommandBuilder commandBuilder;
			GameKeypressInvoker* result = commandBuilder.readBindingsAndCreateInvoker();
			// Act
			result->destroyGlobalCommands();
			// Assert
			Assert::AreEqual((int)result->getGlobalCommands().count(KeyCode::KEY_P), 0);
			Assert::AreEqual((int)result->getGlobalCommands().count(KeyCode::KEY_I), 0);

			Assert::AreEqual((int)result->getPlayerCommands().count(KeyCode::KEY_G), 1);
			Assert::AreEqual((int)result->getPlayerCommands().count(KeyCode::KEY_A), 1);
			Assert::AreEqual((int)result->getPlayerCommands().count(KeyCode::KEY_D), 1);
			Assert::AreEqual((int)result->getPlayerCommands().count(KeyCode::KEY_SPACE), 1);
			delete result;
		}
		TEST_METHOD(KeypressInvoker_Delete_Player_Commands_Should_Remove_PlayerCommands)
		{
			// Arrange
			CommandBuilder commandBuilder;
			GameKeypressInvoker* result = commandBuilder.readBindingsAndCreateInvoker();
			// Act
			result->destroyGlobalCommands();
			// Assert
			Assert::AreEqual((int)result->getGlobalCommands().count(KeyCode::KEY_P), 1);
			Assert::AreEqual((int)result->getGlobalCommands().count(KeyCode::KEY_I), 1);

			Assert::AreEqual((int)result->getPlayerCommands().count(KeyCode::KEY_G), 0);
			Assert::AreEqual((int)result->getPlayerCommands().count(KeyCode::KEY_A), 0);
			Assert::AreEqual((int)result->getPlayerCommands().count(KeyCode::KEY_D), 0);
			Assert::AreEqual((int)result->getPlayerCommands().count(KeyCode::KEY_SPACE), 0);
			delete result;
		}

		TEST_METHOD(KeypressInvoker_Update_Command_Should_Set_New_Command)
		{
			// Arrange
			CommandBuilder commandBuilder;
			GameKeypressInvoker* result = commandBuilder.readBindingsAndCreateInvoker();
			MockCommand m;
			// Act
			result->updateCommand(KeyCode::KEY_G, &m);
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
			result->updateCommand(KeyCode::KEY_G, &m);
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
			result->updateCommand(KeyCode::KEY_G, &m);
			result->enqueueCommand(KeyCode::KEY_A);
			result->executeCommandQueue(dispatcher);
			// Assert
			Assert::AreEqual((int)m.getCalls(), 0);
			delete result;
		}
	};
}