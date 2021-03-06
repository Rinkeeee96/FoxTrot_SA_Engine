#include "pch.h"
#include "AdvertisementHandler.h"

/// @brief 
AdvertisementHandler::AdvertisementHandler()
{

}

/// @brief 
AdvertisementHandler::~AdvertisementHandler()
{

}

/// @brief 
/// Parses the json into a vector of urls
/// Also verifys the json
/// If the json does not contain the expected elements we return a empty vector.
/// @param json 
/// @return 
vector<string> AdvertisementHandler::parseJson(nlohmann::json json)
{
	if (json.contains("URLS") && json.contains("URLCount"))
	{
		vector<string> paths;
		for (auto jsonObject : json["URLS"])
		{
			// Remove the ""
			string path = jsonObject;
			path = path.substr(0,path.size());
			paths.push_back(path);
		}

		// Verify if the amount of paths is correct
		if (json["URLCount"] != paths.size())
		{
			cout << "AdvertisementHandler: Json size mismatch" << endl;
			return vector<string>();
		}

		return paths;
	}
	else
	{
		return vector<string>();
	}
}

/// @brief 
/// This function loops through the url vector and check if the files are downloaded locally
/// If the file is located offline it will not be downloaded.
/// All located ads are placed in adFileNames vector
void AdvertisementHandler::downloadMissingAds()
{
	// First check if we dont have the ads locally
	for (auto ad : adPaths)
	{
		auto fileName = ad.substr(ad.find_last_of("/")+1);
		// Verify if we have the file locally

		bool result = fileLoader.doesFileExist(BASE_PATH_AD_FOLDER + fileName);
		if (!result)
		{
			// Doesnt exists offline so download it.
			string url = ad;
			string path = BASE_PATH_AD_FOLDER + fileName;
			fileLoader.downloadFile(url, path);
		}

		if(fileLoader.doesFileExist(BASE_PATH_AD_FOLDER + fileName))
			adFileNames.push_back(fileName);
	}
}

/// @brief 
/// Reads and parses the json file
/// @param path 
/// @return 
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
		cout << "AdvertisementHandler: Ad file empty or non existent, using blank" << endl;
		filestream.close();
		return false;
	}

	// Potential TODO
	// Json schema to validate
	// Dont do it now as its such a small json

	try {
		filestream >> json;
		adPaths = parseJson(json);
		filestream.close();
		return true;
	}
	catch (exception exc) {
		cout << "AdvertisementHandler: Something went wrong parsing the file, make sure the file is correctly structured" << "\n";
		cout << exc.what() << "\n";
	}

	filestream.close();
	return false;
}

/// @brief 
/// Downloads the latest advertisements
void AdvertisementHandler::downloadLatestAdvertisements()
{
    // Get Json
    string url = JSON_URL;
    string path = JSON_AD_PATH;
    fileLoader.downloadFile(url,path);

	bool result = readFileAndParseJson(path);

	// If result is true it means the json file was downloaded and parsed into the vector
	// If the size is smaller then 0 we continue without ads, as we dont know what to use. 
	if (result && adPaths.size() > 0)
	{
		// The file has been downloaded and is parsed. Links have been placed into the vector
		downloadMissingAds();
		
	}	
	else
	{
		// If json is corrupt or something but you have local files use these
		// Search for local png files
		vector<string> files = fileLoader.getDirFiles(BASE_PATH_AD_FOLDER);

		for (auto file : files)
		{
			// Check if png
			if (file.substr(file.find_last_of(".")) == ".png")
			{
				auto fileName = file.substr(file.find_last_of("/") + 1);
				adFileNames.push_back(fileName);
			}
		}
	}
}

/// @brief 
/// Returns adFileNames
/// @return 
vector<string> AdvertisementHandler::getAvailableAdFileNames()
{
	return adFileNames;
}

