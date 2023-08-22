#include <iostream>
#include "glut/glut.h"
#include "Game.hpp"
#include "Enemy.hpp"
#include "util.hpp"
#include "CollisionHelper.hpp"
#include "Door.hpp"
#include "EnemyBullet.hpp"

Enemy::Enemy()
{
	this->hitbox = new EnemyHitbox(this);
}

Enemy::Enemy(Level *level, float fx, float fy, Orientation orientation): level(level), fx(fx), fy(fy), orientation(orientation)
{
	Enemy();
}


Enemy::~Enemy()
{
}

float Enemy::dfx(float delta)
{
	return this->movement_speed * (float)this->orientation * delta;
}

float Enemy::gun_fx()
{
	return (this->hitbox->left() + this->hitbox->right()) / 2.0f + (float)this->orientation * this->width;
}

float Enemy::gun_fy()
{
	return this->fy + this->height * 0.75f;
}

void Enemy::fire()
{
	this->level->spawn_bullet(new EnemyBullet(this, (float)this->orientation * 2.0f));
}

void Enemy::die()
{
	this->level->despawn_enemy(this);
}

void Enemy::move(float delta)
{
	float new_fx = this->fx + this->dfx(delta);
	int ix = fx2x(new_fx);
	int iy = fy2y(this->fy);
	std::pair<int, int> xy = std::make_pair(ix, iy);
	if (this->level->platform_occupied.count(xy) == 0) { // Can't walk in current direction if there's no platform to walk on
		this->orientation = (Orientation)(-1 * this->orientation);
	}
	else {
		this->fx = new_fx;
	}
}

void Enemy::face_player()
{
	this->orientation = (Orientation)((int)(this->level->player->fx > this->fx) * 2 - 1);
}

void Enemy::check_usable()
{
	if (this->level == nullptr)
		throw std::exception("Level is null");
}


void Enemy::elapse_fire(float delta)
{
	if (this->firing) {
		this->fire_elapsed += delta;
		if (this->fire_elapsed > this->fire_cooldown) {
			this->fire_elapsed = 0.0f;
			this->firing = false;
			this->fired = false;
		}
	}
}

void Enemy::process(float delta)
{
	if (this->level->player->hitbox->top() >= this->gun_fy() && this->level->player->hitbox->bottom() <= this->gun_fy() && !this->firing && randfloat(0.0f, 1.0f) > 0.9995f) {
		this->firing = true;
	}
	if (this->firing) {
		this->elapse_fire(delta);
		if (this->fire_elapsed > 0.5f && !this->fired) {
			this->fire();
			this->fired = true;
		}
	}
	if (!this->firing || this->firing && this->fire_elapsed >= 1.0f) {
		//std::cout << "Moving" << std::endl;
		this->move(delta);
	}
	else if (this->firing && this->fire_elapsed < 1.0f) {
		this->face_player();
	}
}

void Enemy::render_gun()
{
	float middle_h = this->gun_fy();
	float x1 = (this->hitbox->left() + this->hitbox->right()) / 2.0f + (float)this->orientation * this->width / 2.0f;
	float y1 = middle_h + 0.04f * this->height;
	float x2 = this->gun_fx();
	float y2 = middle_h - 0.04f * this->height;
	//std::cout << x1 << " " << y1 << " " << x2 << " " << y2 << std::endl;
	//std::cout << this->orientation << std::endl;
	glColor3f(0.55f, 0.27f, 0.075f); // Brown
	glRectf(x1, y1, x2, y2);
}

void Enemy::render(float delta)
{
	this->check_usable();

	this->hitbox->render(delta, 0.8f, 0.0f, 0.0f);
	this->render_gun();
}
