#pragma once
class Scene;
class GlobalCommand;

class IGlobalCommandCreator
{
public:
	/// @brief
	/// Create an instance of a ui command class 
	/// @param scene
	/// This is the scene this command is used uppon
	virtual GlobalCommand* createCommand(int zIndex) = 0;
};