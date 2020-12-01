#include "stdafx.h"
#include "Engine.h"


/// @brief 
Engine::Engine()
{
	videoEngine.pointerToCurrentScene =	 &sceneManager.currentScene;
	physicsEngine.pointerToCurrentScene = &sceneManager.currentScene;
	particleEngine.pointerToCurrentScene = &sceneManager.currentScene;


	videoEngine.start(*this->eventDispatcher);
	//this->startTickThreads();
}

/// @brief 
Engine::~Engine()
{
	videoEngine.shutdown();
}

/// @brief 
/// Set the current Scene in the scenemanager. Called from game to switch screens.
/// @param sceneID 
/// SceneID to set the currentSceneID to
void Engine::setCurrentScene(const int sceneID)
{
	particleEngine.shutdown();
	physicsEngine.shutdown();
	inputEngine.shutdown();

	this->eventDispatcher =  &sceneManager.setCurrentScene(sceneID);

	particleEngine.start(*this->eventDispatcher);
	inputEngine.start(*this->eventDispatcher);
	physicsEngine.start(*this->eventDispatcher);
}

Scene* Engine::getCurrentScene()
{
	return sceneManager.currentScene;
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
	videoEngine.clearVideoEngine();
	physicsEngine.shutdown();
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

/// @brief 
void Engine::restartPhysicsWorld()
{
	physicsEngine.removeObject();
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
	inputEngine.update();
	particleEngine.update();
	videoEngine.update();
	physicsEngine.update();
}