#include "GameWorld.hpp"

GameWorld::GameWorld()
{
	RenderManager::Initialize(WIDTH, HEIGHT, WINDOW_TITLE);

	Agent* a = new Agent("resources/wreck_out_ship.png", this, -150.0, -140.0);
	Agent* a2 = new Agent("resources/wreck_out_ship.png", this, 150., 50.); 
	a->behaviors->pursueOn(a2);
	a2->behaviors->arriveOn();

	agents.push_back(a);
	agents.push_back(a2);

	obstacles.push_back(new Sprite("resources/asteroid.png", 16, Vector3(-250, 75, 0)));
	obstacles.push_back(new Target);
}

GameWorld::~GameWorld() {
	for(std::vector<Agent*>::iterator it = this->agents.begin(); it != this->agents.end(); ++it) {
		if((*it)) {
			delete (*it);
		}
	}

	for(std::vector<BaseEntity*>::iterator it = this->obstacles.begin(); it != this->obstacles.end(); ++it) {
		if((*it)) {
			delete (*it);
		}
	}
}

void GameWorld::Update(double elapsed_time){
	for(std::vector<Agent*>::iterator it = this->agents.begin(); it != this->agents.end(); ++it) {
		if((*it)) {
			(*it)->Update(elapsed_time);
		}
	}

	for(std::vector<BaseEntity*>::iterator it = this->obstacles.begin(); it != this->obstacles.end(); ++it) {
		if((*it)) {
			(*it)->Update(elapsed_time);
		}
	}
}

void GameWorld::Render()
{
	RenderManager::ClearColorBitBuffer();

	for(std::vector<Agent*>::iterator it = this->agents.begin(); it != this->agents.end(); ++it) {
		if((*it)) {
			(*it)->Render();
		}
	}

	for(std::vector<BaseEntity*>::iterator it = this->obstacles.begin(); it != this->obstacles.end(); ++it) {
		if((*it)) {
			(*it)->Render();
		}
	}
}

void GameWorld::TagObstaclesWithinViewRange(BaseEntity* entity, double detectionBox) {
	for(std::vector<BaseEntity*>::iterator it = this->obstacles.begin(); it != this->obstacles.end(); ++it) 	{
		if((*it)) {
			;//Tag Obstacles that are close
		}
	}
}

void GameWorld::UpdateTarget(int x, int y)
{	
	for(std::vector<BaseEntity*>::iterator it = this->obstacles.begin(); it != this->obstacles.end(); ++it) 	{
		if((*it)) {
			(*it)->UpdateTarget(x - (WIDTH /2), (HEIGHT /2) - y);
		}
	}
	
	for(std::vector<Agent*>::iterator it = this->agents.begin(); it != this->agents.end(); ++it) 	{
		if((*it)) {
			(*it)->UpdateTarget(x - (WIDTH /2), (HEIGHT /2) - y);
		}
	}
}

void GameWorld::MouseHandler(int button, int state, int x, int y)
{
}

double GameWorld::Height() {
	return HEIGHT;
}

double GameWorld::Width() {
	return WIDTH;
}