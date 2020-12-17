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
	API void insertScene(unique_ptr<Scene>);
	API void deregisterCurrentScene();
	
	int getFirstFreeSceneID();

	void updateCurrentScene(float deltaTime);

	// Pointer
	unique_ptr<Scene> currentScene = nullptr;
private:
	// Helper Functions
	bool checkIfSceneExists(const int);
	// TODO what happens when deleting a scene?
	map<int, unique_ptr<Scene>> scenes;
};
