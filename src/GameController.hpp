#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER

#include <vector>
#include "RenderManager.hpp"
#include "BaseEntity.hpp"
#include "Ship.hpp"
#include "Target.hpp"
#include "Sprite.hpp"

#define WIDTH 640
#define HEIGHT 480
#define WINDOW_TITLE "void ray"

class GameController{
private:
	void DrawEntity(BaseEntity s);
public:
	//Class Members
	std::vector<BaseEntity*> agents;
	std::vector<BaseEntity*> obstacles;

	GameController() {
		RenderManager::Initialize(WIDTH, HEIGHT, WINDOW_TITLE);

		agents.push_back(new Target);
		Ship* s = new Ship(-150.0, -140.0); 

		Ship* s2 = new Ship(150., 50.); 
		s->behaviors->pursueOn(s2);
		s2->behaviors->arriveOn();

		agents.push_back(s);
		agents.push_back(s2);

		Sprite* obstacle1 = new Sprite("resources/asteroid.png", 16, Vector3(-250, 75, 0));
		obstacles.push_back(obstacle1);
	};

	~GameController();

	void Update(double elapsed_time);

	void Render();
	void MouseHandler(int button, int state, int x, int y);

	//This is temperary, eventually we will have a messageing system
	void UpdateTarget(int x, int y);

	static double Height();

	static double Width();
};
#endif
