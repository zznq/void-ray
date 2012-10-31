#define _USE_MATH_DEFINES
#include <cmath>

#include "util/Vector3.hpp"
#include "Ship.hpp"
#include "SteeringBehaviors.hpp"
//3.14159265359
#define ToDegrees (180 / M_PI)
#define QuarterTurn (M_PI / 2)

Ship::Ship()
	: Sprite("resources/wreck_out_ship.png", 24)
{
	this->_position = Vector3(-150.f, 150.f, 0.0f);
	this->target = Vector3(0.0f, 0.0f, 0.0f);
	this->_rotation = Vector3(0.0f, 0.0f, 0.0f);

	this->_velocity = Vector3(1.0f, 1.0f, 0.0f);
	this->_heading = Vector3(0.0f, -1.0f, 0.0f);
	this->_heading.normalize();

	this->_side = Vector3(0.0f, 0.0f, 0.0f);

	this->_mass = .1;
	this->_maxSpeed = 150.0;
	this->_maxForce = 2.0;
	this->_maxTurnRate = 150.0;
	this->_timeElapsed = 0.0;

    
    this->behaviors = new SteeringBehaviors(this);
	UpdateTarget(0,0);
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
	}
}

void Ship::UpdateTarget(int x, int y) {
	
	this->target.x = (float)x;
	this->target.y = (float)y;

	/******************
	Rotation
	******************/
	// Target - Position
	/*Vector3 tp = this->target - this->position;
	tp.normalize();

	float radians = acos(this->_heading * tp);

	printf("Radians(acos): %f\n", radians);
	*/

	float deltay = this->target.y - this->_position.y;
	float deltax = this->target.x - this->_position.x;

    float radians = atan2(deltay, deltax);
	this->_rotation.z = radians - QuarterTurn;
}
