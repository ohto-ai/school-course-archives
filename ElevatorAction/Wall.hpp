#pragma once
#include "SingleFloorLevelObject.hpp"

class Wall :
	public SingleFloorLevelObject
{
public:
	Wall(int x, int y);
	~Wall();

	void render(float delta) override;
	void process(float delta, Player *player = nullptr) override;
};

