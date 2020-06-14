#pragma once
#include "AbstractHitbox.hpp"
class Bullet;
class BulletHitbox :
	public AbstractHitbox
{
	Bullet *bullet;
public:
	BulletHitbox(Bullet *bullet);
	~BulletHitbox();

	float x1() const override;
	float y1() const override;
	float x2() const override;
	float y2() const override;
};

