#include "MainMenu.h"
#include "Events/Mouse/MousePressed.h"

#define BIND_FN(function) std::bind(&MainMenu::function, *this)
#define CENTER_X  1920 / 2
#define CENTER_Y 1080 / 2



void MainMenu::OnAttach()
{
	Button startBtn(1, "start", Color(0, 0, 0), BIND_FN(OnStartBtnClick));
	startBtn.setSize(100, 50);

	startBtn.setPositionX(CENTER_X);
	startBtn.setPositionY(CENTER_Y);

	addNewObjectToLayer(1, &startBtn);
}

void MainMenu::Start()
{
}

void MainMenu::OnDetach()
{
}

void MainMenu::OnStartBtnClick()
{
	cout << "clickeroo" << endl;
}
