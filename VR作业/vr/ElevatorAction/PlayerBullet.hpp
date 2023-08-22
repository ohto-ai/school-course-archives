#pragma once
#include "Bullet.hpp"
class Player;
class PlayerBullet :
	public Bullet
{
public:
	PlayerBullet(Level *level, float vx, float vy = 0.0f);
	~PlayerBullet();

	void process(float delta) override;
};

