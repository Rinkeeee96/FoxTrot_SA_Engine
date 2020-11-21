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
/// @brief
/// Start is called when a scene is ready to execute its logic, this can be percieved as the "main loop" of a scene
void Level::start() {
	player->setPositionX(98.8484848484848);
	player->setPositionY(552.871212121211);
	player->setHealth(100);

	this->setObjectToFollow(this->follow);
	for (const auto& s : sounds) {
		EventSingleton::get_instance().dispatchEvent<OnMusicStartEvent>((Event&)OnMusicStartEvent(s.first));
	}
}

void Level::onUpdate() {
	if (this->win) {
		SceneSwitcher::get_instance().switchToScene("WIN_SCREEN", false);
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
					//removeObjectFromScene(object);
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