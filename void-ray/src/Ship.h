#ifndef AI_SHIP
#define AI_SHIP

#include "util/Vector3.h"

class Ship{
private:
	Vector3 _velocity;
	Vector3 _heading;
	Vector3 _side;
	double _mass;
	double _maxSpeed;
	double _maxForce;
	double _maxTurnRate;
	double _timeElapsed;

public:
	static double const SHIP_HALF_HEIGHT;
	static double const SHIP_HEIGHT_OFFSET;
	static double const SHIP_HALF_WIDTH;
	static double const SHIP_WIDTH_OFFSET;
	
	Vector3 position;
	Vector3 target;
	
	Ship();
	void Update(double time_elapsed);
};

#endif