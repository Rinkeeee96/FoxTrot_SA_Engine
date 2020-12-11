#include "pch.h"
#include "Savegame.h"


/// @brief 
/// Saves the savegamedata array to a json file
/// @return 
/// Failed or succes
bool Savegame::saveGameDataToJsonFile()
{
	nlohmann::json json;
	for (auto saveGame : saveGameDataMap)
	{
		nlohmann::json saveGameJson;

		saveGameJson["timestamp"] = saveGame.second.saveGameTimeStamp;

		saveGameJson["savegamename"] = saveGame.second.saveGameName;
		saveGameJson["savegameid"] = saveGame.first;
		saveGameJson["totalscore"] = saveGame.second.totalScore;

		for (auto achievement : saveGame.second.achievements)
		{
			saveGameJson["achievements"].push_back(achievement);
		}
		int count = 0;
		for (auto levelData : saveGame.second.levelData)
		{
			nlohmann::json levelDataJson;
			levelDataJson["score"] = levelData.score;
			levelDataJson["completed"] = levelData.completed;
			levelDataJson["levelnr"] = count++;
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
		json["savegames"].push_back(saveGameJson);
	}
	// Todo move to engine.
	// Write Json data to file
	const char* path = "Assets/Savegame/saveGameData.json";
	std::ofstream file(path); //open in constructor
	file << json;


	return true;
}

/// @brief 
/// Reads a json file and parses it into savegame data map
/// @param path 
/// String path for the folder/file location
/// @return 
/// Returns true when it completes
bool Savegame::readSaveGameDataFromJson(string& path)
{
	nlohmann::json json;

	try {
		
		auto filestream = fileLoader.readFile(path);

		bool validLevel = fileLoader.validateDocument(path, "Assets/Savegame/savegamedataschema.json");

		if (validLevel) {
			try {
				
				filestream >> json;
				parseJsonToMap(json);
				
			}
			catch (exception exc) {
				cout << "Something went wrong parsing the file, make sure the file is correctly structured" << "\n";
				cout << exc.what() << "\n";
				throw exc;
			}
		}
		else {
			throw exception("Something went wrong validating file, make sure the file is correct");
		}

		filestream.close();
		
	}
	catch (exception exc) {
		// File doesnt exist. 
		// Doesnt matter because json can handle empty jsons
	}

	return true;
	
}

/// @brief 
/// Sets the currentsavegame data to the given id
/// @param id 
void Savegame::setCurrentGameData(const int id)
{
	generateTimeStamp(id);
	currentSaveGame = id;
}

/// @brief 
/// Returns the current Savegame data
/// @return 
SaveGameData Savegame::getCurrentGameData()
{
	return saveGameDataMap[currentSaveGame];
}

/// @brief 
/// Saves the given savegamedata into the current slot
/// @param saveGame 
void Savegame::saveCurrentGameData(SaveGameData saveGame)
{
	saveGameDataMap[currentSaveGame] = saveGame;
}

/// @brief 
/// Parses the json file into the map
/// @param json 
void Savegame::parseJsonToMap(nlohmann::json json)
{
	for (auto jsonObject : json["savegames"])
	{
		SaveGameData saveGameData;
		if (!jsonObject.contains("timestamp")) throw exception("Timestamp unavailable in json file");
		if (!jsonObject.contains("savegamename"))throw exception("savegamename unavailable in json file");
		if (!jsonObject.contains("savegameid")) throw exception("savegameid unavailable in json file");

		saveGameData.saveGameName = jsonObject["savegamename"];
		saveGameData.saveGameTimeStamp = jsonObject["timestamp"];
		int id = jsonObject["savegameid"];

		if (jsonObject.contains("totalscore"))
		{
			saveGameData.totalScore = jsonObject["totalscore"];
		}
		if (jsonObject.contains("leveldata"))
		{
			for (auto itemJson : jsonObject["leveldata"])
			{
				LevelData levelD;
				levelD.score = itemJson["score"];
				levelD.completed = itemJson["completed"];
				saveGameData.levelData[itemJson["levelnr"]] = levelD;
			}
		}
		if (jsonObject.contains("achievements"))
		{
			for (auto achievement : jsonObject["achievements"])
			{
				saveGameData.achievements.push_back(achievement);
			}
		}

		if (jsonObject.contains("characterdata"))
		{
			if (jsonObject["characterdata"].contains("inventory"))
			{
				if (jsonObject["characterdata"]["inventory"].contains("items"))
				{
					for (auto itemJson : jsonObject["characterdata"]["inventory"]["items"])
					{
						Item item;
						item.itemCount = itemJson["itemcount"];
						item.itemName = itemJson["itemname"];
						saveGameData.characterData.inventory.items.push_back(item);
					}
					// Parse other item things in future
				}
				// Parse other inventory things in future
			}
			// Parse other character data in future
		}
		saveGameDataMap[id] = saveGameData;
	}
}
