#pragma once
class ICharacter;
class ICharacterCommand;
class ICharacterCommandCreator;

class CharacterCommandFactory
{
public:
	/// @brief
	/// Function for registrating a command creator
	/// a command is created by this creator upon request with its registered classname
	void registerit(const std::string& classname, ICharacterCommandCreator* creator);

	ICharacterCommand* createCharacterCommand(const std::string& classname, ICharacter& character);
private:
	std::map<std::string, ICharacterCommandCreator*> table;
};
