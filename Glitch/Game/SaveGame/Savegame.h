#pragma once
#include <nlohmann\json.hpp>
#include "Game/General/GeneralGameDefines.h"

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
		saveGameDataMap[id].saveGameTimeStamp = std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();
	}

	void addSaveGameData(const int id, SaveGameData savegame)
	{
		const auto p1 = std::chrono::system_clock::now();
		savegame.saveGameTimeStamp = std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();
		saveGameDataMap[id] = savegame;
	}
	void deleteSaveGameData(const int id)
	{
		saveGameDataMap.erase(id);
	}

	bool isSaveGameDataEmpty(const int id)
	{
		return saveGameDataMap.count(id) == 0;
	}

	SaveGameData getSaveGameData(const int id) 
	{ 
		if (!isSaveGameDataEmpty(id))
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