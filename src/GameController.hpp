#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER

#include <vector>
#include "RenderManager.hpp"
#include "BaseEntity.hpp"
#include "Ship.hpp"
#include "Target.hpp"

#define WIDTH 640
#define HEIGHT 480
#define WINDOW_TITLE "void ray"

class GameController{
private:
	void DrawEntity(BaseEntity s);
public:
	//Class Members
	std::vector<BaseEntity*> objects;

	GameController() {
		RenderManager::Initialize(WIDTH, HEIGHT, WINDOW_TITLE);

		objects.push_back(new Target);
		Ship* s = new Ship(-150.0, -140.0); 

		//Ship* s2 = new Ship(150., 50.); 
		s->behaviors->wanderOn();
		//s2->behaviors->arriveOn();

		objects.push_back(s);
		//objects.push_back(s2);
	};

	~GameController();

	void Update(double elapsed_time);

	void Render();
	void MouseHandler(int button, int state, int x, int y);

	//This is temperary, eventually we will have a messageing system
	void UpdateTarget(int x, int y);
};
#endif
