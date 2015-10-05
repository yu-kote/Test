#include "BossPlayer.h"



//*************************************************************
//箱と箱の当り判定
//*************************************************************

bool collision(Vec2f& pos, Vec2f& size, Vec2f& floor_pos, Vec2f& floor_size){

	return (pos.x() + size.x() >= floor_pos.x() && pos.x() <= floor_pos.x() + floor_size.x() &&
		pos.y() + size.y() >= floor_pos.y() && pos.y() <= floor_pos.y() + floor_size.y());

}


//*************************************************************
//初期化
//*************************************************************


void BOSSPLAYER::player_setup()
{

	player.pos = Vec2f(-WIN_WIDTH / 2, WIN_HEIGHT / 2);
	player.size = Vec2f(150, 170);
	player.cut_pos = Vec2f(0, 0);
	player.cut_size = Vec2f(512, 450);


	player.vector = Vec2f(0, 0);
	player.gravity = 1;
	player.jump_power = 25;
	player.speed = 0.2;
	player.knockback_motion = Vec2f(-50, 10);
	player.is_hit = false;
	player.is_jump = false;
	player.attack_total = 0;
	player.floor_count = 0;
}


//*************************************************************
//前に突っ込む処理
//*************************************************************


void BOSSPLAYER::boss_playermove(BOSS::Boss01& boss01, float attack_total)
{

	
	if (collision(player.pos, player.size, Vec2f(boss01.pos.x() + 500, boss01.pos.y()), boss01.size)){
		if (knockback_flag == false){
			player.vector = player.knockback_motion;
			ms_p.crash.play();
			boss01.HP01 -= attack_total;
			knockback_flag = true;
		}
	}

	if (player.pos.x() < -WIN_WIDTH / 2){
		player.is_hit = false;
		knockback_flag = false;
		player.vector.x() = 0;
		player.pos.x() = -WIN_WIDTH / 2;
	}
}

//*************************************************************
//アニメーション
//*************************************************************


void BOSSPLAYER::boss_playerdraw()
{

	index = (animation_count / 5) % 4;
	animation_count++;

	player.cut_pos.x() = (index % 4) * 512;
	//player.cut_pos.y() = (index / 4) * 512;

	switch (player_mode)
	{

	case BOSSPLAYER::PlayerMode::MOVE:

		drawTextureBox(player.pos.x(), player.pos.y(),
			player.size.x(), player.size.y(),
			player.cut_pos.x(), player.cut_pos.y(),
			player.cut_size.x(), player.cut_size.y(),
			hero, Color::white);

		break;

	case BOSSPLAYER::PlayerMode::HIT:




		break;
	case BOSSPLAYER::PlayerMode::JUMP:




		break;
	default:
		break;
	}




}

//*************************************************************
//攻撃にあたる判定
//*************************************************************

void BOSSPLAYER::boss_player_hit(BOSS::Status& get)
{
	//std::cout << get.bossattack << std::endl;
	switch (get.bossattack)
	{
	case BOSS::BossAttack::NONE:



		break;
	case BOSS::BossAttack::ATTACK_TOP:
		if (get.attack_animation_flag == true){
			if (collision(player.pos, player.size, get.attack_pos_top, get.atatck_range)){
				if (player.is_hit == false){
					player.vector = player.knockback_motion;
					ms_p.crash.play();
					player.is_hit = true;
				}
			}
		}
		break;
	case BOSS::BossAttack::ATTACK_MIDDLE:
		if (get.attack_animation_flag == true){
			if (collision(player.pos, player.size, get.attack_pos_middle, get.atatck_range)){
				if (player.is_hit == false){
					player.vector = player.knockback_motion;
					ms_p.crash.play();
					player.is_hit = true;
				}
			}
		}
		break;
	case BOSS::BossAttack::ATTACK_BOTTOM:
		if (get.attack_animation_flag == true){
			if (collision(player.pos, player.size, get.attack_pos_bottom, get.atatck_range)){
				if (player.is_hit == false){
					player.vector = player.knockback_motion;
					ms_p.crash.play();
					player.is_hit = true;
				}
			}
		}
		break;
	default:
		break;

	}




}

