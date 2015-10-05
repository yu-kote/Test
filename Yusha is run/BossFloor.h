#pragma once
#include "lib/framework.hpp"
#include "screen.h"
#include <iostream>


struct Floor_boss{

	Vec2f pos;
	Vec2f size;
};



class FLOOR
{

	

public:
	Texture block = Texture("res/Image/block.png");



	Floor_boss floor;

	bool IsHitFloorTop(Vec2f& pos, Vec2f& floor_pos, Vec2f& floor_size);

	void boss_floor_setup();
	void boss_floor();
	void boss_hit_floor(Vec2f& pos, Vec2f& size, Vec2f& vector, int count, bool is_jump);
	void boss_floor_update(Vec2f& pos, Vec2f& size, Vec2f& vector, int count, bool is_jump);
	

	FLOOR()
	{
		boss_floor_setup();
	}




private:






};



















