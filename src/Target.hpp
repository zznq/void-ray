#ifndef AI_Target
#define AI_Target

#include "Sprite.hpp"

class Target : public Sprite {
public:
	Target();
	void Update(double time_elapsed);
	void Render();
};

#endif