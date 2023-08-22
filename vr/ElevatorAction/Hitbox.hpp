#pragma once
#include "AbstractHitbox.hpp"
#include "Elevator.hpp"

class Hitbox : public AbstractHitbox
{
	float _x1, _y1;
	float _x2, _y2;
public:
	Hitbox(float x1, float y1, float x2, float y2, bool solid);
	~Hitbox();

	static Hitbox *platform(int x, int y);

	float x1() const override;
	float y1() const override;
	float x2() const override;
	float y2() const override;
	virtual void set_x1(float value);
	virtual void set_y1(float value);
	virtual void set_x2(float value);
	virtual void set_y2(float value);
};

