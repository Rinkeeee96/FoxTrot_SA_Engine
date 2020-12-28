#include "pch.h"
#include "HudPopUp.h"

void HudPopUp::setupPopUp()
{
	setAlwaysVisible(true);
}

void HudPopUp::cleanPopUp()
{
}

void HudPopUp::onAttach()
{
}

void HudPopUp::onDetach()
{
}

void HudPopUp::onUpdate()
{
	this->huds.clear();
	// Health HUDS
	int startingID = -662;
	int xAxisChange = 75;
	int startingXAxis = 25;
	int current = 0;
	shared_ptr<SpriteObject> HealthHUD = shared_ptr<SpriteObject>(new SpriteObject(-660, 50, 50, 1, 300, "Assets/Sprites/HUD/Full.png"));
	shared_ptr<SpriteObject> EmptyHealthHUD = shared_ptr<SpriteObject>(new SpriteObject(-661, 50, 50, 1, 300, "Assets/Sprites/HUD/Empty.png"));

	for (size_t i = 0; i < player->getCurrentHealth(); i++)
	{
		this->addHealthHud(startingID, startingXAxis, xAxisChange, current, HealthHUD);
	}
	int damageTaken = player->getTotalHealth() - player->getCurrentHealth();
	for (size_t i = 0; i < damageTaken; i++)
	{
		this->addHealthHud(startingID, startingXAxis, xAxisChange, current, EmptyHealthHUD);
	}
	if (boss.get()) {
		this->addBossHud();
	}
}

void HudPopUp::setPlayer(shared_ptr<Player> _player)
{
	player = _player;
}

void HudPopUp::setBoss(shared_ptr<ICharacter> _boss)
{
	boss = _boss;
}

void HudPopUp::addHealthHud(int& startingID, int& startingXAxis, int& xAxisChange, int& current, shared_ptr<SpriteObject> HUD) {
	shared_ptr<Drawable> health = shared_ptr<Drawable>(new Drawable(startingID--));
	health->setStatic(true);
	health->setPositionX(((startingXAxis + (float)(xAxisChange * (current + 1)))));
	health->setPositionY(100);
	health->setWidth(50);
	health->setHeight(50);
	health->setDrawStatic(true);
	health->registerSprite(SpriteState::DEFAULT, HUD);
	health->changeToState(SpriteState::DEFAULT);

	addObjectInLayer(health);
	this->huds.push_back(health);
	current++;
}

void HudPopUp::addBossHud() {
	shared_ptr<SpriteObject> PROGRESSBAR_EMPTY = shared_ptr<SpriteObject>(new SpriteObject(-503, 24, 192, 1, 1, "Assets/LoadingBar/progress-bar-empty.png"));
	shared_ptr<SpriteObject> PROGRESSBAR_FULL = shared_ptr<SpriteObject>(new SpriteObject(-504, 24, 192, 1, 1, "Assets/LoadingBar/progress-bar-full.png"));

	shared_ptr<Drawable> filler = shared_ptr<Drawable>(new Drawable(-1230));
	filler->setStatic(true);
	filler->setPositionX(500);
	filler->setPositionY(150 - 35);
	filler->setHeight(55);
	filler->setDrawStatic(true);
	filler->registerSprite(SpriteState::DEFAULT, PROGRESSBAR_FULL);
	filler->changeToState(SpriteState::DEFAULT);

	auto w = 920 / this->boss->getTotalHealth();
	filler->setWidth(w * this->boss->getCurrentHealth());

	shared_ptr<Drawable> health = shared_ptr<Drawable>(new Drawable(-1233));
	health->setStatic(true);
	health->setPositionX(460);
	health->setPositionY(150);
	health->setWidth(1000);
	health->setHeight(125);
	health->setDrawStatic(true);
	health->registerSprite(SpriteState::DEFAULT, PROGRESSBAR_EMPTY);
	health->changeToState(SpriteState::DEFAULT);

	addObjectInLayer(health);
	this->huds.push_back(health);
	addObjectInLayer(filler);
	this->huds.push_back(filler);
}
