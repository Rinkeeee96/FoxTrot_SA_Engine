#pragma once



class AdvertisementHandler
{
public:
	AdvertisementHandler(unique_ptr<Engine>& engine);
	~AdvertisementHandler();

	void getLatestAdvertisements();

private:
	FileLoader fileLoader;
	unique_ptr<Engine>& engine;
};



