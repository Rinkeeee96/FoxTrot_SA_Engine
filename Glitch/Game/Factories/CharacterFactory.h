#pragma once
#include <string>
#include <map>
#include <exception>
#include "Game\General\GameErrorCodes.h"
#include "Game\Characters\ICharacter.h"
#include "Game\SpriteState.h"
#include <Engine.h>
#include <Game\Levels\Level.h>

/// @brief 
/// Factory for creating entities
class CharacterFactory {
private:
	map<string, ICharacter*> characterMap;
	map<string, map<SpriteState, SpriteObject*>> spriteObjectMap;
	Engine& engine;
	Level& level;
public:
	CharacterFactory(Engine& _engine, Level& _level);

	void registerCharacter(string name, ICharacter* character, map<SpriteState, SpriteObject*> _spriteObjectMap);
	ICharacter* create(string name, int id);
};