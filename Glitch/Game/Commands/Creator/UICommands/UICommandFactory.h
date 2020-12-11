#pragma once
class Scene;
class IUICommand;
class IUICommandCreator;

class UICommandFactory
{
public:
	/// @brief
	/// Function for registrating a command creator
	/// a command is created by this creator upon request with its registered classname
	void registerit(const std::string& classname, IUICommandCreator* creator);
	/// @brief
	/// Function for creating ui commands and registering a scene with them
	/// a command is created by this creator upon request with its registered classname
	IUICommand* createUICommand(const std::string& classname, Scene& scene);
private:
	map<string, IUICommandCreator*> table;
};
