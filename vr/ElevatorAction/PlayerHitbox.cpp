#include "PlayerHitbox.hpp"



PlayerHitbox::PlayerHitbox(Player *player) : AbstractHitbox(true), player(player)
{
}

PlayerHitbox::~PlayerHitbox()
{
}

float PlayerHitbox::x1() const
{
	return this->player->fx;
}

float PlayerHitbox::y1() const
{
	return this->player->fy + this->player->current_height();
}

float PlayerHitbox::x2() const
{
	return this->player->fx + this->player->width;
}

float PlayerHitbox::y2() const
{
	return this->player->fy;
}
