#pragma once
#include "SingleFloorLevelObject.hpp"
class Platform :
	public SingleFloorLevelObject
{
public:
	static const float THICKNESS;
	static const float R;
	static const float G;
	static const float B;

	Platform(int x, int y);
	~Platform();

	void process(float delta, Player *player) override;
	void render(float delta) override;
};

