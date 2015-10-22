#include "Game.h"



//画像の構造体
Player player; //プレイヤーの構造体
Sword sword;
std::string now_area = "   ";
std::string now_money = " ";
std::string now_playerHp = " ";
std::string now_playerPower = " ";
std::string now_pos_x = "";
std::string now_pos_y = "";
std::string now_sword_num = "";
std::string now_startcount = "";
const int enemy_num = 30;
Enemy enemy[enemy_num];
Enemy enemy2[enemy_num];
Enemy enemy_boss1[3];
Sword sword_e[enemy_num];
Sword sword_e2[enemy_num];
Sword sword_boss1[3];
Animation attack_top_animation[9];
Animation attack_middle_animation[4];
Animation attack_under_animation[4];


//アニメーション
//struct&   動く物体の構造体
//count     使いたい枚数
//frame     何フレームでアニメーションするか
//num		何番目からアニメーションするか
void animation(MovingObject& chara, int count, int change_frame, int num){
	chara.time = (chara.time2++ / change_frame) % count + num;

	chara.cut_pos.x() = (chara.time % 4) * chara.cut_size.x();
	chara.cut_pos.y() = (chara.time / 4) * chara.cut_size.y();
}

//アニメーション
//struct&   動く物体の構造体
//count     使いたい枚数
//frame     何フレームでアニメーションするか
//num		何番目からアニメーションするか
void sword_animation(Sword& sword, int count, int change_frame, int num){
	sword.time = (sword.time2++ / change_frame) % count + num;

	sword.cut_pos.x() = (sword.time % 4) * sword.cut_size.x();
	sword.cut_pos.y() = (sword.time / 4) * sword.cut_size.y();
}

//アニメーションフレーム指定版
// pos.x   pos.y		切り取り位置
// size.x  size.y		切り取りサイズ
// num					パターン番号
// time					フレーム指定
// index				配列の要素数
void animation_delay(Vec2f& pos, Vec2f& size, int& num, int& time, int& index)
{
	pos.x() = (num % 4) * size.x();
	pos.y() = (num / 4) * size.y();

	time--;
	if (time <= 0){
		index++;
	}
}

//四角と四角の当たり判定
bool player_swordCollision(Vec2f box_pos, Vec2f box_size, Vec2f box1_pos, Vec2f box1_size) {

	return (
		box_pos.x() < box1_pos.x() + box1_size.x() &&
		box_pos.x() + box_size.x() > box1_pos.x() &&
		box_pos.y() < box1_pos.y() + box1_size.y() &&
		box_pos.y() + box_size.y() > box1_pos.y());
}

void textureInit(Textures& tx)
{
	tx.default_type = Texture("res/Image/Animation/default.png");
	tx.run = Texture("res/Image/Animation/run.png");
	tx.attack_top_right = Texture("res/Image/Animation/attack1.png");
	tx.attack_top_left = Texture("res/Image/Animation/attack1_m.png");
	tx.attack_middle_right = Texture("res/Image/Animation/attack2.png");
	tx.attack_middle_left = Texture("res/Image/Animation/attack2_m.png");
	tx.attack_under_right = Texture("res/Image/Animation/attack3.png");
	tx.attack_under_left = Texture("res/Image/Animation/attack3_m.png");
	tx.rolling_right = Texture("res/Image/Animation/rolling.png");
	tx.rolling_left = Texture("res/Image/Animation/rolling_m.png");
	tx.sword = Texture("res/Image/Animation/sword.png");
	tx.sword_kane = Texture("res/Image/Animation/ken_kane.png");
	tx.sword_kane2 = Texture("res/Image/Animation/ken_kane2.png");
	tx.sword_kane3 = Texture("res/Image/Animation/ken_kane3.png");
	tx.sword_kane4 = Texture("res/Image/Animation/ken_kane4.png");
	tx.sword_kane5 = Texture("res/Image/Animation/ken_kane5.png");
	tx.sword_kane6 = Texture("res/Image/Animation/ken_kane6.png");
	tx.sword_dai1 = Texture("res/Image/Animation/ken_dai1.png");
	tx.sword_hyt = Texture("res/Image/Animation/ken_hyt.png");
	tx.sword_hyt2 = Texture("res/Image/Animation/ken_hyt2.png");
	tx.sword_hyt3 = Texture("res/Image/Animation/ken_hyt_blue.png");
	tx.sword_uthii = Texture("res/Image/Animation/orenoturugi.png");

	tx.ladder = Texture("res/Image/Animation/radder.png");
	tx.dead = Texture("res/Image/Animation/dead.png");
	tx.title = Texture("res/Image/Title/title.png");
	tx.start = Texture("res/Image/Title/start.png");
	tx.press = Texture("res/Image/Title/press_enter.png");


	tx.attack_sound = Media("res/SE/swing.wav");
	tx.hit_sound = Media("res/SE/sword-slash3.wav");
	tx.cursor = Media("res/SE/cursor.wav");
	tx.warp = Media("res/SE/warp.wav");
	tx.buy = Media("res/SE/buy.wav");
	tx.higurasi = Media("res/SE/higurasi.wav");
	tx.higurasi.looping(1);
}

//*********************************************************************************************//
//プレイヤーの初期化																			　　//	
//*********************************************************************************************//
void charaInit(){

	player.size = Vec2f(200, 400);
	player.cut_pos = Vec2f(0, 0);
	player.cut_size = Vec2f(510, 510);
	player.direction = CharaInfo::RIGHT; //向き
	player.is_exists = CharaInfo::LIVE; //存在しているか
	player.camera = Vec2f(0, 0);
	player.stop_camera_x = MOVE;
	player.stop_camera_y = MOVE;

	player.type = DEFAULT;
	player.time = 0;
	player.time2 = 0;
	player.angle = 0;
	player.zoom = Vec2f(0.8, 0.8);
	player.center = Vec2f(0, 0);
	player.attack_time = 0;



	player.nockback_flag = false;
	player.nockback_time = 60;
	player.nockback = 1;
	player.hit_count = 0;
	player.flashing = 0;




	player.vector = Vec2f(0, 0);
	player.is_invin = false;
	player.invin_time = 20;
	player.animation_reset = false;
	player.is_attack = false;
	player.rolling_count = 0;
	player.rolling_flag = STOP;

	player.start_flag = false;
	player.is_move = MOVE;
	player.is_gravity = MOVE;
	player.ladder_flag = false;
	player.is_ladder_top = true;
	player.ladder_top_count = 0;
	player.change_ladder_top = false;
	player.ladder_down_flag = false;

	player.is_hitfloor = false;




	sword.attack_start = false;
	sword.attack_flag_first = false;
	sword.attack_flag_second = false;
	sword.attack_flag_third = false;
	sword.attack_count = 0;
	sword.attack_is_hit = false;
	sword.attack_start_time1 = 25;
	sword.attack_start_time2 = 18;
	sword.attack_start_time3 = 1;
	sword.attack_end_time_top = 44;
	sword.attack_end_time_middle = 35;
	sword.attack_end_time_under = 24;

	sword.attack_is_dec = false;


	sword.range = 512;
	sword.angle = 0;
	sword.size.x() = sword.range;
	sword.size.y() = sword.size.x() / 4;
	sword.cut_size = Vec2f(512, 128);
	sword.zoom = Vec2f(1, 1);
	sword.hit_range = Vec2f(512, 128);

	sword.attack_power = 10;


	for (int i = 0; i < 9; i++)
		attack_top_animation[i].num = i;
	for (int i = 0; i < 4; i++){
		attack_under_animation[i].num = i;
	}
	attack_middle_animation[0].num = 4;
	attack_middle_animation[1].num = 5;
	attack_middle_animation[2].num = 6;
	attack_middle_animation[3].num = 7;


	attack_top_animation[8].time = 0;
	attack_middle_animation[3].time = 0;
	attack_under_animation[3].time = 0;





}

