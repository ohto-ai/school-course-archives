#pragma once
#include <vector>
#include "Level.hpp"

class Game;
class LevelManager
{
	std::vector<Level *> levels = std::vector<Level *>();
	int current_index = 0;

	Level *current();
public:
	Game *game;
	LevelManager(Game *game);
	~LevelManager();

	void add(Level *level);
	bool go2next();

	void process(float delta);
	void render(float delta);
};

