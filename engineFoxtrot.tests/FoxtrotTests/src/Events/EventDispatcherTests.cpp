#include "pch.h"
#include "CppUnitTest.h"
#include <api.h>
#include "../mocks/MockScene.h"
#include "../mocks/MockObject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsEngine
{
	TEST_CLASS(EventDispachterTests)
	{
	public:	
		/*dispatchEvent
		setEventCallback*/
		TEST_METHOD(DispatchEvent_Should_Call_One_Listiners)
		{
			// Arrange
			EventDispatcher dispather;
			KeyPressedEvent event{KeyCode::KEY_0, 1};

			int calls = 0;
			// Act
			dispather.setEventCallback<KeyPressedEvent>([&calls](const Event& e) -> bool {
					calls++;
					return true;
				});
			dispather.dispatchEvent<KeyPressedEvent>((Event&)event);
			// Assert
			Assert::AreEqual(1, calls);
		}

		TEST_METHOD(DispatchEvent_Should_Call_Zero_Listiners)
		{
			// Arrange
			EventDispatcher dispather;
			KeyPressedEvent event{ KeyCode::KEY_0, 1 };

			int calls = 0;
			// Act
			dispather.setEventCallback<KeyPressedEvent>([&calls](const Event& e) -> bool {
				calls++;
				return true;
				});
			dispather.dispatchEvent<KeyReleasedEvent>((Event&)event);
			// Assert
			Assert::AreEqual(0, calls);
		}
	};
}