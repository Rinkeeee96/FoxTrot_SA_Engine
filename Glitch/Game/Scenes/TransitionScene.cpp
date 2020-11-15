#include "TransitionScene.h"

void TransitionScene::OnAttach()
{
	LoadBackground();
	SceneSwitcher::get_instance().SwitchToScene("GAME");
}

void TransitionScene::OnDetach()
{

}

void TransitionScene::Start()
{
	
}

void TransitionScene::LoadBackground()
{

}

void TransitionScene::run()
{

}