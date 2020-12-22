#pragma once
#include "Game/Scenes/GameScene.h"
#include "Game/Commands/Builder/ICommandBuilder.h"
#include "Game/States/Player/GodState.h"

class IEnemy;
class Player;
/// @brief 
/// Level class. Level has all the information. 
class Level : public GameScene
{
public:
	Level(const int id, const int _sceneHeight, const int _sceneWidth, unique_ptr<Engine>& engine, shared_ptr<SceneStateMachine> _stateMachine);

	void setPlayer(shared_ptr<Object> object);
	void setBoss(shared_ptr<ICharacter> object) { this->boss = object; };
	Player& getPlayer() { return *this->player.get(); };
	ICharacter& getBoss() { return *this->boss.get(); };
	void setSound(map<string, string> sounds);
	void onAttach() override;
	void start(bool playSound) override;
	void pause();
	void onDetach() override;
	void onUpdate(float deltaTime) override;

	void addHuds();
	void addBossHud();

	bool onToggleLayerEvent(const Event& event);
	void setWin(const bool val) { this->win = val; }
	bool getWin() const { return this->win; }

protected:
	void addHealthHud(int& startingID, int& startingXAxis, int& xAxisChange, int& current, shared_ptr<SpriteObject> HUD);
	vector<shared_ptr<Drawable>> huds;

	void throwAchievement(Achievement achievement);
	void increaseTotalGameScore(const int amount);

	shared_ptr<Text> scoreText = nullptr;
	void loadScoreBoard();
	void updateScoreBoard();

	map<string, string> sounds;
	shared_ptr<Object> follow = nullptr;
	shared_ptr<Player> player = nullptr;
	shared_ptr<ICharacter> boss = nullptr;
	bool win = false;

	shared_ptr<ICommandBuilder> commandBuilder;
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