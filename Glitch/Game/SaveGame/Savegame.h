#pragma once

// Maybe also singleton class?
class Inventory;

struct LevelData
{
	int levelID = 0;
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

	vector<LevelData> levelData;
	vector<Achievement> achievements;

	Inventory *inventory;

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

	bool saveGameDataToJsonFile();
	bool readSaveGameDataFromJson(string& path);

private:
	static Savegame instance;
	Savegame() {};

	map<int, SaveGameData*> saveGameDataMap;




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
