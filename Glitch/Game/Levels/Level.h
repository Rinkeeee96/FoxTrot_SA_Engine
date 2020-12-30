#pragma once
#include "Game/Scenes/GameScene.h"
#include "Game/Commands/Builder/ICommandBuilder.h"
#include "Game/States/Player/GodState.h"

class IEnemy;
class InventoryPopup;
class HudPopUp;
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

	void restartPhysics();
	bool onToggleLayerEvent(const Event& event);
	void setWin(const bool val) { this->win = val; }
	bool getWin() const { return this->win; }

	void changeToScene(bool shouldChange, string _next); 
protected:
	bool shouldChangeToScene = false;
	int levelScore = 0;
	string next;
	shared_ptr<InventoryPopup> inventoryPopup = nullptr;
	shared_ptr<HudPopUp> hudPopUp = nullptr;

	void throwAchievement(Achievement achievement);
	void increaseTotalGameScore(const int amount);
	void handleLevelScore();

	shared_ptr<Text> scoreText = nullptr;
	shared_ptr<Text> helpText = nullptr;
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
	int helpPopupZIndex = 0;
	int hudPopUpZIndex = 0;

	int achievementZIndex = 0;

	bool activeAchievementPopup = false;
	chrono::high_resolution_clock::time_point timeAchievementPopupThrown;

	float startPosPlayerX = 0;
	float startPosPlayerY = 0;
	bool shouldRestart  = false;

	bool init = true;
};
