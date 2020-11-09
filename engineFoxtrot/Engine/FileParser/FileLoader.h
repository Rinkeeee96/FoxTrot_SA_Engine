#pragma once
#include <fstream> 

class API FileLoader
{
public:
	std::ifstream readFile(string path) {
		bool exists = std::filesystem::exists(path); // TODO dynamic fonts

		if (exists) {
			std::ifstream ifstream(path);
			return ifstream;
		}
		throw std::exception("file not found exception");
	}
};