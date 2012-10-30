#ifndef AI_SHIPFLAME
#define AI_SHIPFLAME

#include "Entity.hpp"
#include "Sprite.hpp"

class ShipFlame : public Sprite {
public:
	ShipFlame(Entity* parent, float offsetx);
};

#endif
