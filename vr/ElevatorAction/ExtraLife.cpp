#include <cmath>
#include "ExtraLife.hpp"
#include "Hitbox.hpp"
#include "Player.hpp"
#include "glut/glut.h"

ExtraLife::ExtraLife(int x, int y) : SingleFloorLevelObject(x, y)
{
	this->hitbox = new Hitbox(this->x - 0.5f - this->width / 2.0f, this->y - 1.0f + Platform::THICKNESS + this->y_offset + this->height, this->x - 0.5f + this->width / 2.0f, this->y - 1.0f + Platform::THICKNESS + this->y_offset, false);
}


ExtraLife::~ExtraLife()
{
}


void ExtraLife::process(float delta, Player *player)
{
	if (this->taken)
		return;
	if (player->hitbox->collides(this->hitbox)) {
		++player->lives;
		player->score += 200;
		this->taken = true;
	}
}

void ExtraLife::render(float delta)
{
	if (this->taken)
		return;
	float h1 = this->hitbox->left() + 0.333f * (this->hitbox->right() - this->hitbox->left());
	float h2 = this->hitbox->left() + 0.666f * (this->hitbox->right() - this->hitbox->left());
	float v1 = this->hitbox->bottom() + 0.666f * (this->hitbox->top() - this->hitbox->bottom());
	float v2 = this->hitbox->bottom() + 0.333f * (this->hitbox->top() - this->hitbox->bottom());

	glColor3f(0.0f, 1.0f, 0.0f);
	//glBegin(GL_LINE_LOOP);
	//glVertex2f(h1, this->hitbox->top());
	//glVertex2f(h1, v1);
	//glVertex2f(this->hitbox->left(), v1);
	//glVertex2f(this->hitbox->left(), v2);
	//glVertex2f(h1, v2);
	//glVertex2f(h1, this->hitbox->bottom());
	//glVertex2f(h2, this->hitbox->bottom());
	//glVertex2f(h2, v2);
	//glVertex2f(this->hitbox->right(), v2);
	//glVertex2f(this->hitbox->right(), v1);
	//glVertex2f(h2, v1);
	//glVertex2f(h2, this->hitbox->top());
	//glEnd();
	glRectf(h1, this->hitbox->top(), h2, this->hitbox->bottom());
	glRectf(this->hitbox->left(), v1, this->hitbox->right(), v2);
}
