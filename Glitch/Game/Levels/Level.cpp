#include "pch.h"
#include "Level.h"
#include "Game/Characters/Player/Player.h"
#include "Game/Scenes/Statemachine/SceneStateMachine.h"
#include "Game/Commands/Builder/CommandBuilder.h"
#include "Events/Action/ToggleEventLayer.h"
#include "Game/Game.h"
#include "Game/PopUps/Popups.h"
#include "Engine/Events/Action/ToggleEventLayer.h"
#include "Game/General/KeyCodeStringMap.h"

Level::Level(const int id, const int _sceneHeight, const int _sceneWidth, unique_ptr<Engine>& engine, shared_ptr<SceneStateMachine> _stateMachine)
				: GameScene::GameScene(id, _sceneHeight, _sceneWidth, engine, _stateMachine), commandBuilder{new CommandBuilder()},
	gameInvoker(dynamic_cast<GameKeypressInvoker*>(engine->getKeypressedInvoker()))
{
	this->dispatcher.setEventCallback<ToggleLayerEvent>(BIND_EVENT_FN(Level::onToggleLayerEvent));
}

/// @brief
/// OnAttach is executed when a scene is "attached" to the current running context
/// usually this is can be used to prime a level with relevant data before starting it.
void Level::onAttach() {
	for (const auto& s : sounds) {
		if (DEBUG_MAIN)std::cout << s.first << " has value " << s.second << std::endl;
		engine->loadSound(s.first, s.second);
	}
}

/// @brief
/// Start is called when a scene is ready to execute its logic, this can be percieved as the "main loop" of a scene
void Level::start(bool playSound) {

	// TODO kan ik de inventory layers aanmaken in de onAttach?
	inventoryPopupZIndex = this->getHighestLayerIndex() + 1;
	helpPopupZIndex = inventoryPopupZIndex + 1;
	pausePopupZIndex = helpPopupZIndex + 1;

	inventoryPopup = shared_ptr<InventoryPopup>(new InventoryPopup(this->engine, this->dispatcher, this->stateMachine));

	this->addLayerOnZIndex(inventoryPopupZIndex, inventoryPopup);
	this->addLayerOnZIndex(pausePopupZIndex, shared_ptr<Layer>(new PausePopUp(this->engine, this->dispatcher, this->stateMachine)));

	commandBuilder->linkCommandToToggle(gameInvoker, inventoryPopupZIndex, "inventory");
	commandBuilder->linkCommandToToggle(gameInvoker, pausePopupZIndex, "pause");
	commandBuilder->linkCommandToToggle(gameInvoker, helpPopupZIndex, "help");
	
	string helpstring{ "Help: " };
	KeyCode k = gameInvoker->getKeycodeFromIdentifier("help");
	helpstring.append(keycodeStringMap[k]);

	helpText = shared_ptr<Text>(new Text(-99999999, new ColoredText(helpstring, Color(0, 0, 0)), 80, 30, 1770, 130));
	helpText->setDrawStatic(true);
	addNewObjectToLayer(8, helpText, false, true);

	player->respawn();
	player->setTotalHealth(savegame->getCurrentGameData().characterData.totalHealth);
	player->setCurrentHealth(savegame->getCurrentGameData().characterData.totalHealth);
	player->inventory = savegame->getCurrentGameData().characterData.inventory;
	this->addHuds();
	loadScoreBoard();
	this->win = false;

	this->setObjectToFollow(this->follow);
	if (playSound)
	{
		for (const auto& s : sounds) {
			engine->startSound(s.first);
		}
	}
}

/// @brief Updates the level data such as objects that are removed or player is dead or won the level
/// @param deltaTime
/// DeltaTime should be used when calculating timers/manual movements
void Level::onUpdate(float deltaTime)
{
	this->addHuds();

	if (player && inventoryPopup)inventoryPopup->changeCoinCount(player->inventory.coins);

	updateScoreBoard();

	chrono::duration<double> diffFromPreviousCall = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - timeAchievementPopupThrown);

	if (diffFromPreviousCall.count() > 1 && activeAchievementPopup)
	{
		removeLayer(achievementZIndex);
		activeAchievementPopup = false;
	}

	if (this->win)
	{
		increaseTotalGameScore(100);
		throwAchievement("Level " + to_string(stateMachine.get()->levelToBuild) + " completed!");
		SaveGameData save = savegame->getCurrentGameData();
		save.levelData[stateMachine->levelToBuild].completed = true;
		savegame->saveCurrentGameData(save);
		stateMachine->switchToScene("WinScreen", false);
		return;
	}
	if (player->getIsDead())
	{
		stateMachine->switchToScene("DeathScreen", false);
		return;
	}

	for (auto object : this->getAllObjectsInScene()) // TODO get only the non static objects, without looping thru them again and again
	{
		if (!object->getStatic())
		{
			object->onUpdate(engine->getDeltaTime(DELTATIME_TIMESTEP_PHYSICS));

			if (ICharacter *character = dynamic_cast<ICharacter *>(object.get()))
			{
				if (character->getIsDead() && !character->getIsRemoved())
				{
					// TODO Death animation
					object->setIsRemoved(true);
					removeObjectFromScene(object);
					engine->restartPhysicsWorld();
					increaseTotalGameScore(10);
					throwAchievement("First Kill");
				}
			}
		}
	}
}

