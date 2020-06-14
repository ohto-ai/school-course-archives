#include "Platform.hpp"
#include "Hitbox.hpp"

const float Platform::THICKNESS = 0.1f;
const float Platform::R = 0.35f;
const float Platform::G = 0.35f;
const float Platform::B = 0.35f;

Platform::Platform(int x, int y) : SingleFloorLevelObject(x, y)
{
	this->hitboxes.push_back(Hitbox::platform(x, y));
}

Platform::~Platform()
{
}

void Platform::process(float delta, Player *player)
{
}

void Platform::render(float delta)
{
	this->render_hitboxes(delta, this->R, this->G, this->B);
}
