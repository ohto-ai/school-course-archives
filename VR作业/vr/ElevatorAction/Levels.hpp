#pragma once
class Level;
class Levels
{
public:
	Levels();
	~Levels();

	static Level *level1();
	static Level *level2();
	static Level *level3();
	static Level *level4();
};

