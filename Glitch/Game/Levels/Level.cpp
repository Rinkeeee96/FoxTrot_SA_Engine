#include "pch.h"
#include "Level.h"
#include "Game/Game.h"
#include "Game/PopUps/Popups.h"

Level::Level(const int id, const int _sceneHeight, const int _sceneWidth, Engine& engine, SceneStateMachine& _stateMachine) 
				: GameScene::GameScene(id, _sceneHeight, _sceneWidth, engine, _stateMachine)
{
	this->dispatcher.setEventCallback<KeyPressedEvent>(BIND_EVENT_FN(Level::onKeyPressed));
}

bool Level::onKeyPressed(const Event& event) {
	if (this->win || this->player->getIsDead()) return false;

	auto keyPressedEvent = static_cast<const KeyPressedEvent&>(event);
	// TODO command pattern
	switch (keyPressedEvent.getKeyCode())
	{
	case KeyCode::KEY_P:
		if (!paused) {
			PausePopUp* pausePopUp = new PausePopUp(this->dispatcher, this->stateMachine);
			pausePopUp->setupPopUp();
			pausePopupZIndex = addLayerOnHighestZIndex(pausePopUp);
			this->paused = true;
		}
		else
		{
			removeLayer(pausePopupZIndex);
			this->paused = false;
		}
		break;
	case KeyCode::KEY_I:
		if (!inventoryOpen) {
			InventoryPopup* inventoryPopup = new InventoryPopup(this->dispatcher, this->stateMachine);
			inventoryPopup->setupPopUp();
			inventoryPopupZIndex = addLayerOnHighestZIndex(inventoryPopup);
			inventoryOpen = true;
		}
		else
		{
			removeLayer(inventoryPopupZIndex);
			inventoryOpen = false;
		}
		break;
	case KeyCode::KEY_G:
		if (this->player != nullptr && 
			typeid(this->player->getStateMachine().getCurrentState()).name() != typeid(GodState).name()) 
		{
			this->player->getStateMachine().changeState(new GodState, this->player);
		}
		else {
			this->player->getStateMachine().changeState(new NormalState, this->player);
		}
		break;
	default:
		break;
	}
	return false;
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
        engine.loadSound(s.first, s.second);
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
/// Activates the achievement popup and adds the Achievement param to the Achievement vector. If a achievement is already given, it wont be added or shown.
/// @param achievement 
void Level::throwAchievement(Achievement achievement)
{
	if (savegame->getCurrentGameData().isAchievementAchieved(achievement)) return;
	AchievementPopup* achievementPopup = new AchievementPopup(this->dispatcher, this->stateMachine);
	achievementPopup->setupPopUp(achievement);
	achievementZIndex = addLayerOnHighestZIndex(achievementPopup);

	activeAchievementPopup = true;

	SaveGameData temp = savegame->getCurrentGameData();
	temp.achievements.push_back(achievement);
	savegame->saveCurrentGameData(temp);

	timeAchievementPopupThrown = chrono::high_resolution_clock::now();
}

/// @brief 
/// Increases the total and level score by given amount
/// @param amount 
void Level::increaseTotalGameScore(const int amount)
{
	SaveGameData temp = savegame->getCurrentGameData();
	temp.levelData[stateMachine.levelToBuild - 1].score += amount;
	temp.totalScore += amount;
	savegame->saveCurrentGameData(temp);
}

/// @brief 
/// Loads the scoreboard located in the top right corner.
void Level::loadScoreBoard()
{
	SpriteObject* emptyBlock = new SpriteObject(-2500, 309, 253, 1, 300, "Assets/Inventory/text_background.png");
	auto* block1 = new Drawable(-2501);
	block1->setStatic(true);
	block1->setDrawStatic(true);
	block1->setPositionX(1600);
	block1->setPositionY(120);
	block1->setWidth(300);
	block1->setHeight(100);
	block1->registerSprite(SpriteState::DEFAULT, emptyBlock);
	block1->changeToState(SpriteState::DEFAULT);

	int textIDCount = 100;

	auto* text2 = new Text(textIDCount++, new ColoredText(savegame->getCurrentGameData().saveGameName + " " + savegame->getCurrentGameData().getReadableTimeStamp(), Color(0, 0, 0)), 200, 30, 1550, 40);
	text2->setDrawStatic(true);
	addNewObjectToLayer(5, text2, false, true);


	scoreText = new Text(textIDCount++, new ColoredText("TotalScore: " + to_string(savegame->getCurrentGameData().totalScore), Color(0, 0, 0)), 200, 30, 1550, 90);
	scoreText->setDrawStatic(true);
	addNewObjectToLayer(5, scoreText, false, true);

	addNewObjectToLayer(4, block1, false, true);
}

/// @brief 
/// Updates the scoreboard
void Level::updateScoreBoard()
{
	string text = "TotalScore: " + to_string(savegame->getCurrentGameData().totalScore);
	scoreText->changeText(text);
}

/// @brief
/// Start is called when a scene is ready to execute its logic, this can be percieved as the "main loop" of a scene
void Level::start(bool playSound) {
	player->respawn();
	player->setCurrentHealth(3);
	player->setTotalHealth(3);
	this->addHuds();
	loadScoreBoard();
	this->win = false;

	this->setObjectToFollow(this->follow);
	if (playSound)
	{
		for (const auto& s : sounds) {
			engine.startSound(s.first);
		}
	}
}

void Level::onUpdate() {
	this->addHuds();

	updateScoreBoard();

	chrono::duration<double> diffFromPreviousCall = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - timeAchievementPopupThrown);

	if (diffFromPreviousCall.count() > 1 && activeAchievementPopup)
	{
		removeLayer(achievementZIndex);
		activeAchievementPopup = false;
	}

	if (this->win) {
		player->kill();
		increaseTotalGameScore(100);
		throwAchievement("Level " + to_string(stateMachine.levelToBuild -1) + " completed!");
		SaveGameData save = savegame->getCurrentGameData();
		save.levelData[stateMachine.levelToBuild].completed = true;
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
					increaseTotalGameScore(10);
					throwAchievement("First Kill");
				}
			}
		}
	}
}

/// @brief
/// Execute pause logic
void Level::pause() {
	for (const auto& s : sounds) {
		engine.stopLoopEffect(s.first);
	}
}

void Level::onDetach() 
{
	Scene::onDetach();
}