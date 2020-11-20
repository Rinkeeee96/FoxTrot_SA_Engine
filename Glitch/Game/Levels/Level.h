#pragma once
#include "Game\Characters\Player\Player.h"

/// @brief 
/// Level class. Level has all the information. 
class Level : public Scene
{
public:
	Level(const int id, const int _sceneHeight, const int _sceneWidth, map<string, string> _sounds);
	Level(const int id, const int _sceneHeight, const int _sceneWidth);

	void setPlayer(Object* object);
	virtual void setSound(map<string, string> sounds);
	virtual void onAttach() override;
	virtual void start() override;
	virtual void pause();
	virtual void onDetach() override;
	virtual void onUpdate() override;

	void setWin(const bool val) { this->win = val; }
private:
	map<string, string> sounds;
	Object* follow = nullptr;
	Player* player = nullptr;
	bool win = false;
};