#include "stdafx.h"
#include "Engine.h"
#include "Input/Commands/Engine/PauseCommand.h"
#include "Input/Commands/Engine/ToggleFpsCommand.h"
#include "Input/Commands/Engine/ShutdownCommand.h"
/// @brief 
Engine::Engine()
{
}

/// @brief 
Engine::~Engine()
{
	this->shutdown();
}

/// @brief 
/// Create default engine commands that cannot be removed, only overriden by changing the keycode in the invoker
void Engine::constructDefaultCommands(KeypressInvoker* invoker) {
	invoker->registerCommand(KeyCode::KEY_F1, new ToggleFpsCommand(this->videoEngine));
	invoker->registerCommand(KeyCode::KEY_P, new PauseCommand());
	invoker->registerCommand(KeyCode::KEY_F4, new ShutdownCommand(*this));
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
void Engine::restartPhysicsWorld()
{
	physicsEngine.reloadPhysicsObjects();
}

void Engine::start()
{
	videoEngine.pointerToCurrentScene = &sceneManager.currentScene;
	physicsEngine.pointerToCurrentScene = &sceneManager.currentScene;
	particleEngine.pointerToCurrentScene = &sceneManager.currentScene;

	// register default invoker
	useCustomCommandInvoker(new KeypressInvoker());

	videoEngine.start(*this->eventDispatcher);
}

void Engine::update()
{
	particleEngine.update();
	physicsEngine.update();
	videoEngine.update();
	inputEngine.update();
}

void Engine::shutdown()
{
	this->setEngineRunning(false);
	particleEngine.shutdown();
	videoEngine.shutdown();
	physicsEngine.shutdown();
	inputEngine.shutdown();
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
