#ifndef AI_SHIP
#define AI_SHIP

#include "Sprite.hpp"

class Ship : public Sprite {
public:
	Ship();
	void Update(double time_elapsed);
	void UpdateTarget(int x, int y);
};

#endif
