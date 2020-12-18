#include "stdafx.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Engine.h"


/// @brief Constructor
SceneManager::SceneManager()
{
}

/// @brief Destructor
SceneManager::~SceneManager()
{
}

/// @brief 
/// A function to check if a scene exists
/// @param sceneID 
/// Identifier to a SceneID. 
/// @return 
/// If SceneID has a valid scene returns true else false
bool SceneManager::checkIfSceneExists(const int sceneID)
{
	if (scenes.find(sceneID) == scenes.end()) {
		// not found
		return false;
	}
	else {
		// found
		return true;
	}
}

/// @brief 
/// Able to insert a Scene into the scenemanager
/// @param scene 
/// Pointer to a scene
void SceneManager::insertScene(unique_ptr<Scene> scene)
{
	if (scene == nullptr) return;
	scenes[scene->getSceneID()] = move(scene);
}

/// @brief 
/// @param id 
void SceneManager::deregisterCurrentScene()
{
	if (!currentScene) throw exception("SceneManager: Scene does not exist");
	currentScene->onDetach();
	currentScene.reset();
}

/// @brief 
/// Returns the last sceneID available in the map + 1
/// @return 
/// returns int
int SceneManager::getFirstFreeSceneID()
{
	return scenes.end()->second->getSceneID() + 1;
}

void SceneManager::updateCurrentScene(float deltaTime)
{
	if(currentScene)currentScene->onUpdate(deltaTime);
}

/// @brief 
/// A function to change a scene
/// If a scene does not exists throw ERROR_CODE_SCENEMANAGER_SCENES_IS_EMPTY
/// @param sceneID 
/// Identifier to a SceneID.
EventDispatcher& SceneManager::setCurrentScene(const int sceneID)
{
	if (scenes.empty()) throw exception("SceneManager: Scene does not exist");

	if (currentScene)scenes[currentScene->getSceneID()] = move(currentScene);

	currentScene = move(scenes[sceneID]);
	if (DEBUG_SCENE_MANAGER)cout << "Setting current scene to " << sceneID << " with amount of obj: " << currentScene->getAllObjectsInScene().size() << endl;

	return currentScene->getEventDispatcher();
}
