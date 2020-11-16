#pragma once
#include <string>
#include <map>
#include <exception>
#include "Game\General\GameErrorCodes.h"
#include "Game\Characters\ICharacter.h"
#include "Game\SpriteState.h"
#include <Engine.h>
#include <Game\Levels\Level.h>

class CharacterFactory {
private:
	std::map<std::string, ICharacter*> characterMap;
	std::map<std::string, std::map<SpriteState, SpriteObject*>> spriteObjectMap;
	Engine& engine;
	Level& level;
public:
	CharacterFactory(Engine& _engine, Level& _level);

	void registerCharacter(std::string name, ICharacter* character, std::map<SpriteState, SpriteObject*> _spriteObjectMap);
	ICharacter* create(std::string name, int id);
};