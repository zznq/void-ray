#ifndef AI_SHIP
#define AI_SHIP

#include <SDL.h>

#include "util/Vector3.h"
#include "MovingEntity.h"
#include "SteeringBehaviors.h"

class Ship : public MovingEntity {
private:
	SDL_Surface* _screen;
public:
	static double const SHIP_HALF_HEIGHT;
	static double const SHIP_HEIGHT_OFFSET;
	static double const SHIP_HALF_WIDTH;
	static double const SHIP_WIDTH_OFFSET;
	
	Ship(SDL_Surface* screen);
	void Update(double time_elapsed);
    void Render();
};

#endif
