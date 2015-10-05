#pragma once
#include "lib/framework.hpp"
#include "screen.h"
#include "BossMotion.h"
#include "BossFloor.h"
#include "Player.h"
#include <iostream>


bool collision(Vec2f& pos, Vec2f& size, Vec2f& floor_pos, Vec2f& floor_size);

bool isHitFloorTop(Vec2f& pos, Vec2f& floor_pos, Vec2f& floor_size);

class BOSSPLAYER
{

	struct Musics{
		Media crash = Media("res/Music/crash.wav");
		Media jump_up = Media("res/Music/jump_up.wav");
		Media jump_down = Media("res/Music/jump_down.wav");
	};
	Musics ms_p;

	Texture hero = Texture("res/Image/hero.png");

public:
	
	enum PlayerMode{
		MOVE,
		HIT,
		JUMP,
	};

	PlayerMode player_mode;

	struct Player_boss 
	{
		Vec2f pos;
		Vec2f size;
		Vec2f cut_pos;
		Vec2f cut_size;
		Vec2f vector;
		float gravity;
		float jump_power;
		float speed;
		Vec2f knockback_motion;
		bool is_hit;
		bool is_jump;
		int attack_total;
		int floor_count;
	};
	Player_boss player;

	struct P_Get
	{
		Vec2f pos;
		Vec2f size;
		Vec2f vector;
		int floor_count;
		bool is_jump;
	};

	P_Get p_get();

	void player_setup();
	void boss_playerdraw();
	void boss_playermove(BOSS::Boss01& boss01, float attack_total);
	void boss_player_hit(BOSS::Status& get);
	void player_update(BOSS::Status& get, float attack_total, Floor_boss& floor, BOSS::Boss01& boss01);
	void p_floor(Vec2f floor_pos, Vec2f floor_size);
	void notHitFloorFlag();
	void jump();
	void gravity();
	void hit_floor(Vec2f pos,Vec2f size);
	void hit_under_floor(Vec2f pos, Vec2f size);








	BOSSPLAYER()
	{
		knockback_flag = false;
		player_setup();
		animation_count = 0;
		index = 0;
		player_mode = MOVE;
		music_flag = false;
	}

	bool music_flag;

private:
	
	bool knockback_flag;

	int animation_count;
	int index;

};

void Member_boss(Vec2f pos, int attack, Texture& tx);

void Stage_Boss01(int& scene, Player& player);

void Result(bool& music_flag, int& scene);
