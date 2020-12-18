#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsGlitch
{
	TEST_CLASS(SaveGameTests)
	{
	public:
		TEST_METHOD(DeleteGameData_Should_Delete_Saved_Game)
		{
			// Arrange
			Savegame savegame;
			SaveGameData data;
			data.achievements.push_back("achievement");
			// Act
			savegame.setCurrentGameData(1);
			savegame.saveCurrentGameData(data);
			savegame.deleteSaveGameData(1);
			// Assert
			Assert::AreEqual((int)savegame.getCurrentGameData().achievements.size(), 0);
		}

		TEST_METHOD(SaveGameData_Should_Save_Data)
		{
			// Arrange
			Savegame savegame;
			SaveGameData data;
			data.achievements.push_back("achievement");
			// Act
			savegame.saveCurrentGameData(data);
			// Assert
			Assert::AreEqual((int)savegame.getCurrentGameData().achievements.size(), 1);
		}

		TEST_METHOD(SaveGame_Get_Current_GameData_Should_Return_GameData_With_Id_One)
		{
			// Arrange
			Savegame savegame;
			// Act
			auto result = savegame.getCurrentGameData();
			result.achievements.push_back("achievement");
			savegame.setCurrentGameData(2);
			// Assert
			Assert::AreEqual((int)savegame.getCurrentGameData().achievements.size(), 0);
		}
	};
}