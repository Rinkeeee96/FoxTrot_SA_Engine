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

/// @brief 
class Engine
{
public:
	API Engine();
	API ~Engine();

	/// @brief
	/// The engine's keypress invoker contains 'default' engine commands and keybindings for them, these are to always exist
	/// and are thus created in this function, this method is called each time an invoker is assigned. 
	/// Due to the way the invoker is setup, these cannot be overriden by default, only the bindings can be modified.
	void constructDefaultCommands(KeypressInvoker* invoker);

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

	API void onUpdate();

	API void updateFps();
	API void toggleFps();

	bool onKeyPressed(const Event& event);

	API bool getEngineRunning() { return running; };
	API void setEngineRunning(bool run) { running = run; }

	KeypressInvoker* getKeypressedInvoker() { return keypressInvoker; }

	API void restartPhysicsWorld();

private:
	EventDispatcher* eventDispatcher;
	bool running = false;

	FrameData frameData;
	KeypressInvoker* keypressInvoker;

	SceneManager sceneManager;
	ParticleEngine particleEngine;
	PhysicsEngine physicsEngine;
	SoundEngine soundEngine;

	VideoEngine videoEngine{ frameData };
	InputEngine inputEngine{ *this };

	bool engineIsPaused = false;
};
#endif
