#include "Wall.hpp"
#include "Hitbox.hpp"
#include "Platform.hpp"

Wall::Wall(int x, int y) : SingleFloorLevelObject(x, y)
{
	this->hitboxes.push_back(new Hitbox(this->x - 1.0f - Platform::THICKNESS / 2.0f, (float)this->y, this->x - 1.0f + Platform::THICKNESS / 2.0f, this->y - 1.0f, true));
}


Wall::~Wall()
{
}

void Wall::render(float delta)
{
	this->render_hitboxes(delta, Platform::R, Platform::G, Platform::B);
}

void Wall::process(float delta, Player * player)
{
}
