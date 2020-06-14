#include <iostream>
#include <assert.h>
#include <cmath>
#include <stdexcept>
#include "Elevator.hpp"
#include "ElevatorHitbox.hpp"
#include "Player.hpp"
#include "util.hpp"

const float Elevator::R = 0.15f;
const float Elevator::G = 0.15f;
const float Elevator::B = 0.15f;

ElevatorHitbox * Elevator::make_hitbox_inside()
{
	assert(this->hitbox_top != nullptr && this->hitbox_bottom != nullptr);
	ElevatorHitbox *hitbox_inside = new ElevatorHitbox(this, Platform::THICKNESS, 1.0f - Platform::THICKNESS, false);
	return hitbox_inside;
}

void Elevator::init_hitboxes()
{
	this->hitbox_bottom = new ElevatorHitbox(this);
	this->hitbox_top = new ElevatorHitbox(this, 1.0f);
	this->hitbox_inside = this->make_hitbox_inside();
	this->hitboxes.push_back(hitbox_bottom);
	this->hitboxes.push_back(hitbox_top);
	this->hitboxes.push_back(hitbox_inside);
	
	for (int floor = this->min_floor; floor < this->max_floor; floor++) {
		ElevatorDeathbox *hitbox_death = new ElevatorDeathbox(this, floor);
		this->hitboxes_death.push_back(hitbox_death);
		this->hitboxes.push_back(hitbox_death);
	}
}

void Elevator::move_next()
{
	assert(this->max_floor > this->min_floor);
	assert(this->is_moving() == false);

	int next_floor = this->current_floor() + this->passive_direction;
	if (next_floor > this->max_floor || next_floor < this->min_floor)
		this->passive_direction *= -1;

	this->move_generic(this->passive_direction);
}

Elevator::Elevator(int x, int min_floor, int max_floor, bool initially_active, float vspeed) : LevelObject(x), min_floor(min_floor), max_floor(max_floor), vspeed(vspeed)
{
	if (this->max_floor <= this->min_floor)
		throw std::invalid_argument("Max. floor must be greater than min. floor");
	int start_floor;
	if (initially_active) {
		start_floor = randint(min_floor, max_floor);
		this->passive_direction = (randint(0, 1) == 0 ? -1 : 1);
	}
	else {
		start_floor = max_floor;
		this->passive_direction = 0;
	}
	this->fy = (float)start_floor;
	this->target_floor = start_floor;
	
	this->init_hitboxes();
}

Elevator::~Elevator()
{
}

int Elevator::current_floor()
{
	float trunc_val = (this->direction() == 1 ? std::floor(this->fy) : std::ceil(this->fy));
	return (int)trunc_val;
}

bool Elevator::is_moving()
{
	return this->current_floor() != this->target_floor;
}

bool Elevator::move_up()
{
	if (this->is_moving() || this->current_floor() >= this->max_floor)
		return false;
	else {
		this->target_floor = this->current_floor() + 1;
		this->passive_direction = 1;
	}
	return true;
}

bool Elevator::move_down()
{
	if (this->is_moving() || this->current_floor() <= this->min_floor)
		return false;
	else {
		this->target_floor = this->current_floor() - 1;
		this->passive_direction = -1;
	}
	return true;
}

bool Elevator::move_generic(int direction)
{
	assert(direction == 1 || direction == 0 || direction == -1);
	if (direction == 1)
		return this->move_up();
	else if (direction == -1)
		return this->move_down();
	return false;
}

int Elevator::direction()
{
	float diff = (float)this->target_floor - this->fy;
	if (diff > 0)
		return 1;
	else if (diff < 0)
		return -1;
	else
		return this->passive_direction;
}

void Elevator::process_player_inside(Player * player)
{
	if (player->hitbox->collides(this->hitbox_inside)) {
		player->elevator = this;
	}
	else if (player->elevator == this) {
		player->elevator = nullptr;
	}
}

void Elevator::process_player_deathbox(Player * player)
{
	for (ElevatorDeathbox *db : this->hitboxes_death) {
		if (player->hitbox->collides(db)) {
			player->die();
		}
	}
}

void Elevator::process(float delta, Player *player)
{
	this->process_player_deathbox(player);
	this->process_player_inside(player);

	if (this->is_moving()) {
		float sign = (float)this->direction();
		float deltafy = sign * this->vspeed * delta;
		if (sign > 0.0f && player->hitbox->collides(this->hitbox_bottom) || player->hitbox->collides(this->hitbox_top)) {
			float dpy = -player->fy;
			this->hitbox_top->solid = false;
			player->level->move_player(0.0f, deltafy);
			this->hitbox_top->solid = true;
			dpy += player->fy;
			this->fy += dpy;
		}
		else {
			this->fy += deltafy;
		}

		// Correct the fy value to match the exact value of current_floor when elevator reaches its destination
		if(sign * (this->fy - (float)this->target_floor) >= 0) {
			this->fy = (float)this->target_floor;
		}
	}
	else if (player->elevator == this) {
		this->wait_time_elapsed = 0.0f;
	}
	else {
		this->wait_time_elapsed += delta;
		if (this->wait_time_elapsed >= this->wait_time) {
			this->wait_time_elapsed = 0.0f;
			this->move_next();
		}
	}
}

void Elevator::render(float delta)
{
	this->hitbox_top->render(delta, this->R, this->G, this->B);
	this->hitbox_bottom->render(delta, this->R, this->G, this->B);
	this->hitbox_inside->render(delta, 0.15f, 0.0f, 0.6f);
	for(ElevatorDeathbox *hitbox_death : this->hitboxes_death)
		hitbox_death->render(delta, 0.6f, 0.0f, 0.0f);
}