//*********************************************************************************************//
//プレイヤーの動き																		   //	
//*********************************************************************************************//
void charaMove(Textures& tx, int& scene){
	//重力処理
	if (player.is_gravity == MOVE){
		player.vector.y() += player.gravity;
		player.camera.y() += player.vector.y();

		if (player.vector.y() <= player.gravity_max){
			player.vector.y() = player.gravity_max;
		}
	}
	else {
		player.vector.y() = 0;
		player.camera.y() = 0;
	}

	//***************************************************************************************************
	//はしごの処理
	//***************************************************************************************************


	//てっぺんのはしごが変わる時間
	if (player.is_ladder_top == true){
		player.ladder_top_count++;

	}
	//はしごの上判定変化処理
	if (player.ladder_top_count > 50){
		player.is_gravity = MOVE;
		player.is_move = MOVE;
		player.ladder_top_count = 0;
		player.is_ladder_top = false;
		//player.ladder_flag = false;
		player.change_ladder_top = true;
		player.is_invin = false;
		player.type = LADDER_CLIMB;
		for (int i = 0; i < 9; i++)
			attack_top_animation[i].num = i;
		for (int i = 0; i < 4; i++)
			attack_under_animation[i].num = i;

		attack_middle_animation[0].num = 4;
		attack_middle_animation[1].num = 5;
		attack_middle_animation[2].num = 6;
		attack_middle_animation[3].num = 7;

		attack_top_animation[8].time = 0;
		attack_middle_animation[3].time = 0;
		attack_under_animation[3].time = 0;

		env.flushInput();
	}


	//**************************************************************************************************
	//ローリング処理
	//**************************************************************************************************

	if (player.type != LADDER){
		if (player.is_move == MOVE){
			if (player.ladder_flag == false){
				if (sword.attack_start == false){
					if (player.rolling_flag == STOP){
						if (env.isPushKey(GLFW_KEY_SPACE)){
							player.rolling_flag = MOVE;
							player.time2 = 0;
						}
					}
				}
			}
		}
	}

	if (player.rolling_flag == MOVE)
	{

		player.rolling_count++;
		player.is_gravity = STOP;
		player.type = ROLLING;
		player.is_move = STOP;
		player.change_ladder_top = true;
		if (player.direction == CharaInfo::RIGHT)
		{
			if (player.rolling_count <= player.invin_time){
				player.is_invin = true;
				player.pos.x() += player.move_speed * 2;
			}
			if (player.rolling_count > player.invin_time){

				player.is_invin = false;
			}
			if (player.rolling_count >= player.invin_time * 2){
				player.rolling_flag = STOP;
				player.is_move = MOVE;
				player.rolling_count = 0;
				player.type = DEFAULT;
			}
		}
		if (player.direction == CharaInfo::LEFT)
		{
			if (player.rolling_count <= player.invin_time){
				player.is_invin = true;
				player.pos.x() -= player.move_speed * 2;
			}
			if (player.rolling_count > player.invin_time){
				player.is_invin = false;
			}
			if (player.rolling_count >= player.invin_time * 2){
				player.rolling_flag = STOP;
				player.is_move = MOVE;
				player.rolling_count = 0;
				player.type = DEFAULT;
			}
		}
	}


	//***************************************************************************************************
	//カメラワーク処理
	//***************************************************************************************************

	if (player.direction == CharaInfo::RIGHT){
		player.pos.x() += (player.camera_centering - 0.002) * (-player.centeriing_pos * 2 - player.pos.x());
		player.pos.y() += (player.camera_centering - 0.005) * (-500 - player.pos.y());
	}
	if (player.direction == CharaInfo::LEFT){
		player.pos.x() += (player.camera_centering - 0.002) * (player.centeriing_pos - player.pos.x());
		player.pos.y() += (player.camera_centering - 0.005) * (-500 - player.pos.y());
	}


	//***************************************************************************************************
	//攻撃処理
	//***************************************************************************************************
	if (player.direction == CharaInfo::RIGHT){
		sword.hit_range.x() = 512;
		sword.hit_pos.x() = player.pos.x() + player.size.x() / 2;
		sword.hit_pos.y() = player.pos.y() + player.size.y() / 2;
	}
	if (player.direction == CharaInfo::LEFT){
		sword.hit_range.x() = 512;
		sword.hit_pos.x() = player.pos.x() + player.size.x() / 2 - 512;
		sword.hit_pos.y() = player.pos.y() + player.size.y() / 2;
	}
	if (player.is_move == MOVE){
		if (player.ladder_flag == false){
			if (player.rolling_flag == STOP){
				if (sword.attack_start == false){
					if (env.isPushKey('K')){
						sword.attack_flag_first = true;
						sword.attack_start = true;
						player.is_move = STOP;
						player.stop_camera_x = STOP;

					}
				}
			}
		}
	}
	if (sword.attack_start == true){
		if (sword.attack_flag_first == true){
			sword.attack_count++;
			player.type = ATTACK_TOP;
			if (sword.attack_count == sword.attack_start_time1){
				sword.attack_is_dec = true;
			}
			else{
				sword.attack_is_dec = false;
			}
			if (sword.attack_count > 10 && sword.attack_count < 30){
				if (player.rolling_flag == STOP){
					if (env.isPushKey('K')){
						sword.attack_flag_second = true;
					}
				}
			}
			if (sword.attack_count > sword.attack_end_time_top){
				sword.attack_count = 0;
				if (sword.attack_flag_second == false){
					player.is_move = MOVE;
					player.stop_camera_x = MOVE;
					sword.attack_start = false;
				}
				sword.attack_flag_first = false;
			}
		}
		if (sword.attack_flag_first == false){
			if (sword.attack_flag_second == true){
				sword.attack_count++;
				player.type = ATTACK_MIDDLE;
				if (sword.attack_count > 12 && sword.attack_count < 27){
					if (player.direction == CharaInfo::RIGHT){
						player.pos.x() += player.move_speed / 4;
					}
					if (player.direction == CharaInfo::LEFT){
						player.pos.x() -= player.move_speed / 4;
					}
				}
				if (sword.attack_count == sword.attack_start_time2){
					sword.attack_is_dec = true;
				}
				else{
					sword.attack_is_dec = false;
				}
				if (player.rolling_flag == STOP){
					if (env.isPushKey('K')){
						sword.attack_flag_third = true;
					}
				}
				if (sword.attack_count > sword.attack_end_time_middle){
					sword.attack_count = 0;
					if (sword.attack_flag_third == false){
						player.is_move = MOVE;
						player.stop_camera_x = MOVE;
						sword.attack_start = false;
					}
					sword.attack_flag_second = false;
				}
			}
		}

		if (sword.attack_flag_second == false){
			if (sword.attack_flag_third == true){
				sword.attack_count++;
				player.type = ATTACK_UNDER;
				if (sword.attack_count > 2 && sword.attack_count < 17){
					if (player.direction == CharaInfo::RIGHT){
						player.pos.x() += player.move_speed / 4;
					}
					if (player.direction == CharaInfo::LEFT){
						player.pos.x() -= player.move_speed / 4;
					}
				}
				if (sword.attack_count == sword.attack_start_time3){
					sword.attack_is_dec = true;
				}
				else{
					sword.attack_is_dec = false;
				}
				if (sword.attack_count > sword.attack_end_time_under){
					sword.attack_count = 0;
					player.is_move = MOVE;
					player.stop_camera_x = MOVE;
					sword.attack_start = false;
					sword.attack_flag_third = false;
				}
			}
		}
	}

	//*********************************************************************************
	//攻撃ヒット処理
	//*********************************************************************************
	for (int i = 0; i < enemy_num; i++){
		if (sword_e[i].attack_is_dec == true){
			if (player.is_invin == false){
				if (player_swordCollision(player.pos, player.size, sword_e[i].hit_pos, sword_e[i].hit_range)){
					player.HP -= enemy[i].power;
					player.nockback_flag = true;
					if (player.pos.x() > enemy[i].pos.x())
						player.nockback = 1;
					if (player.pos.x() < enemy[i].pos.x())
						player.nockback = -1;
					tx.hit_sound.play();
				}
			}
		}
		if (sword_e2[i].attack_is_dec == true){
			if (player.is_invin == false){
				if (player_swordCollision(player.pos, player.size, sword_e2[i].hit_pos, sword_e2[i].hit_range)){
					player.HP -= enemy2[i].power;
					player.nockback_flag = true;
					if (player.pos.x() > enemy2[i].pos.x())
						player.nockback = 1;
					if (player.pos.x() < enemy2[i].pos.x())
						player.nockback = -1;
					tx.hit_sound.play();
				}
			}
		}
		if (player.money < player.max_money){
			player.money++;
		}
	}
	for (int i = 0; i < 3; i++){
		if (sword_boss1[i].attack_is_dec == true){
			if (player.is_invin == false){
				if (player_swordCollision(player.pos, player.size, sword_boss1[i].hit_pos, sword_boss1[i].hit_range)){
					player.HP -= enemy_boss1[i].power;
					player.nockback_flag = true;
					if (player.pos.x() > enemy_boss1[i].pos.x())
						player.nockback = 1;
					if (player.pos.x() < enemy_boss1[i].pos.x())
						player.nockback = -1;
					tx.hit_sound.play();
				}
			}
		}
	}

	if (player.nockback_flag == true){
		player.hit_count++;
		player.flashing++;
		if (player.hit_count < player.nockback_time){
			player.is_move = STOP;
			player.pos.x() += 3 * player.nockback;
		}
		else{
			player.nockback_flag = false;
			player.hit_count = 0;
			player.flashing = 0;
			player.is_move = MOVE;
		}
	}



	//***************************************************************************************************
	//スタートカウント
	//***************************************************************************************************
	if (player.start_flag == false){
		player.start_count++;
	}


	//***************************************************************************************************
	//アニメーションのフレームリセット
	//***************************************************************************************************

	if (!env.isPressKey('A') && !env.isPressKey('D') && sword.attack_start == false && player.ladder_flag == false /*&& !env.isPressKey('L') */ && player.rolling_flag == STOP)
	{
		player.type = DEFAULT;
	}
	if (player.ladder_flag == false){
		if (env.isPushKey('A') || env.isPushKey('D')){
			if (player.rolling_flag == STOP){
				player.time2 = 0;
			}
		}
		if (player.HP <= 0){
			player.HP = 0;
			player.is_exists = CharaInfo::DEAD;
		}
	}
	if (player.is_exists == CharaInfo::DEAD){
		scene++;
	}
	if (env.isPressKey('B')){
		player.power++;
		player.HP++;
		player.HP_max++;
	}
}

