#pragma once
#include "Game/Scenes/GameScene.h"
#include "Game/Commands/Builder/ICommandBuilder.h"
#include "Game/States/Player/GodState.h"

class Player;
/// @brief 
/// Level class. Level has all the information. 
class Level : public GameScene
{
public:
	Level(const int id, const int _sceneHeight, const int _sceneWidth, unique_ptr<Engine>& engine, SceneStateMachine& _stateMachine);

	void setPlayer(Object* object);
	void setSound(map<string, string> sounds);
	void onAttach() override;
	void start(bool playSound) override;
	void pause();
	void onDetach() override;
	void onUpdate() override;

	void addHuds();

	bool onToggleLayerEvent(const Event& event);
	void setWin(const bool val) { this->win = val; }

private:
	void addHealthHud(int& startingID, int& startingXAxis, int& xAxisChange, int& current, SpriteObject* HUD);
	vector<Drawable*> huds;

	void throwAchievement(Achievement achievement);
	void increaseTotalGameScore(const int amount);

	Text* scoreText = nullptr;
	void loadScoreBoard();
	void updateScoreBoard();

	map<string, string> sounds;
	Object* follow = nullptr;
	Player* player = nullptr;
	bool win = false;

	ICommandBuilder* commandBuilder;
	GameKeypressInvoker* gameInvoker;
	int pausePopupZIndex = 0;
	int inventoryPopupZIndex = 0;
	int achievementZIndex = 0;

	bool inventoryOpen = false;
	bool activeAchievementPopup = false;
	chrono::high_resolution_clock::time_point timeAchievementPopupThrown;

	float startPosPlayerX = 0;
	float startPosPlayerY = 0;
};