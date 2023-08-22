#pragma once
#include "SingleFloorLevelObject.hpp"
#include "Player.hpp"

class SingleFloorLevelObject;
class Level;
class PlayerSpawnPoint :
	public SingleFloorLevelObject
{
public:
	PlayerSpawnPoint(int x, int y);
	~PlayerSpawnPoint();

	Player *spawn(Level *level, Player *player);
	void process(float delta, Player *player) override;
	void render(float delta) override;
};

