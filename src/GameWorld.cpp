#include "GameWorld.hpp"
#include "ChildSprite.hpp"

GameWorld::GameWorld()
{
	RenderManager::Initialize(WIDTH, HEIGHT, WINDOW_TITLE);

	//Agent* a = new Agent("resources/wreck_out_ship.png", this, -150.0, -140.0);
	Agent* a2 = new Agent("resources/wreck_out_ship.png", this, 60.f, 60.f); 
	//a->behaviors->pursueOn(a2);
	a2->behaviors->arriveOn();
  //a2->behaviors->obstacleAvoidanceOn();

	a2->AddChild(new ChildSprite("resources/flame.png", 14, -28.0f));
	a2->AddChild(new ChildSprite("resources/flame.png", -14, -28.0f));
	
	//agents.push_back(a);
	agents.push_back(a2);

	obstacles.push_back(new Sprite("resources/asteroid.png", 16, Vector3(75.0f, 160.0f, 0)));
	obstacles.push_back(new Sprite("resources/asteroid.png", 16, Vector3(125.0f, 20.0f, 0)));
	obstacles.push_back(new Sprite("resources/asteroid.png", 16, Vector3(90.0f, 620.0f, 0)));
	obstacles.push_back(new Sprite("resources/asteroid.png", 16, Vector3(62.0f, -10.0f, 0)));
	obstacles.push_back(new Sprite("resources/asteroid.png", 16, Vector3(20.0f, 60.0f, 0)));
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

	for(std::vector<BaseEntity*>::iterator it = this->obstacles.begin(); it != this->obstacles.end(); ++it) {
		if((*it)) {
			(*it)->Render();
		}
	}

	for(std::vector<Agent*>::iterator it = this->agents.begin(); it != this->agents.end(); ++it) {
		if((*it)) {
			(*it)->Render();
		}
	}
}

void GameWorld::TagObstaclesWithinViewRange(BaseEntity* entity, double detectionBox) {
	for(std::vector<BaseEntity*>::iterator it = this->obstacles.begin(); it != this->obstacles.end(); ++it) 	{
		if((*it)) {
      if(vectorMag(entity->Position() - (*it)->Position()) < detectionBox) {
			  (*it)->SetEntityNearViewRange();
      } else {
			  (*it)->ClearEntityNearViewRange();
      }
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
