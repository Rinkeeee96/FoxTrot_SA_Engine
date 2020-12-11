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

/// @brief 
void Engine::restartPhysicsWorld()
{
	physicsEngine.reloadPhysicsObjects();
}

/// @brief
/// Returns the deltaTime from the frameData class using default physics timestep
/// @param timeStep
/// Timestep to base deltaTime calculation on
/// @returns float
float Engine::getDeltaTime(int timeStep)
{
	return frameData.calculateDeltaTime(DELTATIME_TIMESTEP_PHYSICS);
}

void Engine::loadSound(const string& identifier, const string& path)
{
	this->soundEngine.addFile(identifier, path);
}

void Engine::loadSound(map<string, string> sounds)
{
	this->soundEngine.setFiles(sounds);
}

void Engine::startSound(const string& identifier) {
	this->soundEngine.playMusic(identifier, 15);
}

void Engine::stopSound(const string& identifier) {
	this->soundEngine.stopMusic();
}
void Engine::stopLoopEffect(const string& identifier) {
	this->soundEngine.onStopLoopedEffect(identifier);
}

void Engine::onUpdate()
{
	particleEngine.update();
	physicsEngine.update();
	videoEngine.update();
	inputEngine.update();
}
