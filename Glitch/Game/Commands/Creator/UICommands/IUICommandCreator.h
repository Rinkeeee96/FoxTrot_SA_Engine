#pragma once
class Scene;
class IUICommand;

class IUICommandCreator
{
public:
	/// @brief
	/// Create an instance of a ui command class 
	/// @param scene
	/// This is the scene this command is used uppon
	virtual IUICommand* createUICommand(int zIndex) = 0;
};