#include "pch.h"
#include "Savegame.h"


Savegame Savegame::instance;

bool Savegame::saveGameDataToJsonFile()
{
	for (auto saveGame : saveGameDataMap)
	{
		nlohmann::json json;


		// Get Timestamp
		const auto p1 = std::chrono::system_clock::now();
		json["timestamp"] = std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();

		json["savegamename"] = saveGame.second->saveGameName;
		json["savegameid"] = saveGame.first;

		for (auto achievement : saveGame.second->achievements)
		{
			json["achievements"].push_back(achievement);
		}

		json["totalscore"] = saveGame.second->totalScore;
		

		// Write Json data to file
		std::stringstream sstm;
		sstm << "saveGameData" << saveGame.first << ".json";
		string saveFile = sstm.str();
		std::ofstream file(saveFile);
		file << json;
	}



	return true;
}

bool Savegame::readSaveGameDataFromJson(string& path)
{
	nlohmann::json json;

	try {
		auto filestream = fileLoader.readFile(path);
		filestream >> json;
		filestream.close();

		try {
			parseJsonToMap(json);
		}
		catch (exception e) {
			cout << "Something went wrong parsing the file, make sure the file is correctly structured" << "\n";
			cout << e.what() << "\n";
		}
	}
	catch (exception e) {
		cout << "Something went wrong opening file, make sure the file exists" << "\n";
		cout << e.what() << "\n";
	}

	return true;
	
}

void Savegame::addAchievement(Achievement& achievement)
{
	if (!currentSaveGame) return;
	currentSaveGame->achievements.push_back(achievement);
}

void Savegame::changeSaveGameName(string& name)
{
	if (!currentSaveGame) return;
	currentSaveGame->saveGameName = name;
}

void Savegame::addLevelData(const int levelID, LevelData levelData)
{
	if (!currentSaveGame) return;
	currentSaveGame->levelData[levelID] = levelData;
}

void Savegame::updateCharacterData(CharacterData characterData)
{
	if (!currentSaveGame) return;
	currentSaveGame->characterData = characterData;
}

void Savegame::updateOverWorldProgress(const int progress)
{
	if (!currentSaveGame) return;
	currentSaveGame->overWorldProgress = progress;
}

void Savegame::loadSaveGameData(const int id)
{
	if (saveGameDataMap.find(id) != saveGameDataMap.end()) {
		//SaveGame is found in map. Use this one.
		currentSaveGame = saveGameDataMap[id];
	}
	else {
		// Try to load it from file. 
	}
}

void Savegame::parseJsonToMap(nlohmann::json json)
{

}
