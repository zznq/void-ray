#ifndef VOID_RAY_AGENT
#define VOID_RAY_AGENT

#include <string>
#include "Sprite.hpp"
#include "GameWorld.hpp"

class GameWorld;

class Agent : public Sprite {
private:
	void _setup(GameWorld *world, float x, float y);
public:
	GameWorld *world;

	Agent(GameWorld *world);
	Agent(GameWorld *world, float x, float y);
	Agent(std::string path, GameWorld *world);
	Agent(std::string path, GameWorld *world, float x, float y);
	void UpdateTarget(int x, int y);
};

#endif
