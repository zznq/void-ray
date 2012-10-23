#include "GameController.hpp"

GameController::~GameController() {
	for(std::vector<Entity*>::iterator it = this->objects.begin(); it != this->objects.end(); ++it) {
		if((*it)) {
			delete (*it);
		}
	}
}

void GameController::Update(double elapsed_time){
	for(std::vector<Entity*>::iterator it = this->objects.begin(); it != this->objects.end(); ++it) {
		if((*it)) {
			(*it)->Update(elapsed_time);
		}
	}
}

void GameController::Render()
{
	RenderManager::ClearColorBitBuffer();

	for(std::vector<Entity*>::iterator it = this->objects.begin(); it != this->objects.end(); ++it) {
		if((*it)) {
			(*it)->Render();
		}
	}
}

void GameController::MouseHandler(int button, int state, int x, int y)
{
}
