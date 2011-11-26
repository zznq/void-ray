#include "Ship.h"

double const Ship::SHIP_HALF_HEIGHT = 0.4;
double const Ship::SHIP_HEIGHT_OFFSET = 0.2;
double const Ship::SHIP_HALF_WIDTH = 0.2;
double const Ship::SHIP_WIDTH_OFFSET = 0.0;

Ship::Ship()
{
	this->position = new Vector3(1.0f, -1.0f, 0.0f);
}