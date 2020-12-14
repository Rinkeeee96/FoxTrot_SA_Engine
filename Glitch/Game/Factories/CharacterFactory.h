#pragma once
#include "Game\General\GameErrorCodes.h"
#include "Game\Characters\ICharacter.h"
#include "Game\SpriteState.h"

class Level;
/// @brief 
/// Factory for creating entities
class CharacterFactory {
private:
	map<string, ICharacter*> characterMap;
	map<string, map<SpriteState, shared_ptr<SpriteObject>>> spriteObjectMap;
	unique_ptr<Engine>& engine;
	Level& level;
public:
	CharacterFactory(unique_ptr<Engine>& _engine, Level& _level);

	void registerCharacter(string name, ICharacter* character, int* textureId);
	ICharacter* create(string name, int id);
};