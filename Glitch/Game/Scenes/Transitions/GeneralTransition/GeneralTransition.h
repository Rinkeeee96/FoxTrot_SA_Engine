#pragma once
#include "Game/Scenes/GameScene.h"
#include "Game/AdvertisementHandler/AdvertisementHandler.h"

#define TRANSITION_SCENE_DURATION_S		3

/// @brief Transition Screen
class GeneralTransition : public GameScene
{
public:
	GeneralTransition(const int id, unique_ptr<Engine>& engine, shared_ptr<SceneStateMachine> _statemachine) : GameScene(id, engine, _statemachine) 
	{
		adHandler = unique_ptr<AdvertisementHandler>(new AdvertisementHandler());
	};
	~GeneralTransition() {};

	// Inherited via Scene
	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void start(bool playSound) override;
	virtual void onUpdate(float deltaTime) override;

	void setNextScene(string const identifier);

private:

	string getRandomAdFileName();

	void loadBackground();
	shared_ptr<Drawable> animation = nullptr;

	unique_ptr<AdvertisementHandler> adHandler;

	string nextScene = "";
	float timer = 0;
};


