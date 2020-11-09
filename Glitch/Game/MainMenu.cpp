#include "MainMenu.h"
#include "Events/Mouse/MousePressed.h"

void MainMenu::OnAttach()
{
	Button startBtn(1, "start", Color(0, 0, 0));

	startBtn.setSize(100, 50);

	startBtn.setPositionX(500);
	startBtn.setPositionY(500);

	auto startBtnClick = MainMenu::OnStartBtnClick;

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
