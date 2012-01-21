#include "Ship.h"

double const Ship::SHIP_HALF_HEIGHT = 0.4;
double const Ship::SHIP_HEIGHT_OFFSET = 0.2;
double const Ship::SHIP_HALF_WIDTH = 0.2;
double const Ship::SHIP_WIDTH_OFFSET = 0.0;

Ship::Ship()
{
	this->position = Vector3(0.0f, 0.0f, 0.0f);
	this->target = Vector3(1.0f, -1.5f, 0.0f);

	this->_velocity = Vector3(5.0f, 5.0f, 0.0f);
	this->_heading = Vector3(0.0f, 0.0f, 0.0f);
	this->_side = Vector3(0.0f, 0.0f, 0.0f);

	this->_mass = 1;
	this->_maxSpeed = 500;
	this->_maxForce = 150.0;
	this->_maxTurnRate = 150.0;
	this->_timeElapsed = 0.0;
}

void Ship::Update(double time_elapsed)
{
	//For some reason this doesn't like really small values of time_elapsed;

	//this->_timeElapsed = time_elapsed;
	this->_timeElapsed = .001;

	//Calculate steering
	Vector3 desiredVelocity = (this->target - this->position);
	desiredVelocity.normalize();
	desiredVelocity *= this->_maxSpeed;

	Vector3 steeringForce = desiredVelocity - this->_velocity;

	Vector3 acceleration = steeringForce / this->_mass;

	this->_velocity += (acceleration * this->_timeElapsed);

	this->position += (this->_velocity * this->_timeElapsed);

	if(vectorMagSq(this->_velocity) > 0.00000001){
		this->_velocity.normalize();
		this->_heading = this->_velocity;
	}
}