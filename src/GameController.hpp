#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER

#include <vector>
#include "RenderManager.hpp"
#include "Entity.hpp"
#include "Ship.hpp"
#include "Target.hpp"

class GameController{
private:
	void DrawEntity(Entity s);
public:
	//Class Members
	std::vector<Entity*> objects;

	GameController() {
		//objects = std::vector<Entity*>(2);

		RenderManager::Initialize();

		objects.push_back(new Ship);
		objects.push_back(new Target);
	};

	void Update(double elapsed_time);

	void Render();
	void MouseHandler(int button, int state, int x, int y);
};
#endif
