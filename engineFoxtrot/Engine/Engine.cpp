#include "stdafx.h"
#include "Engine.h"
#include "Input/Commands/Engine/PauseCommand.h"


/// @brief 
Engine::Engine()
{
	videoEngine.pointerToCurrentScene =	 &sceneManager.currentScene;
	physicsEngine.pointerToCurrentScene = &sceneManager.currentScene;
	particleEngine.pointerToCurrentScene = &sceneManager.currentScene;

	// register default invoker
	useCustomCommandInvoker(new KeypressInvoker());
	constructDefaultCommands(keypressInvoker);

	videoEngine.start(*this->eventDispatcher);
}

/// @brief 
Engine::~Engine()
{
	videoEngine.shutdown();
}

void Engine::constructDefaultCommands(KeypressInvoker* invoker) {
	// TODO Maybe make it so systems are always stored in a vector?
	invoker->registerCommand(KeyCode::KEY_P, new PauseCommand({
		&this->inputEngine,
		&this->videoEngine,
		&this->physicsEngine
		})
	);
}

/// @brief 
/// Override the default invoker with a custom one from the application
void Engine::useCustomCommandInvoker(KeypressInvoker* newInvoker)
{
	constructDefaultCommands(newInvoker);
	this->keypressInvoker = newInvoker;
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
	inputEngine.registerKeypressInvoker(this->keypressInvoker);
	physicsEngine.start(*this->eventDispatcher);

	sceneManager.getSceneWithID(sceneID)->onAttach();
	sceneManager.getSceneWithID(sceneID)->onAttach();
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
	physicsEngine.removeObject();
}

void Engine::loadSound(const string& identifier, const string& path)
{
	this->soundEngine.addFile(identifier, path);
}

void Engine::loadSound(map<string, string> sounds)
{
	this->soundEngine.setFiles(sounds);
}

void Engine::onUpdate()
{
	// TODO change after command pattern is implemented
	if (!engineIsPaused) { 
		particleEngine.update();
		physicsEngine.update();
	}
	videoEngine.update();
	inputEngine.update();
}
