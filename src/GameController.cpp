#include "GameController.h"

#include "Ship.h"

void GameController::Update(double elapsed_time){
	this->ship->Update(elapsed_time);
}

void GameController::DrawEntity(MovingEntity *s){
    s->Render();
}

void GameController::Render()
{
    DrawEntity(ship);
}

void GameController::MouseHandler(int button, int state, int x, int y)
{
}