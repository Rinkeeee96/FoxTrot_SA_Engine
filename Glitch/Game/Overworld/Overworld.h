#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "../../SceneSwitcher/SceneSwitcher.h"

/// @brief 
/// Overworld level
class Overworld : public Scene
{
public:
	Overworld(const int id) : Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH) {};
	~Overworld();
	// Inherited via Scene
	void OnAttach() override;
	void OnDetach() override;
	void OnLevel1BtnClick();
	void OnLevel2BtnClick();
	void Start() override;
	virtual void update() override;

private:
	void LoadBackground();
	void LoadMusic();
	void LoadButtons();

	//button functions
	void OnStartBtnClick();
	void OnStopBtnClick();
	void OnCreditsBtnClick();
	void OnLoadBtnClick();
};

inline Overworld::~Overworld()
{
}