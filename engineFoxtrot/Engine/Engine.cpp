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
	this->eventDispatcher =  &sceneManager.setCurrentScene(sceneID);

	particleEngine.start(*this->eventDispatcher);
	soundEngine.start(*this->eventDispatcher);
	inputEngine.start(*this->eventDispatcher);
	physicsEngine.start(*this->eventDispatcher);

	sceneManager.getSceneWithID(sceneID)->onAttach();
	sceneManager.getSceneWithID(sceneID)->onAttach();
}

/// @brief Returns the currentScene
/// @return 
Scene* Engine::getCurrentScene()
{
	return sceneManager.currentScene;
}

// TODO Remove after command pattern is implemented
bool Engine::onKeyPressed(const Event& event) {
	auto keyPressedEvent = static_cast<const KeyPressedEvent&>(event);
	// TODO command pattern
	switch (keyPressedEvent.getKeyCode())
	{
	case KeyCode::KEY_P:
		engineIsPaused = !engineIsPaused;
		break;
	default:
		return false;
	}
	return true;
}

/// @brief Insert a Scene into the current scene
/// @param scene
void Engine::insertScene(Scene* scene)
{
	sceneManager.insertScene(scene);
}

/// @brief Deregister a scene according to the given sceneID
/// @param id 
void Engine::deregisterScene(const int id)
{
	inputEngine.shutdown();
	sceneManager.deregisterScene(id);
	videoEngine.clearVideoEngine();

	soundEngine.shutdown();
	particleEngine.shutdown();
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

/// @brief Calls reloadPhysicsObject from the physicsEngine
void Engine::restartPhysicsWorld()
{
	physicsEngine.reloadPhysicsObjects();
}

/// @brief Calls addFile from the sound engine.
/// @param identifier 
/// @param path 
void Engine::loadSound(const string& identifier, const string& path)
{
	this->soundEngine.addFile(identifier, path);
}

/// @brief Calls setFile from the sound engine.
/// @param sounds 
void Engine::loadSound(map<string, string> sounds)
{
	this->soundEngine.setFiles(sounds);
}

/// @brief Calls playMusic from the sound engine.
/// @param identifier 
void Engine::startSound(const string& identifier) {
	this->soundEngine.playMusic(identifier, 15);
}

/// @brief Calls stopMusic from the sound engine.
/// @param identifier 
void Engine::stopSound(const string& identifier) {
	this->soundEngine.stopMusic();
}

/// @brief Calls onStopLoopedEffect from the sound engine.
/// @param identifier 
void Engine::stopLoopEffect(const string& identifier) {
	this->soundEngine.onStopLoopedEffect(identifier);
}

/// @brief Calls the update function on all the subsystems
void Engine::onUpdate()
{
	particleEngine.update();
	physicsEngine.update();
	videoEngine.update();
	inputEngine.update();
}
