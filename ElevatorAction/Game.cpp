#include <iostream>
#include <algorithm>
#include <functional>
#include "Game.hpp"
#include "GameStates.hpp"
#include "LevelManager.hpp"
#include "glut/glut.h"



Game::Game(void(*levelgen_callback)(Game *game)) : input(UserInput()), gamestate(GameStates::main_menu(this)), levelgen_function(levelgen_callback)
{
	this->levelgen_function(this);
}


Game::~Game()
{
}

void Game::keyboard_press(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		this->input.up = true;
		break;
	case 's':
		this->input.down = true;
		break;
	case 'a':
		this->input.left = true;
		break;
	case 'd':
		this->input.right = true;
		break;
	case 'e':
	case ' ':
		this->input.use = true;
		break;
	}
}

void Game::keyboard_release(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		this->input.up = false;
		break;
	case 's':
		this->input.down = false;
		break;
	case 'a':
		this->input.left = false;
		break;
	case 'd':
		this->input.right = false;
		break;
	case 'e':
	case ' ':
		this->input.use = false;
		break;
	}
}

void Game::specialkey_press(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		this->input.up = true;
		break;
	case GLUT_KEY_DOWN:
		this->input.down = true;
		break;
	case GLUT_KEY_LEFT:
		this->input.left = true;
		break;
	case GLUT_KEY_RIGHT:
		this->input.right = true;
		break;
	}
}

void Game::specialkey_release(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		this->input.up = false;
		break;
	case GLUT_KEY_DOWN:
		this->input.down = false;
		break;
	case GLUT_KEY_LEFT:
		this->input.left = false;
		break;
	case GLUT_KEY_RIGHT:
		this->input.right = false;
		break;
	}
}

void Game::set_gamestate(GameState * state)
{
	GameState *oldstate = this->gamestate;
	this->gamestate = state;
	delete oldstate;
}

void Game::add_level(Level * level)
{
	this->levels->add(level);
}

void Game::game_over()
{
	if (this->gamestate->state != GameState::IN_GAME)
		throw std::exception("Not in game");

	this->set_gamestate(GameStates::game_over(this));
}

void Game::add_score(int score)
{
	this->scores.push_back(score);
	std::sort(this->scores.begin(), this->scores.end(), std::greater<int>());
	if (this->scores.size() > 10) {
		this->scores.erase(this->scores.begin() + 9, this->scores.end());
	}
}

void Game::process(float delta)
{
	// Repetitions of max_delta in process step
	//std::cout << delta << std::endl;
	float max_delta = 0.01f;
	int reps = delta / max_delta;
	for (int i = 0; i < reps; i++) {
		this->gamestate->process(max_delta);
	}
	this->gamestate->process(delta - reps * max_delta);
}

void Game::render(float delta)
{
	this->gamestate->render(delta);
}
