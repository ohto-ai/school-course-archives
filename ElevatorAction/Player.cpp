#include <iostream>
#include "glut/glut.h"
#include "Game.hpp"
#include "Player.hpp"
#include "util.hpp"
#include "CollisionHelper.hpp"
#include "Door.hpp"
#include "PlayerBullet.hpp"

Player::Player()
{
	this->hitbox = new PlayerHitbox(this);
}

Player::Player(Level *level, float fx, float fy, Orientation orientation): level(level), fx(fx), fy(fy), orientation(orientation)
{
	Player();
}


Player::~Player()
{
}

float Player::dfx(float delta)
{
	return this->velx * delta;
}

float Player::dfy(float delta)
{
	return this->vely * delta;
}

float Player::current_height()
{
	if (this->input == nullptr) {
		this->input = &this->level->manager->game->input;
	}
	if (this->input->down && !this->inside_elevator() && !this->dying)
		return this->height / 2.0f;
	return this->height;
}

float Player::gun_fx()
{
	return (this->hitbox->left() + this->hitbox->right()) / 2.0f + (float)this->orientation * this->width;
}

float Player::gun_fy()
{
	return this->fy + this->height * 0.75f;
}

bool Player::inside_elevator()
{
	return this->elevator != nullptr;
}

bool Player::near_door()
{
	return this->door != nullptr;
}

bool Player::crouching()
{
	return this->current_height() < this->height;
}

void Player::fire()
{
	if (!this->firing) {
		this->level->spawn_bullet(new PlayerBullet(this->level, (float)this->orientation * 2.0f));
		this->firing = true;
	}
}

void Player::die()
{
	this->dying = true;
	--this->lives;
	this->level->kill_player();
}

void Player::check_usable()
{
	if (this->level == nullptr)
		throw std::exception("Level is null");
}

std::pair<float, float> Player::process_player_commands()
{
	this->input = &this->level->manager->game->input;
	float dirx = 0.0f, diry = 0.0f;
	if (this->input->left) {
		dirx -= 1.0f;
		this->orientation = LEFT;
	}
	if (this->input->right) {
		dirx += 1.0f;
		this->orientation = RIGHT;
		//std::cout << "right" << std::endl;
	}
	if (this->input->up) {
		//std::cout << "lele" << std::endl;
		if (this->inside_elevator()) {
			this->elevator->move_up();
		}
		else {
			diry += 1.0f;
		}
	}
	else if (this->input->down && this->inside_elevator()) {
		this->elevator->move_down();
	}

	if (this->input->use) {
		if (this->near_door()) {
			this->door->opendoor();
		}
		else if (!this->crouching()) {
			this->fire();
		}
	}

	//std::cout << this->input->right << std::endl;
	return std::make_pair(dirx, diry);
}

void Player::elapse_jump(float delta)
{
	if (this->jumping) {
		this->jump_elapsed += delta;
		if (this->jump_elapsed > this->jump_cooldown) {
			this->jump_elapsed = 0.0f;
			this->jumping = false;
		}
	}
}

void Player::elapse_fire(float delta)
{
	if (this->firing) {
		this->fire_elapsed += delta;
		if (this->fire_elapsed > this->fire_cooldown) {
			this->fire_elapsed = 0.0f;
			this->firing = false;
		}
	}
}

void Player::process(float delta)
{
	this->check_usable();

	this->elapse_jump(delta);
	this->elapse_fire(delta);

	std::pair<float, float> dirxy = this->process_player_commands();
	float dirx = dirxy.first;
	float diry = dirxy.second;

	if (/*!this->on_ground ||*/ this->jumping) {
		diry = 0.0f;
		//std::cout << "!onground" << std::endl;
	}

	//v2normalize(&dirx, &diry);
	if (diry > 0) {
		this->jumping = true;
	}
	
	// Add movement direction's effect to player velocity
	this->velx = dirx * movement_speed;
	if(diry > 0.0f)
		this->vely = diry * jump_speed;

	// Subtract gravity
	this->vely -= std::fmax(2.0f, abs(this->vely)) * delta;
	if (this->vely < -2.0f)
		this->vely = -2.0f;
	//std::cout << this->velx << " " << this->vely << std::endl;

	float current_fy = this->fy;
	//std::cout << this->dfx(delta) << " " << this->dfy(delta) << std::endl;
	this->level->move_player(this->dfx(delta), this->dfy(delta));
	//std::cout << this->fx << std::endl;
	this->on_ground = current_fy == this->fy;
	if (this->on_ground) {
		//std::cout << "onground" << std::endl;
	}


	// Reset velocities after movement
	this->velx = 0.0f;
}

void Player::render_gun()
{
	if (!this->crouching()) {
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
}

void Player::render(float delta)
{
	this->check_usable();

	this->hitbox->render(delta, 0.0f, 0.8f, 0.0f);
	this->render_gun();
}
