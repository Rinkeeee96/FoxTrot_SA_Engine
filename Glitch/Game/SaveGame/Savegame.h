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

	int getOverWorldProgress()
	{
		double progress = 0;
		for (auto data : levelData)
		{
			if (data.completed) progress++;
		}
		return (int)((progress / MAX_AMOUNT_OF_LEVELS) * 100);
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
	
	void addSaveGameData(const int id, SaveGameData savegame) { saveGameDataMap[id] = savegame; }
	void deleteSaveGameData(const int id) {	saveGameDataMap.erase(id); }

	bool isSaveGameDataEmpty(const int id) { return saveGameDataMap.count(id) == 0; }

	SaveGameData getSaveGameData(const int id);

private:
	FileLoader fileLoader;
	map<int, SaveGameData> saveGameDataMap;
	int currentSaveGame = 0;

	void parseJsonToMap(nlohmann::json json);
};