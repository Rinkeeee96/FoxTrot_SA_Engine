#pragma once
#include <nlohmann\json.hpp>
#include "Game/General/GeneralGameDefines.h"

/// @brief Struct for item data containing itemName and count

struct Item
{
	string itemName;
	int itemCount = 0;
};

/// @brief Struct for inventory containing a vector of Items
struct Inventory
{
	int coins = 0;

	vector<Item> items;
};

/// @brief Struct for level data containing score and completed bool
struct LevelData
{
	int score = 0;
	bool completed = false;
};

/// @brief Struct for character data containing an Inventory
struct CharacterData
{
	Inventory inventory;

	int totalHealth = 3;
};

#define Achievement string

/// @brief Struct for a saveGameData containing al info of a saveGame
struct SaveGameData
{
	int saveGameTimeStamp = 0;
	string saveGameName = "";
	int totalScore = 0;

	LevelData levelData[MAX_AMOUNT_OF_LEVELS];
	vector<Achievement> achievements;
	CharacterData characterData;

	/// @brief 
	/// Checks if the achievement is already in the vector
	/// @param achievement 
	/// @return 
	bool isAchievementAchieved(Achievement achievement)
	{
		if (std::count(achievements.begin(), achievements.end(), achievement))
			return true;
		else 
			return false;
	}

	/// @brief Returns the overworld progress calculated from the leveldata
	/// @return 
	int getOverWorldProgress()
	{
		double progress = 0;
		for (auto data : levelData)
		{
			if (data.completed) progress++;
		}
		return (int)((progress / ((int64_t)MAX_AMOUNT_OF_LEVELS - 1)) * 100);
	}

	/// @brief Returns the timestamp in readable format.
	/// @return 
	string getReadableTimeStamp()
	{
		time_t rawtime = saveGameTimeStamp;
		struct tm* dt = new tm();
		localtime_s(dt, &rawtime);

		stringstream transTime;
		transTime << put_time(dt, "%Y-%m-%d %H:%M");
		string myTime = transTime.str();
		return myTime;
	}
};

/// @brief 
/// Class used for all savegame handling
class Savegame
{
public:
	Savegame() {};
	~Savegame() {};

	// Loading and parsing savegamedata etc
	// Call at end of Game
	bool saveGameDataToJsonFile();
	// Call at beginning of game
	bool readSaveGameDataFromJson(string& path);

	void setCurrentGameData(const int id);
	SaveGameData getCurrentGameData();
	void saveCurrentGameData(SaveGameData saveGame);
	
	void generateTimeStamp(const int id)
	{
		if (isSaveGameDataEmpty(id)) return;
		const auto p1 = std::chrono::system_clock::now();
		saveGameDataMap[id].saveGameTimeStamp = (int)std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();
	}

	void addSaveGameData(const int id, SaveGameData savegame)
	{
		const auto p1 = std::chrono::system_clock::now();
		savegame.saveGameTimeStamp = (int)std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();
		saveGameDataMap[id] = savegame;
	}
	void deleteSaveGameData(const int id)
	{
		saveGameDataMap.erase(id);
	}

	bool isSaveGameDataEmpty(const int id) { return saveGameDataMap.count(id) == 0; }

	SaveGameData getSaveGameData(const int id);

private:
	FileLoader fileLoader;
	map<int, SaveGameData> saveGameDataMap;
	int currentSaveGame = 0;

	void parseJsonToMap(nlohmann::json json);
};
