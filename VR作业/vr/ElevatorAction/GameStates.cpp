#include "GameStates.hpp"


GameStates::GameStates()
{
}


GameStates::~GameStates()
{
}

GameStateMainMenu *GameStates::main_menu(Game *game)
{
	return new GameStateMainMenu(game);
}

GameStateScoreboard *GameStates::scoreboard(Game *game)
{
	return new GameStateScoreboard(game);
}

GameStateInGame *GameStates::in_game(Game *game)
{
	return new GameStateInGame(game);
}

GameStateGameOver *GameStates::game_over(Game *game)
{
	return new GameStateGameOver(game);
}

GameStateExit *GameStates::exit(Game *game)
{
	return new GameStateExit(game);
}

GameState * GameStates::from_enum(Game * game, GameState::GS state)
{
	switch (state) {
	case GameState::MAIN_MENU:
		return main_menu(game);
		break;
	case GameState::IN_GAME:
		return in_game(game);
		break;
	case GameState::SCOREBOARD:
		return scoreboard(game);
		break;
	case GameState::GAME_OVER:
		return game_over(game);
		break;
	case GameState::EXIT:
		return exit(game);
		break;
	default:
		throw std::exception("Invalid state");
		break;
	}
}
