#pragma once
#include "Game/Scenes/GameScene.h"
/// @brief Scene for the game info screen
class GameInfo : public GameScene
{
public:
	GameInfo(const int id, unique_ptr<Engine>& _engine, shared_ptr<SceneStateMachine> _statemachine) : GameScene(id, _engine, _statemachine) {};
	~GameInfo() { };

	// Inherited via GameScene
	virtual void onAttach() override;
	virtual void start(bool playSound) override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onDetach() override;

private:
	void loadText();
	void loadButtons();
	void loadBackground();
	vector<string> splitToLines(string stringToSplit, int maximumLineLength);
	vector<shared_ptr<Text>> splitText(string text, int startingId);

	vector<shared_ptr<Text>> text;
	function<void(void)> onBackClick = [this]() {
		moveToNextScene = true;
		nextScene = "MainMenu";
	};
};

