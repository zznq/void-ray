#include <cmath>
#include "Ship.h"

#include "util/Vector3.h"
#include "SteeringBehaviors.h"

/*
static double const Ship::SHIP_HALF_HEIGHT = 0.2;
static double const Ship::SHIP_HEIGHT_OFFSET = 0.1;
static double const Ship::SHIP_HALF_WIDTH = 0.1;
static double const Ship::SHIP_WIDTH_OFFSET = 0.0;
*/

Ship::Ship()
	: Sprite("resources/wreck_out_ship.png")
{
	this->position = Vector3(0.0f, 0.0f, 0.0f);
	this->target = Vector3(0.0f, 0.0f, -5.0f);

	this->_velocity = Vector3(1.0f, 1.0f, -5.0f);
	this->_heading = Vector3(1.0f, -1.5f, -5.0f);
	this->_side = Vector3(0.0f, 0.0f, -5.0f);

	this->_mass = 1;
	this->_maxSpeed = 1;
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

	/*s
	this->_vertices[0] = this->position.x + 0.000f;
	this->_vertices[1] = this->position.y + 0.128f;
	this->_vertices[2] = 0.0f;
	this->_vertices[3] = this->position.x + 0.128f;
	this->_vertices[4] = this->position.y + 0.128f;
	this->_vertices[5] = 0.0f;
	this->_vertices[6] = this->position.x + 0.128f;
	this->_vertices[7] = this->position.y + 0.000f;
	this->_vertices[8] = 0.0f;
	this->_vertices[9] = this->position.x + 0.000f;
	this->_vertices[10] = this->position.y + 0.000f;
	this->_vertices[11] = 0.0f;
	*/
	float vertices[] = {
		this->position.x + 0.000f, this->position.y + 0.128f, 0.0f,
		this->position.x + 0.128f, this->position.y + 0.128f, 0.0f,
		this->position.x + 0.128f, this->position.y + 0.000f, 0.0f,
		this->position.x + 0.000f, this->position.y + 0.000f, 0.0f
	};
	std::vector<float> _v (vertices, vertices + 12);
	this->_vertices = _v;
}

void Ship::Render(){
	RenderManager::DrawImage(this->_path, &this->_vertices[0]);
}
