#pragma once
#include "Elevator.hpp"
class Player;
class Level;
class ElevatorExit :
	public Elevator
{
	bool flashing = false;
	float flashing_time = 1.5f;
	float flashing_elapsed = 0.0f;
public:
	Level *level = nullptr;
	ElevatorExit(Level *level, int x = 1, float vspeed = 1.0f);
	~ElevatorExit();

	bool move_up() override;
	bool move_down() override;
	void check_usable() override;
	void process(float delta, Player *player) override;
	void render(float delta) override;
};

