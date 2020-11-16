#include "CharacterFactory.h"

CharacterFactory::CharacterFactory(Engine& _engine) : engine{ _engine } {}

void CharacterFactory::registerCharacter(std::string name, ICharacter* character, std::map<SpriteState, SpriteObject*> _spriteObjectMap) {
	if (characterMap.count(name) == 0) {
		characterMap.insert(std::pair<std::string, ICharacter*>(name, character));
		spriteObjectMap.insert(std::pair<std::string, std::map<SpriteState, SpriteObject*>>(name, _spriteObjectMap));
	}
}

ICharacter* CharacterFactory::create(std::string name, int id) {
	if (characterMap.count(name) > 0) {
		auto clone = characterMap[name]->clone(id);

		if (name == "player") {
			engine.attachCamera(id);
		}

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