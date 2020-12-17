#include "pch.h"
#include "CharacterFactory.h"
#include "Game/Levels/Level.h"

/// @brief 
/// Constructor
CharacterFactory::CharacterFactory(unique_ptr<Engine>& _engine, Level& _level) : engine{ _engine }, level{_level} {}

/// @brief 
/// Register object with its name in factory for later cloning
/// @param name 
/// @param character 
/// @param _spriteObjectMap , All sprites of the object 
void CharacterFactory::registerCharacter(string name, shared_ptr<ICharacter> character, int* textureID) {
	if (characterMap.count(name) == 0) {
		characterMap.insert(pair<string&, shared_ptr<ICharacter>>(name, character));
		map<SpriteState, shared_ptr<SpriteObject>> spriteMap = character->buildSpritemap(*textureID);
		*textureID += static_cast<int>(spriteMap.size());
		spriteObjectMap.insert(pair<string, map<SpriteState, shared_ptr<SpriteObject>>>(name, spriteMap));
	}
	else {
		throw exception("identifier already registered");
	}
}

/// @brief 
/// Creates an empty objects and registerd sprites
/// @param name 
/// @param id 
shared_ptr<ICharacter> CharacterFactory::create(string name, int id) {
	if (characterMap.count(name) > 0) {
		shared_ptr<ICharacter> clone = characterMap[name]->clone(id);

		if (name == "player") {
			level.setPlayer(shared_ptr<Object>(clone));
		}

		auto sprites = spriteObjectMap[name];

		map<SpriteState, shared_ptr<SpriteObject>>::iterator it = sprites.begin();
		if (sprites.begin() == sprites.end()) {
			return clone;
		}
		while (it != sprites.end())
		{
			clone->registerSprite(it->first, it->second);
			it++;
		}
		clone->changeToState(SpriteState::DEFAULT);
		return clone;
	}
	else {
		throw exception("identifier does not exist");
	}
}
