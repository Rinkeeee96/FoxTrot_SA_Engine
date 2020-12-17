#pragma once
class EventDispatcher;
class Engine;
class Scene;

/// @brief 
/// Contains all scenes. Manages all scenes and objects.
class SceneManager
{
public:
	API SceneManager();
	API ~SceneManager();

	// Scene modifiers
	API EventDispatcher& setCurrentScene(const int sceneID);
	API shared_ptr<Scene> getSceneWithID(const int sceneID);
	API void insertScene(shared_ptr<Scene>);
	API void deregisterScene(const int id);
	
	int getFirstFreeSceneID();

	// Pointer
	shared_ptr<Scene> currentScene = nullptr;
private:
	// Helper Functions
	bool checkIfSceneExists(const int);
	map<int, shared_ptr<Scene>> scenes;
};
