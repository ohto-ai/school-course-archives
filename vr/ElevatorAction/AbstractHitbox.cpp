#include "AbstractHitbox.hpp"
#include <algorithm>
#include "glut/glut.h"
#include "util.hpp"


AbstractHitbox::AbstractHitbox(bool solid) : solid(solid)
{
}


AbstractHitbox::~AbstractHitbox()
{
}

float AbstractHitbox::left() const
{
	return (float)std::min(this->x1(), this->x2());
}

float AbstractHitbox::right() const
{
	return (float)std::max(this->x1(), this->x2());
}

float AbstractHitbox::top() const
{
	return (float)std::max(this->y1(), this->y2());
}

float AbstractHitbox::bottom() const
{
	return (float)std::min(this->y1(), this->y2());
}

bool AbstractHitbox::collides(AbstractHitbox *h)
{
	return fle(this->left(), h->right()) && fge(this->right(), h->left()) &&
		fge(this->top(), h->bottom()) && fle(this->bottom(), h->top());
}

bool AbstractHitbox::intersects(AbstractHitbox *h)
{
	return flt(this->left(), h->right()) && fgt(this->right(), h->left()) &&
		fgt(this->top(), h->bottom()) && flt(this->bottom(), h->top());
}

void AbstractHitbox::render(float delta, float r, float g, float b)
{
	glColor3f(r, g, b);
	glRectf(this->x1(), this->y1(), this->x2(), this->y2());
}

