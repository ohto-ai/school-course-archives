#pragma once
#include <string>
#include "GameState.hpp"
class GameStateMainMenu :
	public GameState
{
public:
	static const int num_items = 3;
	const GameState::GS states[num_items] = {
		GameState::IN_GAME,
		GameState::SCOREBOARD,
		GameState::EXIT,
	};
	const char choice_texts[num_items][20] = {
		"New Game",
		"Scoreboard",
		"Exit"
	};
	int choice = 0;
	bool selection_changed = false;
	float selection_change_cooldown = 0.15f;
	float selection_change_elapsed = 0.0;

	GameStateMainMenu(Game *game);
	~GameStateMainMenu();

	float choice_height(int choice);
	void process(float delta) override;
	void render_title();
	void render_choices();
	void render_selection();
	void render(float delta) override;
};

