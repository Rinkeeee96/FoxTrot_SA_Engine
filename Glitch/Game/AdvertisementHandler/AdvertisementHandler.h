#pragma once



class AdvertisementHandler
{
public:
	AdvertisementHandler(unique_ptr<Engine>& engine);
	~AdvertisementHandler();

	void getLatestAdvertisements();

private:
	vector<string> adPaths;
	void downloadMissingAds();
	void parseJson(nlohmann::json json);

	FileLoader fileLoader;
	unique_ptr<Engine>& engine;
};



