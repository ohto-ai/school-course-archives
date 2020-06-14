#include <assert.h>
#include <stdexcept>
#include "ElevatorExit.hpp"
#include "Player.hpp"
#include "Level.hpp"


ElevatorExit::ElevatorExit(Level *level, int x, float vspeed) : Elevator(x, -1, 1, false, vspeed), level(level)
{
}


ElevatorExit::~ElevatorExit()
{
}

bool ElevatorExit::move_up()
{
	return false;
}

bool ElevatorExit::move_down()
{
	if (this->level->document_doors_opened >= this->level->document_doors) {
		this->target_floor = this->min_floor;
		return true;
	}
	else {
		this->flashing = true;
		this->flashing_elapsed = 0.0f;
		return false;
	}
}

void ElevatorExit::check_usable()
{
	if (this->level == nullptr)
		throw std::exception("No level assigned");
}

void ElevatorExit::process(float delta, Player * player)
{
	assert(this->passive_direction == 0);

	if (this->flashing)
	{
		this->flashing_elapsed += delta;
		if (this->flashing_elapsed >= this->flashing_time) {
			this->flashing = false;
			this->flashing_elapsed = 0.0f;
		}
	}

	Elevator::process(delta, player);
	if (this->target_floor == this->min_floor && !this->is_moving()) {
		player->level->exit();
	}
}

void ElevatorExit::render(float delta)
{
	this->hitbox_top->render(delta, this->R, this->G, this->B);
	this->hitbox_bottom->render(delta, this->R, this->G, this->B);
	if (!this->flashing || this->flashing && (int)(this->flashing_elapsed / 0.1f) % 2 == 1) {
		this->hitbox_inside->render(delta, 0.25f, 0.0f, 1.0f);
	}
	else {
		this->hitbox_inside->render(delta, 0.8f, 0.0f, 0.0f);
	}
}
