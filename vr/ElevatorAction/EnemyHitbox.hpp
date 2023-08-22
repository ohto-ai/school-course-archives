#pragma once
#include "AbstractHitbox.hpp"
#include "Enemy.hpp"
class Enemy;
class EnemyHitbox :
	public AbstractHitbox
{
public:
	Enemy *enemy;
	EnemyHitbox(Enemy *enemy);
	~EnemyHitbox();

	float x1() const override;
	float y1() const override;
	float x2() const override;
	float y2() const override;
};

