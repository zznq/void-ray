#define _USE_MATH_DEFINES
#include <cmath>

#include "util/Vector3.hpp"
#include "Ship.hpp"
#include "SteeringBehaviors.hpp"
//3.14159265359
#define ToDegrees (180 / M_PI)

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
	this->_rotation = 0.0;
    
    this->behaviors = new SteeringBehaviors(this);
}

void Ship::Update(double time_elapsed)
{
	this->_timeElapsed = time_elapsed;

	float deltay = this->target.y - this->position.y;
	float deltax = this->target.x - this->position.x;

    float radians = atan2(deltay, deltax);

	this->_rotation = (radians * ToDegrees) - 90;

	Vector3 steeringForce = this->behaviors->Calculate();

	Vector3 acceleration = steeringForce / this->_mass;

	this->_velocity += (acceleration * this->_timeElapsed);

	this->position += (this->_velocity * this->_timeElapsed);

	if(vectorMagSq(this->_velocity) > 0.00000001){
		this->_velocity.normalize();
		this->_heading = this->_velocity;
	}
}

void Ship::UpdateTarget(int x, int y) {
	this->target.x = (float)x;
	this->target.y = (float)y;
}

void Ship::Render() {
	Vector3 pos = this->getPosition();

	RenderManager::MoveAndRotate(this->getPosition(), this->_rotation, RenderManager::ROTATEZ);

	RenderManager::DrawImage(this->_path, &this->_vertices[0]);
}
