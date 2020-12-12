#pragma once
class Scene;
class GlobalCommand;
class IGlobalCommandCreator;

class GlobalCommandFactory
{
public:
	void registerit(const std::string& classname, IGlobalCommandCreator* creator);
	GlobalCommand* createCommand(const std::string& classname, const int layerIndex);
private:
	map<string, IGlobalCommandCreator*> table;
};
