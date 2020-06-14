#pragma once
#include <vector>
#include "AbstractHitbox.hpp"
class CollisionHelper
{
public:
	CollisionHelper();
	~CollisionHelper();

	static bool will_collide(AbstractHitbox *moving_hitbox, float dx, float dy, AbstractHitbox *standing_hitbox);
	static bool collides_with_solid(AbstractHitbox *moving_hitbox, float dx, float dy, std::vector<AbstractHitbox *> hitboxes);
	static std::pair<float, float> move_nointersect(AbstractHitbox *moving_hitbox, float dx, float dy, AbstractHitbox *standing_hitbox);
	static std::pair<float, float> move_and_slide(AbstractHitbox *moving_hitbox, float dx, float dy, std::vector<AbstractHitbox *>standing_hitboxes, bool solid_only = true);
};

