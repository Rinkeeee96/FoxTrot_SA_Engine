#pragma once
#include <fstream> 

/// @brief 
/// Class responsible for opening files
class API FileLoader
{
private:
	
public:
	virtual ~FileLoader() {};
	ifstream readFile(string path);
	bool validateDocument(string path, string validationPath);

	bool doesFileExist(const string& path);
	void downloadFile(const string& url, const string& pathAndFilename);

	vector<string> getDirFiles(const string& path);
};