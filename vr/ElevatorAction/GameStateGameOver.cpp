#include <iostream>
#include "GameStateGameOver.hpp"
#include "Game.hpp"
#include "GameStates.hpp"
#include "util.hpp"
#include "glut/glut.h"

GameStateGameOver::GameStateGameOver(Game *game) : GameState(game, GAME_OVER)
{
}


GameStateGameOver::~GameStateGameOver()
{
}

void GameStateGameOver::process(float delta)
{
	if (this->game->input.use) {
		// Save score
		this->game->add_score(this->game->player->score);

		// Reset player
		Player *p = this->game->player;
		this->game->player = new Player();
		delete p;

		// Generate levels again
		LevelManager *lm = this->game->levels;
		this->game->levels = new LevelManager(this->game);
		delete lm;
		this->game->levelgen_function(this->game);

		this->game->input.clear();
		this->game->set_gamestate(GameStates::main_menu(this->game));
	}
}

void GameStateGameOver::render_title()
{
	void *font = GLUT_BITMAP_TIMES_ROMAN_24;
	float height = 24.0f;

	beginText();
	drawStringCentered(font, glutGet(GLUT_WINDOW_HEIGHT) / 2.0f, (char *)"GAME OVER");
	endText();
}

void GameStateGameOver::render_score()
{
	void *font = GLUT_BITMAP_9_BY_15;
	float height = 15.0f;

	char fmt[20] = "Score: %07d";
	char score_text[20];
	sprintf_s(score_text, fmt, this->game->player->score);

	beginText();
	drawStringCentered(font, glutGet(GLUT_WINDOW_HEIGHT) / 2.0f - height, score_text);
	endText();
}

void GameStateGameOver::render_option()
{
	void *font = GLUT_BITMAP_HELVETICA_18;
	float height = 18.0f;

	beginText();
	drawStringCentered(font, height, (char *)"Main Menu");
	endText();

	float bitmap_length = glutBitmapLength(font, (const unsigned char *)"Main Menu");
	float right_point_x = (glutGet(GLUT_WINDOW_WIDTH) - bitmap_length) / 2.0f - height;
	float right_point_y = 1.5f * height;
	glPushMatrix();

	glTranslatef(-1.0f, -1.0f, 0.0f);
	glScalef(2.0f / glutGet(GLUT_WINDOW_WIDTH), 2.0f / glutGet(GLUT_WINDOW_HEIGHT), 1.0f);

	glBegin(GL_TRIANGLES);
	glVertex2f(right_point_x, right_point_y);
	glVertex2f(right_point_x - height, right_point_y + height / 2.0f);
	glVertex2f(right_point_x - height, right_point_y - height / 2.0f);
	glEnd();

	glPopMatrix();
}

void GameStateGameOver::render(float delta)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glLoadIdentity();

	render_title();
	render_score();
	render_option();
}
