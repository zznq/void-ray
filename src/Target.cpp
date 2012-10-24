#include <cmath>

#include "util/Vector3.hpp"
#include "Target.hpp"
#include "SteeringBehaviors.hpp"

/*
	Top Right: (0.95f, 0.95f, 0.0f)
	Top Left: (-1.0f, 0.95f, 0.0f)
	Bottom Left: (-1.0f, -1.0, 0.0f)
	Bottom Right (0.95f, -1.0, 0.0f)
*/

Target::Target()
	: Sprite("resources/target.png")
{
	this->position = Vector3(0.0f, 0.0f, 0.0f);

	this->target = Vector3(0.0f, 0.0f, 0.0f);

	this->_velocity = Vector3(1.0f, 1.0f, -5.0f);
	this->_heading = Vector3(1.0f, -1.5f, -5.0f);
	this->_side = Vector3(0.0f, 0.0f, -5.0f);

	this->_timeElapsed = 0.0;

    this->behaviors = new SteeringBehaviors(this);
	
	/*x,y,z*/

	float vertices[] = {
		-0.064f,  0.064f, 0.0f,
		 0.064f,  0.064f, 0.0f,
		 0.064f, -0.064f, 0.0f,
		-0.064f, -0.064f, 0.0f
	};
	std::vector<float> _v (vertices, vertices + 12);
	this->_vertices = _v;
}

void Target::Update(double time_elapsed)
{
	this->_timeElapsed = time_elapsed;
}

void Target::Render(){
	RenderManager::MoveAndRotate(this->position, 0, 0);
	
	Sprite::Render();
}
