#pragma once

#define BASE_PATH_AD_FOLDER "./Assets/Advertisements/"
#define JSON_AD_PATH		"./Assets/Advertisements/advertisements.json"
#define JSON_URL			"https://raw.githubusercontent.com/Rinkeeee96/FoxTrot_SA_Engine/master/Glitch/Assets/Advertisements/advertisements.json"

/// @brief 
/// Class for handling advertisements
class AdvertisementHandler
{
public:
	AdvertisementHandler();
	~AdvertisementHandler();

	void downloadLatestAdvertisements();

	vector<string> getAvailableAdFileNames();

private:
	vector<string> adPaths;

	vector<string> adFileNames;
	void downloadMissingAds();

	bool readFileAndParseJson(const string& path);
	vector<string> parseJson(nlohmann::json json);

	FileLoader fileLoader;
};



