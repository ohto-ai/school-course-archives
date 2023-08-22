#pragma once
#include "AbstractHitbox.hpp"
#include "Elevator.hpp"
class Elevator;
class ElevatorDeathbox :
	public AbstractHitbox
{
	int floor;
	float _x1() const;
	float _y1() const;
	float _x2() const;
	float _y2() const;
	bool is_below_elevator() const;
public:
	Elevator *elevator;

	ElevatorDeathbox(Elevator *elevator, int floor);
	~ElevatorDeathbox();

	float x1() const override;
	float y1() const override;
	float x2() const override;
	float y2() const override;
	float _top() const;

	void render(float delta, float r, float g, float b) override;
};