//*********************************************************************************************//
//キャラのアニメーション																		   //	
//*********************************************************************************************//
void charaDraw(Textures& tx){

	if (attack_top_animation[8].time <= 0 || attack_middle_animation[3].time <= 0 || attack_under_animation[3].time <= 0){
		attack_top_animation[0].time = 3;
		attack_top_animation[1].time = 2;
		attack_top_animation[2].time = 3;
		attack_top_animation[3].time = 15;
		attack_top_animation[4].time = 1;
		attack_top_animation[5].time = 1;
		attack_top_animation[6].time = 12;
		attack_top_animation[7].time = 3;
		attack_top_animation[8].time = 4;

		attack_middle_animation[0].time = 12;
		attack_middle_animation[1].time = 15;
		attack_middle_animation[2].time = 1;
		attack_middle_animation[3].time = 7;

		attack_under_animation[0].time = 3;
		attack_under_animation[1].time = 1;
		attack_under_animation[2].time = 14;
		attack_under_animation[3].time = 6;
		player.index = 0;
	}


	if (env.isPushKey(GLFW_KEY_UP)){
		tx.cursor.play();
		(sword.type < 12) ? ++sword.type : 0;
	}
	if (env.isPushKey(GLFW_KEY_DOWN)){
		tx.cursor.play();
		(sword.type > 0) ? --sword.type : 12;
	}
	if (player.type != ROLLING && player.type != LADDER_CLIMB){
		switch (sword.type){
		case 0:
			now_sword_num = "ふつう";
			drawTextureBox(sword.pos.x(), sword.pos.y(),
						   sword.size.x(), sword.size.y(),
						   0, 0,
						   sword.cut_size.x(), sword.cut_size.y(),
						   tx.sword, Color(0, 0, 0, 0.5 + 0.5* cos(player.flashing)),
						   sword.angle, sword.zoom, Vec2f(0, sword.size.y() / 2));
			break;
		case 1:
			now_sword_num = "かねやま作１";
			drawTextureBox(sword.pos.x(), sword.pos.y(),
						   sword.size.x(), sword.size.y(),
						   0, 0,
						   sword.cut_size.x(), sword.cut_size.y(),
						   tx.sword_kane, Color(1, 1, 1, 0.5 + 0.5* cos(player.flashing)),
						   sword.angle, sword.zoom, Vec2f(0, sword.size.y() / 2));
			break;
		case 2:
			now_sword_num = "かねやま作２";
			drawTextureBox(sword.pos.x(), sword.pos.y(),
						   sword.size.x(), sword.size.y(),
						   0, 0,
						   sword.cut_size.x(), sword.cut_size.y(),
						   tx.sword_kane2, Color(1, 1, 1, 0.5 + 0.5* cos(player.flashing)),
						   sword.angle, sword.zoom, Vec2f(0, sword.size.y() / 2));
			break;

		case 3:
			now_sword_num = "かねやま作３";
			drawTextureBox(sword.pos.x(), sword.pos.y(),
						   sword.size.x(), sword.size.y(),
						   0, 0,
						   sword.cut_size.x(), sword.cut_size.y(),
						   tx.sword_kane3, Color(1, 1, 1, 0.5 + 0.5* cos(player.flashing)),
						   sword.angle, sword.zoom, Vec2f(0, sword.size.y() / 2));
			break;
		case 4:
			now_sword_num = "かねやま作４";
			drawTextureBox(sword.pos.x(), sword.pos.y(),
						   sword.size.x(), sword.size.y(),
						   0, 0,
						   sword.cut_size.x(), sword.cut_size.y(),
						   tx.sword_kane4, Color(1, 1, 1, 0.5 + 0.5* cos(player.flashing)),
						   sword.angle, sword.zoom, Vec2f(0, sword.size.y() / 2));
			break;
		case 5:
			now_sword_num = "かねやま作５";
			drawTextureBox(sword.pos.x(), sword.pos.y(),
						   sword.size.x(), sword.size.y(),
						   0, 0,
						   sword.cut_size.x(), sword.cut_size.y(),
						   tx.sword_kane5, Color(1, 1, 1, 0.5 + 0.5* cos(player.flashing)),
						   sword.angle, sword.zoom, Vec2f(0, sword.size.y() / 2));
			break;
		case 6:
			now_sword_num = "かねやま作６";
			drawTextureBox(sword.pos.x(), sword.pos.y(),
						   sword.size.x(), sword.size.y(),
						   0, 0,
						   sword.cut_size.x(), sword.cut_size.y(),
						   tx.sword_kane6, Color(1, 1, 1, 0.5 + 0.5* cos(player.flashing)),
						   sword.angle, sword.zoom, Vec2f(0, sword.size.y() / 2));
			break;
		case 7:
			now_sword_num = "大ちゃん作";
			drawTextureBox(sword.pos.x(), sword.pos.y(),
						   sword.size.x(), sword.size.y(),
						   0, 0,
						   sword.cut_size.x(), sword.cut_size.y(),
						   tx.sword_dai1, Color(1, 1, 1, 0.5 + 0.5* cos(player.flashing)),
						   sword.angle, sword.zoom, Vec2f(0, sword.size.y() / 2));
			break;
		case 8:
			now_sword_num = "ほしな作１";
			drawTextureBox(sword.pos.x(), sword.pos.y(),
						   sword.size.x(), sword.size.y(),
						   0, 0,
						   sword.cut_size.x(), sword.cut_size.y(),
						   tx.sword_hyt, Color(1, 1, 1, 0.5 + 0.5* cos(player.flashing)),
						   sword.angle, sword.zoom, Vec2f(0, sword.size.y() / 2));
			break;
		case 9:
			now_sword_num = "ほしな作２";
			drawTextureBox(sword.pos.x(), sword.pos.y(),
						   sword.size.x(), sword.size.y(),
						   0, 0,
						   sword.cut_size.x(), sword.cut_size.y(),
						   tx.sword_hyt2, Color(1, 1, 1, 0.5 + 0.5* cos(player.flashing)),
						   sword.angle, sword.zoom, Vec2f(0, sword.size.y() / 2));
			break;
		case 10:
			now_sword_num = "ほしな作３";
			sword_animation(sword, 8, 5, 0);
			drawTextureBox(sword.pos.x(), sword.pos.y(),
						   sword.size.x(), sword.size.y(),
						   sword.cut_pos.x(), sword.cut_pos.y(),
						   sword.cut_size.x(), sword.cut_size.y(),
						   tx.sword_hyt3, Color(1, 1, 1, 0.5 + 0.5* cos(player.flashing)),
						   sword.angle, sword.zoom, Vec2f(0, sword.size.y() / 2));
			break;
		case 11:
			now_sword_num = "ウッチー作";
			drawTextureBox(sword.pos.x(), sword.pos.y(),
						   sword.size.x(), sword.size.y(),
						   0, 0,
						   sword.cut_size.x(), sword.cut_size.y(),
						   tx.sword_uthii, Color(1, 1, 1, 0.5 + 0.5* cos(player.flashing)),
						   sword.angle, sword.zoom, Vec2f(0, sword.size.y() / 2));
			break;
		}
	}



	Vec2f displace = Vec2f(20, 50);

	switch (player.type)
	{
	case DEFAULT:
		player.se_flag = false;
		if (player.direction == CharaInfo::RIGHT){
			animation(player, 3, 20, 0);
			drawTextureBox(player.pos.x() + player.centering_size, player.pos.y(),
						   player.cut_size.x(), player.cut_size.y(),
						   player.cut_pos.x(), player.cut_pos.y(),
						   player.cut_size.x(), player.cut_size.y(),
						   tx.default_type, Color(0, 0, 0, 0.5 + 0.5* cos(player.flashing)),
						   player.angle, player.zoom, player.center);
			sword.zoom.x() = 1;
			switch (player.time){
			case 0:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + displace.x(), player.pos.y() + player.size.y() / 2 + displace.y());
				sword.angle = -160 * one_angle;
				break;
			case 1:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + displace.x(), player.pos.y() + player.size.y() / 2 + displace.y());
				sword.angle = -160 * one_angle;
				break;
			case 2:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + displace.x(), player.pos.y() + player.size.y() / 2 + displace.y());
				sword.angle = -160 * one_angle;
				break;

			}
		}
		else if (player.direction == CharaInfo::LEFT){
			animation(player, 3, 20, 4);
			drawTextureBox(player.pos.x() + player.centering_size, player.pos.y(),
						   player.cut_size.x(), player.cut_size.y(),
						   player.cut_pos.x(), player.cut_pos.y(),
						   player.cut_size.x(), player.cut_size.y(),
						   tx.default_type, Color(0, 0, 0, 0.5 + 0.5* cos(player.flashing)),
						   player.angle, player.zoom, player.center);
			sword.zoom.x() = -1;
			switch (player.time){
			case 4:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - displace.x(),
								  player.pos.y() + player.size.y() / 2 + displace.y());
				sword.angle = 160 * one_angle;
				sword.zoom.x() = -1;
				break;
			case 5:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - displace.x(),
								  player.pos.y() + player.size.y() / 2 + displace.y());
				sword.angle = 160 * one_angle;
				sword.zoom.x() = -1;
				break;
			case 6:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - displace.x(),
								  player.pos.y() + player.size.y() / 2 + displace.y());
				sword.angle = 160 * one_angle;
				sword.zoom.x() = -1;
				break;

			}
		}
		break;
	case RUN:
		if (player.direction == CharaInfo::RIGHT){
			animation(player, 5, 6, 0);
			drawTextureBox(player.pos.x() + player.centering_size, player.pos.y(),
						   player.cut_size.x(), player.cut_size.y(),
						   player.cut_pos.x(), player.cut_pos.y(),
						   player.cut_size.x(), player.cut_size.y(),
						   tx.run, Color(0, 0, 0, 0.5 + 0.5* cos(player.flashing)),
						   player.angle, player.zoom, player.center);
			sword.zoom.x() = 1;
			switch (player.time){
			case 0:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + displace.x(),
								  player.pos.y() + player.size.y() / 2 + displace.y());
				sword.angle = -160 * one_angle;
				break;
			case 1:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + displace.x() + 10,
								  player.pos.y() + player.size.y() / 2 + displace.y() - 2);
				sword.angle = -160 * one_angle;
				break;
			case 2:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + displace.x() + 15,
								  player.pos.y() + player.size.y() / 2 + displace.y() - 1);
				sword.angle = -160 * one_angle;
				break;
			case 3:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + displace.x() + 25,
								  player.pos.y() + player.size.y() / 2 + displace.y());
				sword.angle = -160 * one_angle;
				break;
			case 4:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + displace.x() + 10,
								  player.pos.y() + player.size.y() / 2 + displace.y());
				sword.angle = -160 * one_angle;
				break;
			}
		}
		else if (player.direction == CharaInfo::LEFT){
			animation(player, 5, 6, 8);
			drawTextureBox(player.pos.x() + player.centering_size, player.pos.y(),
						   player.cut_size.x(), player.cut_size.y(),
						   player.cut_pos.x(), player.cut_pos.y(),
						   player.cut_size.x(), player.cut_size.y(),
						   tx.run, Color(0, 0, 0, 0.5 + 0.5* cos(player.flashing)),
						   player.angle, player.zoom, player.center);
			sword.zoom.x() = -1;
			switch (player.time){
			case 8:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - displace.x(),
								  player.pos.y() + player.size.y() / 2 + displace.y());
				sword.angle = 160 * one_angle;
				break;
			case 9:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - displace.x() - 10,
								  player.pos.y() + player.size.y() / 2 + displace.y() - 2);
				sword.angle = 160 * one_angle;
				break;
			case 10:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - displace.x() - 15,
								  player.pos.y() + player.size.y() / 2 + displace.y() - 1);
				sword.angle = 160 * one_angle;

				break;
			case 11:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - displace.x() - 25,
								  player.pos.y() + player.size.y() / 2 + displace.y());
				sword.angle = 160 * one_angle;

				break;
			case 12:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - displace.x() - 10,
								  player.pos.y() + player.size.y() / 2 + displace.y());
				sword.angle = 160 * one_angle;

				break;
			}
		}
		break;
	case ATTACK_TOP:
		animation_delay(player.cut_pos, player.cut_size, attack_top_animation[player.index].num, attack_top_animation[player.index].time, player.index);

		if (player.direction == CharaInfo::RIGHT){
			drawTextureBox(player.pos.x() + player.centering_size, player.pos.y(),
						   player.cut_size.x(), player.cut_size.y(),
						   player.cut_pos.x(), player.cut_pos.y(),
						   player.cut_size.x(), player.cut_size.y(),
						   tx.attack_top_right, Color(0, 0, 0, 0.5 + 0.5* cos(player.flashing)),
						   player.angle, player.zoom, player.center);
			sword.zoom.x() = 1;
			switch (player.index){
			case 0:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + 60,
								  player.pos.y() + player.size.y() / 2 + 80);
				sword.angle = -162 * one_angle;
				break;
			case 1:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - 5,
								  player.pos.y() + player.size.y() / 2 + 189);
				sword.angle = 208 * one_angle;
				break;
			case 2:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - 20,
								  player.pos.y() + player.size.y() / 2 + 218);
				sword.angle = 206 * one_angle;
				break;
			case 3:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - 107,
								  player.pos.y() + player.size.y() / 2 + 125);
				sword.angle = 208 * one_angle;
				break;
			case 4:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + 131,
								  player.pos.y() + player.size.y() / 2 + 81);
				sword.angle = 80 * one_angle;
				tx.attack_sound.play();
				break;
			case 5:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + 160,
								  player.pos.y() + player.size.y() / 2 - 60);
				sword.angle = 7 * one_angle;
				break;
			case 6:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + 66,
								  player.pos.y() + player.size.y() / 2 - 186);
				sword.angle = 0 * one_angle;
				break;
			case 7:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + 10,
								  player.pos.y() + player.size.y() / 2 - 50);
				sword.angle = -7 * one_angle;
				break;
			case 8:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - 100,
								  player.pos.y() + player.size.y() / 2 + 40);
				sword.angle = -17 * one_angle;
				break;

			}
		}
		else if (player.direction == CharaInfo::LEFT){
			drawTextureBox(player.pos.x() + player.centering_size, player.pos.y(),
						   player.cut_size.x(), player.cut_size.y(),
						   player.cut_pos.x(), player.cut_pos.y(),
						   player.cut_size.x(), player.cut_size.y(),
						   tx.attack_top_left, Color(0, 0, 0, 0.5 + 0.5* cos(player.flashing)),
						   player.angle, player.zoom, player.center);
			sword.zoom.x() = 1;

			switch (player.index){
			case 0:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - 60,
								  player.pos.y() + player.size.y() / 2 + 80);
				sword.angle = -12 * one_angle;
				break;
			case 1:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + 5,
								  player.pos.y() + player.size.y() / 2 + 189);
				sword.angle = -28 * one_angle;
				break;
			case 2:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + 20,
								  player.pos.y() + player.size.y() / 2 + 218);
				sword.angle = -26 * one_angle;
				break;
			case 3:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + 107,
								  player.pos.y() + player.size.y() / 2 + 125);
				sword.angle = -28 * one_angle;
				break;
			case 4:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - 131,
								  player.pos.y() + player.size.y() / 2 + 81);
				sword.angle = 100 * one_angle;
				tx.attack_sound.play();
				break;
			case 5:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - 160,
								  player.pos.y() + player.size.y() / 2 - 60);
				sword.angle = 187 * one_angle;
				break;
			case 6:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - 66,
								  player.pos.y() + player.size.y() / 2 - 186);
				sword.angle = 180 * one_angle;
				break;
			case 7:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - 10,
								  player.pos.y() + player.size.y() / 2 - 50);
				sword.angle = 187 * one_angle;
				break;
			case 8:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + 100,
								  player.pos.y() + player.size.y() / 2 + 40);
				sword.angle = 197 * one_angle;
				break;

			}
		}

		break;
	case ATTACK_MIDDLE:
		animation_delay(player.cut_pos, player.cut_size, attack_middle_animation[player.index].num, attack_middle_animation[player.index].time, player.index);

		if (player.direction == CharaInfo::RIGHT){
			drawTextureBox(player.pos.x() + player.centering_size, player.pos.y(),
						   player.cut_size.x(), player.cut_size.y(),
						   player.cut_pos.x(), player.cut_pos.y(),
						   player.cut_size.x(), player.cut_size.y(),
						   tx.attack_middle_right, Color(0, 0, 0, 0.5 + 0.5* cos(player.flashing)),
						   player.angle, player.zoom, player.center);
			sword.zoom.x() = 1;
			switch (player.index){
			case 0:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - 95,
								  player.pos.y() + player.size.y() / 2 + 92);
				sword.angle = -16 * one_angle;
				break;
			case 1:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + 100,
								  player.pos.y() + player.size.y() / 2 - 50);
				sword.angle = -0 * one_angle;
				if (player.se_flag == false){
					tx.attack_sound.play();
					player.se_flag = true;
				}
				break;
			case 2:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + 50,
								  player.pos.y() + player.size.y() / 2);
				sword.angle = -7 * one_angle;

				break;
			case 3:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + 20,
								  player.pos.y() + player.size.y() / 2 + 45);
				sword.angle = -16 * one_angle;
				break;
			}
		}
		else if (player.direction == CharaInfo::LEFT){
			drawTextureBox(player.pos.x() + player.centering_size, player.pos.y(),
						   player.cut_size.x(), player.cut_size.y(),
						   player.cut_pos.x(), player.cut_pos.y(),
						   player.cut_size.x(), player.cut_size.y(),
						   tx.attack_middle_left, Color(0, 0, 0, 0.5 + 0.5* cos(player.flashing)),
						   player.angle, player.zoom, player.center);
			sword.zoom.x() = 1;
			switch (player.index){
			case 0:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + 95,
								  player.pos.y() + player.size.y() / 2 + 92);
				sword.angle = 196 * one_angle;
				break;
			case 1:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - 100,
								  player.pos.y() + player.size.y() / 2 - 50);
				sword.angle = 180 * one_angle;
				if (player.se_flag == false){
					tx.attack_sound.play();
					player.se_flag = true;
				}
				break;
			case 2:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - 50,
								  player.pos.y() + player.size.y() / 2);
				sword.angle = 187 * one_angle;

				break;
			case 3:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - 20,
								  player.pos.y() + player.size.y() / 2 + 45);
				sword.angle = 196 * one_angle;
				break;
			}
		}
		break;

	case ATTACK_UNDER:
		animation_delay(player.cut_pos, player.cut_size, attack_under_animation[player.index].num, attack_under_animation[player.index].time, player.index);

		if (player.direction == CharaInfo::RIGHT){
			drawTextureBox(player.pos.x() + player.centering_size, player.pos.y(),
						   player.cut_size.x(), player.cut_size.y() + player.cut_size.y(),
						   player.cut_pos.x(), player.cut_pos.y(),
						   player.cut_size.x(), player.cut_size.y() + player.cut_size.y(),
						   tx.attack_under_right, Color(0, 0, 0, 0.5 + 0.5* cos(player.flashing)),
						   player.angle, player.zoom, Vec2f(0, 0));
			sword.zoom.x() = 1;
			switch (player.index){
			case 0:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + 26,
								  player.pos.y() + player.size.y() / 2 + 132);
				sword.angle = -16 * one_angle;
				break;
			case 1:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - 14,
								  player.pos.y() + player.size.y() / 2 + 208);
				sword.angle = -3 * one_angle;
				tx.attack_sound.play();
				break;
			case 2:
				if (attack_under_animation[2].time < 7){
					sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + 10,
									  player.pos.y() + player.size.y() / 2 + 208);
					sword.angle = 110 * one_angle;
				}
				if (attack_under_animation[2].time >= 7){
					sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + 10,
									  player.pos.y() + player.size.y() / 2 + 208);
					sword.angle = 80 * one_angle;
				}
				break;
			case 3:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - 20,
								  player.pos.y() + player.size.y() / 2 + 105);
				sword.angle = 168 * one_angle;
				break;
			}
		}
		else if (player.direction == CharaInfo::LEFT){
			drawTextureBox(player.pos.x() + player.centering_size, player.pos.y(),
						   player.cut_size.x(), player.cut_size.y() + player.cut_size.y(),
						   player.cut_pos.x(), player.cut_pos.y(),
						   player.cut_size.x(), player.cut_size.y() + player.cut_size.y(),
						   tx.attack_under_left, Color(0, 0, 0, 0.5 + 0.5* cos(player.flashing)),
						   player.angle, player.zoom, Vec2f(0, 0));
			sword.zoom.x() = 1;
			switch (player.index){
			case 0:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - 26,
								  player.pos.y() + player.size.y() / 2 + 132);
				sword.angle = 196 * one_angle;
				break;
			case 1:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + 14,
								  player.pos.y() + player.size.y() / 2 + 208);
				sword.angle = 183 * one_angle;
				tx.attack_sound.play();
				break;
			case 2:
				if (attack_under_animation[2].time < 7){
					sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - 10,
									  player.pos.y() + player.size.y() / 2 + 208);
					sword.angle = 80 * one_angle;
				}
				if (attack_under_animation[2].time >= 7){
					sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 - 10,
									  player.pos.y() + player.size.y() / 2 + 208);
					sword.angle = 110 * one_angle;
				}
				break;
			case 3:
				sword.pos = Vec2f(player.pos.x() + player.size.x() / 2 + 20,
								  player.pos.y() + player.size.y() / 2 + 105);
				sword.angle = 12 * one_angle;
				break;
			}
		}

		break;
	case ROLLING:
		animation(player, 5, 8, 0);
		if (player.direction == CharaInfo::RIGHT){
			drawTextureBox(player.pos.x() + player.centering_size, player.pos.y(),
						   player.cut_size.x(), player.cut_size.y(),
						   player.cut_pos.x(), player.cut_pos.y()+2,
						   player.cut_size.x(), player.cut_size.y(),
						   tx.rolling_right, Color(0, 0, 0, 0.5 + 0.5* cos(player.flashing)),
						   player.angle, player.zoom, player.center);
		}
		else if (player.direction == CharaInfo::LEFT){
			drawTextureBox(player.pos.x() + player.centering_size, player.pos.y(),
						   player.cut_size.x(), player.cut_size.y(),
						   player.cut_pos.x(), player.cut_pos.y()+2,
						   player.cut_size.x(), player.cut_size.y(),
						   tx.rolling_left, Color(0, 0, 0, 0.5 + 0.5* cos(player.flashing)),
						   player.angle, player.zoom, player.center);
		}
		break;
	case LADDER_CLIMB:
		animation(player, 4, 8, 0);
		drawTextureBox(player.pos.x() + player.centering_size, player.pos.y(),
					   player.cut_size.x(), player.cut_size.y(),
					   player.cut_pos.x(), player.cut_pos.y(),
					   player.cut_size.x(), player.cut_size.y(),
					   tx.ladder, Color(0, 0, 0, 0.5 + 0.5* cos(player.flashing)),
					   player.angle, Vec2f(1.2, 1), Vec2f(100, 0));
		break;

	}

	drawFillBox(WIDTH / 2 - 600, -HEIGHT / 2 + 200, 500, 100, Color(0, 0, 0, 0.5));
	tx.font.size(100);
	tx.font.draw(now_money, Vec2f(WIDTH / 2 - 600, -HEIGHT / 2 + 200), Color::white);

	tx.font.size(50);
	tx.font.draw("エリア  " + now_area, Vec2f(WIDTH / 2 - 600, HEIGHT / 2 - 200), Color::white);

	if (env.isPushKey('Y') && player.debug == false){
		player.debug = true;
		env.flushInput();
	}
	if (player.debug == true){
		tx.font.draw("HP    " + std::to_string((int)player.HP), Vec2f(-1500, +600), Color::white);
		tx.font.draw("Power " + std::to_string((int)player.power), Vec2f(-1500, +550), Color::white);
		tx.font.draw("Posx " + std::to_string((int)player.pos.x()), Vec2f(-1500, +500), Color::white);
		tx.font.draw("Posy " + std::to_string((int)player.pos.y()), Vec2f(-1500, +450), Color::white);
		tx.font.draw("けんのしゅるい　" + now_sword_num, Vec2f(-1500, -500), Color::white);

		if (env.isPushKey('Y')){
			player.debug = false;
			env.flushInput();
		}
	}

	now_money = std::to_string((int)player.money);
	player.p_HP_line = player.HP_max * 7;
	drawFillBox(-WIDTH / 2 + 100, HEIGHT / 2 - 100,
				player.p_HP_line, 50, Color::black, 0, Vec2f(1, 1), Vec2f(0, 0));

	drawFillBox(-WIDTH / 2 + 100, HEIGHT / 2 - 100,
				player.p_HP_line * (player.HP / player.HP_max), 50, Color::lime);



}

