#pragma once
#include "Game/Ground/IGround.h"
#include <Game/Characters/Player/Player.h>

#define MIN_HEIGHT 500

/// @brief 
/// "Moving" ground class
class MovingGround : public IGround {
private:
	EventDispatcher& dispatcher;
public:
	MovingGround(EventDispatcher& _dispatcher, const int id) : IGround(id), dispatcher{ _dispatcher } {
		this->staticObject = BodyType::KINEMATIC;
	}
	 
	void setStatic(const bool) override { }

	/// @brief
	/// Moves ground
	virtual void onUpdate(float deltaTime) override {
		if (this->getPositionY() - deltaTime * 100 > MIN_HEIGHT) {
			return;
		}
		this->setPositionY(this->getPositionY() - deltaTime * 100);
		UpdatePhysicsBodyEvent e{ *this };
		dispatcher.dispatchEvent<UpdatePhysicsBodyEvent>(e);
	};
};