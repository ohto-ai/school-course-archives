#pragma once
#include "SingleFloorLevelObject.hpp"
class Hitbox;
class ExtraLife :
	public SingleFloorLevelObject
{
public:
	bool taken = false;
	float width = 0.35f;
	float height = 0.35f;
	float y_offset = 0.2f;
	Hitbox *hitbox;

	ExtraLife(int x, int y);
	~ExtraLife();

	void process(float delta, Player *player) override;
	void render(float delta) override;
};

