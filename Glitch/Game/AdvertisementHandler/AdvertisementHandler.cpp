#include "pch.h"
#include "AdvertisementHandler.h"

AdvertisementHandler::AdvertisementHandler(unique_ptr<Engine>& _engine) : engine(_engine)
{

}

AdvertisementHandler::~AdvertisementHandler()
{

}

void AdvertisementHandler::parseJson(nlohmann::json json)
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
		if (json["URLCount"] == paths.size())
		{
			adPaths = paths;
		}
		// Else just dont use the ads
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

	}
}

void AdvertisementHandler::getLatestAdvertisements()
{
    // Get Json
    // https://raw.githubusercontent.com/Rinkeeee96/FoxTrot_SA_Engine/master/Glitch/Assets/Advertisements/advertisements.json
    string url = "https://raw.githubusercontent.com/Rinkeeee96/FoxTrot_SA_Engine/master/Glitch/Assets/Advertisements/advertisements.json";
    string path = "./Assets/Advertisements/ads.json";
    fileLoader.downloadFile(url,path);

	nlohmann::json json;
	bool parseErrors = false;
	ifstream filestream;
	try
	{
		filestream = fileLoader.readFile(path);
	}
	catch (const std::exception&)
	{
		// If error is thrown this means the document is empty or non existant. 
		// Doesnt matter in our case as we will work with the ads we have
		cout << "Error thrown in fileloader, starting with 3 empty savegames" << endl;
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
			parseJson(json);
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

	if (adPaths.size() <= 0) return;

	// Verify how many ads we have locally and store it. 
	// If we have ads online that we dont have locally we download them
	downloadMissingAds();
}

