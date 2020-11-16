#include "pch.h"
#include "Level.h"

/// @brief 
/// @param sceneID 
/// @param _sounds this contains the sounds for the level with identifier and filepath
Level::Level(const int id, const int _sceneHeight, const int _sceneWidth, map<string, string> _sounds = map<string, string>()) : Scene::Scene(id, _sceneHeight, _sceneWidth), sounds(_sounds)
{

}

Level::Level(const int id, const int _sceneHeight, const int _sceneWidth) : Scene::Scene(id, _sceneHeight, _sceneWidth)
{

}

void Level::setSound(map<string, string> _sounds)
{
	sounds = _sounds;
}

/// @brief
/// OnAttach is executed when a scene is "attached" to the current running context
/// usually this is can be used to prime a level with relevant data before starting it.
/// Must be implemented by a concrete implementation of a scene
void Level::onAttach() {
	for (const auto& s : sounds) {
		if(DEBUG_MAIN)std::cout << s.first << " has value " << s.second << std::endl;
		EventSingleton::get_instance().dispatchEvent<SoundAttachEvent>((Event&)SoundAttachEvent(s.first, s.second));
	}
}
/// @brief
/// Start is called when a scene is ready to execute its logic, this can be percieved as the "main loop" of a scene
/// Must be implemented by a concrete implementation of a scene
void Level::start() {
	this->setObjectToFollow(this->follow);
	for (const auto& s : sounds) {
		EventSingleton::get_instance().dispatchEvent<OnMusicStartEvent>((Event&)OnMusicStartEvent(s.first));
	}
}

void Level::onUpdate() {
	for (auto obj : this->getAllObjectsInScene())
	{
		if (!obj->getStatic()) {
			obj->onUpdate();

			// TODO Refactor
			if (ICharacter* d = dynamic_cast<ICharacter*>(obj)) {
				if (d->getObjectId() == this->follow->getObjectId()) {
					if (d->getIsDead()) {
						throw std::exception("level done");
					}
				}
			}
		}
	}
}

/// @brief
/// OnDetach is called when a scene is destroyed/closed and is responsible for cleanup
/// Must be implemented by a concrete implementation of a scene
void Level::pause() {
	for (const auto& s : sounds) {
		EventSingleton::get_instance().dispatchEvent<OnMusicStopEvent>((Event&)OnMusicStopEvent(s.first));
	}
}

void Level::onDetach() {}//cleaup buffer