void status_shop(Textures& tx, int& scene){
	int select1 = 0;
	int select2 = 0;
	bool buy = false;
	float hp_up = 0;
	float power_up = 0;
	Color not_select_color = Color::white;
	Color now_select_color = Color::red;
	Color select[6];
	std::string now_hp;
	std::string now_power;
	std::string now_money;
	bool shop = true;

	std::string have_money_hp;

	std::string have_money_power;

	if (player.money_flag == false){
		player.hp_money = enemy[0].money;
		player.power_money = enemy[0].money;
		player.money_flag = true;
	}
	enum{
		UP,
		BACK,
	};

	enum{
		HP,
		ATTACK,
		CANCEL,
	};
	while (shop == true){
		if (!env.isOpen()) exit(0);
		env.begin();
		tx.font.size(100);
		env.bgColor(Color::black);
		hp_up = player.HP_max;
		power_up = player.power;
		now_hp = std::to_string((int)player.HP_max);
		now_power = std::to_string((int)player.power);
		now_money = std::to_string((int)player.money);

		tx.cursor.gain(0.5f);

		for (int i = 0; i < 6; i++){
			select[i] = not_select_color;
		}
		tx.cursor.pitch(2.0f);
		if (buy == false){
			if (env.isPushKey(GLFW_KEY_UP)){
				tx.cursor.play();
				(select1 <= 0) ? 0, tx.cursor.stop() : --select1;
			}
			if (env.isPushKey(GLFW_KEY_DOWN)){
				tx.cursor.play();
				(select1 >= 1) ? 1, tx.cursor.stop() : ++select1;
			}
			switch (select1){
			case UP:
				select[1] = now_select_color;
				if (env.isPushKey(GLFW_KEY_ENTER)){
					buy = true;
					tx.cursor.play();
					env.flushInput();
				}
				break;
			case BACK:
				select[2] = now_select_color;
				if (env.isPushKey(GLFW_KEY_ENTER)){
					scene = GAME;
					tx.cursor.play();
					env.flushInput();
					shop = false;
				}
				break;
			}
		}
		if (buy == true){
			if (env.isPushKey(GLFW_KEY_UP)){
				tx.cursor.play();
				(select2 <= 0) ? 0, tx.cursor.stop() : --select2;
			}
			if (env.isPushKey(GLFW_KEY_DOWN)){
				tx.cursor.play();
				(select2 >= 2) ? 2, tx.cursor.stop() : ++select2;

			}

			switch (select2){
			case HP:
				select[3] = now_select_color;
				if (env.isPushKey(GLFW_KEY_ENTER)){
					if (player.max_money >= player.hp_money){
						player.HP_max += 10;
						player.money -= player.hp_money;
						player.max_money -= player.hp_money;
						player.hp_money += player.hp_money * 0.1;
						tx.buy.play();
					}
				}
				break;
			case ATTACK:
				select[4] = now_select_color;
				if (env.isPushKey(GLFW_KEY_ENTER)){
					if (player.max_money >= player.hp_money){
						player.power += 3;
						player.money -= player.hp_money;
						player.max_money -= player.hp_money;
						player.hp_money += player.hp_money * 0.1;
						tx.buy.play();
					}
				}
				break;
			case CANCEL:
				select[5] = now_select_color;
				if (env.isPushKey(GLFW_KEY_ENTER)){
					buy = false;
					tx.cursor.play();
				}
				break;
			}
			tx.font.draw("カネ　　 " + now_money, Vec2f(-200, 50), Color::white);
			tx.font.draw("ヒットポイント +10  必要" + std::to_string((int)player.hp_money), Vec2f(-200, -150), select[3]);
			tx.font.draw("こうげき力     +3　 必要" + std::to_string((int)player.hp_money), Vec2f(-200, -300), select[4]);
			tx.font.draw("もどる  ", Vec2f(-200, -450), select[5]);
		}

		tx.font.draw("ステータスを上げる　", Vec2f(-1200, -200), select[1]);
		tx.font.draw("もどる　", Vec2f(-1200, -350), select[2]);

		tx.font.draw("ヒットポイント " + now_hp, Vec2f(-1300, 600), Color::white);
		tx.font.draw("こうげき力　　 " + now_power, Vec2f(-1300, 400), Color::white);

		if (env.isPushKey('E'))
			return;
		env.end();
	}
}

