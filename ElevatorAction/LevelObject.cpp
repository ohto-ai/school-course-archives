#include "LevelObject.hpp"



LevelObject::LevelObject(int x) : x(x)
{
}


LevelObject::~LevelObject()
{
	for (AbstractHitbox *ah : this->hitboxes) {
		delete ah;
	}
}

void LevelObject::render_hitboxes(float delta, float r, float g, float b)
{
	for (AbstractHitbox *ah : this->hitboxes) {
		ah->render(delta, r, g, b);
	}
}
