#pragma once
#include "AbstractHitbox.hpp"
#include "Elevator.hpp"
#include "Platform.hpp"

class Elevator;
class ElevatorHitbox :
	public AbstractHitbox
{
public:
	Elevator *elevator;
	float offset_y;
	float height;

	ElevatorHitbox(Elevator *elevator, float offset_y = 0.0f, float height = Platform::THICKNESS, bool solid = true);
	~ElevatorHitbox();

	float x1() const override;
	float y1() const override;
	float x2() const override;
	float y2() const override;
};

