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
	// Stub, to be completed
	int health = 0;
	int stamina = 0;
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

	Inventory inventory;

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

	// Loads the savegamedata with id to currentSaveGameData
	void loadSaveGameData(const int id);

	// Actions on current savegame data
	void addAchievement(Achievement& achievement);
	void changeSaveGameName(string& name);
	void addLevelData(const int levelID, LevelData levelData);
	void updateCharacterData(CharacterData characterData);
	void updateOverWorldProgress(const int progress);

	// Getters for currentSaveGameData


	// Todo set private
	// Just for testing purposes
	map<int, SaveGameData*> saveGameDataMap;

private:
	static Savegame instance;
	Savegame() {};

	FileLoader fileLoader;

	SaveGameData* currentSaveGame;

	void parseJsonToMap(nlohmann::json json);



};


// Mockup of savegame data in Json:

//{
//	"saveGameTimestamp": 1605262284,
//		"saveGameName" : "SaveGame1",
//		"saveGameID" : 3,
//		"levelCompletion" : [
//	{
//		"levelID": 1,
//			"score" : 76,
//			"completed" : true
//	},
//	{
//	  "levelID": 2,
//	  "score" : 76,
//	  "completed" : false
//	}
//		],
//		"totalScore": 69420,
//			"achievements" : [
//				"take inventory",
//					"move player position"
//			] ,
//			"characterStats" : {
//					"health": 10,
//						"stamina" : 10
//				},
//					"inventory" : [
//					{
//						"itemid": 1,
//							"itemCount" : 10
//					},
//	{
//	  "itemid": 1,
//	  "itemCount" : 10
//	}
//					]
//}
