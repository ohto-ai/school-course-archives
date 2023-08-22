#include "DocumentDoor.hpp"



DocumentDoor::DocumentDoor(int x, int y) : Door(x, y, 0.8f, 0.0f, 0.0f, true)
{
}


DocumentDoor::~DocumentDoor()
{
}

void DocumentDoor::activate(Player * player)
{
	if (!this->obtained) {
		++player->level->document_doors_opened;
		player->score += 500;
		this->r = 1.0f;
		this->g = 1.0f;
		this->b = 1.0f;
		this->obtained = true;
	}
}
