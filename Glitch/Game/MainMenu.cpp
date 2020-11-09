#include "MainMenu.h"
#include "Events/Mouse/MousePressed.h"

#define BIND_FN(function) std::bind(&MainMenu::function, *this)

void MainMenu::OnAttach()
{
	Button startBtn(1, "start", Color(0, 0, 0), BIND_FN(OnStartBtnClick));
	startBtn.setSize(100, 50);
	startBtn.setPositionX(500);
	startBtn.setPositionY(500);

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
