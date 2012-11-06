#define _USE_MATH_DEFINES
#include <cmath>

#include "util/Vector3.hpp"
#include "Ship.hpp"
#include "SteeringBehaviors.hpp"
#include "ShipFlame.hpp"

//3.14159265359
#define ToDegrees (180 / M_PI)
#define QuarterTurn (M_PI / 2)

Ship::Ship()
	: Sprite("resources/wreck_out_ship.png", 24)
{
	ShipFlame* sf1 = new ShipFlame(this, 14);
	ShipFlame* sf2 = new ShipFlame(this, -14);

	this->_position = Vector3(-150.f, 150.f, 0.0f);
	
	this->_mass = .1;
	this->_maxSpeed = 150.0;
	this->_maxForce = 2.0;
	this->_maxTurnRate = 150.0;
	this->_timeElapsed = 0.0;
}

Ship::Ship(float x, float y)
	: Sprite("resources/wreck_out_ship.png", 24)
{
	ShipFlame* sf1 = new ShipFlame(this, 14);
	ShipFlame* sf2 = new ShipFlame(this, -14);

	this->_position = Vector3(x, y, 0.0f);
	
	this->_mass = .1;
	this->_maxSpeed = 150.0;
	this->_maxForce = 2.0;
	this->_maxTurnRate = 150.0;
	this->_timeElapsed = 0.0;
}

void Ship::Update(double time_elapsed)
{
	this->_timeElapsed = time_elapsed;

	float _distance = distance(this->target, this->_position);
	
	Vector3 steeringForce = this->behaviors->Calculate();

	Vector3 acceleration = steeringForce / this->_mass;

	this->_velocity += (acceleration * this->_timeElapsed);
	
	this->_velocity.truncate(this->_maxSpeed);

	this->_position += (this->_velocity * this->_timeElapsed);

	if(vectorMagSq(this->_velocity) > 0.00000001){
		Vector3 newHeading = Vector3(this->_velocity);
		newHeading.normalize();
		this->_heading = newHeading;

		this->_side = Perp(this->_heading);
	}

	UpdateRotation();
}

void Ship::UpdateRotation() {
	//Determines if the heading is to the left or right of us
	float sign = _copysignf(1.0f, this->_heading * this->_left);
	float _radians = acos(this->_heading * this->_up);

	this->_rotation.z = sign * _radians;
}

void Ship::UpdateTarget(int x, int y) {
	this->target.x = (float)x;
	this->target.y = (float)y;

	UpdateRotation();
}
