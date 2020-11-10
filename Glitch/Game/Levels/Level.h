#pragma once
#include <api.h>
#include "SceneManager/Scene.h"
#include "Events/EventSingleton.h"
#include "Events/Sound/OnMusicStartEvent.h"
#include "Events\Sound\SoundAttachEvent.h"
#include "Events\Sound\OnMusicStopEvent.h"

/// @brief 
/// Level class. Level has all the information. 

#if(EXPORT)
class DLLEXPORT Level : public Scene
#else
class Level : public Scene
#endif
{
public:
	Level(const int id, map<string, string> sounds);
	Level(const int id);

	virtual void setSound(map<string, string> sounds);
	virtual void onAttach() override;
	virtual void start() override;
	virtual void pause();
	virtual void onDetach() override;
	virtual void onUpdate() override;
private:
	map<string, string> sounds;
};