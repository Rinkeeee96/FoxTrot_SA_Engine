#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "Game/Scenes/Story/ChapterScene/ChapterScene.h"

/// @brief Class for the chapter one screen
class ChapterOneScene : public ChapterScene
{
public:
	ChapterOneScene(const int id, unique_ptr<Engine>& _engine, shared_ptr<SceneStateMachine> _statemachine) : ChapterScene(id, _engine, _statemachine) {};
	~ChapterOneScene() { };
	// Inherited via Scene
	void onAttach() override;
	void start(bool playSound) override;
	void onUpdate(float deltaTime) override { ChapterScene::onUpdate(deltaTime); };
	void onDetach() override;
protected:
	void loadText() override;
	void loadBackground() override;
	void loadMusic() override;
};
