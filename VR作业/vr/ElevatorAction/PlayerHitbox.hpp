#pragma once
#include "AbstractHitbox.hpp"
#include "Player.hpp"

class PlayerHitbox :
	public AbstractHitbox
{
public:
	Player *player;
	PlayerHitbox(Player *player);
	~PlayerHitbox();

	float x1() const override;
	float y1() const override;
	float x2() const override;
	float y2() const override;
};

