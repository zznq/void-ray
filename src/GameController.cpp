#include "GameController.hpp"

GameController::~GameController() {
	for(std::vector<BaseEntity*>::iterator it = this->agents.begin(); it != this->agents.end(); ++it) {
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

void GameController::Update(double elapsed_time){
	for(std::vector<BaseEntity*>::iterator it = this->agents.begin(); it != this->agents.end(); ++it) {
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

void GameController::Render()
{
	RenderManager::ClearColorBitBuffer();

	for(std::vector<BaseEntity*>::iterator it = this->agents.begin(); it != this->agents.end(); ++it) {
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

void GameController::UpdateTarget(int x, int y)
{	
	for(std::vector<BaseEntity*>::iterator it = this->obstacles.begin(); it != this->obstacles.end(); ++it) 	{
		if((*it)) {
			(*it)->UpdateTarget(x - (WIDTH /2), (HEIGHT /2) - y);
		}
	}
	
	for(std::vector<BaseEntity*>::iterator it = this->agents.begin(); it != this->agents.end(); ++it) 	{
		if((*it)) {
			(*it)->UpdateTarget(x - (WIDTH /2), (HEIGHT /2) - y);
		}
	}
}

void GameController::MouseHandler(int button, int state, int x, int y)
{
}

double GameController::Height() {
	return HEIGHT;
}

double GameController::Width() {
	return WIDTH;
}