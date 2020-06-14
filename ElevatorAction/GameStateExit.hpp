#pragma once
#include "GameState.hpp"
class GameStateExit :
	public GameState
{
public:
	GameStateExit(Game *game);
	~GameStateExit();

	void process(float delta) override;
	void render(float delta) override;
};

