#include <iostream>
#include <assert.h>
#include "CollisionHelper.hpp"
#include "Hitbox.hpp"
#include "util.hpp"
#include "glut/glut.h"


CollisionHelper::CollisionHelper()
{
}


CollisionHelper::~CollisionHelper()
{
}

bool CollisionHelper::will_collide(AbstractHitbox * moving_hitbox, float dx, float dy, AbstractHitbox * standing_hitbox)
{
	Hitbox moved_hitbox = Hitbox(moving_hitbox->x1() + dx, moving_hitbox->y1() + dy, moving_hitbox->x2() + dx, moving_hitbox->y2() + dy, moving_hitbox->solid);
	return moved_hitbox.intersects(standing_hitbox);
}

bool CollisionHelper::collides_with_solid(AbstractHitbox * moving_hitbox, float dx, float dy, std::vector<AbstractHitbox*> hitboxes)
{
	for (AbstractHitbox *h : hitboxes) {
		if (!h->solid || moving_hitbox == h) {
			continue;
		}
		if (will_collide(moving_hitbox, dx, dy, h)) {
			return true;
		}
	}
	return false;
}

//std::pair<float, float> CollisionHelper::move_nointersect(AbstractHitbox * moving_hitbox, float dx, float dy, AbstractHitbox * standing_hitbox)
//{
//	if (moving_hitbox->intersects(standing_hitbox)) {
//		std::cout << dx << " " << dy << std::endl;
//		std::cout << "Hitboxes already intersect";
//		int asdlk;
//		std::cin >> asdlk;
//		throw std::exception("Hitboxes already intersect");
//	}
//	else if (standing_hitbox == nullptr || !will_collide(moving_hitbox, dy, dy, standing_hitbox) || (dx == 0 && dy == 0)) {
//		//std::cout << dx << " " << dy << std::endl;
//		return std::make_pair(dx, dy);
//	}
//	//else if (moving_hitbox->collides(standing_hitbox)) {
//	//	//std::cout << .0f << " " << 0.f << std::endl;
//	//	return std::make_pair(0.0f, 0.0f);
//	//}
//
//	// This fllowing code only works properly if the hitboxes do not already intersect and a collission is guaranteed
//	assert(!moving_hitbox->intersects(standing_hitbox));
//	assert(will_collide(moving_hitbox, dy, dy, standing_hitbox));
//	assert(dx != 0.0f || dy != 0.0f);
//	
//	float collision_hd, collision_vd; // Horizontal and vertical distance from collision
//	if (dx == 0.0f)
//		collision_hd = -1.0f; // Infinite
//	else {
//		collision_hd = (dx > 0 ? standing_hitbox->left() - moving_hitbox->right() : moving_hitbox->left() - standing_hitbox->right());
//		if (collision_hd < 0.0f)
//			collision_hd = 0.0f;
//	}
//
//	if (dy == 0.0f)
//		collision_vd = -1.0f; // Infinite
//	else {
//		collision_vd = (dy > 0 ? standing_hitbox->bottom() - moving_hitbox->top() : moving_hitbox->bottom() - standing_hitbox->top());
//		if (collision_vd < 0.0f)
//			collision_vd = 0.0f;
//	}
//
//	// At most one collission distance (horizontal or vertical) may be infinite
//	assert(collision_hd >= 0.0f || collision_vd >= 0.0f);
//	//float scale;
//	//if (collision_hd < 0.0f || collision_vd < collision_hd) { // Vertical foremost collision
//	//	assert(collision_vd <= std::fabsf(dy)); // Sanity check for vertical collission
//	//	scale = collision_vd / fabsf(dy);
//	//}
//	//else if (collision_vd < 0.0f || collision_hd <= collision_vd) { // Horizontal foremost or both vertical and horizontal collision (<=)
//	//	assert(collision_hd <= fabsf(dx)); // Sanity check for horizontal collission
//	//	scale = collision_hd / fabsf(dx);
//	//}
//	//
//	//assert(0.0f <= scale && scale <= 1.0f); // Sanity check for scale;
//	//return std::make_pair(scale * dx, scale * dy);
//
//	float new_dx, new_dy;
//	if (collision_hd < 0.0f)
//		new_dx = dx;
//	else
//		new_dx = fsgn(dx) * std::fmin(std::fabsf(dx), std::fabsf(collision_hd));
//
//	if (collision_vd < 0.0f)
//		new_dy = dy;
//	else
//		new_dy = fsgn(dy) * std::fmin(std::fabsf(dy), std::fabsf(collision_vd));
//
//	return std::make_pair(new_dx, new_dy);
//}