void gameInit(Textures& tx){
	mapAdjust();
	mapTypeInit();

	charaInit();
	mapChipDraw(player, player.stage_serect, now_area);

	for (int i = 0; i < enemy_num; i++){
		enemy[i].pos = enemyStartInit(i, player.stage_serect);
		enemyInit(enemy[i], sword_e[i]);
	}

	if (player.stage_serect == MAP_TYPE_GRASS1){
		for (int i = 0; i < enemy_num; i++){
			enemy2[i].pos = enemyStartInit(i, player.stage_serect);
			enemy2Init(enemy2[i], sword_e2[i]);
		}
	}
	if (player.stage_serect == MAP_TYPE_GRASS2){
		for (int i = 0; i < enemy_num; i++){
			enemy2[i].pos = enemyStartInit(i, player.stage_serect);
			enemy2Init(enemy2[i], sword_e2[i]);
			enemy2[i].power = 41;
			enemy2[i].HP = 700;
			enemy2[i].HP_max = 700;
		}
	}

	if (player.stage_serect == MAP_TYPE_ROCK2){
		for (int i = 0; i < 3; i++){
			enemy_boss1[i].pos = boss_enemyStartInit(i, player.stage_serect);
			boss1_enemyInit(enemy_boss1[i], sword_boss1[i]);
		}
	}

	player.HP = player.HP_max;
	tx.font.size(50);
}

