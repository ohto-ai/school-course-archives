#pragma once
#include <vector>
#include "GameState.hpp"
#include "UserInput.hpp"
#include "Player.hpp"
#include "LevelManager.hpp"
class UserInput;
class LevelManager;
class GameState;
class Level;
class Game
{
public:
	LevelManager *levels = new LevelManager(this);
	UserInput input;
	GameState *gamestate;
	Player *player = new Player();
	std::vector<int> scores = std::vector<int>();
	void (*levelgen_function)(Game *game);

	Game(void(*levelgen_callback)(Game *game));
	~Game();

	void keyboard_press(unsigned char key, int x, int y);
	void keyboard_release(unsigned char key, int x, int y);
	void specialkey_press(int key, int x, int y);
	void specialkey_release(int key, int x, int y);
	void set_gamestate(GameState *state);
	void add_level(Level *level);
	void game_over();
	void add_score(int score);
	void process(float delta);
	void render(float delta);
};

