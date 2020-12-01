#pragma once
class PauseScreen : public Scene
{
public:
	PauseScreen();
	~PauseScreen();

	// Inherited via Scene
	void onAttach() override;
	void onDetach() override;
	void start() override;
	void onUpdate() override;
private:
	void loadBackground();
	void loadMusic();
	void loadButtons();

	//button functions
	//void onStartBtnClick();
	//void onStopBtnClick();
	//void onCreditsBtnClick();
	//void onLoadBtnClick();
	//Button* startBtn = nullptr;
	//Button* stopBtn = nullptr;

};

