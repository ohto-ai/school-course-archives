#include "UserInput.hpp"



UserInput::UserInput()
{
}


UserInput::~UserInput()
{
}

void UserInput::clear()
{
	this->up = false;
	this->down = false;
	this->left = false;
	this->right = false;
	this->use = false;
}
