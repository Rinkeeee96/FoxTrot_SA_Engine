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

/// @brief 
class Engine
{
public:
	API Engine();
	API ~Engine();

	//SceneManager calls
	API void setCurrentScene(const int sceneID);
	API Scene* getCurrentScene();
	bool onKeyPressed(const Event& event);
	API void insertScene(Scene * scene);
	API void deregisterScene(const int id);

	// Sound calls
	API void loadSound(const string& identifier, const string& path);
	API void loadSound(map<string, string> sounds);

	bool getPhysicsPaused();

	// Input calls
	API void pollEvents();

	API void onUpdate();

	API void updateFps();
	API void toggleFps();

	API bool getEngineRunning() { return running; };
	API void setEngineRunning(bool run) { running = run; }

	API void restartPhysicsWorld();

	API float getDeltaTime();

	//API EventDispatcher& getDispatcher() { return *eventDispatcher; }
	
	SoundEngine soundEngine;

private:
	float deltaTime = 0;

	EventDispatcher* eventDispatcher;
	bool running = false;

	FrameData frameData;
	
	SceneManager sceneManager;
	ParticleEngine particleEngine;
	PhysicsEngine physicsEngine{ frameData };

	VideoEngine videoEngine{ frameData };
	InputEngine inputEngine{ *this };

	bool engineIsPaused = false;
};
#endif
