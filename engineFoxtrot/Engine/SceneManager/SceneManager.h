#pragma once
#include "Scene.h"

/// @brief 
/// Contains all scenes. Manages all scenes and objects.
class SceneManager
{
public:
	API SceneManager();
	API ~SceneManager();

	// Scene modifiers
	void API setCurrentScene(const int sceneID);
	API Scene* getSceneWithID(const int sceneID);
	void API insertScene(Scene* scene);
	void API deregisterScene(const int id);
	int getFirstFreeSceneID();

	// Pointer
	Scene* currentScene = nullptr;

protected:
	

private:

	// Helper Functions
	bool checkIfSceneExists(const int);
	// TODO what happens when deleting a scene?
	map<int,Scene*> scenes;

};
