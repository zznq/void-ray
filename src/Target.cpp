#include <cmath>

#include "util/Vector3.hpp"
#include "Target.hpp"
#include "SteeringBehaviors.hpp"

Target::Target()
	: Sprite("resources/target.png", 16)
{
	this->_position = Vector3(0.0f, 0.0f, 0.0f);
	this->target = Vector3(0.0f, 0.0f, 0.0f);
	this->_rotation = Vector3(0.0f, 0.0f, 0.0f);

	this->_velocity = Vector3(0.0f, 0.0f, 0.0f);
	this->_heading = Vector3(0.0f, 0.0f, 0.0f);
	this->_side = Vector3(0.0f, 0.0f, 0.0f);

	this->_timeElapsed = 0.0;

    this->behaviors = new SteeringBehaviors(this);
}

void Target::UpdateTarget(int x, int y) {
	this->_position.x = (float)x;
	this->_position.y = (float)y;
}
