#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER

#include "Entity.hpp"
#include "Ship.h"

class GameController{
private:
	void DrawEntity(Entity *s);
public:
	//Class Members
	Entity *ship;
	GameController(SDL_Surface* screen) { ship = new Ship(screen); }

	void Update(double elapsed_time);

	void Render();
	void MouseHandler(int button, int state, int x, int y);
};
#endif
