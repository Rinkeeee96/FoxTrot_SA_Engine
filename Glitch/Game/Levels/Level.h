#pragma once
#include <api.h>
#include "SceneManager/Scene.h"
#include "Events/EventSingleton.h"
#include "Events/Sound/OnMusicStartEvent.h"
#include "Events\Sound\SoundAttachEvent.h"
#include "Events\Sound\OnMusicStopEvent.h"

/// @brief 
/// Level class. Level has all the information. 
/// 
class Level : public Scene
{
public:
	Level(const int id, const int _sceneHeight, const int _sceneWidth, map<string, string> _sounds);
	Level(const int id, const int _sceneHeight, const int _sceneWidth);

	virtual void setSound(map<string, string> sounds);
	virtual void onAttach() override;
	virtual void start() override;
	virtual void pause();
	virtual void OnDetach() override;
	virtual void onUpdate() override;
private:
	map<string, string> sounds;
};