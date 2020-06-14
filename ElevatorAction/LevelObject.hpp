#pragma once
#include "Usable.hpp"
#include "AbstractHitbox.hpp"
#include <vector>
class Player;
class LevelObject : public Usable
{
public:
	int x;
	std::vector<AbstractHitbox *> hitboxes = std::vector<AbstractHitbox *>();

	LevelObject(int x);
	~LevelObject();
	virtual void process(float delta, Player *player = nullptr) = 0;
	virtual void render(float delta) = 0;
	virtual void render_hitboxes(float delta, float r, float g, float b);
};

