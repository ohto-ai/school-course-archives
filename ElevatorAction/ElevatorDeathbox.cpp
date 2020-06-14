#include <cmath>
#include "ElevatorDeathbox.hpp"

float ElevatorDeathbox::_x1() const
{
	return (float)this->elevator->x - 1.0f;
}

float ElevatorDeathbox::_y1() const
{
	return (float)this->floor - 1.0f + Platform::THICKNESS / 2;
}

float ElevatorDeathbox::_x2() const
{
	return (float)this->elevator->x;
}

float ElevatorDeathbox::_y2() const
{
	return (float)this->floor - 1.0f;
}

bool ElevatorDeathbox::is_below_elevator() const
{
	return this->elevator->fy - 1.0f >= this->_top();
	return false;
}

ElevatorDeathbox::ElevatorDeathbox(Elevator * elevator, int floor) : AbstractHitbox(false), elevator(elevator), floor(floor)
{
}

ElevatorDeathbox::~ElevatorDeathbox()
{
}

float ElevatorDeathbox::x1() const
{
	return (this->is_below_elevator() ? this->_x1() : -1.0f);
}

float ElevatorDeathbox::y1() const
{
	return (this->is_below_elevator() ? this->_y1() : -1.0f);
}

float ElevatorDeathbox::x2() const
{
	return (this->is_below_elevator() ? this->_x2() : -1.0f);
}

float ElevatorDeathbox::y2() const
{
	return (this->is_below_elevator() ? this->_y2() : -1.0f);
}

float ElevatorDeathbox::_top() const
{
	return std::fmaxf(this->_y1(), this->_y2());
}

void ElevatorDeathbox::render(float delta, float r, float g, float b)
{
	if (this->is_below_elevator()) {
		AbstractHitbox::render(delta, r, g, b);
	}
}

