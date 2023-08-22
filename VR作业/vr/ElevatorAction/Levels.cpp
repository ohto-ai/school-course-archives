#include "Levels.hpp"
#include "Level.hpp"
#include "Elevator.hpp"
#include "ExtraLife.hpp"


Levels::Levels()
{
}


Levels::~Levels()
{
}

Level * Levels::level1()
{
	Level *level = new Level(5, 3, 1);
	level->add_elevator(new Elevator(4, 1, 3, false));
	level->add_xy(new ExtraLife(1, 2));
	level->build();
	return level;
}

Level * Levels::level2()
{
	Level *level = new Level(3, 10, 5);
	level->add_elevator(new Elevator(2, 1, 10));
	level->add_xy(new ExtraLife(3, 7));
	level->add_xy(new ExtraLife(1, 3));
	level->build();
	return level;
}

Level * Levels::level3()
{
	Level *level = new Level(5, 5, 4);
	level->add_elevator(new Elevator(4, 4, 5));
	level->add_elevator(new Elevator(2, 2, 4));
	level->add_elevator(new Elevator(4, 1, 2));
	level->build();
	return level;
}

Level * Levels::level4()
{
	Level *level = new Level(7, 5, 4);
	level->add_elevator(new Elevator(4, 3, 5, true));
	level->add_elevator(new Elevator(5, 1, 5, false));
	level->add_elevator(new Elevator(6, 4, 5, true));
	level->add_xy(new ExtraLife(7, 4));
	level->build();
	return level;
}