//*************************************************************
//アップデート
//*************************************************************

void BOSSPLAYER::player_update(BOSS::Status& get, float attack_total, Floor_boss& floor, BOSS::Boss01& boss01)
{

	boss_player_hit(get);
	hit_under_floor(floor.pos, floor.size);
	hit_floor(Vec2f(floor.pos.x(), floor.pos.y() + 256), floor.size);
	hit_floor(Vec2f(floor.pos.x(), floor.pos.y() + 512), floor.size);
	jump();
	if (get.gamestop == false)
	gravity();

	notHitFloorFlag();
	boss_playerdraw();
	boss_playermove(boss01, attack_total);


}

//*************************************************************
//よーわからん　
//*************************************************************

BOSSPLAYER::P_Get BOSSPLAYER::p_get()
{
	return BOSSPLAYER::P_Get{
		player.pos,
		player.size,
		player.vector,
		player.floor_count,
		player.is_jump,
	};
}

//*************************************************************
//床の判定をなくす
//*************************************************************

void BOSSPLAYER::notHitFloorFlag(){
	if (player.is_jump == true){
		if (env.isPushKey(GLFW_KEY_DOWN)){
			player.floor_count++;
			ms_p.jump_down.play();
			player.is_jump = false;
		}
	}

	if (player.floor_count > 0){
		++player.floor_count;
	}
	if (player.floor_count == 25)
		player.floor_count = 0;
}

//*************************************************************
//ジャンプ
//*************************************************************

void BOSSPLAYER::jump()
{
	if (player.is_jump == true){
		if (env.isPushKey(GLFW_KEY_SPACE)){
			player.vector.y() = player.jump_power;
			ms_p.jump_up.play();
			player.is_jump = false;
		}
	}
}
//*************************************************************
//重力
//*************************************************************

void BOSSPLAYER::gravity()
{
	player.vector.y() -= player.gravity;
	player.vector.x() += player.speed;
	player.pos += player.vector;
}


//*************************************************************
//床の判定
//*************************************************************

void BOSSPLAYER::hit_floor(Vec2f pos, Vec2f size)
{
	if (player.vector.y() < 0){
		if (player.floor_count == 0){
			if (collision(player.pos, player.size, pos, size))
			{
				player.pos.y() = pos.y() + size.y();
				player.vector.y() = 0;
				player.is_jump = true;
			}

		}
	}
}
//*************************************************************
//一番下の地面処理
//*************************************************************

void BOSSPLAYER::hit_under_floor(Vec2f pos, Vec2f size)
{
	if (player.vector.y() < 0){
		if (collision(player.pos, player.size, pos, size))
		{
			player.pos.y() = pos.y() + size.y();
			player.vector.y() = 0;
			player.is_jump = true;
		}
	}
}


