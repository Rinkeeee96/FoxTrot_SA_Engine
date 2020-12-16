#pragma once

#ifndef ENGINE__H
#define ENGINE__H

#include "./SceneManager/SceneManager.h"
#include "./Physics/PhysicsEngine.h"
#include "./ParticleSystem/ParticleEngine.h"
#include "./SceneManager/SceneManager.h"

#include "./Video/VideoEngine.h"
#include "./Sound/SoundEngine.h"
#include "./Input/InputEngine.h"
#include "./Fps/FrameData.h"

#include "Events/EventDispatcher.h"

#define	ENGINE_TICK60	 17
#define ENGINE_TICK30	 33

#define TIME_STEP 1

/// @brief Engine interface class connecting the game to the engine
class Engine
{
public:
	API Engine() {};
	API ~Engine() {};

	// Inherited via ISubsystem
	API void start();
	API void update();
	API void shutdown();

	/// @brief
	/// The engine's keypress invoker contains 'default' engine commands and keybindings for them, these are to always exist
	/// and are thus created in this function, this method is called each time an invoker is assigned. 
	/// Due to the way the invoker is setup, these cannot be overriden by default, only the bindings can be modified.
	API void useCustomCommandInvoker(KeypressInvoker* newInvoker);

	//SceneManager calls
	API void setCurrentScene(const int sceneID);
	API Scene* getCurrentScene();
	API void insertScene(Scene * scene);
	API void deregisterScene(const int id);

	// Sound calls
	API void loadSound(const string& identifier, const string& path);
	API void loadSound(map<string, string> sounds);
	API void startSound(const string& identifier);
	API void stopSound(const string& identifier);
	API void stopLoopEffect(const string& identifier);

	API void updateFps();

	API void toggleFps();

	API bool getEngineRunning() { return running; };
	API void setEngineRunning(bool run) { running = run; }

	KeypressInvoker* getKeypressedInvoker() { return keypressInvoker; }

	API float getDeltaTime(int timeStep);
	API void restartPhysicsWorld();
private:
	void constructDefaultCommands(KeypressInvoker* invoker);
	EventDispatcher* eventDispatcher;
	bool running = false;

	float deltaTimePhysics = 0;
	float deltaTimeRender = 0;
	
	unique_ptr<FrameData> frameData;
	KeypressInvoker* keypressInvoker;

	SceneManager sceneManager;
	ParticleEngine particleEngine{ frameData };
	PhysicsEngine physicsEngine{ frameData };
	SoundEngine soundEngine;

	VideoEngine videoEngine{ frameData };
	InputEngine inputEngine{ *this };

	bool engineIsPaused = false;
};
#endif
