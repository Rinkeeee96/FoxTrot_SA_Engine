#include "pch.h"
#include "SaveScreen.h"

#define BIND_FN(function) std::bind(&SaveScreen::function, *this)

#define CENTER_X  (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)

void SaveScreen::onAttach()
{
	loadButtons();
	loadBackground();
	loadMusic();

	string path = "Assets/SaveGame/saveGameData.json";
	Savegame::get_instance().readSaveGameDataFromJson(path);
}

void SaveScreen::onDetach()
{
	EventSingleton::get_instance().dispatchEvent<OnMusicStopEvent>((Event&)OnMusicStopEvent("MENU_SOUND"));
	Scene::onDetach();
}

void SaveScreen::start()
{
	EventSingleton::get_instance().dispatchEvent<OnMusicStartEvent>((Event&)OnMusicStartEvent("MENU_SOUND"));
}

void SaveScreen::onUpdate()
{
}

void SaveScreen::loadBackground()
{
	SpriteObject* BG_LAYER_0 = new SpriteObject(-999, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_0.png");
	SpriteObject* BG_LAYER_ADVENTRUE = new SpriteObject(-998, 37, 50, 6, 300, "Assets/Sprites/Character/adventure_run_right.png");
	SpriteObject* BG_LAYER_2 = new SpriteObject(-997, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_2.png");

	auto* layer0 = new Drawable(-992);
	layer0->setStatic(true);
	layer0->setPositionX(1);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);

	auto* animation = new Drawable(-991);
	animation->setStatic(true);
	animation->setPositionX(175);
	animation->setPositionY(875);
	animation->setWidth(370);
	animation->setHeight(500);
	animation->registerSprite(SpriteState::DEFAULT, BG_LAYER_ADVENTRUE);
	animation->changeToState(SpriteState::DEFAULT);
	animation->setScalable(false);

	auto* layer2 = new Drawable(-990);
	layer2->setStatic(true);
	layer2->setPositionX(1);
	layer2->setPositionY(1080);
	layer2->setWidth(1920);
	layer2->setHeight(1080);
	layer2->registerSprite(SpriteState::DEFAULT, BG_LAYER_2);
	layer2->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(0, layer0);
	addNewObjectToLayer(1, animation);
	addNewObjectToLayer(2, layer2);
}

void SaveScreen::loadMusic()
{
	EventSingleton::get_instance().dispatchEvent<SoundAttachEvent>((Event&)SoundAttachEvent("MENU_SOUND", "Assets/Sound/file_example_WAV_1MG.wav"));
}

void SaveScreen::loadButtons()
{
	Button* save1 = new PrimaryButton(-996, "Save 1", BIND_FN(onSave1BtnClick));
	save1->setPositionX(CENTER_X - save1->getWidth() / 2);
	save1->setPositionY(CENTER_Y - save1->getHeight() / 2);

	Button* save2 = new PrimaryButton(-995, "Save 2", BIND_FN(onSave2BtnClick));
	save2->setPositionX(CENTER_X - save2->getWidth() / 2);
	save2->setPositionY(CENTER_Y - save2->getHeight() / 2 + 100);
	save2->disable();

	Button* save3 = new PrimaryButton(-994, "Save 3", BIND_FN(onSave3BtnClick));
	save3->setPositionX(CENTER_X - save3->getWidth() / 2);
	save3->setPositionY(CENTER_Y - save3->getHeight() / 2 + 200);
	save3->disable();

	Button* stopBtn = new SecondaryButton(-993, "To Main Menu", BIND_FN(onStopBtnClick));
	stopBtn->setPositionX(WINDOW_WIDTH - 40 - stopBtn->getWidth());
	stopBtn->setPositionY(WINDOW_HEIGHT - 10 - stopBtn->getHeight());

	addNewObjectToLayer(3, save1);
	addNewObjectToLayer(3, save2);
	addNewObjectToLayer(3, save3);
	addNewObjectToLayer(3, stopBtn);
}

void SaveScreen::onSave1BtnClick()
{
	Savegame::get_instance().setCurrentGameData(1);
	SceneSwitcher::get_instance().switchToScene("OVERWORLD", false);
}

void SaveScreen::onSave2BtnClick()
{
	Savegame::get_instance().setCurrentGameData(2);
	SceneSwitcher::get_instance().switchToScene("OVERWORLD", true);
}

void SaveScreen::onSave3BtnClick()
{
	Savegame::get_instance().setCurrentGameData(3);
	SceneSwitcher::get_instance().switchToScene("OVERWORLD", true);
}

void SaveScreen::onStopBtnClick() {
	SceneSwitcher::get_instance().switchToScene("MAIN_MENU",false);
}