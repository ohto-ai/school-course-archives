#include <utility>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include "Level.hpp"
#include "util.hpp"
#include "DocumentDoor.hpp"
#include "EnemyDoor.hpp"
#include "Platform.hpp"
#include "CollisionHelper.hpp"
#include "LevelManager.hpp"
#include "Game.hpp"
#include "ElevatorExit.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Wall.hpp"

#include <cstdio>
#include "glut/glut.h"


int Level::remaining_free()
{
	return this->size() - this->occupied.size();
}

void Level::generate_missing()
{
	this->generate_walls();
	this->generate_missing_spawnpoint();
	this->generate_missing_doors();
	this->generate_missing_platforms();
}

void Level::generate_walls()
{
	for (int y = 1; y <= this->height; y++) {
		this->objects.push_back(new Wall(1, y));
		this->objects.push_back(new Wall(this->width+1, y));
	}
}

void Level::generate_missing_spawnpoint()
{
	if(this->spawns.size() <= 0)
		for(int x = 1; x <= this->width; x++)
			for(int y = this->height; y >= 1; y--)
				if (this->occupied.count(std::make_pair(x, y)) == 0) {
					this->add_spawnpoint(x, y);
					//std::cout << "Added PlayerSpawnPoint." << std::endl;
					return;
				}
}

void Level::generate_roof()
{
	for (int x = 1; x <= this->width; x++)
		this->add_platform(x, this->height + 1);
}

void Level::generate_missing_doors()
{
	this->insert_document_doors();
	// Fill up the rest of free space with enemy doors
	for (int y = 1; y <= this->height; y++) {
		for (int x = 1; x <= this->width; x++) {
			if (this->occupied.count(std::make_pair(x, y)) == 0) { // Free position
				if (y < this->height) {
					this->add_xy(new EnemyDoor(x, y));
				}
				else {
					this->add_xy(new EnemyDoor(x, y, 2.0f, 5.0f, 0, 1)); // Go easy on the floor where the player spawns
				}
			}
		}
	}
}

void Level::generate_missing_platforms()
{
	for (int y = 1; y <= this->height; y++) {
		for (int x = 1; x <= this->width; x++) {
			std::pair<int, int> xy = std::make_pair(x, y);
			if (!this->platform_occupied.count(xy) && !this->elevator_occupied.count(xy)) { // Not occupied by either a platform or an elevator
				this->add_platform(x, y);
				//if (x == this->spawns.front()->x && y == this->spawns.front()->y) {
				//	this->hitboxes.push_back(this->objects.back()->hitboxes.front());
				//}
			}
		}
	}
}

void Level::insert_document_doors()
{
	int remaining_document = this->document_doors;
	while (this->remaining_free() > 0 && remaining_document > 0) {
		int posx, posy;
		do {	// Find a random free position in the level to insert document doors
			posx = randint(1, this->width);
			posy = randint(1, this->height);
		} while (this->occupied.count(std::make_pair(posx, posy)));
		this->add_xy(new DocumentDoor(posx, posy));
		--remaining_document;
		//std::cout << "Added DocumentDoor." << std::endl;
	}
}

Player *Level::spawn(Player * player)
{
	if (this->spawns.size() <= 0)
		throw std::exception("No spawn points for Player in Level");
	int rand_index = randint(0, this->spawns.size() - 1);
	return this->spawns.at(rand_index)->spawn(this, player);
}

void Level::game_over()
{
	this->manager->game->game_over();
}

void Level::add_exit()
{
	//this->add_elevator(new Elevator(1, 0, 1));
	this->add_elevator(new ElevatorExit(this));
}

void Level::add_hitboxes()
{
	for (LevelObject *lo : this->objects) {
		for (AbstractHitbox *h : lo->hitboxes) {
			this->hitboxes.push_back(h);
		}
	}
}

Level::Level(int width, int height, int document_doors, Player *player): width(width), height(height), document_doors(document_doors), player(player)
{
	this->add_exit();
}


Level::~Level()
{
	for (LevelObject *lo : this->objects)
		delete lo;
}

int Level::size()
{
	return this->width * this->height;
}

void Level::add_elevator(Elevator* e)
{
	// Check if elevator space is occupied/compromised
	for (int i = e->min_floor; i <= e->max_floor; i++) {
		auto xy = std::pair<int, int>(e->x, i);
		if (this->occupied.count(xy) || this->platform_occupied.count(xy)) {
			throw std::exception("Position occupied");
		}
	}
	// Add elevator
	for (int i = e->min_floor; i <= e->max_floor; i++) {
		auto xy = std::pair<int, int>(e->x, i);
		this->occupied.insert(xy);
		this->elevator_occupied.insert(xy);
	}
	this->objects.push_back(e);
}

void Level::add_platform(int x, int y)
{
	std::pair<int,int> xy = std::make_pair(x, y);
	if (this->platform_occupied.count(xy))
		throw std::exception("Position occupied");

	this->platform_occupied.insert(xy);
	this->objects.push_back(new Platform(x,y));
}

void Level::add_spawnpoint(int x, int y)
{
	if (this->occupied.count(std::make_pair(x, y)))
		throw std::exception("Position occupied");
	PlayerSpawnPoint *spawn = new PlayerSpawnPoint(x, y);
	this->add_xy(spawn);
	this->spawns.push_back(spawn);
}

