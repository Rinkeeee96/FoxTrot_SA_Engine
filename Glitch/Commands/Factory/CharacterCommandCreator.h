#pragma once
#include "ICharacterCommandCreator.h"
#include "CharacterCommandFactory.h"

template <class T>
class CharacterCommandCreator : public ICharacterCommandCreator
{
public:
	CharacterCommandCreator(string _key) : key{ _key } {};
	void registerClass(shared_ptr<CharacterCommandFactory> factory) { 
		factory->registerit(key, this); 
	};

	ICharacterCommand* createCharacterCommand(ICharacter& character) { return new T(character, key); }
private:
	string key;
};