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
	API Scene* getSceneWithID(const int sceneID);
	API void insertScene(Scene* scene);
	API void deregisterScene(const int id);
	int getFirstFreeSceneID();

	// Pointer
	Scene* currentScene = nullptr;
private:
	// Helper Functions
	bool checkIfSceneExists(const int);
	// TODO what happens when deleting a scene?
	map<int, Scene*> scenes;
	Engine* engine;
};
