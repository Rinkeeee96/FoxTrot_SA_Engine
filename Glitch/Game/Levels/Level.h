#pragma once
#include "Game/Characters/Player/Player.h"
#include "Game/Scenes/GameScene.h"
#include "Game/States/Player/GodState.h"
/// @brief 
/// Level class. Level has all the information. 
class Level : public GameScene
{
public:
	Level(const int id, const int _sceneHeight, const int _sceneWidth, Engine& engine, SceneStateMachine& _stateMachine);

	void setPlayer(Object* object);
	void setSound(map<string, string> sounds);
	void onAttach() override;
	void start(bool playSound) override;
	void pause();
	void onDetach() override;
	void onUpdate() override;

	void addHuds();

	bool onKeyPressed(const Event& event);
	void setWin(const bool val) { this->win = val; }

private:
	void addHealthHud(int& startingID, int& startingXAxis, int& xAxisChange, int& current, SpriteObject* HUD);
	vector<Drawable*> huds;

	map<string, string> sounds;
	Object* follow = nullptr;
	Player* player = nullptr;
	bool win = false;

	int pausePopupZIndex = 0;
	int inventoryPopupZIndex = 0;

	bool inventoryOpen = false;

	float startPosPlayerX = 0;
	float startPosPlayerY = 0;
};