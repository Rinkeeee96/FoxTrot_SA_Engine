#pragma once
#include <nlohmann\json.hpp>

// Maybe also singleton class?


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
	static Savegame& get_instance() { return instance; }
	// prohibit copy & move
	Savegame(const Savegame&) = delete;
	Savegame(Savegame&&) = delete;
	Savegame& operator=(const Savegame&) = delete;
	Savegame& operator=(Savegame&&) = delete;

	// Loading and parsing savegamedata etc
	// Call at end of Game
	bool saveGameDataToJsonFile();
	// Call at beginning of game
	bool readSaveGameDataFromJson(string& path);

	void saveGameData(const int id, SaveGameData saveGame);
	SaveGameData getGameData(const int id);

private:
	static Savegame instance;
	Savegame() {};

	FileLoader fileLoader;
	map<int, SaveGameData> saveGameDataMap;

	void parseJsonToMap(nlohmann::json json);
};