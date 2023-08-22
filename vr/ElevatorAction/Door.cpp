#include <cmath>
#include "glut/glut.h"
#include "util.hpp"
#include "Door.hpp"
#include "Player.hpp"

const float Door::WIDTH = 0.35f;
const float Door::HEIGHT = 0.8f;
const float Door::WINDOW_FRAME_WIDTH = 0.05f;
const float Door::KNOB_WIDTH = 0.05f;

Door::Door(int x, int y, float r, float g, float b, bool player_can_open): SingleFloorLevelObject(x, y), r(r), g(g), b(b), player_can_open(player_can_open)
{
	float x1 = to_x1(x, y, Door::WIDTH, Door::HEIGHT);
	float y1 = to_y1(x, y, Door::WIDTH, Door::HEIGHT);
	float x2 = to_x2(x, y, Door::WIDTH, Door::HEIGHT);
	float y2 = to_y2(x, y, Door::WIDTH, Door::HEIGHT);
	this->hitbox = new Hitbox(x1, y1, x2, y2, false);
	this->hitboxes.push_back(this->hitbox);
}


Door::~Door()
{
}

void Door::opendoor()
{
	if (!this->open) {
		this->open = true;
	}
}

void Door::activate(Player * player)
{
}

void Door::render_background()
{
	this->render_hitboxes(0.0f, 0.0f, 0.0f, 0.0f);
}

void Door::render_doorknob(float right) {
	float x1, y1, x2, y2;
	float middle_horizontal_line = (this->hitbox->top() + this->hitbox->bottom()) / 2.0f;
	
	glColor3f(0.8f, 0.8f, 0.0f);
	x1 = right - Door::KNOB_WIDTH;
	y1 = middle_horizontal_line + Door::KNOB_WIDTH / 2.0f;
	x2 = right;
	y2 = middle_horizontal_line - Door::KNOB_WIDTH / 2.0f;
	glRectf(x1, y1, x2, y2);
}

void Door::render_closed()
{
	this->render_background();
	float x1, y1, x2, y2;
	float vertical_window_line = (this->hitbox->left() + this->hitbox->right()) / 2.0f;
	float horizontal_window_line = this->hitbox->top() - std::fmin(Door::WIDTH, Door::HEIGHT) / 2.0f;
	float bottom_window_limit = this->hitbox->top() - std::fmin(Door::WIDTH, Door::HEIGHT);
	float frame_offset = Door::WINDOW_FRAME_WIDTH / 2.0f;

	// Draw door around "windows"
	// Vertical middle window bar
	glColor3f(this->r, this->g, this->b);
	x1 = vertical_window_line - frame_offset;
	y1 = this->hitbox->top();
	x2 = vertical_window_line + frame_offset;
	y2 = bottom_window_limit;
	glRectf(x1, y1, x2, y2);

	// Vertical left window bar
	x1 = this->hitbox->left();
	y1 = this->hitbox->top();
	x2 = this->hitbox->left() + Door::WINDOW_FRAME_WIDTH;
	y2 = bottom_window_limit;
	glRectf(x1, y1, x2, y2);

	// Vertical right window bar
	x1 = this->hitbox->right() - Door::WINDOW_FRAME_WIDTH;
	y1 = this->hitbox->top();
	x2 = this->hitbox->right();
	y2 = bottom_window_limit;
	glRectf(x1, y1, x2, y2);

	// Horizontal middle window bar
	x1 = this->hitbox->left();
	y1 = horizontal_window_line + frame_offset;
	x2 = this->hitbox->right();
	y2 = horizontal_window_line - frame_offset;
	glRectf(x1, y1, x2, y2);

	// Horizontal top window bar
	x1 = this->hitbox->left();
	y1 = this->hitbox->top();
	x2 = this->hitbox->right();
	y2 = this->hitbox->top() - Door::WINDOW_FRAME_WIDTH;
	glRectf(x1, y1, x2, y2);

	// The rest of the door (below windows)
	x1 = this->hitbox->left();
	y1 = bottom_window_limit + Door::WINDOW_FRAME_WIDTH;
	x2 = this->hitbox->right();
	y2 = this->hitbox->bottom();
	glRectf(x1, y1, x2, y2);

	// Draw door knob
	this->render_doorknob(this->hitbox->right() - 0.05f);
}

void Door::render_halfopen()
{
	this->render_background();
	float x1, y1, x2, y2;
	float middle_vertical_line = (this->hitbox->left() + this->hitbox->right()) / 2.0f;
	
	// Draw door
	glColor3f(this->r, this->g, this->b);
	x1 = this->hitbox->left();
	y1 = this->hitbox->top();
	x2 = middle_vertical_line;
	y2 = this->hitbox->bottom();
	glRectf(x1, y1, x2, y2);

	// Draw door knob
	this->render_doorknob(middle_vertical_line - 0.02f);
}

void Door::render_open()
{
	this->render_background();
	float x1, y1, x2, y2;

	// Draw door
	glColor3f(this->r, this->g, this->b);
	x1 = this->hitbox->left();
	y1 = this->hitbox->top();
	x2 = this->hitbox->left() + 0.05f;
	y2 = this->hitbox->bottom();
	glRectf(x1, y1, x2, y2);

	// Draw door knob
	this->render_doorknob(this->hitbox->left());
}

void Door::on_closed()
{
}

void Door::render(float delta)
{
	if (!this->open)
		this->render_closed();
	else if (this->open_elapsed < 0.15f)
		this->render_halfopen();
	else if (this->open_elapsed < 0.85f)
		this->render_open();
	else if (this->open_elapsed < 1.0f)
		this->render_halfopen();
}

void Door::process(float delta, Player *player)
{
	if (this->player_can_open) {
		if (player->hitbox->collides(this->hitbox)) {
			player->door = this;
		}
		else if (player->door == this) {
			player->door = nullptr;
		}
	}
	if (this->open)
		this->open_elapsed += delta;
	if (this->open_elapsed >= 1.0f) {
		this->open_elapsed = 0.0f;
		this->open = false;
		this->activated = false;
		this->on_closed();
	}
	else if (this->open_elapsed >= 0.15f && !this->activated) {
		this->activate(player);
		this->activated = true;
	}
}
