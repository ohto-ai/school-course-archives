#include "Bullet.hpp"
#include "BulletHitbox.hpp"

Bullet::Bullet(Level * level, float fx, float fy, float vx, float vy) : level(level), fx(fx), fy(fy), vx(vx), vy(vy), hitbox(BulletHitbox(this))
{
}

Bullet::~Bullet()
{
}

float Bullet::dx(float delta)
{
	return this->vx * delta;
}

float Bullet::dy(float delta)
{
	return this->vy * delta;
}

void Bullet::render(float delta)
{
	this->hitbox.render(delta, this->r, this->g, this->b);
}
