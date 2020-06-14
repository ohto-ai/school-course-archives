#include <assert.h>
#include "GameStateMainMenu.hpp"
#include "Game.hpp"
#include "GameStates.hpp"
#include "util.hpp"
#include "glut/glut.h"

GameStateMainMenu::GameStateMainMenu(Game *game) : GameState(game, MAIN_MENU)
{
}


GameStateMainMenu::~GameStateMainMenu()
{
}

float GameStateMainMenu::choice_height(int choice)
{
	float panel_height = glutGet(GLUT_WINDOW_HEIGHT) - 2.0f * 24.0f;
	float middle_line = panel_height / 2.0f;
	float height = middle_line + 18.0f * this->num_items / 2.0f - 18.0f * (choice + 1);
	return height;
}

void GameStateMainMenu::process(float delta)
{
	assert(0 <= this->choice && this->choice < this->num_items);
	if (this->game->input.use) {
		this->selection_changed = false;
		this->selection_change_elapsed = 0.0f;
		this->game->input.clear();
		this->game->set_gamestate(GameStates::from_enum(this->game, this->states[this->choice]));
	}
	else if(!this->selection_changed) {
		if (this->game->input.up) {
			this->selection_changed = true;
			if (this->choice == 0) {
				this->choice = this->num_items - 1;
			}
			else {
				--this->choice;
			}
		}
		else if (this->game->input.down) {
			this->selection_changed = true;
			this->choice = (this->choice + 1) % num_items;
		}
	}
	else if (this->selection_changed) {
		this->selection_change_elapsed += delta;
		if (this->selection_change_elapsed >= this->selection_change_cooldown) {
			this->selection_changed = false;
			this->selection_change_elapsed = 0.0f;
		}
	}
}

void GameStateMainMenu::render_title()
{
	void *font = GLUT_BITMAP_TIMES_ROMAN_24;
	float height = 24.0f;

	beginText();
	drawStringCentered(font, glutGet(GLUT_WINDOW_HEIGHT) - 2.0f * height, (char *)"Elevator Action");
	endText();
}

void GameStateMainMenu::render_choices()
{
	void *font = GLUT_BITMAP_HELVETICA_18;
	float height = 18.0f;

	beginText();
	for (int i = 0; i < this->num_items; i++) {
		char *text = (char *)*(this->choice_texts + i);
		drawStringCentered(font, this->choice_height(i), text);
	}
	endText();
}

void GameStateMainMenu::render_selection()
{
	float max_bitmap_length = glutBitmapLength(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)"Scoreboard");
	float font_height = 18.0f;
	float right_point_x = (glutGet(GLUT_WINDOW_WIDTH) - max_bitmap_length) / 2.0f - font_height;
	float right_point_y = this->choice_height(this->choice) + font_height / 2.0f;
	glPushMatrix();

	//glTranslatef(glutGet(GLUT_WINDOW_WIDTH) / 2.0f, glutGet(GLUT_WINDOW_HEIGHT) / 2.0f, 0.0f);
	glTranslatef(-1.0f, -1.0f, 0.0f);
	glScalef(2.0f / glutGet(GLUT_WINDOW_WIDTH), 2.0f / glutGet(GLUT_WINDOW_HEIGHT), 1.0f);

	glBegin(GL_TRIANGLES);
	glVertex2f(right_point_x, right_point_y);
	glVertex2f(right_point_x - font_height, right_point_y + font_height / 2.0f);
	glVertex2f(right_point_x - font_height, right_point_y - font_height / 2.0f);
	glEnd();

	glPopMatrix();
}

void GameStateMainMenu::render(float delta)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	
	glLoadIdentity();
	this->render_title();
	this->render_choices();
	this->render_selection();
}
