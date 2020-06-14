#pragma once
class Game;

class GameState
{
public:
	enum GS {
		MAIN_MENU,
		SCOREBOARD,
		IN_GAME,
		GAME_OVER,
		EXIT,
	} state;
	Game *game;
	GameState(Game *game, GS state);
	~GameState();

	virtual void process(float delta) = 0;
	virtual void render(float delta) = 0;
};

