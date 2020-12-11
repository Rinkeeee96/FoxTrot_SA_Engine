#include "pch.h"
#include "CharacterFactory.h"
#include "Game/Levels/Level.h"

/// @brief 
/// Constructor
CharacterFactory::CharacterFactory(Engine& _engine, Level& _level) : engine{ _engine }, level{_level} {}

/// @brief 
/// Register object with its name in factory for later cloning
/// @param name 
/// @param character 
/// @param _spriteObjectMap , All sprites of the object 
void CharacterFactory::registerCharacter(string name, ICharacter* character, int* textureID) {
	if (characterMap.count(name) == 0) {
		characterMap.insert(pair<string&, ICharacter*>(name, character));
		map<SpriteState, SpriteObject*> spriteMap = character->buildSpritemap(*textureID);
		*textureID += static_cast<int>(spriteMap.size());
		spriteObjectMap.insert(pair<string, map<SpriteState, SpriteObject*>>(name, spriteMap));
	}
}

/// @brief 
/// Creates an empty objects and registerd sprites
/// @param name 
/// @param id 
ICharacter* CharacterFactory::create(string name, int id) {
	if (characterMap.count(name) > 0) {
		auto clone = characterMap[name]->clone(id);

		if (name == "player") {
			level.setPlayer(clone);
		}

		auto sprites = spriteObjectMap[name];

		map<SpriteState, SpriteObject*>::iterator it = sprites.begin();
		while (it != sprites.end())
		{
			clone->registerSprite(it->first, it->second);
			it++;
		}
		clone->changeToState(SpriteState::DEFAULT);
		return clone;
	}
	throw exception(GAME_ERRORCODES[ENTITY_NOT_FOUND]);
}