#include "Agent.hpp"

Agent::Agent(GameWorld *world)
	: Sprite("resources/wreck_out_ship.png", 24)
{
	this->_setup(world, -150.f, 150.f);
}

Agent::Agent(GameWorld *world, float x, float y)
	: Sprite("resources/wreck_out_ship.png", 24)
{
	this->_setup(world, x, y);
}

Agent::Agent(std::string path, GameWorld *world)
	: Sprite(path, 24)
{
	this->_setup(world, -150.f, 150.f);
}

Agent::Agent(std::string path,GameWorld *world, float x, float y)
	: Sprite(path, 24)
{
	this->_setup(world, x, y);
}

void Agent::_setup(GameWorld *world, float x, float y) {
	this->world = world;

	this->_drawHelpers = true;

	this->position = Vector3(x, y, 0.0f);
	
	this->_mass = 0.5;
	this->_maxSpeed = 50.0;
	this->_maxForce = 35.0;
	this->_maxTurnRate = 10.0;
	this->_timeElapsed = 0.0;

  this->_radius = 12;
}

void Agent::UpdateTarget(int x, int y) {
	this->target.x = (float)x;
	this->target.y = (float)y;
}
