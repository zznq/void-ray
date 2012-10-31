#define _USE_MATH_DEFINES
#include <cmath>

#include "util/Vector3.hpp"
#include "ShipFlame.hpp"
#include "SteeringBehaviors.hpp"
//3.14159265359
#define ToDegrees (180 / M_PI)
#define QuarterTurn (M_PI / 2)

ShipFlame::ShipFlame(BaseEntity* parent, float offsetx)
	: Sprite(parent, "resources/flame.png", 14)
{
	this->_position = Vector3(offsetx, -28.0f, 0.0f);
	this->target = Vector3(0.0f, 0.0f, 0.0f);
	this->_rotation = Vector3(0.0f, 0.0f, 0.0f);

	this->_velocity = Vector3(1.0f, 1.0f, 0.0f);
	this->_heading = Vector3(0.0f, -1.0f, 0.0f);
	this->_heading.normalize();

	this->_side = Vector3(0.0f, 0.0f, 0.0f);

	this->_mass = .1;
	this->_maxSpeed = 70.0;
	this->_maxForce = 10.0;
	this->_maxTurnRate = 150.0;
	this->_timeElapsed = 0.0;
    
    this->behaviors = new SteeringBehaviors(this);
}
