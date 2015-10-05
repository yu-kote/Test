#include "BossFloor.h"

bool FLOOR::IsHitFloorTop(Vec2f& pos, Vec2f& floor_pos, Vec2f& floor_size){

	return (pos.x() >= floor_pos.x() && pos.x() <= floor_pos.x() + floor_size.x() &&
		pos.y() >= floor_pos.y() && pos.y() <= floor_pos.y() + floor_size.y());

}

void FLOOR::boss_floor_setup(){

	floor.pos.x() = -WIN_WIDTH / 2;
	floor.pos.y() = -WIN_HEIGHT / 2;
	floor.size.x() = WIN_WIDTH;
	floor.size.y() = 32;



}

void FLOOR::boss_floor()
{


	drawTextureBox(floor.pos.x(), floor.pos.y(),
		floor.size.x(), floor.size.y(),
		0, 0,
		256, 256,
		block,
		Color::white);


	drawTextureBox(floor.pos.x(), floor.pos.y() + 256,
		floor.size.x(), floor.size.y(),
		0, 0,
		256, 256,
		block,
		Color::white);

	drawTextureBox(floor.pos.x(), floor.pos.y() + 512,
		floor.size.x(), floor.size.y(),
		0, 0,
		256, 256,
		block,
		Color::white);





}


void FLOOR::boss_hit_floor(Vec2f& pos, Vec2f& size, Vec2f& vector, int count, bool is_jump)
{
	if ((IsHitFloorTop(pos, floor.pos, floor.size) ||
		IsHitFloorTop(Vec2f(pos.x() + size.x(), pos.y()), floor.pos, floor.size)) &&count == 0 &&
		vector.y()<0){

		pos.y() = floor.pos.y() + floor.size.y();
		vector.y() = 0;
		is_jump = true;
	}

}



void FLOOR::boss_floor_update(Vec2f& pos, Vec2f& size, Vec2f& vector, int count, bool is_jump)
{

	boss_floor();
	boss_hit_floor(pos, size, vector, count, is_jump);

}
