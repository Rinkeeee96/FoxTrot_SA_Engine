#include "pch.h"
#include "CppUnitTest.h"
#include <api.h>
#include "../mocks/MockScene.h"
#include "../mocks/MockObject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsEngine
{

	TEST_CLASS(ValidatorTests)
	{
	public:
		TEST_METHOD(Validator_Load_ValidJson)
		{
			// Arrange
			FileLoader fileloader;
			// Act
			auto result = fileloader.validateDocument("TestAssets/valid.json", "TestAssets/jsonValidator.json");
			// Assert
			Assert::IsTrue(result);
		}

		TEST_METHOD(Validator_Load_InvalidJson)
		{
			// Arrange
			FileLoader fileloader;
			// Act
			auto result = fileloader.validateDocument("TestAssets/invalid.json", "TestAssets/jsonValidator.json");
			// Assert
			Assert::IsFalse(result);
		}
	};
}