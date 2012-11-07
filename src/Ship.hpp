#ifndef AI_SHIP
#define AI_SHIP

#include "Sprite.hpp"

class Ship : public Sprite {
private:
	void _setup(float x, float y);
public:
	Ship();
	Ship(float x, float y);
	void UpdateTarget(int x, int y);
};

#endif