void gameUpdate(Textures& tx, int& scene){
	int enemy_change = player.stage_serect;

	charaMove(tx, scene);
	if (player.stage_serect == MAP_TYPE_ROCK1){
		for (int i = 0; i < enemy_num; i++){
			enemyMove(enemy[i], sword_e[i], player, sword, tx);
		}
	}
	else if (player.stage_serect == MAP_TYPE_GRASS1){
		for (int i = 0; i < enemy_num; i++){
			enemy2Move(enemy2[i], sword_e2[i], player, sword, tx);
		}
	}
	else if (player.stage_serect == MAP_TYPE_GRASS2){
		for (int i = 0; i < enemy_num; i++){
			enemy2Move(enemy2[i], sword_e2[i], player, sword, tx);
		}
	}
	if (player.stage_serect == MAP_TYPE_ROCK2){
		for (int i = 0; i < 3; i++){
			boss1_enemyMove(enemy_boss1[i], sword_boss1[i], player, sword, tx);
		}
	}
	mapCollision(player, sword, scene, tx);
	if (player.stage_serect == MAP_TYPE_ROCK1){
		for (int i = 0; i < enemy_num; i++){
			mapCollision_enemy(enemy[i], player, sword_e[i], i, player.stage_serect);
		}
	}
	if (player.stage_serect == MAP_TYPE_GRASS1){
		for (int i = 0; i < enemy_num; i++){
			mapCollision_enemy(enemy2[i], player, sword_e2[i], i, player.stage_serect);
		}
	}
	if (player.stage_serect == MAP_TYPE_GRASS2){
		for (int i = 0; i < enemy_num; i++){
			mapCollision_enemy(enemy2[i], player, sword_e2[i], i, player.stage_serect);
		}
	}
	if (player.stage_serect == MAP_TYPE_ROCK2){
		for (int i = 0; i < 3; i++){
			boss_mapCollision_enemy(enemy_boss1[i], player, sword_boss1[i], i, player.stage_serect);
		}
	}

	if (player.stage_serect != enemy_change){
		gameInit(tx);
	}

	if (env.isPushKey('G')){
		scene++;
		env.flushInput();
	}
}

