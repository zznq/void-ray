#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER

#include "MovingEntity.h"
#include "Ship.h"
#include "util/PrecisionTimer.h"

class GameController{
private:
	//PrecisionTimer timer;
	void DrawEntity(MovingEntity *s);
public:
	//Class Members
	MovingEntity *ship;
	GameController() { /*timer = PrecisionTimer();*/ ship = new Ship(); }

	void Start();
	void Update();

	/* GLUT Callback functions */
	void Render();
	void MouseHandler(int button, int state, int x, int y);
};
#endif