#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER

#include "MovingEntity.h"
#include "Ship.h"

class GameController{
private:
	void DrawEntity(MovingEntity *s);
public:
	//Class Members
	MovingEntity *ship;
	GameController(SDL_Surface* screen) { ship = new Ship(screen); }

	void Update(double elapsed_time);

	void Render();
	void MouseHandler(int button, int state, int x, int y);
};
#endif
