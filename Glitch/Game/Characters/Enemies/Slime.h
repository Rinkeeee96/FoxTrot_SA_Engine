#pragma once
#include "Game/Characters/Enemies/IEnemy.h"

class Slime : public IEnemy {
public:
	Slime(const int id) : IEnemy(id) {}

	virtual void onUpdate() override {
		// TODO AI Logic
	};
};