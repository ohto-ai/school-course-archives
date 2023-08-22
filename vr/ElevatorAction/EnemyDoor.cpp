#include "EnemyDoor.hpp"
#include "Player.hpp"
#include "util.hpp"
#include "Enemy.hpp"

EnemyDoor::EnemyDoor(int x, int y, float min_wait_time, float max_wait_time, int min_enemies, int max_enemies) : Door(x, y, 0.0f, 0.0f, 0.8f, false), min_wait_time(min_wait_time), max_wait_time(max_wait_time), num_enemies(randint(min_enemies, max_enemies))
{
}


EnemyDoor::~EnemyDoor()
{
}

void EnemyDoor::spawn_enemy(Player *player)
{
	Enemy *enemy = new Enemy();
	enemy->level = player->level;
	enemy->fx = (float)this->x - 0.5f - enemy->width / 2.0f;
	enemy->fy = (float)this->y - 1.0f + Platform::THICKNESS;
	enemy->face_player();
	player->level->spawn_enemy(enemy);
}

void EnemyDoor::activate(Player * player)
{
	this->spawn_enemy(player);
	this->num_spawned += 1;
}

void EnemyDoor::on_closed()
{
	this->wait_time_elapsed = 0.0f;
}

void EnemyDoor::process(float delta, Player *player)
{
	if (player->fy <= (float)this->y && player->fy >= (float)this->y - 1.0f && !this->spawning) { // Player is on the same floor as EnemyDoor and enemy spawning wasn't initiated
		this->spawning = true;
	}
	if (this->spawning && this->num_spawned < this->num_enemies) { // Spawning is initiated and there's still enemies left to spawn
		if (this->wait_time_elapsed == 0.0f) {
			this->wait_time = randfloat(this->min_wait_time, this->max_wait_time);
		}
		if (!this->open) { // Door is not in the process of spawning an enemy (open)
			this->wait_time_elapsed += delta;
			if (this->wait_time_elapsed >= this->wait_time) {
				this->opendoor();
			}
		}
	}
	Door::process(delta, player);
}
