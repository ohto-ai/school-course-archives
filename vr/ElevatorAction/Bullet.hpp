#pragma once
#include "BulletHitbox.hpp"
class Level;
class Bullet
{
protected:
	Level *level;
public:
	float fx, fy; // Bullet center
	float vx, vy;
	float w = 0.08f, h = 0.04f;
	float r, g, b;
	BulletHitbox hitbox;
	
	Bullet(Level *level, float fx, float fy, float vx, float vy = 0.0f);
	~Bullet();

	float dx(float delta);
	float dy(float delta);
	virtual void process(float delta) = 0;
	virtual void render(float delta);
};

