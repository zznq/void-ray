#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER

#include "Ship.h"

class GameController{
private:
	void DrawShip(Ship *s);
public:
	Ship *ship;
	Ship *ship2;
	GameController() { ship = new Ship(); ship2 = new Ship(); ship2->position->x = 0.0f; ship2->position->y = 0.0f; }
	void Render();
};
#endif