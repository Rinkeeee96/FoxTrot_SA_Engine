#include "pch.h"
#include "AdvertisementHandler.h"

AdvertisementHandler::AdvertisementHandler(unique_ptr<Engine>& _engine) : engine(_engine)
{

}

AdvertisementHandler::~AdvertisementHandler()
{

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
		// Doesnt matter in our case as we use 3 empty savegames. 
		// Dont throw an error but we do notify the developer
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
			// handle Json
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

    // Parse Json 
}

