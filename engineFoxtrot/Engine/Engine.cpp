#include "stdafx.h"
#include "Engine.h"
#include "Input/Commands/Engine/ToggleFpsCommand.h"
#include "Input/Commands/Engine/ShutdownCommand.h"
/// @brief 
/// Create default engine commands that cannot be removed, only overriden by changing the keycode in the invoker
void Engine::constructDefaultCommands(KeypressInvoker* invoker) {
	invoker->registerCommand(KeyCode::KEY_F1, new ToggleFpsCommand(*this));
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
	//sceneManager.getSceneWithID(sceneID)->onAttach();
}

/// @brief 
/// @param scene
void Engine::insertScene(unique_ptr<Scene> scene)
{
	sceneManager.insertScene(move(scene));
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
	frameData->updateFps();
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

/// @brief
/// Returns the deltaTime from the frameData class using default physics timestep
/// @param timeStep
/// Timestep to base deltaTime calculation on
/// @returns float
float Engine::getDeltaTime(int timeStep)
{
	return frameData->calculateDeltaTime(timeStep);
}

/// @brief The startup function for the engine is for setting the currentScene pointer and the general initialisation
void Engine::start()
{
	frameData = make_unique<FrameData>();
	videoEngine.pointerToCurrentScene = &sceneManager.currentScene;
	physicsEngine.pointerToCurrentScene = &sceneManager.currentScene;
	particleEngine.pointerToCurrentScene = &sceneManager.currentScene;

	// register default invoker
	useCustomCommandInvoker(new KeypressInvoker());

	videoEngine.start(*this->eventDispatcher);
}

/// @brief Calls the update function on all the subsystems
void Engine::update()
{
	particleEngine.update();
	physicsEngine.update();
	videoEngine.update();
	inputEngine.update();
}

/// @brief Calls the shutdown function on all the subsystems
void Engine::shutdown()
{
	if (this->running)
	{
		this->setEngineRunning(false);
		inputEngine.shutdown();
		particleEngine.shutdown();
		videoEngine.shutdown();
		physicsEngine.shutdown();
	}

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