#pragma once
#include "Door.hpp"

class EnemyDoor :
	public Door
{
public:
	float min_wait_time;
	float max_wait_time;
	float wait_time;
	float wait_time_elapsed = 0.0f;
	int num_enemies;
	int num_spawned = 0;
	bool spawning = false;

	EnemyDoor(int x, int y, float min_wait_time = 0.0f, float max_wait_time = 4.0f, int min_enemies = 1, int max_enemies = 2);
	~EnemyDoor();

	void spawn_enemy(Player *player);
	void activate(Player *player) override;
	void on_closed() override;
	void process(float delta, Player *player) override;
};

