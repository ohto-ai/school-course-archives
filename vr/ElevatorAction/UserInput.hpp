#pragma once
class UserInput
{
public:
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool use = false;

	UserInput();
	~UserInput();

	void clear();
};

