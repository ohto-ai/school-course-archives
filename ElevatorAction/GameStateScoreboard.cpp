#include <cstdio>
#include "GameStateScoreboard.hpp"
#include "Game.hpp"
#include "GameStates.hpp"
#include "util.hpp"
#include "glut/glut.h"

GameStateScoreboard::GameStateScoreboard(Game *game) : GameState(game, SCOREBOARD)
{
}


GameStateScoreboard::~GameStateScoreboard()
{
}

float GameStateScoreboard::score_height(int index)
{
	float font_height = 15.0f;
	float panel_top = glutGet(GLUT_WINDOW_HEIGHT) - 2.0f * 18.0f;
	float panel_bottom = 2.0f * 18.0f;
	float middle_line = (panel_top + panel_bottom) / 2.0f;
	float height = middle_line + font_height * 10 / 2.0f - font_height * (index + 1);
	return height;
}

void GameStateScoreboard::process(float delta)
{
	if (this->game->input.use) {
		this->game->input.clear();
		this->game->set_gamestate(GameStates::main_menu(this->game));
	}
}

void GameStateScoreboard::render_title()
{
	void *font = GLUT_BITMAP_HELVETICA_18;
	float height = 18.0f;

	beginText();
	drawStringCentered(font, glutGet(GLUT_WINDOW_HEIGHT) - 2.0f * height, (char *)"Scoreboard");
	endText();
}

void GameStateScoreboard::render_scores()
{
	void *font = GLUT_BITMAP_9_BY_15;
	char fmt[20] = "%2d. %07d";
	char score_text[20];

	beginText();
	for (int i = 0; i < 10; i++) {
		int score = ((unsigned)i >= this->game->scores.size() ? 0 : this->game->scores.at(i));
		sprintf_s(score_text, fmt, i + 1, score);
		drawStringCentered(font, this->score_height(i), score_text);
	}
	endText();
}

void GameStateScoreboard::render_option()
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


void GameStateScoreboard::render(float delta)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glLoadIdentity();
	this->render_title();
	this->render_scores();
	this->render_option();
}
