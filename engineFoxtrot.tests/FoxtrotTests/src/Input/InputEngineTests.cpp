#include "pch.h"
#include "CppUnitTest.h"
#include <api.h>
#include "../mocks/MockScene.h"
#include "../mocks/MockObject.h"
#include <FoxtrotTests/src/mocks/MockKeyPressedCommand.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsEngine
{

	TEST_CLASS(InputEngineTests)
	{
	public:
		TEST_METHOD(RegisterKeyPressedInvoker_Should_Register_KeyPressedInvoker)
		{
			// Arrange
			KeypressInvoker invoker;
			MockKeyPressedCommand command;
			invoker.registerCommand(KeyCode::KEY_UP, &command);
			Engine e;
			InputEngine engine{ e };
			// Act
			engine.registerKeypressInvoker(&invoker);
			// Assert
			Assert::IsTrue(true);
		}

		TEST_METHOD(RegisterCommand_And_Update_Should_Not_Call_ICommand)
		{
			// Arrange
			KeypressInvoker invoker;
			EventDispatcher dispatcher;
			MockKeyPressedCommand command;
			invoker.registerCommand(KeyCode::KEY_UP, &command);
			Engine e;
			InputEngine engine{ e };
			// Act
			engine.start(dispatcher);
			engine.registerKeypressInvoker(&invoker);
			engine.update();
			// Assert
			Assert::AreEqual((int)command.getCalls(), 0);
		}

		TEST_METHOD(DispatchEvent_KeyDOWN_Should_Not_Execute_Command)
		{
			// Arrange
			KeypressInvoker invoker;
			EventDispatcher dispatcher;
			MockKeyPressedCommand command;
			invoker.registerCommand(KeyCode::KEY_UP, &command);
			Engine e;
			InputEngine engine{ e };
			KeyPressedEvent event{ KeyCode::KEY_DOWN, 1 };
			// Act
			engine.start(dispatcher);
			engine.registerKeypressInvoker(&invoker);
			dispatcher.dispatchEvent<KeyPressedEvent>(event);
			engine.update();
			// Assert
			Assert::AreEqual((int)command.getCalls(), 0);
		}

		TEST_METHOD(DispatchEvent_KeyUP_Should_Execute_Command_One_Time)
		{
			// Arrange
			KeypressInvoker invoker;
			EventDispatcher dispatcher;
			MockKeyPressedCommand command;
			invoker.registerCommand(KeyCode::KEY_UP, &command);
			Engine e;
			InputEngine engine{ e };
			KeyPressedEvent event{ KeyCode::KEY_UP, 1 };
			// Act
			engine.start(dispatcher);
			engine.registerKeypressInvoker(&invoker);
			dispatcher.dispatchEvent<KeyPressedEvent>(event);
			engine.update();
			// Assert
			Assert::AreEqual((int)command.getCalls(), 1);
		}
	};
}