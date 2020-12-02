#pragma once
#include <nlohmann\json.hpp>

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
	int overWorldProgress = 0;

	int totalScore = 0;

	map<int,LevelData> levelData;
	vector<Achievement> achievements;
	CharacterData characterData;
};

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
	
	SaveGameData getSaveGameData(const int id) 
	{ 
		if (saveGameDataMap.count(id) > 0)
		{
			return saveGameDataMap[id];
		}
		throw exception("Trying to get unknown");
	}

private:
	FileLoader fileLoader;
	map<int, SaveGameData> saveGameDataMap;
	int currentSaveGame = 0;

	void parseJsonToMap(nlohmann::json json);
};