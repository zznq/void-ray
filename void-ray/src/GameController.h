#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER

#include "Ship.h"
#include "util/PrecisionTimer.h"

class GameController{
private:
	PrecisionTimer timer;
	void DrawShip(Ship *s);
public:
	//Class Members
	Ship *ship;
	GameController() { timer = PrecisionTimer(); ship = new Ship(); }

	void Start();
	void Update();

	/* GLUT Callback functions */
	void Render();
	void MouseHandler(int button, int state, int x, int y);
};
#endif