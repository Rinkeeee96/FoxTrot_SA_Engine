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
// TODO Weet niet of deze hier moet?!?!??! Is even voor de test
#include "Events/Codes/KeyCodes.h"

#define	ENGINE_TICK60	 17
#define ENGINE_TICK30	 33

/// @brief 
class Engine
{
public:
	API Engine();
	API ~Engine();

//private:
	/*API void engineTick60();
	API void engineTick30();*/
	API void startTickThreads();
	API void stopTickThreads();

	/*atomic_bool stopThreadTick60 = false;
	atomic_bool stopThreadTick30 = false;

	thread *engineTick60Thread = nullptr;
	thread *engineTick30Thread = nullptr;*/

	//SceneManager calls
	API void setCurrentScene(const int sceneID);
	API Scene* getCurrentScene();
	API void insertScene(Scene * scene);

	// Video calls
	API void loadSprite(const SpriteObject& spriteObject);
	API void attachCamera(const int objectId);

	// Sound calls
	API void loadSound(const string& identifier, const string& path);
	API void loadSound(map<string, string> sounds);

	// Input calls
	API void pollEvents();

	//Events
	API void EventListeners();
	API bool Event_LoadSprite(Event& event);
private:
	PhysicsEngine physicsEngine;
	ParticleEngine particleEngine;
	SoundEngine soundEngine;
	InputEngine inputEngine;
	SceneManager sceneManager;
	VideoEngine videoEngine;

	FrameData* frameData = nullptr;
};
#endif
