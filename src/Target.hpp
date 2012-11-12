#ifndef VOID_RAY_TARGET
#define VOID_RAY_TARGET

#include "Sprite.hpp"

class Target : public Sprite {
public:
	Target() : Sprite("resources/target.png", 16) { };
	void UpdateTarget(int x, int y);
};
#endif
