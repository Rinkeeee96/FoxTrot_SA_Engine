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

	//SceneManager calls
	API void setCurrentScene(const int sceneID);
	API Scene* getCurrentScene();
	bool onKeyPressed(const Event& event);
	API void insertScene(Scene * scene);
	API void deregisterScene(const int id);

	API void onUpdate();

	API bool getEngineRunning() { return running; };
	API void setEngineRunning(bool run) { running = run; }

	SoundEngine& getSoundEngine() { return soundEngine; };
	VideoEngine& getVideoEngine() { return videoEngine; };
	PhysicsEngine& getPhysicsEngine() { return physicsEngine; }
	FrameData& getFrameData() { return frameData; }

private:
	EventDispatcher* eventDispatcher;
	bool running = false;

	FrameData frameData;

	SoundEngine soundEngine;
	SceneManager sceneManager;
	ParticleEngine particleEngine;
	PhysicsEngine physicsEngine;
	VideoEngine videoEngine{ frameData };
	InputEngine inputEngine{ *this };

	bool engineIsPaused = false;
};
#endif
