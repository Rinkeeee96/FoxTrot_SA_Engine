#pragma once
#include "Game/PopUps/Ipopup.h"
#include "Game/Scenes/Statemachine/SceneStateMachine.h"

/// @brief Class for the Heads up display PopUp
class HudPopUp : public IPopup
{
public:
	HudPopUp(unique_ptr<Engine>& _engine, EventDispatcher& _dispatcher, shared_ptr<SceneStateMachine> _stateMachine)
		: IPopup(_engine, _dispatcher, _stateMachine) {};
	~HudPopUp() {};

	void setupPopUp() override;
	void cleanPopUp() override {};
	void onAttach() override {};
	void onDetach() override {};

	void onUpdate();

	void setPlayer(shared_ptr<Player> _player);
	void setBoss(shared_ptr<ICharacter> _boss);

	void addHealthHud(int& startingID, int& startingXAxis, int& xAxisChange, int& current, shared_ptr<SpriteObject> HUD);
	void addBossHud();

private:
	vector<shared_ptr<Drawable>> huds;

	shared_ptr<Player> player = nullptr;
	shared_ptr<ICharacter> boss = nullptr;
};