/// @brief
// Destroys player commands and calls scene base
void Level::onDetach()
{
	SaveGameData save = savegame->getCurrentGameData();

	if (player->getCurrentHealth() > 0) save.characterData.totalHealth = player->getCurrentHealth();
	else
		save.characterData.totalHealth = 1;
	
	save.characterData.inventory = player->inventory;
	savegame->saveCurrentGameData(save);
	gameInvoker->destroyPlayercommands();



	Scene::onDetach();
}
/// @brief
/// toggle a layer received from the event and set its state oposite to its current render state
/// "toggeling" it
bool Level::onToggleLayerEvent(const Event& event) {
	auto layerEvent = dynamic_cast<const ToggleLayerEvent&>(event);

	int layerIndex = layerEvent.getLayerIndex();
	bool currentRenderstate = this->getLayers()[layerIndex]->getRender();

	this->toggleLayer(layerIndex, ! currentRenderstate);
	return true;
}

// @brief 
/// Sets player in the level the camera will follow this object
/// @param Object player
void Level::setPlayer(shared_ptr<Object> object) {
	this->follow = object;
	if (auto _player = dynamic_pointer_cast<Player>(object)) {
		this->player = _player;

		commandBuilder->buildPlayerCommands(*this->player, gameInvoker);

		startPosPlayerX = _player->getPositionX();
		startPosPlayerY = _player->getPositionY();
	}
	else {
		throw exception("Level: not a player object");
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
/// Add HUD for lifes of player
void Level::addHuds() {
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
}

/// @brief
/// Add single HUD for lifes of player
void Level::addHealthHud(int& startingID, int& startingXAxis, int& xAxisChange, int& current, shared_ptr<SpriteObject> HUD) {
	shared_ptr<Drawable> health = shared_ptr<Drawable>(new Drawable(startingID--));
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
	auto achievementPopup = shared_ptr<AchievementPopup>(new AchievementPopup(this->dispatcher, this->stateMachine));
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
	temp.levelData[stateMachine->levelToBuild - 1].score += amount;
	temp.totalScore += amount;
	savegame->saveCurrentGameData(temp);
}

/// @brief 
/// Loads the scoreboard located in the top right corner.
void Level::loadScoreBoard()
{
	shared_ptr<SpriteObject> emptyBlock = shared_ptr<SpriteObject>(new SpriteObject(-2500, 309, 253, 1, 300, "Assets/Inventory/text_background.png"));
	shared_ptr<Drawable> block1 = shared_ptr<Drawable>(new Drawable(-2501));
	block1->setStatic(true);
	block1->setDrawStatic(true);
	block1->setPositionX(1600);
	block1->setPositionY(120);
	block1->setWidth(300);
	block1->setHeight(100);
	block1->registerSprite(SpriteState::DEFAULT, emptyBlock);
	block1->changeToState(SpriteState::DEFAULT);

	int textIDCount = 100;

	shared_ptr<Text> text2 = shared_ptr<Text>(new Text(textIDCount++, new ColoredText(savegame->getCurrentGameData().saveGameName + " " + savegame->getCurrentGameData().getReadableTimeStamp(), Color(0, 0, 0)), 200, 30, 1550, 40));
	text2->setDrawStatic(true);
	addNewObjectToLayer(5, text2, false, true);

	scoreText = shared_ptr<Text>(new Text(textIDCount++, new ColoredText("Total score: " + to_string(savegame->getCurrentGameData().totalScore), Color(0, 0, 0)), 200, 30, 1550, 90));
	scoreText->setDrawStatic(true);
	addNewObjectToLayer(5, scoreText, false, true);

	addNewObjectToLayer(4, block1, false, true);
}

/// @brief 
/// Updates the scoreboard
void Level::updateScoreBoard()
{
	string text = "Total score: " + to_string(savegame->getCurrentGameData().totalScore);
	scoreText->changeText(text);
}

/// @brief
/// Execute pause logic
void Level::pause() {
	for (const auto& s : sounds) {
		engine->stopLoopEffect(s.first);
	}
}

