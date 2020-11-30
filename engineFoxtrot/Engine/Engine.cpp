#include "stdafx.h"
#include "Engine.h"
#include "Events\AppTickEvent30.h"
#include "Events\AppTickEvent60.h"
#include "Events\Video\VideoLoadSpriteEvent.h"

/// @brief 
Engine::Engine()
{
	videoEngine.pointerToCurrentScene =	 &sceneManager.currentScene;
	physicsEngine.pointerToCurrentScene = &sceneManager.currentScene;
	particleEngine.pointerToCurrentScene = &sceneManager.currentScene;

	//this->startTickThreads();
}

/// @brief 
Engine::~Engine()
{
}

/// @brief 
/// Set the current Scene in the scenemanager. Called from game to switch screens.
/// @param sceneID 
/// SceneID to set the currentSceneID to
void Engine::setCurrentScene(const int sceneID)
{
	sceneManager.setCurrentScene(sceneID);
}

Scene* Engine::getCurrentScene()
{
	return sceneManager.currentScene;
}

/// @brief 
void Engine::pollEvents() 
{
	this->inputEngine.pollEvents();
}

/// @brief 
/// @param scene
void Engine::insertScene(Scene* scene)
{
	sceneManager.insertScene(scene);
}

/// @brief 
/// @param id 
void Engine::deregisterScene(const int id)
{
	sceneManager.deregisterScene(id);
}

/// @brief
/// Updates the fps counter
void Engine::updateFps() {
	frameData.updateFps();
}

/// @brief
/// Toggles fps visibility
void Engine::toggleFps() {
	videoEngine.toggleFps();
}

void Engine::loadSound(const string& identifier, const string& path)
{
	this->soundEngine.AddFile(identifier, path);
}

void Engine::loadSound(map<string, string> sounds)
{
	this->soundEngine.SetFiles(sounds);
}


void Engine::onUpdate()
{
	videoEngine.onUpdate();
	physicsEngine.onUpdate();
}