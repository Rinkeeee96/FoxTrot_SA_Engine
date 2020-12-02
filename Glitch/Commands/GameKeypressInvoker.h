#pragma once
#include "Commands/ICharacterCommand.h"
#include "Input/KeypressInvoker.h"
class Player;
class ICharacter;
class GameKeypressInvoker : public KeypressInvoker
{

public:
	void registerPlayerCommand(KeyCode code, unique_ptr<ICharacterCommand> command);

	unordered_map<KeyCode, reference_wrapper<unique_ptr<ICharacterCommand>>>& getPlayerCommands();

	void registerGlobalCommand(KeyCode code, unique_ptr<ICommand> command);

	void linkCommandsToPlayer(Player& player);

	/// @brief
	/// Update the keycode that is set to this command, unbinds the previously registerd command if present
	/// @param code
	/// The new keycode for the command in the map
	/// @param command
	/// A shared pointer to the command which needs to be updated
	void updateCommand(KeyCode code, unique_ptr<ICommand> command) override;
private:
	// store references to the uniqueptr and its keycode
	unordered_map<KeyCode, reference_wrapper<unique_ptr<ICharacterCommand>>> playerCommands;
	unordered_map<KeyCode, reference_wrapper<unique_ptr<ICommand>>> globalCommands;
};