void Level::add_xy(SingleFloorLevelObject * sflo)
{
	if (this->occupied.count(std::make_pair(sflo->x, sflo->y)))
		throw std::exception("Position occupied");
	this->occupied.insert(std::make_pair(sflo->x, sflo->y));
	this->objects.push_back(sflo);
}

void Level::set_player(Player * player)
{
	this->player = this->spawn(player);
}

void Level::move_player(float dx, float dy)
{
	//std::cout <<  dx << " dp " << dy << std::endl;
	std::pair<float, float>dxdy = CollisionHelper::move_and_slide(this->player->hitbox, dx, dy, this->hitboxes);
	//std::cout << dxdy.first << " ddp " << dxdy.second << std::endl;
	player->fx += dxdy.first;
	player->fy += dxdy.second;
	//std::cout << player->fx << " p " << player->fy << std::endl;
}

void Level::check_usable()
{
	if (!this->built)
		throw std::exception("Level hasn't been built");
}

void Level::kill_player()
{
	this->player_death = true;
}

void Level::exit()
{
	this->player->score += 2000;
	this->manager->go2next();
}

void Level::spawn_bullet(Bullet * bullet)
{
	this->bullets.push_back(bullet);
}

void Level::despawn_bullet(Bullet * bullet)
{
	auto it = std::find(this->bullets.begin(), this->bullets.end(), bullet);
	if (it != this->bullets.end()) {
		//delete *it;
		this->bullets.erase(it);
	}
}

void Level::spawn_enemy(Enemy * enemy)
{
	this->enemies.push_back(enemy);
}

void Level::despawn_enemy(Enemy * enemy)
{
	auto it = std::find(this->enemies.begin(), this->enemies.end(), enemy);
	if (it != this->enemies.end()) {
		//delete *it;
		this->enemies.erase(it);
	}
}

void Level::transition_to(Level * level)
{
	this->player->on_ground = false;
	this->player->jumping = false;
	this->player->firing = false;
	this->player->dying = false;
	this->player->jump_elapsed = 0.0f;
	this->player->fire_elapsed = 0.0f;
	this->player->elevator = nullptr;
	this->player->door = nullptr;
	level->set_player(this->player);
}

void Level::process(float delta)
{
	this->check_usable();
	if (this->player_death) {
		if (this->player_death_elapsed < 0.33f) {
			this->player_originalw = this->player->width;
			this->player_originalh = this->player->height;
		}
		else if(this->player_death_elapsed < this->player_death_duration - 0.66f) {
			this->player->width -= player_originalw * delta / (this->player_death_duration - 0.33f - 0.66f);
			this->player->height -= player_originalh * delta / (this->player_death_duration - 0.33f - 0.66f);
		}
		this->player_death_elapsed += delta;
		if (this->player_death_elapsed > this->player_death_duration) {
			this->player->width = this->player_originalw;
			this->player->height = this->player_originalh;
			this->player_death_elapsed = 0.0f;
			this->player_death = false;
			if (this->player->lives <= 0) {
				this->game_over();
			}
			else {
				this->spawn(this->player);
			}
		}
	}
	else {
		this->player->process(delta);
		for (LevelObject *object : this->objects) {
			object->process(delta, this->player);
		}
		for (Bullet *b : this->bullets) {
			b->process(delta);
		}
		for (Enemy *e : this->enemies) {
			e->process(delta);
		}
	}
}

void Level::render_stats()
{
	char textScore[20], textDocuments[20], textLives[20];
	sprintf_s(textScore, "Score: %07d", this->player->score);
	sprintf_s(textDocuments, "Documents: %2d/%2d", this->document_doors_opened, this->document_doors);
	sprintf_s(textLives, "Lives: %d", this->player->lives);

	void * font = GLUT_BITMAP_HELVETICA_12;
	float y = glutGet(GLUT_WINDOW_HEIGHT) - 12.0f;
	glColor3f(1.0f, 1.0f, 1.0f);

	beginText();
	drawString(font, 0.0f, y, textScore);
	//drawString(font, (glutGet(GLUT_WINDOW_WIDTH) - glutBitmapLength(font, (const unsigned char*)textDocuments)) / 2.0f, y, textDocuments);
	drawStringCentered(font, y, textDocuments);
	drawString(font, glutGet(GLUT_WINDOW_WIDTH) - glutBitmapLength(font, (const unsigned char*)textLives), y, textLives);
	endText();
}

void Level::render(float delta)
{
	this->check_usable();

	glLoadIdentity();
	glTranslatef(-1.0f, std::fmin(-1.0, -this->player->fy * 2.0f / (float)this->width), 0.0f);
	glScalef(2.0f / (float)this->width, 2.0f / (float)this->width, 1.0f);
	for (LevelObject *object : this->objects) {
		object->render(delta);
	}
	for (Enemy *e : this->enemies) {
		e->render(delta);
	}
	this->player->render(delta);
	for (Bullet *b : this->bullets) {
		b->render(delta);
	}
	glLoadIdentity();
	this->render_stats();
}

void Level::build()
{
	if (this->built)
		throw std::exception("Level has already been built");
	this->generate_missing();
	this->generate_roof();
	this->add_hitboxes();
	this->built = true;
}
