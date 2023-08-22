#pragma once
#include "Bullet.hpp"
class Enemy;
class EnemyBullet :
	public Bullet
{
	Enemy *enemy;
public:
	EnemyBullet(Enemy *enemy, float vx, float vy = 0.0f);
	~EnemyBullet();

	void process(float delta) override;
};

