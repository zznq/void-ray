#include "util/Vector3.hpp"
#include "ShipFlame.hpp"

ShipFlame::ShipFlame(BaseEntity* parent, float offsetx)
	: Sprite(parent, "resources/flame.png", 14)
{
	this->_position = Vector3(offsetx, -28.0f, 0.0f);
}