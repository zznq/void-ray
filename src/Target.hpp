#ifndef AI_Target
#define AI_Target

#include "Sprite.hpp"

class Target : public Sprite {
public:
	Target();
	void UpdateTarget(int x, int y);
};

#endif
