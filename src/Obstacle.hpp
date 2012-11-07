#ifndef AI_OBSTACLE
#define AI_OBSTACLE

#include "Sprite.hpp"

class Obstacle : public Sprite {
public:
	Obstacle() : Sprite("resources/obstacle.png", 16) { };
};

#endif