#pragma once
#include "lib/framework.hpp"
#include "screen.h"
#include <iostream>

class BOSS
{
	struct Musics{
		Media boss01_swing = Media("res/Music/Boss01_hit.wav");
	};
	Musics ms;

	struct Textures{
		Texture boss_normal = Texture("res/Image/boss_normal.png");
		Texture bossattack_top = Texture("res/Image/boss_top.png");
		Texture bossattack_middle = Texture("res/Image/boss_middle.png");
		Texture bossattack_bottom = Texture("res/Image/boss_bottom.png");
		Texture wind = Texture("res/Image/wind.png");
	};
	Textures tx;

	Media boss01_BGM = Media("res/Music/Boss_BGM.wav");


public:
	enum BossAttack
	{
		NONE,
		ATTACK_TOP,
		ATTACK_MIDDLE,
		ATTACK_BOTTOM,
	};

	struct Boss01 {
		Vec2f pos;
		Vec2f size;
		Vec2f cut_pos;
		Vec2f cut_size;
		Vec2f attack_pos_top = Vec2f(-WIN_WIDTH / 2, 0);
		Vec2f attack_pos_middle = Vec2f(-WIN_WIDTH / 2, -MAP_HEIGHT);
		Vec2f attack_pos_bottom = Vec2f(-WIN_WIDTH / 2, -MAP_HEIGHT * 2);
		Vec2f atatck_range = Vec2f(WIN_WIDTH / 1.5, MAP_HEIGHT - 30);
		bool attack_animation_flag = false;
		BossAttack bossattack = BossAttack::NONE;

		float HP01;
		
		bool gamestop = false;
	};
	Boss01 boss01;

	struct Status
	{
		Vec2f pos;
		Vec2f size;
		Vec2f attack_pos_top;
		Vec2f attack_pos_middle;
		Vec2f attack_pos_bottom;
		Vec2f atatck_range;
		bool attack_animation_flag;
		BossAttack bossattack;
		float HP01;
		bool gamestop;
	};

	void setup();
	void bossanimation();
	void bossattackrange();
	void boss_death_motion(int& scene);
	void boss_gameover(int& scene);
	void boss_update(int& scene);

	Status get();

	BOSS(){
		setup();
		boss_HP_line = 500;
		boss_HP_max = 35;
		music_flag = false;
		boss01_BGM.play();
		BGM_end = 1;
		boss_count = 900;
		boss_clear_flag = false;
		boss_gameover_flag = false;

	}

	int boss_count;
	bool boss_clear_flag;
	bool boss_gameover_flag;

private:


	Color boss_c = Color::yellow;
	int time_[5];
	float change_time = 60;
	float change_attack_time = 20;
	
	bool music_flag;
	float BGM_end;

	float wind_trans = 0;
	float wind_trans_speed = 0.02;

	float boss_death_count = 0;
	float boss_trans = 1;
	float boss_HP_line;
	float boss_HP_max;
	

	Random random;
};


