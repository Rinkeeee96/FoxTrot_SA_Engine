#pragma once
#include "JsonFacade.h"
#include <fstream> 
#include "nlohmann/json.hpp"

class API FileParser
{
public:
	std::ifstream readJSON(string path) {
		bool exists = std::filesystem::exists(path); // TODO dynamic fonts

		if (exists) {
			std::ifstream ifstream(path);

			nlohmann::json j;
			ifstream >> j;

			for (auto& element : j)
			{
				std::cout << element << '\n';
			}

			ifstream.close();



			return ifstream;
		}
		throw std::exception("file not found exception");
	}
	// Set to Private after testing!!!
	IJsonFacade* jsonEngine = new JsonFacade;
private:
};

