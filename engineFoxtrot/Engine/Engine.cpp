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
	frameData = new FrameData;

	EventListeners();
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
void Engine::deRegisterScene(const int id)
{
	sceneManager.deRegisterScene(id);
}

/// @brief 
/// Load a animated sprite (PNG) into the AnimatedTexture map
/// @param spriteObject 
void Engine::loadSprite(const SpriteObject& spriteObject) {
	bool exists = std::filesystem::exists(spriteObject.getFileName());
	if (!exists)
		throw ERROR_CODE_IMAGE_FILE_NOT_FOUND;
	videoEngine.loadImage(spriteObject);
}


void Engine::loadSound(const string& identifier, const string& path)
{
	this->soundEngine.AddFile(identifier, path);
}

void Engine::loadSound(map<string, string> sounds)
{
	this->soundEngine.SetFiles(sounds);
}


void Engine::EventListeners() {
	EventSingleton::get_instance().setEventCallback<VideoLoadSpriteEvent>(BIND_EVENT_FN(Engine::Event_LoadSprite));
}

bool Engine::Event_LoadSprite(Event& event) {
	auto loadEvent = static_cast<VideoLoadSpriteEvent&>(event);
	this->loadSprite(loadEvent.GetSpriteObject());
	// TODO is this called in a single loop or once per sprite?
	return false;
}