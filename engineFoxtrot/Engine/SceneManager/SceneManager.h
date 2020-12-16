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
	API unique_ptr<Scene>& getSceneWithID(const int sceneID);
	API void insertScene(unique_ptr<Scene> scene);
	API void deregisterScene(const int id);
	
	int getFirstFreeSceneID();

	// Pointer
	unique_ptr<Scene> currentScene;
private:
	// Helper Functions
	bool checkIfSceneExists(const int);
	// TODO what happens when deleting a scene?
	map<int, unique_ptr<Scene>> scenes;
	Engine* engine;
};