//std::pair<float, float> CollisionHelper::move_nointersect(AbstractHitbox * moving_hitbox, float dx, float dy, AbstractHitbox * standing_hitbox)//
//{
//	if (moving_hitbox->intersects(standing_hitbox)) {
//		std::cout << dx << " " << dy << std::endl;
//		std::cout << "Hitboxes already intersect";
//		int asdlk;
//		std::cin >> asdlk;
//		throw std::exception("Hitboxes already intersect");
//	}
//
//	float dx_new, dy_new;
//	for (dx_new = 0.0f; fabsf(dx_new) <= fabsf(dx); dx_new += fsgn2(dx) * 0.01f) {
//		//std::cout << "dx = " << dx << "; dx_new = " << dx_new << std::endl;
//		Hitbox moved_hitbox = Hitbox(moving_hitbox->x1() + dx_new, moving_hitbox->y1(), moving_hitbox->x2() + dx_new, moving_hitbox->y2(), moving_hitbox->solid);
//		if (moved_hitbox.intersects(standing_hitbox) && fabsf(dx_new) > 0.0f) {
//			dx_new -= fsgn2(dx) * 0.01f;
//			break;
//		}
//	}
//	for (dy_new = 0.0f; fabsf(dy_new) <= fabsf(dy); dy_new += fsgn2(dy) * 0.01f) {
//		Hitbox moved_hitbox = Hitbox(moving_hitbox->x1(), moving_hitbox->y1() + dy_new, moving_hitbox->x2(), moving_hitbox->y2() + dy_new, moving_hitbox->solid);
//		if (moved_hitbox.intersects(standing_hitbox) && fabsf(dy_new) > 0.0f) {
//			dy_new -= fsgn2(dy) * 0.01f;
//			break;
//		}
//	}
//
//	return std::make_pair(dx_new, dy_new);
//}

std::pair<float, float> CollisionHelper::move_nointersect(AbstractHitbox * moving_hitbox, float dx, float dy, AbstractHitbox * standing_hitbox)
{
	//if (moving_hitbox->intersects(standing_hitbox)) {
	//	throw std::exception("Hitboxes already overlap");
	//}

	float dx_new = 0.0f, dy_new = 0.0f;
	if (!will_collide(moving_hitbox, dx, 0.0f, standing_hitbox)) {
		dx_new = dx;
	}
	if (!will_collide(moving_hitbox, 0.0f, dy, standing_hitbox)) {
		dy_new = dy;
	}
	return std::make_pair(dx_new, dy_new);
}

std::pair<float, float> CollisionHelper::move_and_slide(AbstractHitbox * moving_hitbox, float dx, float dy, std::vector<AbstractHitbox*> standing_hitboxes, bool solid_only)
{
	AbstractHitbox *hmin = nullptr;
	auto current_xy = std::make_pair(dx, dy);
	if (solid_only && !moving_hitbox->solid) {
		return current_xy;
	}
	float min_x = dx;
	float min_y = dy;
	auto min_xy = current_xy;
	for (AbstractHitbox *h : standing_hitboxes) {
		if (solid_only && !h->solid) {
			continue;
		}
		auto new_xy = CollisionHelper::move_nointersect(moving_hitbox, dx, dy, h);
		if (fabsf(new_xy.first) < fabsf(min_x))
			min_x = new_xy.first;
		if (fabsf(new_xy.second) < fabsf(min_y))
			min_y = new_xy.second;
		if (v2len(new_xy) < v2len(min_xy)) {
			min_xy = new_xy;
			hmin = h;
		}
	}
	//std::cout << min_xy.first << " min " << min_xy.second << std::endl;
	if (hmin != nullptr) {
		//glColor3f(1.0f, 0.0f, 0.0f);
		//glRectf(hmin->left() - 0.05f, hmin->top() + 0.05f, hmin->right() + 0.05f, hmin->bottom() - 0.05f);
		//std::cout << hmin->top() << " h " << hmin->left() << " h " << hmin->bottom() << " h " << hmin->right() << std::endl;
	}
	//return min_xy;
	return std::make_pair(min_x, min_y);
}
