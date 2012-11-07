#include "Ship.hpp"
#include "ChildSprite.hpp"

Ship::Ship()
	: Sprite("resources/wreck_out_ship.png", 24)
{
	this->_setup(-150.f, 150.f);
}

Ship::Ship(float x, float y)
	: Sprite("resources/wreck_out_ship.png", 24)
{
	this->_setup(x, y);
}

void Ship::_setup(float x, float y) {
	ChildSprite* sf1 = new ChildSprite(this, "resources/flame.png", 14);
	ChildSprite* sf2 = new ChildSprite(this, "resources/flame.png", -14);

	this->_position = Vector3(x, y, 0.0f);
	
	this->_mass = .1;
	this->_maxSpeed = 150.0;
	this->_maxForce = 2.0;
	this->_maxTurnRate = 150.0;
	this->_timeElapsed = 0.0;
}

void Ship::UpdateTarget(int x, int y) {
	this->target.x = (float)x;
	this->target.y = (float)y;
}
