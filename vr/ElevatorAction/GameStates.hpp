#pragma once
#include "GameStateMainMenu.hpp"
#include "GameStateScoreboard.hpp"
#include "GameStateInGame.hpp"
#include "GameStateGameOver.hpp"
#include "GameStateExit.hpp"
class GameState;
class Game;
class GameStates
{
public:
	GameStates();
	~GameStates();

	static GameStateMainMenu *main_menu(Game *game);
	static GameStateScoreboard *scoreboard(Game *game);
	static GameStateInGame *in_game(Game *game);
	static GameStateGameOver *game_over(Game *game);
	static GameStateExit *exit(Game *game);
	static GameState *from_enum(Game *game, GameState::GS state);
};

