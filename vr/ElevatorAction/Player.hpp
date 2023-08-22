#pragma once
#include "Level.hpp"
#include "PlayerHitbox.hpp"
#include "UserInput.hpp"

class Level;
class PlayerHitbox;
class Elevator;
class Door;
class Player : public Usable
{
	std::pair<float, float> process_player_commands();
	void elapse_jump(float delta);
	void elapse_fire(float delta);
public:
	int lives = 2;
	int score = 0;
	float fx, fy; // Coordinates of the lower left point of the player
	float width = 0.2f, height = 0.5f;
	float velx = 0.0f, vely = 0.0f;
	float movement_speed = 1.0f;
	float jump_speed = 1.2f;
	float jump_elapsed = 0.0f;
	float jump_cooldown = 2.0f;
	float fire_elapsed = 0.0f;
	float fire_cooldown = 0.75f;
	bool on_ground = false;
	bool jumping = false;
	bool firing = false;
	bool dying = false;
	enum Orientation {
		LEFT = -1,
		RIGHT = 1
	} orientation = RIGHT;
	Level *level = nullptr;
	PlayerHitbox *hitbox = nullptr;
	UserInput *input = nullptr;
	Elevator *elevator = nullptr;
	Door *door = nullptr;

	Player();
	Player(Level *level, float fx, float fy, Orientation orientation = Orientation::RIGHT);
	~Player();

	float dfx(float delta);
	float dfy(float delta);
	float current_height();
	float gun_fx();
	float gun_fy();
	bool inside_elevator();
	bool near_door();
	bool crouching();
	void fire();
	void die();
	void check_usable() override;
	void process(float delta);
	void render_gun();
	void render(float delta);
};

