#include "pch.h"
#include "CppUnitTest.h"
#include <api.h>
#include "../mocks/MockScene.h"
#include "../mocks/MockObject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsEngine
{

	TEST_CLASS(FileLoaderTests)
	{
	public:
		TEST_METHOD(FileLoader_Load_ExistingFile_Should_Return_Filestream)
		{
			// Arrange
			FileLoader fileloader;
			// Act
			auto result = fileloader.readFile("TestAssets/tests.txt");
			// Assert
			Assert::IsTrue(result.is_open());
			result.close();
		}

		TEST_METHOD(FileLoader_Load_NonExistingFile_Should_Throw_Error)
		{
			// Arrange
			FileLoader fileloader;
			// Act
			ifstream result;
			try {
				result = fileloader.readFile("TestAssets/NotValid.txt");
			}
			// Assert
			catch (exception e) {
				Assert::IsFalse(result.is_open());
				Assert::AreEqual(e.what(), "FileLoader: file not found exception");
			}
		}
	};
}