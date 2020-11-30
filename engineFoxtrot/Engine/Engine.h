#pragma once

#ifndef ENGINE__H
#define ENGINE__H

#include "./SceneManager/SceneManager.h"
#include "./Physics/PhysicsEngine.h"
#include "./ParticleSystem/ParticleEngine.h"
#include "./SceneManager/SceneManager.h"

#include "Events/EventSingleton.h"
#include "./Video/VideoEngine.h"
#include "./Sound/SoundEngine.h"
#include "./Input/InputEngine.h"
#include "./Fps/FrameData.h"

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
	API void insertScene(Scene * scene);
	API void deregisterScene(const int id);

	// Video calls
	API void loadSprite(const SpriteObject& spriteObject);

	// Sound calls
	API void loadSound(const string& identifier, const string& path);
	API void loadSound(map<string, string> sounds);

	// Input calls
	API void pollEvents();

	API void onUpdate();

	API void updateFps();
	API void toggleFps();

	API bool getEngineRunning() { return running; };
	API void setEngineRunning(bool run) { running = run; }
private:

	bool running = false;

	PhysicsEngine physicsEngine;
	ParticleEngine particleEngine;
	SoundEngine soundEngine;
	InputEngine inputEngine = InputEngine(*this);
	SceneManager sceneManager;
	FrameData frameData;
	VideoEngine videoEngine = VideoEngine(frameData);
};
#endif
