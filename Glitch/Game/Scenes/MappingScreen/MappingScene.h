#pragma once
#include "Game/Scenes/GameScene.h"
#include "Game/Commands/GameKeypressInvoker.h"
#include "Game/Commands/Builder/CommandBuilder.h"

class MappingScene : public GameScene
{
public:
	MappingScene(const int id, unique_ptr<Engine>& engine, shared_ptr<SceneStateMachine> _statemachine) : GameScene(id, engine, _statemachine) {
		invoker = (GameKeypressInvoker*)engine->getKeypressedInvoker();
	};
	~MappingScene() {};

	void onAttach() override;
	void onDetach() override;
	void start(bool playSound) override;
	virtual void onUpdate(float deltaTime) override;

private:
	int textId = -1;
	float listStartX = 200;
	float listStartY = 400;
	int blockId = 1;

	void loadBackground();
	void loadMusic();
	void loadButtons();
	void loadSaveGame();

	void parseKeycodeList(unordered_map<KeyCode, string> parseList, const string& header);
	GameKeypressInvoker* invoker = nullptr;
	CommandBuilder builder;

	void createButtons();

	void updatePlayerCommand(const string& identifier);
	void updateGlobalCommand(const string& identifier);


	function<void(void)> onGodModeBtnClick = [this]() {
		updatePlayerCommand("godmode");
	};

	function<void(void)> onJumpBtnClick = [this]() {
		updatePlayerCommand("jump");
	};

	function<void(void)> onMoveLeftBtnClick = [this]() {
		updatePlayerCommand("moveLeft");
	};

	function<void(void)> onMoveRightBtnClick = [this]() {
		updatePlayerCommand("moveRight");
	};

	function<void(void)> onInventoryBtnClick = [this]() {
		updateGlobalCommand("inventory");
	};

	function<void(void)> onPauseBtnClick = [this]() {
		updateGlobalCommand("pause");
	};

	function<void(void)> onHelpBtnClick = [this]() {
		updateGlobalCommand("help");
	};

	function<void(void)> onFasterBtnClick = [this]() {
		updateGlobalCommand("faster");
	};

	function<void(void)> onSlowerBtnClick = [this]() {
		updateGlobalCommand("slower");
	};

	function<void(void)> onStopBtnClick = [this]() {
		moveToNextScene = true;
		nextScene = "MainMenu";
	};
};
