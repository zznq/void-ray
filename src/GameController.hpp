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
		RenderManager::Initialize();

		objects.push_back(new Target);
		objects.push_back(new Ship);
	};

	~GameController();

	void Update(double elapsed_time);

	void Render();
	void MouseHandler(int button, int state, int x, int y);
};
#endif
