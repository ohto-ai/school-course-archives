#include "Hitbox.hpp"
#include "Platform.hpp"

Hitbox::Hitbox(float x1, float y1, float x2, float y2, bool solid) : AbstractHitbox(solid)
{
	this->set_x1(x1);
	this->set_y1(y1);
	this->set_x2(x2);
	this->set_y2(y2);
}

Hitbox::~Hitbox()
{
}

Hitbox * Hitbox::platform(int x, int y)
{
	return new Hitbox((float)x - 1.0f, (float)y - 1.0f + Platform::THICKNESS, (float)x, (float)y - 1.0f, true);
}

float Hitbox::x1() const
{
	return this->_x1;
}

float Hitbox::y1() const
{
	return this->_y1;
}

float Hitbox::x2() const
{
	return this->_x2;
}

float Hitbox::y2() const
{
	return this->_y2;
}

void Hitbox::set_x1(float value)
{
	this->_x1 = value;
}

void Hitbox::set_y1(float value)
{
	this->_y1 = value;
}

void Hitbox::set_x2(float value)
{
	this->_x2 = value;
}

void Hitbox::set_y2(float value)
{
	this->_y2 = value;
}

