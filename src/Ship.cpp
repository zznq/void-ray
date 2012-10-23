#include <cmath>

#include "util/Vector3.hpp"
#include "Ship.hpp"
#include "SteeringBehaviors.hpp"

/*
	Top Right: (0.95f, 0.95f, 0.0f)
	Top Left: (-1.0f, 0.95f, 0.0f)
	Bottom Left: (-1.0f, -1.0, 0.0f)
	Bottom Right (0.95f, -1.0, 0.0f)
*/

Ship::Ship()
	: Sprite("resources/wreck_out_ship.png")
{
	this->position = Vector3(-0.5f, 0.5f, 0.0f);
	this->target = Vector3(0.0f, 0.0f, 0.0f);

	this->_velocity = Vector3(1.0f, 1.0f, 0.0f);
	this->_heading = Vector3(1.0f, -1.5f, 0.0f);
	this->_side = Vector3(0.0f, 0.0f, 0.0f);

	this->_mass = 1;
	this->_maxSpeed = 1;
	this->_maxForce = 10.0;
	this->_maxTurnRate = 150.0;
	this->_timeElapsed = 0.0;
    
    this->behaviors = new SteeringBehaviors(this);

	float vertices[] = {
		-0.064f,  0.064f, 0.0f,
		 0.064f,  0.064f, 0.0f,
		 0.064f, -0.064f, 0.0f,
		-0.064f, -0.064f, 0.0f
	};
	std::vector<float> _v (vertices, vertices + 12);
	this->_vertices = _v;
}

void Ship::Update(double time_elapsed)
{
	this->_timeElapsed = time_elapsed;

    //int radians = acos(this->_velocity * this->_heading);

	Vector3 steeringForce = this->behaviors->Calculate();

	Vector3 acceleration = steeringForce / this->_mass;

	this->_velocity += (acceleration * this->_timeElapsed);

	this->position += (this->_velocity * this->_timeElapsed);

	printf("Postion is: x %f y: %f z: %f\n", this->position.x, this->position.y, this->position.z);
	if(vectorMagSq(this->_velocity) > 0.00000001){
		this->_velocity.normalize();
		this->_heading = this->_velocity;
	}

	/*
	float vertices[] = {
		this->position.x + 0.000f, this->position.y + 0.128f, 0.0f,
		this->position.x + 0.128f, this->position.y + 0.128f, 0.0f,
		this->position.x + 0.128f, this->position.y + 0.000f, 0.0f,
		this->position.x + 0.000f, this->position.y + 0.000f, 0.0f
	};
	std::vector<float> _v (vertices, vertices + 12);
	this->_vertices = _v;
	*/
}

void Ship::Render(){
	RenderManager::MoveAndRotate(this->position, 0, 0);
	RenderManager::DrawImage(this->_path, &this->_vertices[0]);
}
