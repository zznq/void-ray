#ifndef AI_SHIP
#define AI_SHIP

#include "Sprite.h"

class Ship : public Sprite {
public:
	/*static double const SHIP_HALF_HEIGHT;
	static double const SHIP_HEIGHT_OFFSET;
	static double const SHIP_HALF_WIDTH;
	static double const SHIP_WIDTH_OFFSET;*/
	
	Ship();
	void Update(double time_elapsed);
	void Render();
};

#endif
