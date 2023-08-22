#include "PlayerBullet.hpp"
#include "Bullet.hpp"
#include "Level.hpp"
#include "CollisionHelper.hpp"
#include "Enemy.hpp"

PlayerBullet::PlayerBullet(Level *level, float vx, float vy) : Bullet(level, level->player->gun_fx(), level->player->gun_fy(), vx, vy)
{
	this->r = 1.0f;
	this->g = 0.65f;
	this->b = 0.0f;
}


PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::process(float delta)
{
	float dx = this->dx(delta);
	float dy = this->dy(delta);
	for (Enemy *e : this->level->enemies) { // Kill enemy & despawn
		if (CollisionHelper::will_collide(&this->hitbox, dx, dy, e->hitbox)) {
			e->die();
			this->level->player->score += 100;
			this->level->despawn_bullet(this);
			return;
		}
	}
	if (CollisionHelper::collides_with_solid(&this->hitbox, dx, dy, this->level->hitboxes)) { // Collide with level geometry & despawn
		this->level->despawn_bullet(this);
	}
	else {
		this->fx += this->dx(delta);
		this->fy += this->dy(delta);
	}
}
