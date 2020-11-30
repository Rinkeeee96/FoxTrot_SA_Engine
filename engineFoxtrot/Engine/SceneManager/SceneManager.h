#pragma once
#include "Scene.h"
class EventDispatcher;

/// @brief 
/// Contains all scenes. Manages all scenes and objects.
class SceneManager
{
public:
	API SceneManager(shared_ptr<EventDispatcher> _dispatcher);
	API ~SceneManager();

	// Scene modifiers
	void API setCurrentScene(const int sceneID);
	API Scene* getSceneWithID(const int sceneID);
	void API insertScene(Scene* scene);
	void API deregisterScene(const int id);
	int getFirstFreeSceneID();

	// Pointer
	Scene* currentScene = nullptr;
private:
	shared_ptr<EventDispatcher> dispatcher;
	// Helper Functions
	bool checkIfSceneExists(const int);
	// TODO what happens when deleting a scene?
	map<int,Scene*> scenes;

};
