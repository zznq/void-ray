#ifndef VOID_RAY_GAME_WORLD
#define VOID_RAY_GAME_WORLD

#include <vector>
#include "RenderManager.hpp"
#include "BaseEntity.hpp"
#include "Agent.hpp"
#include "Target.hpp"
#include "Sprite.hpp"

#define WIDTH 640
#define HEIGHT 480
#define WINDOW_TITLE "void ray"

class Agent;
class BaseEntity;

class GameWorld{
private:
	void DrawEntity(BaseEntity s);
public:
	//Class Members
	std::vector<Agent*> agents;
	std::vector<BaseEntity*> obstacles;

	GameWorld();
	~GameWorld();

	void Update(double elapsed_time);

	void Render();
	void MouseHandler(int button, int state, int x, int y);

	void TagObstaclesWithinViewRange(BaseEntity* entity, double detectionBox); 

	//This is temperary, eventually we will have a messageing system
	void UpdateTarget(int x, int y);

	static double Height();
	static double Width();
};
#endif
