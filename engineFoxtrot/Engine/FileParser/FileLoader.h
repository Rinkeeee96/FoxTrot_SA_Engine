#pragma once
#include <fstream> 
#include <string>
#include <map>

class API FileLoader
{
private:

public:
	std::ifstream readFile(string path);
};