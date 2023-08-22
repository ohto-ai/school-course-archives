#pragma once
#include "Door.hpp"
#include "Player.hpp"
class DocumentDoor :
	public Door
{
	bool obtained = false;
public:
	DocumentDoor(int x, int y);
	~DocumentDoor();

	void activate(Player *player) override;
};

