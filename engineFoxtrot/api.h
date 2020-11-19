#pragma once
// ----- events ----------------------
#include "Events/Event.h"
#include "Events/AppTickEvent30.h"
#include "Events/AppTickEvent60.h"

#include "Events/Action/OnCollisionEvent.h"
#include "Events/EventSingleton.h"

#include "Events/Sound/OnMusicStartEvent.h"
#include "Events/Sound/SoundAttachEvent.h"
#include "Events/Sound/OnMusicStopEvent.h"

#include "Events/Sound/PlaySoundEffectEvent.h"
#include "Events/Sound/StopSoundEffectEvent.h"


#include "Events/Window/WindowCloseEvent.h"
#include "Events/Mouse/MousePressed.h"
#include "Events/EventSingleton.h"
#include "Events/Video/VideoLoadSpriteEvent.h"
#include "Engine/Events/Action/ObjectStopEvent.h"
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
#include "Engine/SceneManager/Scene.h"
#include "Engine/SceneManager/SceneManager.h"
// ----- Objects / behavior --------------------
#include "Engine/SceneManager/Objects/Object.h"
#include "SceneManager/Objects/Drawable.h"
// ----- File loader --------------------
#include "Engine/FileParser/FileLoader.h"
// ----- main engine --------------------
#include "Engine/Engine.h"