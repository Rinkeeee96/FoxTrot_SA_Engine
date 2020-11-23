#include "stdafx.h"
#include "SceneManager.h"

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
void SceneManager::insertScene(Scene* scene)
{
	if (scene == nullptr) return;
	scenes[scene->getSceneID()] = scene;
}

/// @brief 
/// @param id 
void SceneManager::deRegisterScene(const int id)
{
	scenes.erase(scenes.find(id));
}

/// @brief 
/// Returns the last sceneID available in the map + 1
/// @return 
/// returns int
int SceneManager::getFirstFreeSceneID()
{
	return scenes.end()->second->getSceneID() + 1;
}

/// @brief 
/// A function to change a scene
/// If a scene does not exists throw ERROR_CODE_SCENEMANAGER_SCENES_IS_EMPTY
/// @param sceneID 
/// Identifier to a SceneID.
void SceneManager::setCurrentScene(const int sceneID)
{
	if (scenes.empty()) throw ERROR_CODE_SCENEMANAGER_SCENES_IS_EMPTY;

	currentScene = getSceneWithID(sceneID);
	if (DEBUG_SCENE_MANAGER)cout << "Setting current scene to " << sceneID << " with amount of obj: " << currentScene->getAllObjectsInScene().size() << endl;
}

/// @brief 
/// Get a scene with a sceneID
/// If a scene does not exists throw ERROR_CODE_SCENEMANAGER_SCENES_IS_EMPTY
/// @param sceneID 
/// Identifier to a SceneID.
/// @return
/// Returns pointer to the found Scene. 
Scene* SceneManager::getSceneWithID(const int sceneID)
{
	if (scenes.empty()) throw ERROR_CODE_SCENEMANAGER_SCENES_IS_EMPTY;
	if (scenes.find(sceneID) == scenes.end()) {
		// not found
		throw ERROR_CODE_SCENEMANAGER_CANT_FIND_SCENE_WITH_ID;
	}
	else {
		// found
		return scenes[sceneID];
	}
}
