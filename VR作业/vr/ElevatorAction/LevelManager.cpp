#include <stdexcept>
#include "LevelManager.hpp"
#include "Game.hpp"

Level * LevelManager::current()
{
	if (this->levels.size() > 0)
		return this->levels.at(this->current_index);
	return nullptr;
}

LevelManager::LevelManager(Game *game) : game(game)
{
}


LevelManager::~LevelManager()
{
}

void LevelManager::add(Level *level)
{
	if (this->levels.size() == 0) {
		level->set_player(this->game->player);
	}
	this->levels.push_back(level);
	level->manager = this;
}

bool LevelManager::go2next()
{
	if (this->game->gamestate->state == GameState::IN_GAME) {
		if ((unsigned)this->current_index < this->levels.size() - 1) {
			Level *current = this->levels.at(current_index);
			Level *next = this->levels.at(current_index + 1);
			current->transition_to(next);
			++this->current_index;
			
			return true;
		}
		this->game->game_over();
	}
	return false;
}

void LevelManager::process(float delta)
{
	Level *current = this->current();
	if(current != nullptr)
		current->process(delta);
}

void LevelManager::render(float delta)
{
	Level *current = this->current();
	if (current != nullptr)
		current->render(delta);
}
