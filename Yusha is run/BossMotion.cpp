#include "BossMotion.h"

//*************************************************************
//初期化
//*************************************************************


void BOSS::setup()
{

	random.setSeed(u_int(time(nullptr)));

	boss01.pos = Vec2f(0, -500);
	boss01.size = Vec2f(1500, 1000);
	boss01.cut_pos = Vec2f(0, 0);
	boss01.cut_size = Vec2f(2048, 1024);
	boss01.HP01 = 35;

	for (int i = 0; i < 5; i++){
		time_[i] = 0;
	}

}


//*************************************************************
//攻撃範囲
//*************************************************************

void BOSS::bossattackrange()
{

	switch (boss01.bossattack)
	{
	case BOSS::BossAttack::NONE:
		if (boss01.attack_animation_flag == false){
			wind_trans = 1;
		}
		break;
	case BOSS::BossAttack::ATTACK_TOP:
		if (boss01.attack_animation_flag == true){
			wind_trans -= wind_trans_speed;

			drawTextureBox(boss01.attack_pos_top.x(), boss01.attack_pos_top.y(),
				boss01.atatck_range.x(), boss01.atatck_range.y(),
				0, 0,
				boss01.atatck_range.x() - 100, 128,
				tx.wind, Color(1, 1, 1, wind_trans));
		}

		break;
	case BOSS::BossAttack::ATTACK_MIDDLE:

		if (boss01.attack_animation_flag == true){
			wind_trans -= wind_trans_speed;

			drawTextureBox(boss01.attack_pos_middle.x(), boss01.attack_pos_middle.y(),
				boss01.atatck_range.x(), boss01.atatck_range.y(),
				0, 0,
				boss01.atatck_range.x() - 100, 128,
				tx.wind, Color(1, 1, 1, wind_trans));
		}
		break;

	case BOSS::BossAttack::ATTACK_BOTTOM:


		if (boss01.attack_animation_flag == true){
			wind_trans -= wind_trans_speed;

			drawTextureBox(boss01.attack_pos_bottom.x(), boss01.attack_pos_bottom.y(),
				boss01.atatck_range.x(), boss01.atatck_range.y(),
				0, 0,
				boss01.atatck_range.x() - 100, 128,
				tx.wind, Color(1, 1, 1, wind_trans));
		}
		break;

	default:
		break;
	}

}

//*************************************************************
//ボスのアニメーション
//*************************************************************


void BOSS::bossanimation()
{
	drawFillBox(boss01.pos.x(), boss01.pos.y() + 800,
		boss01.HP01 * (boss_HP_line / boss_HP_max),
		30, Color::lime);

	if (boss01.HP01 < 0)
		boss01.HP01 = 0;



	if (boss01.gamestop == true){
		time_[1] = 0;
	}

	BOSS::boss_c = Color::white;
	switch (boss01.bossattack)
	{
	case BOSS::BossAttack::NONE:

		boss01.cut_pos.x() = 0;

		time_[1]++;

		if (time_[1] > change_time)
		{
			boss01.bossattack = (BossAttack)random(4);
			time_[1] = 0;
			music_flag = false;
		}

		drawTextureBox(boss01.pos.x(), boss01.pos.y(),
			boss01.size.x(), boss01.size.y(),
			boss01.cut_pos.x(), boss01.cut_pos.y(),
			boss01.cut_size.x(), boss01.cut_size.y(),
			tx.boss_normal, Color(1,1,1,boss_trans));

		break;
	case BOSS::BossAttack::ATTACK_TOP:


		time_[2]++;



		if (time_[2] > change_time)
		{
			boss01.bossattack = BossAttack::NONE;
			boss01.attack_animation_flag = false;
			time_[2] = 0;
		}

		if (time_[2] > change_time - change_attack_time && boss01.attack_animation_flag == false){
			boss01.cut_pos.x() = boss01.cut_size.x();
			if (music_flag == false){
				ms.boss01_swing.play();
				music_flag = true;
			}
			boss01.attack_animation_flag = true;
		}


		drawTextureBox(boss01.pos.x(), boss01.pos.y(),
			boss01.size.x(), boss01.size.y(),
			boss01.cut_pos.x(), boss01.cut_pos.y(),
			boss01.cut_size.x(), boss01.cut_size.y(),
			tx.bossattack_top, boss_c);
		break;

	case BOSS::BossAttack::ATTACK_MIDDLE:

		time_[3]++;

		if (time_[3] > change_time)
		{
			boss01.bossattack = BossAttack::NONE;
			boss01.attack_animation_flag = false;
			time_[3] = 0;
		}


		if (time_[3] > change_time - change_attack_time && boss01.attack_animation_flag == false){
			boss01.cut_pos.x() = boss01.cut_size.x();
			if (music_flag == false){
				ms.boss01_swing.play();
				music_flag = true;
			}
			boss01.attack_animation_flag = true;
		}

		drawTextureBox(boss01.pos.x(), boss01.pos.y(),
			boss01.size.x(), boss01.size.y(),
			boss01.cut_pos.x(), boss01.cut_pos.y(),
			boss01.cut_size.x(), boss01.cut_size.y(),
			tx.bossattack_middle, boss_c);
		break;
	case BOSS::BossAttack::ATTACK_BOTTOM:

		time_[4]++;

		if (time_[4] > change_time)
		{
			boss01.bossattack = BossAttack::NONE;
			boss01.attack_animation_flag = false;
			time_[4] = 0;
		}

		if (time_[4] > change_time - change_attack_time && boss01.attack_animation_flag == false){
			boss01.cut_pos.x() = boss01.cut_size.x();
			if (music_flag == false){
				ms.boss01_swing.play();
				music_flag = true;
			}
			boss01.attack_animation_flag = true;
		}

		drawTextureBox(boss01.pos.x(), boss01.pos.y(),
			boss01.size.x(), boss01.size.y(),
			boss01.cut_pos.x(), boss01.cut_pos.y(),
			boss01.cut_size.x(), boss01.cut_size.y(),
			tx.bossattack_bottom, boss_c);
		break;
	default:
		break;
	}

	time_[0]++;


}

//*************************************************************
//ボス死亡処理
//*************************************************************

void BOSS::boss_death_motion(int& scene)
{

	if (boss01.HP01 <= 0){
		boss01.gamestop = true;
		boss_trans -= 0.001;
		boss01.pos.x() += sin(boss_death_count += 0.5);
		boss01_BGM.gain(BGM_end -= 0.001);
		boss_count = 1;
	}
	
	if (boss_trans <= 0){
		scene = 3;
		boss_clear_flag = true;
	}
}

//*************************************************************
//ゲームオーバー
//*************************************************************

void BOSS::boss_gameover(int& scene)
{
	//std::cout << boss_count << std::endl;
	if(boss_clear_flag == false)
	boss_count--;

	if (boss_count < 0){
		scene = 4;
		boss_gameover_flag = true;
	}
}

//*************************************************************
//ゲッター
//*************************************************************

BOSS::Status BOSS::get()
{
	return BOSS::Status {
		boss01.pos,
		boss01.size,
		boss01.attack_pos_top,
		boss01.attack_pos_middle,
		boss01.attack_pos_bottom,
		boss01.atatck_range,
		boss01.attack_animation_flag,
		boss01.bossattack,
		boss01.HP01,
		boss01.gamestop
	};
}



//*************************************************************
//アップデート
//*************************************************************

void BOSS::boss_update(int& scene)
{

	bossanimation();
	bossattackrange();
	boss_death_motion(scene);
	boss_gameover(scene);
}