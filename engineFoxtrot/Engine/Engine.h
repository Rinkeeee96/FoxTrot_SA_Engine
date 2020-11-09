#pragma once

#ifndef ENGINE__H
#define ENGINE__H

#include "./SceneManager/SceneManager.h"
#include "./FileParser/FileParser.h"
#include "./Physics/PhysicsEngine.h"
#include "./ParticleSystem/ParticleEngine.h"
#include "./SceneManager/SceneManager.h"

#include "Events/EventSingleton.h"
#include "./Video/VideoEngine.h"
#include "./Sound/SoundEngine.h"
#include "./Input/InputEngine.h"
#include "./Fps/FrameData.h"
// TODO Weet niet of deze hier moet?!?!??! Is even voor de test
#include "Events/Codes/KeyCodes.h"

#define	ENGINE_TICK60	 17
#define ENGINE_TICK30	 33

/// @brief 
class API Engine
{
public:
	Engine();
	~Engine();

//private:
	void engineTick60();
	void engineTick30();
	void startTickThreads();
	void stopTickThreads();

	atomic_bool stopThreadTick60 = false;
	atomic_bool stopThreadTick30 = false;

	thread *engineTick60Thread = nullptr;
	thread *engineTick30Thread = nullptr;

	//SceneManager calls
	void setCurrentScene(const int sceneID);
	void insertScene(Scene * scene);

	// Video calls
	void loadSprite(const SpriteObject& spriteObject);

	// Input calls
	void pollEvents();
private:
	PhysicsEngine physicsEngine;
	ParticleEngine particleEngine;
	SoundEngine soundEngine;
	InputEngine inputEngine;
	//FileParser fileParser;
	SceneManager sceneManager;
	VideoEngine videoEngine;
	FrameData* frameData = nullptr;
};
#endif
