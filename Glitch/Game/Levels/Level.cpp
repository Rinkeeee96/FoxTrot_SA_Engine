#include "pch.h"
#include "Level.h"
#include "Game/Characters/Player/Player.h"
#include "Game/Scenes/Statemachine/SceneStateMachine.h"
#include "Game/Commands/Builder/CommandBuilder.h"
#include "Events/Action/ToggleEventLayer.h"
#include "Game/Game.h"
#include "Game/PopUps/Popups.h"
#include "Engine/Events/Action/ToggleEventLayer.h"

Level::Level(const int id, const int _sceneHeight, const int _sceneWidth, Engine& engine, SceneStateMachine& _stateMachine) 
				: GameScene::GameScene(id, _sceneHeight, _sceneWidth, engine, _stateMachine), commandBuilder{new CommandBuilder()}
{
	gameInvoker = dynamic_cast<GameKeypressInvoker*>(engine.getKeypressedInvoker());
	this->dispatcher.setEventCallback<ToggleLayerEvent>(BIND_EVENT_FN(Level::onToggleLayerEvent));
}

/// @brief
/// OnAttach is executed when a scene is "attached" to the current running context
/// usually this is can be used to prime a level with relevant data before starting it.
void Level::onAttach() {
	for (const auto& s : sounds) {
		if (DEBUG_MAIN)std::cout << s.first << " has value " << s.second << std::endl;
		engine.loadSound(s.first, s.second);
	}
	// TODO kan ik de inventory layers aanmaken in de onAttach?
	inventoryPopupZIndex = this->getHighestLayerIndex();
	pausePopupZIndex = this->getHighestLayerIndex() + 1;	

	this->addLayerOnZIndex(inventoryPopupZIndex, new InventoryPopup(this->dispatcher, this->stateMachine));
	this->addLayerOnZIndex(pausePopupZIndex, new PausePopUp(this->dispatcher, this->stateMachine));

	commandBuilder->linkCommandToToggle(gameInvoker, inventoryPopupZIndex, "inventory");
	commandBuilder->linkCommandToToggle(gameInvoker, pausePopupZIndex, "pause");
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
			engine.startSound(s.first);
		}
	}
}

void Level::onUpdate() {
	this->addHuds();

	if (this->win) {
		player->kill();
		SaveGameData save = savegame->getCurrentGameData();
		save.levelData[stateMachine.levelToBuild - 1].completed = true;
		savegame->saveCurrentGameData(save);
		stateMachine.switchToScene("WinScreen", false);
		return;
	}
	if (player->getIsDead()) {
		stateMachine.switchToScene("DeathScreen", false);
		return;
	}

	// TODO get only the non static objects, without looping thru them again and again
	for (auto object : this->getAllObjectsInScene()) 	{
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

void Level::onDetach()
{
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
void Level::setPlayer(Object* object) {
	this->follow = object;
	if (Player* _player = dynamic_cast<Player*>(object)) {
		this->player = _player;

		commandBuilder->buildPlayerCommands(*this->player, gameInvoker);

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
/// Execute pause logic
void Level::pause() {
	for (const auto& s : sounds) {
		engine.stopLoopEffect(s.first);
	}
}

