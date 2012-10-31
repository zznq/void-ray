#ifndef AI_SHIPFLAME
#define AI_SHIPFLAME

#include "BaseEntity.hpp"
#include "Sprite.hpp"

class ShipFlame : public Sprite {
public:
	ShipFlame(BaseEntity* parent, float offsetx);
};

#endif
