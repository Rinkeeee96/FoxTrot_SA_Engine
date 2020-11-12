#pragma once
#include <string>
#include <map>
#include <exception>
#include <Game\General\GameErrorCodes.h>
#include <Game\Characters\ICharacter.h>

class CharacterFactory {
private:
	std::map<std::string, ICharacter*> keyValues;
	std::map<std::string, std::map<SpriteState, SpriteObject*>> spriteObjectMap;
public:
	void registerCharacter(std::string name, ICharacter* character, std::map<SpriteState, SpriteObject*> _spriteObjectMap) {
		if (keyValues.count(name) == 0) {
			keyValues.insert(std::pair<std::string, ICharacter*>(name, character));
			spriteObjectMap.insert(std::pair<std::string, std::map<SpriteState, SpriteObject*>>(name, _spriteObjectMap));
		}
	}

	ICharacter* create(std::string name, int id) {
		if (keyValues.count(name) > 0) {
			auto clone = keyValues[name]->clone(id);

			auto sprites = spriteObjectMap[name];

			std::map<SpriteState, SpriteObject*>::iterator it = sprites.begin();
			while (it != sprites.end())
			{
				clone->registerSprite(it->first, it->second);
				it++;
			}
			clone->changeToState(SpriteState::DEFAULT);
			return clone;
		}
		throw std::exception(GAME_ERRORCODES[ENTITY_NOT_FOUND]);
	}
};