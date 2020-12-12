#pragma once
class Scene;
class GlobalCommand;
class IGlobalCommandCreator;

class GlobalCommandFactory
{
public:
	/// @brief
	/// Function for registrating a command creator
	/// a command is created by this creator upon request with its registered classname
	void registerit(const std::string& classname, IGlobalCommandCreator* creator);
	/// @brief
	/// Function for creating ui commands and registering a layer id
	/// a command is created by this creator upon request with its registered classname
	GlobalCommand* createCommand(const std::string& classname, const int layerIndex);
private:
	map<string, IGlobalCommandCreator*> table;
};
