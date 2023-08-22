#pragma once
#include "GameState.hpp"
class GameStateScoreboard :
	public GameState
{
public:
	GameStateScoreboard(Game *game);
	~GameStateScoreboard();

	float score_height(int index);
	void process(float delta) override;
	void render_title();
	void render_scores();
	void render_option();
	void render(float delta) override;
};

