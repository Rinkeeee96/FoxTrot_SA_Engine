#pragma once
#include "Game/Characters/Enemies/IEnemy.h"

class Slime : public IEnemy {
public:
	Slime() : IEnemy(-1) {}
	Slime(const int id) : IEnemy(id) {}

	virtual void onUpdate() override {
		// TODO AI Logic
	};

	virtual ICharacter* clone(int id) override {
		return new Slime(id);
	}
};