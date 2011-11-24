#ifndef AI_SHIP
#define AI_SHIP

#include "util\Vector3.h"

class Ship{

public:
	static Vector3 const *SHIP_SIZE;
	Vector3 *position;
	Ship();
};

#endif