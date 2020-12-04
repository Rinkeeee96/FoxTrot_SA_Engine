#pragma once
#include <nlohmann\json.hpp>


//TODO change when new levels are built
#define MAX_AMOUNT_OF_LEVELS 3

struct Item
{
	string itemName;
	int itemCount = 0;
};

struct Inventory
{
	vector<Item> items;
};

struct LevelData
{
	int score = 0;
	bool completed = false;
};

struct CharacterData
{
	Inventory inventory;
};

#define Achievement string

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
	
	void addSaveGameData(const int id, SaveGameData savegame)
	{
		saveGameDataMap[id] = savegame;
	}
	void deleteSaveGameData(const int id)
	{
		saveGameDataMap.erase(id);
	}

	bool isSaveGameDataEmpty(const int id)
	{
		return saveGameDataMap.count(id) > 0;
	}

	SaveGameData getSaveGameData(const int id) 
	{ 
		if (isSaveGameDataEmpty(id))
		{
			return saveGameDataMap[id];
		}
		throw exception("Trying to get unknown SaveGame");
	}

private:
	FileLoader fileLoader;
	map<int, SaveGameData> saveGameDataMap;
	int currentSaveGame = 0;

	void parseJsonToMap(nlohmann::json json);
};