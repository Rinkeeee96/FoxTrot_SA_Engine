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

	void addHuds();

	void setWin(const bool val) { this->win = val; }
private:
	void addHealthHud(int& startingID, int& startingXAxis, int& xAxisChange, int& current, SpriteObject* HUD);
	vector<Drawable*> huds;

	map<string, string> sounds;
	Object* follow = nullptr;
	Player* player = nullptr;
	bool win = false;

	float startPosPlayerX = 0;
	float startPosPlayerY = 0;
};