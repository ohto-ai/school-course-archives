#pragma once
#include "GameState.hpp"
#include "Game.hpp"
class GameStateInGame :
	public GameState
{
public:
	GameStateInGame(Game *game);
	~GameStateInGame();

	void process(float delta) override;
	void render(float delta) override;
};

