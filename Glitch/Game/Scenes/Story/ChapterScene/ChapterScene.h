#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "Game/Scenes/GameScene.h"

class ChapterScene : public GameScene
{
public:
	ChapterScene(const int id, Engine& _engine, SceneStateMachine& _statemachine);
	virtual ~ChapterScene() { };
	// Inherited via Scene
	virtual void onAttach() override {};
	virtual void onDetach() override {};
	virtual void start(bool playSound) override {};
	void onUpdate() override {};

	bool onKeyPressed(const Event& event);
protected:
	vector<Text*> text;

	virtual void loadText() {};
	virtual void loadBackground() {};
	virtual void loadMusic() {};

	void loadButtons();
	void onSkipClick();

	vector<string> splitToLines(string stringToSplit, int maximumLineLength);
	vector<Text*> splitText(string text);
	int speed_ = 1;
};
