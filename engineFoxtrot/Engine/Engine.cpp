#include "stdafx.h"
#include "Engine.h"

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
	particleEngine.shutdown();
	videoEngine.shutdown();
	inputEngine.shutdown();
	physicsEngine.shutdown();

	sceneManager.setCurrentScene(sceneID);
	this->eventDispatcher = sceneManager.currentScene->dispatcher;

	particleEngine.start(*this->eventDispatcher);
	videoEngine.start(*this->eventDispatcher);
	inputEngine.start(*this->eventDispatcher);
	physicsEngine.start(*this->eventDispatcher);
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
	videoEngine.clearVideoEngine();
	physicsEngine.clean();
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
	particleEngine.onUpdate();
	videoEngine.onUpdate();
	physicsEngine.onUpdate();
}