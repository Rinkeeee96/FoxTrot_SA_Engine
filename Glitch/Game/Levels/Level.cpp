#include "pch.h"
#include "Level.h"
#include "Game/Game.h"

Level::Level(const int id, const int _sceneHeight, const int _sceneWidth, Engine& engine, SceneStateMachine& _stateMachine) : GameScene::GameScene(id, _sceneHeight, _sceneWidth, engine, _stateMachine)
{

}

// @brief 
/// Sets player in the level the camera will follow this object
/// @param Object player
void Level::setPlayer(Object* object) {
	this->follow = object;
	if (Player* _player = dynamic_cast<Player*>(object)) {
		this->player = _player;
		startPosPlayerX = _player->getPositionX();
		startPosPlayerY = _player->getPositionY();
	}
	else {
		throw exception("not a player object");
	}
}

// @brief 
/// Register sounds by the level
/// @param sound map 
void Level::setSound(map<string, string> _sounds)
{
	sounds = _sounds;
}

/// @brief
/// OnAttach is executed when a scene is "attached" to the current running context
/// usually this is can be used to prime a level with relevant data before starting it.
void Level::onAttach() {
    for (const auto& s : sounds) {
		if(DEBUG_MAIN)std::cout << s.first << " has value " << s.second << std::endl;
        engine.soundEngine.onLoadBackgroundMusicEvent(s.first, s.second);
    }
}

/// @brief
/// Add HUD for lifes of player
void Level::addHuds() {
	this->huds = std::vector<Drawable*>();
	// Health HUDS
	int startingID = -662;
	int xAxisChange = 75;
	int startingXAxis = 25;
	int current = 0;
	SpriteObject* HealthHUD = new SpriteObject(-660, 50, 50, 1, 300, "Assets/Sprites/HUD/Full.png");
	SpriteObject* EmptyHealthHUD = new SpriteObject(-661, 50, 50, 1, 300, "Assets/Sprites/HUD/Empty.png");

	for (size_t i = 0; i < player->getCurrentHealth(); i++)
	{
		this->addHealthHud(startingID, startingXAxis, xAxisChange, current, HealthHUD);
	}
	int damageTaken = player->getTotalHealth() - player->getCurrentHealth();
	for (size_t i = 0; i < damageTaken; i++)
	{
		this->addHealthHud(startingID, startingXAxis, xAxisChange, current, EmptyHealthHUD);
	}
}

/// @brief
/// Add single HUD for lifes of player
void Level::addHealthHud(int& startingID, int& startingXAxis, int& xAxisChange, int& current, SpriteObject* HUD) {
	auto* health = new Drawable(startingID--);
	health->setStatic(true);
	health->setPositionX(((startingXAxis + (float)(xAxisChange * (current + 1)))));
	health->setPositionY(100);
	health->setWidth(50);
	health->setHeight(50);
	health->setDrawStatic(true);
	health->registerSprite(SpriteState::DEFAULT, HUD);
	health->changeToState(SpriteState::DEFAULT);
	
	addNewObjectToLayer(100, health, false, true);
	this->huds.push_back(health);
	current++;
}

/// @brief
/// Start is called when a scene is ready to execute its logic, this can be percieved as the "main loop" of a scene
void Level::start(bool playSound) {
	player->respawn();
	player->setCurrentHealth(3);
	player->setTotalHealth(3);
	this->addHuds();
	this->win = false;

	this->setObjectToFollow(this->follow);
	if (playSound)
	{
		for (const auto& s : sounds) {
			engine.soundEngine.onStartBackgroundMusicEvent(s.first);
		}
	}

}

void Level::onUpdate() {
	this->addHuds();

	if (this->win) {
		player->kill();
		SaveGameData save = savegame->getCurrentGameData();
		save.levelData[stateMachine.levelToBuild -1].completed = true;
		savegame->saveCurrentGameData(save);
		stateMachine.switchToScene("WinScreen", false);
		return;
	}
	if (player->getIsDead()) {
		stateMachine.switchToScene("DeathScreen", false);
		return;
	}

	for (auto object : this->getAllObjectsInScene()) // TODO get only the non static objects, without looping thru them again and again
	{
		if (!object->getStatic()) {
			object->onUpdate();

			if (ICharacter* character = dynamic_cast<ICharacter*>(object)) {
				if (character->getIsDead() && !character->getIsRemoved()) {
					// TODO Death animation
					object->setIsRemoved(true);
					removeObjectFromScene(object);
					engine.restartPhysicsWorld();
				}
			}
		}
	}
}

/// @brief
/// Execute pause logic
void Level::pause() {
	for (const auto& s : sounds) {
		engine.soundEngine.onStopLoopedEffect(s.first);
	}
}

void Level::onDetach() 
{
	Scene::onDetach();
}//cleaup buffer