void gameDraw(Textures& tx){
	env.bgColor(Color::gray);
	mapChipDraw(player, player.stage_serect, now_area);
	if (player.stage_serect == MAP_TYPE_ROCK1){
		for (int i = 0; i < enemy_num; i++){
			enemyDraw(player, enemy[i], sword_e[i], tx);
		}
	}
	if (player.stage_serect == MAP_TYPE_GRASS1){
		for (int i = 0; i < enemy_num; i++){
			enemy2Draw(player, enemy2[i], sword_e2[i], tx);
		}
	}
	if (player.stage_serect == MAP_TYPE_GRASS2){
		for (int i = 0; i < enemy_num; i++){
			enemy2Draw(player, enemy2[i], sword_e2[i], tx);
		}
	}
	if (player.stage_serect == MAP_TYPE_ROCK2){
		for (int i = 0; i < 3; i++){
			boss1_enemyDraw(player, enemy_boss1[i], sword_boss1[i], tx);
		}
	}
	charaDraw(tx);

}

void gameover(Textures& tx, int& scene){
	int count;
	env.bgColor(Color::black);

	tx.font.size(250);
	tx.font.draw("YOU DEAD", Vec2f(-1000, 0), Color::red);
	count = count++ % 120;
	tx.font.size(100);
	if (count < 30){
		tx.font.draw("Press Enter", Vec2f(-1000, -500), Color::white);
	}
	else if (count < 60){
		tx.font.draw("Press Enter．", Vec2f(-1000, -500), Color::white);
	}
	else if (count < 90){
		tx.font.draw("Press Enter．．", Vec2f(-1000, -500), Color::white);
	}
	else if (count < 120){
		tx.font.draw("Press Enter．．．", Vec2f(-1000, -500), Color::white);
	}
	if (env.isPushKey(GLFW_KEY_ENTER)){
		player.stage_serect = MAP_TYPE_STARTMAP;
		gameInit(tx);
		scene = GAME;
		player.money = 0;
		player.max_money = 0;
		env.flushInput();
	}
}


float trans = 1;
void title(Textures& tx, int& scene){


	env.bgColor(Color::black);
	drawTextureBox(-2048, -1024,
				   4096, 2048,
				   0, 0,
				   4096, 2048,
				   tx.title, Color(1, 1, 1, trans));
	drawTextureBox(-300, -600,
				   512, 256,
				   0, 0,
				   512, 256,
				   tx.start, Color(1, 1, 1, trans));
	drawTextureBox(-300, -750,
				   512, 256,
				   0, 0,
				   512, 256,
				   tx.press, Color(1, 1, 1, trans));

	if (env.isPushKey(GLFW_KEY_ENTER)){
		player.title_startflag = true;
	}
	if (player.title_startflag == true){
		trans -= 0.01;
	}
	if (trans <= 0){
		scene++;
		gameInit(tx);

		env.flushInput();
	}
}
