#pragma once

// ----- events ----------------------
#include "Events/Event.h"
#include "Events/AppTickEvent30.h"
#include "Events/AppTickEvent60.h"

#ifndef RUN_UNIT_TESTS
#include "Events/Action/OnCollisionEvent.h"
#include "Events/EventSingleton.h"
#endif

// ----- engine core ----------------------
#include "Engine/General/ErrorCodes.h"
// ----- individual engines ----------------
#include "Engine/ParticleSystem/ParticleEngine.h"
#include "Engine/Physics/PhysicsEngine.h"
#include "Engine/Video/VideoEngine.h"
#include "Engine/Sound/SoundEngine.h"
#include "Engine/Input/InputEngine.h"
// ----- commands -------------------------

// ----- scene manager --------------------
#include "Engine/SceneManager/Layer.h"
#include "Engine/SceneManager/Object.h"
#include "Engine/SceneManager/Scene.h"
#include "Engine/SceneManager/SceneManager.h"
// ----- main engine --------------------
#include "Engine/Engine.h"