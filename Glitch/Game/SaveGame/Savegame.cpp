#include "pch.h"
#include "Savegame.h"


Savegame Savegame::instance;

bool Savegame::saveGameDataToJsonFile()
{
	//saveGameData.json
	nlohmann::json json;
	for (auto saveGame : saveGameDataMap)
	{
		nlohmann::json saveGameJson;

		// Get Timestamp
		const auto p1 = std::chrono::system_clock::now();
		saveGameJson["timestamp"] = std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();

		saveGameJson["savegamename"] = saveGame.second.saveGameName;
		saveGameJson["savegameid"] = saveGame.first;
		saveGameJson["totalscore"] = saveGame.second.totalScore;

		for (auto achievement : saveGame.second.achievements)
		{
			saveGameJson["achievements"].push_back(achievement);
		}
		for (auto levelData : saveGame.second.levelData)
		{
			nlohmann::json levelDataJson;
			levelDataJson["score"] = levelData.second.score;
			levelDataJson["completed"] = levelData.second.completed;
			saveGameJson["leveldata"].push_back(levelDataJson);
		}
		nlohmann::json characterData;
		nlohmann::json items;
		for (Item item : saveGame.second.characterData.inventory.items)
		{
			nlohmann::json itemJson;
			itemJson["itemname"] = item.itemName;
			itemJson["itemcount"] = item.itemCount;

			characterData["inventory"]["items"].push_back(itemJson);
		}	
		saveGameJson["characterdata"] = characterData;
		json["saveGames"].push_back(saveGameJson);
	}
	// Write Json data to file
	std::ofstream file("saveGameData.json");
	file << json;


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

void Savegame::saveGameData(const int id, SaveGameData saveGame)
{
	saveGameDataMap[id] = saveGame;
}

SaveGameData Savegame::getGameData(const int id)
{
	SaveGameData data;
	return data;
}

void Savegame::parseJsonToMap(nlohmann::json json)
{

}
