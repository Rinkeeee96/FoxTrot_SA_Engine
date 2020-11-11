#include "Level.h"

/// @brief 
/// @param sceneID 
/// @param _sounds this contains the sounds for the level with identifier and filepath
Level::Level(const int id, map<string, string> _sounds = map<string, string>()) : Scene::Scene(id), sounds(_sounds)
{

}

Level::Level(const int id) : Scene::Scene(id)
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
		//EventSingleton::get_instance().dispatchEvent<SoundAttachEvent>((Event&)SoundAttachEvent(s.first, s.second));
	}
}
/// @brief
/// Start is called when a scene is ready to execute its logic, this can be percieved as the "main loop" of a scene
/// Must be implemented by a concrete implementation of a scene
void Level::start() {
	for (const auto& s : sounds) {
		EventSingleton::get_instance().dispatchEvent<OnMusicStartEvent>((Event&)OnMusicStartEvent(s.first));
	}
}

void Level::onUpdate() {

}

/// @brief
/// OnDetach is called when a scene is destroyed/closed and is responsible for cleanup
/// Must be implemented by a concrete implementation of a scene
void Level::pause() {
	for (const auto& s : sounds) {
		EventSingleton::get_instance().dispatchEvent<OnMusicStopEvent>((Event&)OnMusicStopEvent(s.first));
	}
}


int Level::getHeight() { return this->height; }
int Level::getWidth() { return this->width; }
void Level::setHeight(int height) { this->height = height; }
void Level::setWidth(int width) { this->width= width; }

void Level::onDetach() {}//cleaup buffer