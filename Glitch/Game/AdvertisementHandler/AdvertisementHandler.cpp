#include "pch.h"
#include "AdvertisementHandler.h"

AdvertisementHandler::AdvertisementHandler()
{

}

AdvertisementHandler::~AdvertisementHandler()
{

}

vector<string> AdvertisementHandler::parseJson(nlohmann::json json)
{
	if (json.contains("URLS") && json.contains("URLCount"))
	{
		vector<string> paths;
		for (auto jsonObject : json["URLS"])
		{
			// Remove the ""
			string path = jsonObject;
			path.substr(1,path.size()-1);
			paths.push_back(path);
		}

		// Verify if the amount of paths is correct
		if (json["URLCount"] != paths.size())
		{
			// Dont know what to do else
		}

		return paths;
	}
	else
	{
		throw exception("Json does not contain expected elements");
	}
}

void AdvertisementHandler::downloadMissingAds()
{
	// First check if we dont have the ads locally
	for (auto ad : adPaths)
	{
		auto fileName = ad.substr(ad.find_last_of("/")+1);
		cout << fileName << endl;
		// Verify if we have the file locally

		bool result = fileLoader.doesFileExist(BASE_PATH_AD_FOLDER + fileName);
		if (!result)
		{
			cout << "File does not exists locally, downloading!" << endl;
			// Doesnt exists offline so download it.
			string url = ad;
			string path = BASE_PATH_AD_FOLDER + fileName;
			fileLoader.downloadFile(url, path);
		}
		else
		{
			cout << "File exists locally, no need to download" << endl;
		}

		adFileNames.push_back(fileName);
	}
}


bool AdvertisementHandler::readFileAndParseJson(const string& path)
{
	nlohmann::json json;
	ifstream filestream;
	try
	{
		filestream = fileLoader.readFile(path);
	}
	catch (const std::exception&)
	{
		// If error is thrown this means the document is empty or non existant. 
		// Doesnt matter in our case as we will work with the ads we have
		cout << "Ad file empty or non existent, using blank" << endl;
	}
	bool validLevel = true;
	//try
	//{
	//	validLevel = fileLoader.validateDocument(path, "Assets/Savegame/savegamedataschema.json");
	//}
	//catch (const std::exception& exc)
	//{
	//	cout << "Something went wrong parsing the file, make sure the file is correctly structured" << "\n";
	//	cout << exc.what() << "\n";
	//	throw exc;
	//}

	if (validLevel) {
		try {
			filestream >> json;
			adPaths = parseJson(json);
			filestream.close();
			return true;
		}
		catch (exception exc) {
			cout << "Something went wrong parsing the file, make sure the file is correctly structured" << "\n";
			cout << exc.what() << "\n";
		}
	}
	else {
		throw exception("SaveGame: Something went wrong validating file, make sure the file is correct");
	}
	filestream.close();
	return false;
}

void AdvertisementHandler::downloadLatestAdvertisements()
{
    // Get Json
    // https://raw.githubusercontent.com/Rinkeeee96/FoxTrot_SA_Engine/master/Glitch/Assets/Advertisements/advertisements.json
    string url = "https://raw.githubusercontent.com/Rinkeeee96/FoxTrot_SA_Engine/master/Glitch/Assets/Advertisements/advertisements.json";
    string path = JSON_AD_PATH;
    fileLoader.downloadFile(url,path);

	bool result = readFileAndParseJson(path);

	// Verify how many ads we have locally and store it. 
	// If we have ads online that we dont have locally we download them
	if (result && adPaths.size() >= 0)
	{
		// The file has been downloaded and is parsed. Links have been placed into the vector
		downloadMissingAds();
	}
	else
	{
		// The file has not been downloaded and the vector is empty
	}



	
}

vector<string> AdvertisementHandler::getAvailableAdFileNames()
{
	return adFileNames;
}

