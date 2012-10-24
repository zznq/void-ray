#include <cmath>

#include "util/Vector3.hpp"
#include "Ship.hpp"
#include "SteeringBehaviors.hpp"

Ship::Ship()
	: Sprite("resources/wreck_out_ship.png", 24)
{
	this->position = Vector3(-150.f, 150.f, 0.0f);
	this->target = Vector3(0.0f, 0.0f, 0.0f);

	this->_velocity = Vector3(1.0f, 1.0f, 0.0f);
	this->_heading = Vector3(1.0f, -1.5f, 0.0f);
	this->_side = Vector3(0.0f, 0.0f, 0.0f);

	this->_mass = .1;
	this->_maxSpeed = 70.0;
	this->_maxForce = 10.0;
	this->_maxTurnRate = 150.0;
	this->_timeElapsed = 0.0;
    
    this->behaviors = new SteeringBehaviors(this);
}

void Ship::Update(double time_elapsed)
{
	this->_timeElapsed = time_elapsed;

    //int radians = acos(this->_velocity * this->_heading);

	Vector3 steeringForce = this->behaviors->Calculate();

	Vector3 acceleration = steeringForce / this->_mass;

	this->_velocity += (acceleration * this->_timeElapsed);

	this->position += (this->_velocity * this->_timeElapsed);

	if(vectorMagSq(this->_velocity) > 0.00000001){
		this->_velocity.normalize();
		this->_heading = this->_velocity;
	}
}
