#include "pch.h"
#include "Level.h"

/// @brief 
/// @param sceneID 
/// @param _sounds this contains the sounds for the level with identifier and filepath
Level::Level(const int id, const int _sceneHeight, const int _sceneWidth, map<string, string> _sounds = map<string, string>()) : 
	Scene::Scene(id, _sceneHeight, _sceneWidth), 
	sounds(_sounds)
{

}

Level::Level(const int id, const int _sceneHeight, const int _sceneWidth) : Scene::Scene(id, _sceneHeight, _sceneWidth)
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
		EventSingleton::get_instance().dispatchEvent<SoundAttachEvent>((Event&)SoundAttachEvent(s.first, s.second));
	}
}

void Level::addHuds() {
	// Health HUDS
	int startingID = -662;
	int xAxisChange = 75;
	int startingXAxis = 75;
	int current = 0;
	SpriteObject* HUD = new SpriteObject(-660, 50, 50, 1, 300, "Assets/Sprites/HUD/Full.png");
	SpriteObject* HUDEmpty = new SpriteObject(-661, 50, 50, 1, 300, "Assets/Sprites/HUD/Empty.png");

	for (size_t i = 0; i < player->getHealth(); i++)
	{
		auto* health1 = new Drawable(startingID--);
		health1->setStatic(true);
		health1->setPositionX(25 + (startingXAxis + (xAxisChange * (current + 1))));
		health1->setPositionY(100);
		health1->setWidth(50);
		health1->setHeight(50);
		health1->registerSprite(SpriteState::DEFAULT, HUD);
		health1->changeToState(SpriteState::DEFAULT);

		huds.push_back(health1);
		addNewObjectToLayer(4, health1, false);
		current++;
	}
	for (size_t i = 0; i < (player->getTotalHealth() - player->getHealth()); i++)
	{
		auto* health1 = new Drawable(startingID--);
		health1->setStatic(true);
		health1->setPositionX(25 + (startingXAxis + (xAxisChange * (current + 1))));
		health1->setPositionY(100);
		health1->setWidth(50);
		health1->setHeight(50);
		health1->registerSprite(SpriteState::DEFAULT, HUDEmpty);
		health1->changeToState(SpriteState::DEFAULT);

		huds.push_back(health1);
		addNewObjectToLayer(4, health1, false);
		current++;
	}
}

/// @brief
/// Start is called when a scene is ready to execute its logic, this can be percieved as the "main loop" of a scene
void Level::start() {
	player->setPositionX(50);
	player->setPositionY(885);
	player->setHealth(2);
	player->setTotalHealth(3);
	this->addHuds();

	this->setObjectToFollow(this->follow);
	for (const auto& s : sounds) {
		EventSingleton::get_instance().dispatchEvent<OnMusicStartEvent>((Event&)OnMusicStartEvent(s.first));
	}
}

void Level::onUpdate() {
	if (this->win) {
		SceneSwitcher::get_instance().switchToScene("WIN_SCREEN", false);
		player->kill();
		this->win = false;
		return;
	}
	if (player->getIsDead()) {
		SceneSwitcher::get_instance().switchToScene("DEAD_SCREEN", false);
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
					EventSingleton::get_instance().dispatchEvent<RemoveEvent>((Event&)RemoveEvent());
				}
			}
		}
	}
}

/// @brief
/// Execute pause logic
void Level::pause() {
	for (const auto& s : sounds) {
		EventSingleton::get_instance().dispatchEvent<OnMusicStopEvent>((Event&)OnMusicStopEvent(s.first));
	}
}

void Level::onDetach() 
{
	//Scene::onDetach();
}//cleaup buffer