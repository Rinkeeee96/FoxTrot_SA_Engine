#pragma once

#define BASE_PATH_AD_FOLDER "./Assets/Advertisements/"
#define JSON_AD_PATH		"./Assets/Advertisements/ads.json"

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



