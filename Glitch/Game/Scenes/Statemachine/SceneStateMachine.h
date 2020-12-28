#pragma once
#include "Game/Scenes/Factory/FactoryMethod.h"
#include "Game/Scenes/Scenes.h"
#include "Game/Scenes/Factory/CreatorImpl.h"
class IPopup;
class Savegame;

/// @brief Class for the scene state machine
class SceneStateMachine : public enable_shared_from_this<SceneStateMachine>
{
public:
	SceneStateMachine(unique_ptr<Engine>& engine, shared_ptr<Savegame> savegame);
	~SceneStateMachine();

	void switchToScene(string const identifier, bool useTransitionScreen, bool playSound = true);

	string& getCurrentLevelIdentifier();

	void registerActivePopup(IPopup* popup) {
		activePopups.push_back(popup);
	}

	int activePopupCount() { return activePopups.size(); }

	void deregisterActivePopup(IPopup* popupToDeregister) {

		/*auto el = std::find(activePopups.begin(), activePopups.end(), popupToDeregister);
		auto p = std::remove_if(activePopups.begin(), el, (popupToDeregister == *el));

		activePopups.erase(p, el);*/


		activePopups.erase(
			std::remove_if(
				activePopups.begin(),
				activePopups.end(),
				[&popupToDeregister](const auto& p) { return popupToDeregister == p; }
			),
			activePopups.end()
		);
	}

	int levelToBuild = 0;
private:

	shared_ptr<Savegame> savegame;
	shared_ptr<SceneFactory>  factory = nullptr;

	unique_ptr<Scene> loadLevel(const string& identifier);
	unique_ptr<Engine>& engine;

	vector<IPopup*> activePopups;

	int currentSceneId = -1;
	int sceneId = 0;
	string currentLevelIdentifier = "";
};