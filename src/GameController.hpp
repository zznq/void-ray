#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER

#include <vector>
#include "RenderManager.hpp"
#include "BaseEntity.hpp"
#include "Ship.hpp"
#include "ShipFlame.hpp"
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
		Ship* s = new Ship; 
		
		//ShipFlame* sf1 = new ShipFlame(s, 14);
		//ShipFlame* sf2 = new ShipFlame(s, -14);
		//objects.push_back(sf1);
		//objects.push_back(sf2);
		objects.push_back(s);
	};

	~GameController();

	void Update(double elapsed_time);

	void Render();
	void MouseHandler(int button, int state, int x, int y);

	//This is temperary, eventually we will have a messageing system
	void UpdateTarget(int x, int y);
};
#endif
