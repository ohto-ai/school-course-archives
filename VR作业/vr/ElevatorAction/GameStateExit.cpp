#include <cstdlib>
#include "GameStateExit.hpp"


GameStateExit::GameStateExit(Game *game) : GameState(game, EXIT)
{
}


GameStateExit::~GameStateExit()
{
}

void GameStateExit::process(float delta)
{
	exit(0);
}

void GameStateExit::render(float delta)
{
}
