#ifndef VOID_RAY_OBSTACLE
#define VOID_RAY_OBSTACLE

#include "Sprite.hpp"

class Obstacle : public Sprite {
public:
	Obstacle() : Sprite("resources/obstacle.png", 16) { };
};

#endif
