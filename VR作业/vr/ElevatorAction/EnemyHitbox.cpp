#include "EnemyHitbox.hpp"



EnemyHitbox::EnemyHitbox(Enemy *enemy) : AbstractHitbox(true), enemy(enemy)
{
}

EnemyHitbox::~EnemyHitbox()
{
}

float EnemyHitbox::x1() const
{
	return this->enemy->fx;
}

float EnemyHitbox::y1() const
{
	return this->enemy->fy + this->enemy->height;
}

float EnemyHitbox::x2() const
{
	return this->enemy->fx + this->enemy->width;
}

float EnemyHitbox::y2() const
{
	return this->enemy->fy;
}
