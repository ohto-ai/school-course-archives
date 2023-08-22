#include "BulletHitbox.hpp"
#include "Bullet.hpp"


BulletHitbox::BulletHitbox(Bullet * bullet) : AbstractHitbox(true), bullet(bullet)
{
}

BulletHitbox::~BulletHitbox()
{
}

float BulletHitbox::x1() const
{
	return this->bullet->fx - this->bullet->w / 2.0f;
}

float BulletHitbox::y1() const
{
	return this->bullet->fy + this->bullet->h / 2.0f;
}

float BulletHitbox::x2() const
{
	return this->bullet->fx + this->bullet->w / 2.0f;
}

float BulletHitbox::y2() const
{
	return this->bullet->fy - this->bullet->h / 2.0f;
}