void Member_boss(Vec2f pos, int attack, Texture_ tx){
	if (attack >= 2){
		drawTextureBox(pos.x() - 128, pos.y() + 60, 128, 128, 0, 0, 512, 512, tx.sub_chara[0]);
		if (attack >= 3){
			drawTextureBox(pos.x() - 220, pos.y() + 60, 128, 128, 0, 0, 512, 512, tx.sub_chara[1]);
			if (attack >= 4){
				drawTextureBox(pos.x() - 200, pos.y() + 150, 128, 128, 0, 0, 512, 512, tx.sub_chara[2]);
				if (attack >= 5){
					drawTextureBox(pos.x() - 310, pos.y() + 60, 128, 128, 0, 0, 512, 512, tx.sub_chara[3]);
					if (attack >= 6){
						drawTextureBox(pos.x() - 290, pos.y() + 160, 128, 128, 0, 0, 512, 512, tx.sub_chara[4]);
						if (attack >= 7){
							drawTextureBox(pos.x() - 350, pos.y() + 140, 128, 128, 0, 0, 512, 512, tx.sub_chara[5]);
							if (attack >= 8){
								drawTextureBox(pos.x() - 360, pos.y() + 250, 128, 128, 0, 0, 512, 512, tx.sub_chara[6]);
								if (attack >= 9){
									drawTextureBox(pos.x() - 400, pos.y() + 60, 128, 128, 0, 0, 512, 512, tx.sub_chara[7]);
									if (attack >= 10){
										drawTextureBox(pos.x() - 425, pos.y() + 140, 128, 128, 0, 0, 512, 512, tx.sub_chara[8]);
										if (attack >= 11){
											drawTextureBox(pos.x() - 430, pos.y() + 250, 128, 128, 0, 0, 512, 512, tx.sub_chara[9]);

										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void Stage_Boss01(int& scene, Player& player){

	BOSS boss1;
	//boss1.setup();

	BOSSPLAYER player_boss;

	FLOOR floor1;

	Texture bg = Texture("res/Image/grass.png");
	Texture ui = Texture("res/Image/ui.png");

	Font font("res/meiryo.ttc");

	Texture_ tx;
	tx.sub_chara[0] = Texture("res/title.image/knight.png");
	tx.sub_chara[1] = Texture("res/title.image/witch.png");
	tx.sub_chara[2] = Texture("res/title.image/priest.png");
	tx.sub_chara[3] = Texture("res/title.image/archer.png");
	tx.sub_chara[4] = Texture("res/title.image/fighter.png");
	tx.sub_chara[5] = Texture("res/title.image/knight.png");
	tx.sub_chara[6] = Texture("res/title.image/witch.png");
	tx.sub_chara[7] = Texture("res/title.image/archer.png");
	tx.sub_chara[8] = Texture("res/title.image/fighter.png");
	tx.sub_chara[9] = Texture("res/title.image/priest.png");
	while (env.isOpen())
	{
		env.begin();
		drawTextureBox(-WIN_WIDTH / 2, -WIN_HEIGHT / 2,
			WIN_WIDTH, WIN_HEIGHT,
			0, 0,
			WIN_WIDTH, WIN_HEIGHT,
			bg,
			Color::white);
		drawTextureBox(-WIN_WIDTH / 2, -WIN_HEIGHT / 2,
			WIN_WIDTH, WIN_HEIGHT,
			0, 0,
			WIN_WIDTH, WIN_HEIGHT,
			ui,
			Color::white);
		Member_boss(player_boss.player.pos, player.attack_power, tx);

		font.size(130);
		font.draw(std::to_string(boss1.boss_count / 60), Vec2f(430, 360), Color::black);
		font.draw(std::to_string(player.attack_power), Vec2f(-200, 360), Color::black);
		font.draw(std::to_string(player.have_money), Vec2f(-800, 360), Color::black);


		player_boss.player_update(boss1.get(), player.attack_power, floor1.floor, boss1.boss01);

		floor1.boss_floor_update(player_boss.player.pos,
			player_boss.player.size,
			player_boss.player.vector,
			player_boss.player.floor_count,
			player_boss.player.is_jump);

		boss1.boss_update(scene);
		boss1.boss_death_motion(scene);
		//boss1.boss_gameover(scene);
		//std::cout << scene << std::endl;

		if (boss1.boss_gameover_flag == true){
			break;
		}
		if (boss1.boss_clear_flag == true){
			break;
		}

		
		env.end();

	}



}

void Result(bool& music_flag, int& scene){
	Media clear = Media("res/Music/clear.wav");
	Font font = Font("res/meiryo.ttc");

	while (1){
		if (!env.isOpen()) exit(0);
		env.begin();
		if (music_flag == false){
			clear.play();
			music_flag = true;
		}
		font.size(300);
		font.draw("クリア", Vec2f(0, 0) - font.drawSize("クリア") / 2, Color::yellow);
		font.size(100);
		font.draw("Enterキーでタイトル", Vec2f(300, -300) - font.drawSize("Enterキーでタイトル") / 2, Color::yellow);

		if (env.isPushKey(GLFW_KEY_ENTER))
		{
			scene = 0;
			music_flag = false;
			break;
		}
		env.end();
	}
	

}

