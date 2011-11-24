#include "Ship.h"

Vector3 const *Ship::SHIP_SIZE = new Vector3(.6, .2, -1.0);

Ship::Ship()
{
	this->position = new Vector3(1.0, -1.0, 0.0);
}