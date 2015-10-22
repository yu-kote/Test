#include "Enemy.h"

int kill;

//アニメーション
//struct&   動く物体の構造体
//count     使いたい枚数
//frame     何フレームでアニメーションするか
//num		何番目からアニメーションするか
void enemy_animation(MovingObject& chara, int count, int change_frame, int num){
	chara.time = (chara.time2++ / change_frame) % count + num;

	chara.cut_pos.x() = (chara.time % 4) * chara.cut_size.x();
	chara.cut_pos.y() = (chara.time / 4) * chara.cut_size.y();
}

//アニメーションフレーム指定版
// pos.x   pos.y		切り取り位置
// size.x  size.y		切り取りサイズ
// num					パターン番号
// time					フレーム指定
// index				配列の要素数
void enemy_animation_delay(Vec2f& pos, Vec2f& size, int& num, int& time, int& index)
{
	pos.x() = (num % 4) * size.x();
	pos.y() = (num / 4) * size.y();

	time--;
	if (time <= 0){
		index++;
	}
}

bool circleCollision(Vec2f pos, Vec2f pos2, float size){
	return ((pos.x() - pos2.x()) * (pos.x() - pos2.x()) +
			(pos.y() - pos2.y())*(pos.y() - pos2.y()) <= size * size);
}

bool swordCollision(Vec2f box_pos, Vec2f box_size, Vec2f box1_pos, Vec2f box1_size) {

	return (
		box_pos.x() < box1_pos.x() + box1_size.x() &&
		box_pos.x() + box_size.x() > box1_pos.x() &&
		box_pos.y() < box1_pos.y() + box1_size.y() &&
		box_pos.y() + box_size.y() > box1_pos.y());
}

//*********************************************************************************************//
//enemyの初期化																			　　//	
//*********************************************************************************************//
void enemyInit(Enemy& enemy, Sword& sword){
	enemy.size = Vec2f(200, 400);
	enemy.cut_pos = Vec2f(0, 0);
	enemy.cut_size = Vec2f(512, 512);
	enemy.direction = CharaInfo::LEFT; //向き
	enemy.is_exists = CharaInfo::LIVE; //存在しているか
	enemy.camera = Vec2f(0, 0);
	enemy.stop_camera_x = MOVE;
	enemy.stop_camera_y = MOVE;

	enemy.type = DEFAULT;
	enemy.time = 0;
	enemy.time2 = 0;
	enemy.angle = 0;
	enemy.zoom = Vec2f(0.8, 0.8);
	enemy.center = Vec2f(0, 0);
	enemy.attack_time = 0;

	enemy.HP = 200;
	enemy.HP_max = 200;
	enemy.HP_line = 300;
	enemy.power = 21;
	enemy.nockback_flag = false;
	enemy.nockback_time = 60;
	enemy.nockback = 1;
	enemy.hit_count = 0;
	enemy.flashing = 0;

	enemy.dead_trans = 1;

	enemy.money = 171;


	enemy.vector = Vec2f(0, 0);
	enemy.is_invin = false;
	enemy.invin_time = 20;
	enemy.animation_reset = false;
	enemy.is_attack = false;
	enemy.rolling_count = 0;
	enemy.rolling_flag = STOP;

	enemy.start_flag = false;
	enemy.is_move = MOVE;
	enemy.is_gravity = MOVE;


	enemy.is_hitfloor = false;

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

	sword.pos.x() = enemy.pos.x() + enemy.size.x() / 2;
	sword.pos.y() = enemy.pos.y();
	sword.range = 512;
	sword.angle = 0;
	sword.size.x() = sword.range;
	sword.size.y() = sword.size.x() / 4;
	sword.cut_size = Vec2f(512, 128);
	sword.zoom = Vec2f(1, 1);
	sword.hit_range = Vec2f(512, 128);

	sword.attack_power = 10;


	for (int i = 0; i < 9; i++)
		enemy.enemy_attack_top_animation[i].num = i;
	for (int i = 0; i < 4; i++){
		enemy.enemy_attack_under_animation[i].num = i;
	}
	enemy.enemy_attack_middle_animation[0].num = 4;
	enemy.enemy_attack_middle_animation[1].num = 5;
	enemy.enemy_attack_middle_animation[2].num = 6;
	enemy.enemy_attack_middle_animation[3].num = 7;


	enemy.enemy_attack_top_animation[8].time = 0;
	enemy.enemy_attack_middle_animation[3].time = 0;
	enemy.enemy_attack_under_animation[3].time = 0;




	//enemyしか持っていない情報
	enemy.look_area = 1000;
	enemy.is_moving = false;
	enemy.move_time = 0;
	enemy.attack = 0;
	enemy.rolling = false;
	enemy.run_right = STOP;
	enemy.run_left = STOP;
	enemy.popnum = 0;
}

void enemy2Init(Enemy& enemy, Sword& sword){
	enemy.size = Vec2f(200, 400);
	enemy.cut_pos = Vec2f(0, 0);
	enemy.cut_size = Vec2f(512, 512);
	enemy.direction = CharaInfo::LEFT; //向き
	enemy.is_exists = CharaInfo::LIVE; //存在しているか
	enemy.camera = Vec2f(0, 0);
	enemy.stop_camera_x = MOVE;
	enemy.stop_camera_y = MOVE;

	enemy.type = DEFAULT;
	enemy.time = 0;
	enemy.time2 = 0;
	enemy.angle = 0;
	enemy.zoom = Vec2f(0.8, 0.8);
	enemy.center = Vec2f(0, 0);
	enemy.attack_time = 0;

	enemy.HP = 500;
	enemy.HP_max = 500;
	enemy.HP_line = 300;
	enemy.power = 31;
	enemy.nockback_flag = false;
	enemy.nockback_time = 60;
	enemy.nockback = 1;
	enemy.hit_count = 0;
	enemy.flashing = 0;

	enemy.dead_trans = 1;

	enemy.money = 501;


	enemy.vector = Vec2f(0, 0);
	enemy.is_invin = false;
	enemy.invin_time = 20;
	enemy.animation_reset = false;
	enemy.is_attack = false;
	enemy.rolling_count = 0;
	enemy.rolling_flag = STOP;

	enemy.start_flag = false;
	enemy.is_move = MOVE;
	enemy.is_gravity = MOVE;


	enemy.is_hitfloor = false;

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

	sword.pos.x() = enemy.pos.x() + enemy.size.x() / 2;
	sword.pos.y() = enemy.pos.y();
	sword.range = 512;
	sword.angle = 0;
	sword.size.x() = sword.range;
	sword.size.y() = sword.size.x() / 4;
	sword.cut_size = Vec2f(512, 128);
	sword.zoom = Vec2f(1, 1);
	sword.hit_range = Vec2f(512, 128);

	sword.attack_power = 10;


	for (int i = 0; i < 9; i++)
		enemy.enemy_attack_top_animation[i].num = i;
	for (int i = 0; i < 4; i++){
		enemy.enemy_attack_under_animation[i].num = i;
	}
	enemy.enemy_attack_middle_animation[0].num = 4;
	enemy.enemy_attack_middle_animation[1].num = 5;
	enemy.enemy_attack_middle_animation[2].num = 6;
	enemy.enemy_attack_middle_animation[3].num = 7;


	enemy.enemy_attack_top_animation[8].time = 0;
	enemy.enemy_attack_middle_animation[3].time = 0;
	enemy.enemy_attack_under_animation[3].time = 0;




	//enemyしか持っていない情報
	enemy.look_area = 1000;
	enemy.is_moving = false;
	enemy.move_time = 0;
	enemy.attack = 0;
	enemy.rolling = false;
	enemy.run_right = STOP;
	enemy.run_left = STOP;
	enemy.popnum = 0;
}

void boss1_enemyInit(Enemy& enemy, Sword& sword){
	enemy.size = Vec2f(200, 400);
	enemy.cut_pos = Vec2f(0, 0);
	enemy.cut_size = Vec2f(512, 512);
	enemy.direction = CharaInfo::LEFT; //向き
	enemy.is_exists = CharaInfo::LIVE; //存在しているか
	enemy.camera = Vec2f(0, 0);
	enemy.stop_camera_x = MOVE;
	enemy.stop_camera_y = MOVE;

	enemy.type = DEFAULT;
	enemy.time = 0;
	enemy.time2 = 0;
	enemy.angle = 0;
	enemy.zoom = Vec2f(0.8, 0.8);
	enemy.center = Vec2f(0, 0);
	enemy.attack_time = 0;

	enemy.HP = 500;
	enemy.HP_max = 500;
	enemy.HP_line = 300;
	enemy.power = 31;
	enemy.nockback_flag = false;
	enemy.nockback_time = 60;
	enemy.nockback = 1;
	enemy.hit_count = 0;
	enemy.flashing = 0;

	enemy.dead_trans = 1;

	enemy.money = 2000;


	enemy.vector = Vec2f(0, 0);
	enemy.is_invin = false;
	enemy.invin_time = 20;
	enemy.animation_reset = false;
	enemy.is_attack = false;
	enemy.rolling_count = 0;
	enemy.rolling_flag = STOP;

	enemy.start_flag = false;
	enemy.is_move = MOVE;
	enemy.is_gravity = MOVE;


	enemy.is_hitfloor = false;

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

	sword.pos.x() = enemy.pos.x() + enemy.size.x() / 2;
	sword.pos.y() = enemy.pos.y();
	sword.range = 512;
	sword.angle = 0;
	sword.size.x() = sword.range;
	sword.size.y() = sword.size.x() / 4;
	sword.cut_size = Vec2f(512, 128);
	sword.zoom = Vec2f(1, 1);
	sword.hit_range = Vec2f(512, 128);

	sword.attack_power = 10;


	for (int i = 0; i < 9; i++)
		enemy.enemy_attack_top_animation[i].num = i;
	for (int i = 0; i < 4; i++){
		enemy.enemy_attack_under_animation[i].num = i;
	}
	enemy.enemy_attack_middle_animation[0].num = 4;
	enemy.enemy_attack_middle_animation[1].num = 5;
	enemy.enemy_attack_middle_animation[2].num = 6;
	enemy.enemy_attack_middle_animation[3].num = 7;


	enemy.enemy_attack_top_animation[8].time = 0;
	enemy.enemy_attack_middle_animation[3].time = 0;
	enemy.enemy_attack_under_animation[3].time = 0;




	//enemyしか持っていない情報
	enemy.look_area = 1500;
	enemy.is_moving = false;
	enemy.move_time = 0;
	enemy.attack = 0;
	enemy.rolling = false;
	enemy.run_right = STOP;
	enemy.run_left = STOP;
	enemy.popnum = 0;
}

//*********************************************************************************************//
//enemyの動き																		   //	
//*********************************************************************************************//
void enemyMove(Enemy& enemy, Sword& sword, Player& player, Sword sword2, Textures& tx){

	if (enemy.pos.x() + enemy.size.x() > -WIDTH / 2 && enemy.pos.x() < WIDTH / 2 &&
		enemy.pos.y() + enemy.size.y() > -HEIGHT / 2 && enemy.pos.y() < HEIGHT / 2){
		if (enemy.is_exists == CharaInfo::LIVE){
			if (circleCollision(player.pos, enemy.pos, enemy.look_area)){
				enemy.move_time = enemy.move_time++ % 200;
				if (player.pos.x() > enemy.pos.x()){
					if (enemy.is_move == MOVE)
						enemy.direction = CharaInfo::RIGHT;
				}
				if (player.pos.x() < enemy.pos.x()){
					if (enemy.is_move == MOVE)
						enemy.direction = CharaInfo::LEFT;
				}
				if (player.pos.x() > enemy.pos.x() + enemy.look_area / 3){
					if (enemy.is_move == MOVE){
						enemy.pos.x() += enemy.move_speed * 0.5;
						enemy.type = RUN;
					}
				}
				else if (player.pos.x() <= enemy.pos.x() - enemy.look_area / 3){
					if (enemy.is_move == MOVE){
						enemy.pos.x() -= enemy.move_speed * 0.5;
						enemy.type = RUN;
					}
				}
				else if (enemy.move_time <= 150){
					enemy.type = DEFAULT;
				}
				else if (enemy.move_time == 151){
					if (enemy.is_move == MOVE){
						enemy.attack = true;
					}
				}
				if (enemy.move_time == 170 && enemy.type == ATTACK_TOP){
					enemy.attack = true;
				}
				if (enemy.move_time == 180 && enemy.type == ATTACK_MIDDLE){
					enemy.attack = true;
				}
			}
			else{
				enemy.type = DEFAULT;
			}


			//重力処理
			if (enemy.is_gravity == MOVE){
				enemy.vector.y() += enemy.gravity;
				enemy.camera.y() += enemy.vector.y();

				if (enemy.vector.y() <= enemy.gravity_max){
					enemy.vector.y() = enemy.gravity_max;
				}
			}
			else {
				enemy.vector.y() = 0;
				enemy.camera.y() = 0;
			}



			//**************************************************************************************************
			//ローリング処理
			//**************************************************************************************************

			if (enemy.is_move == MOVE){
				if (enemy.rolling == true){
					enemy.rolling_flag = MOVE;
					enemy.time2 = 0;
					enemy.rolling = false;
				}
			}


			if (enemy.rolling_flag == MOVE)
			{
				enemy.rolling_count++;
				enemy.is_gravity = STOP;
				enemy.type = ROLLING;
				if (enemy.direction == CharaInfo::RIGHT)
				{
					if (enemy.rolling_count <= enemy.invin_time){
						enemy.is_move = STOP;
						enemy.is_invin = true;
						enemy.pos.x() += (enemy.move_speed * 0.5) * 2;
					}
					if (enemy.rolling_count > enemy.invin_time){
						enemy.is_invin = false;
					}
					if (enemy.rolling_count >= enemy.invin_time * 2){
						enemy.rolling_flag = STOP;
						enemy.is_move = MOVE;
						enemy.rolling_count = 0;
						enemy.type = DEFAULT;
					}
				}
				if (enemy.direction == CharaInfo::LEFT)
				{
					if (enemy.rolling_count <= enemy.invin_time){
						enemy.is_move = STOP;
						enemy.is_invin = true;
						enemy.pos.x() -= (enemy.move_speed * 0.5) * 2;
					}
					if (enemy.rolling_count > enemy.invin_time){

						enemy.is_invin = false;
					}
					if (enemy.rolling_count >= enemy.invin_time * 2){
						enemy.rolling_flag = STOP;
						enemy.is_move = MOVE;
						enemy.rolling_count = 0;
						enemy.type = DEFAULT;
					}
				}
			}


			//***************************************************************************************************
			//攻撃処理
			//***************************************************************************************************
			if (enemy.direction == CharaInfo::RIGHT){
				sword.hit_range.x() = 512;
				sword.hit_pos.x() = enemy.pos.x() + enemy.size.x() / 2;
				sword.hit_pos.y() = enemy.pos.y() + enemy.size.y() / 2;
			}
			if (enemy.direction == CharaInfo::LEFT){
				sword.hit_range.x() = 512;
				sword.hit_pos.x() = enemy.pos.x() + enemy.size.x() / 2 - 512;
				sword.hit_pos.y() = enemy.pos.y() + enemy.size.y() / 2;
			}
			if (enemy.is_move == MOVE){
				if (enemy.rolling_flag == STOP){
					if (sword.attack_start == false){
						if (enemy.attack == true){
							sword.attack_flag_first = true;
							sword.attack_start = true;
							enemy.is_move = STOP;
							enemy.stop_camera_x = STOP;
							enemy.time2 = 0;

							enemy.attack = false;
						}
					}
				}
			}
			if (sword.attack_start == true){
				if (sword.attack_flag_first == true){
					sword.attack_count++;
					enemy.type = ATTACK_TOP;
					if (sword.attack_count == sword.attack_start_time1){
						sword.attack_is_dec = true;
					}
					else{
						sword.attack_is_dec = false;
					}
					if (sword.attack_count > 10 && sword.attack_count < 30){
						if (enemy.rolling_flag == STOP){
							if (enemy.attack == true){
								sword.attack_flag_second = true;
								enemy.attack = false;
							}
						}
					}
					if (sword.attack_count > sword.attack_end_time_top){
						sword.attack_count = 0;
						if (sword.attack_flag_second == false){
							enemy.is_move = MOVE;
							enemy.stop_camera_x = MOVE;
							sword.attack_start = false;
						}
						sword.attack_flag_first = false;
					}
				}
				if (sword.attack_flag_first == false){
					if (sword.attack_flag_second == true){
						sword.attack_count++;
						enemy.type = ATTACK_MIDDLE;
						if (sword.attack_count > 12 && sword.attack_count < 27){
							if (enemy.direction == CharaInfo::RIGHT){
								enemy.pos.x() += enemy.move_speed / 4;
							}
							if (enemy.direction == CharaInfo::LEFT){
								enemy.pos.x() -= enemy.move_speed / 4;
							}
						}
						if (sword.attack_count == sword.attack_start_time2){
							sword.attack_is_dec = true;
						}
						else{
							sword.attack_is_dec = false;
						}
						if (enemy.rolling_flag == STOP){
							if (enemy.attack == true){
								sword.attack_flag_third = true;
								enemy.attack = false;
							}
						}
						if (sword.attack_count > sword.attack_end_time_middle){
							sword.attack_count = 0;
							if (sword.attack_flag_third == false){
								enemy.is_move = MOVE;
								enemy.stop_camera_x = MOVE;
								sword.attack_start = false;
							}
							sword.attack_flag_second = false;
						}
					}
				}

				if (sword.attack_flag_second == false){
					if (sword.attack_flag_third == true){
						sword.attack_count++;
						enemy.type = ATTACK_UNDER;
						if (sword.attack_count > 2 && sword.attack_count < 17){
							if (enemy.direction == CharaInfo::RIGHT){
								enemy.pos.x() += enemy.move_speed / 4;
							}
							if (enemy.direction == CharaInfo::LEFT){
								enemy.pos.x() -= enemy.move_speed / 4;
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
							enemy.is_move = MOVE;
							enemy.stop_camera_x = MOVE;
							sword.attack_start = false;
							sword.attack_flag_third = false;
						}
					}
				}
			}


			if (sword2.attack_is_dec == true){

				if (enemy.is_invin == false){
					if (swordCollision(enemy.pos, enemy.size, sword2.hit_pos, sword2.hit_range)){
						enemy.HP -= player.power;
						enemy.nockback_flag = true;
						if (enemy.pos.x() > player.pos.x())
							enemy.nockback = 1;
						if (enemy.pos.x() < player.pos.x())
							enemy.nockback = -1;
						tx.hit_sound.play();
					}
				}
			}
			if (enemy.nockback_flag == true){
				enemy.hit_count++;
				enemy.flashing++;
				if (enemy.hit_count < enemy.nockback_time){
					enemy.is_move = STOP;
					enemy.pos.x() += 3 * enemy.nockback;
				}
				else{
					enemy.nockback_flag = false;
					enemy.hit_count = 0;
					enemy.flashing = 0;
					enemy.is_move = MOVE;
				}
			}
			//***************************************************************************************************
			//アニメーションのフレームリセット
			//***************************************************************************************************

			if (sword.attack_start == false && enemy.rolling_flag == STOP && enemy.type != RUN)
			{
				enemy.type = DEFAULT;
			}
			if (enemy.HP < 0){
				enemy.HP = 0;
				enemy.is_exists = CharaInfo::DEAD;
				enemy.time2 = 0;
				player.max_money += enemy.money;
				kill++;
			}

		}
	}
}

void enemy2Move(Enemy& enemy, Sword& sword, Player& player, Sword sword2, Textures& tx){

	if (enemy.pos.x() + enemy.size.x() > -WIDTH / 2 && enemy.pos.x() < WIDTH / 2 &&
		enemy.pos.y() + enemy.size.y() > -HEIGHT / 2 && enemy.pos.y() < HEIGHT / 2){
		if (enemy.is_exists == CharaInfo::LIVE){
			if (circleCollision(player.pos, enemy.pos, enemy.look_area)){
				enemy.move_time = enemy.move_time++ % 100;
				if (player.pos.x() > enemy.pos.x()){
					if (enemy.is_move == MOVE)
						enemy.direction = CharaInfo::RIGHT;
				}
				if (player.pos.x() < enemy.pos.x()){
					if (enemy.is_move == MOVE)
						enemy.direction = CharaInfo::LEFT;
				}
				if (player.pos.x() > enemy.pos.x() + enemy.look_area / 3){
					if (enemy.is_move == MOVE){
						enemy.pos.x() += enemy.move_speed * 0.5;
						enemy.type = RUN;
					}
				}
				else if (player.pos.x() <= enemy.pos.x() - enemy.look_area / 3){
					if (enemy.is_move == MOVE){
						enemy.pos.x() -= enemy.move_speed * 0.5;
						enemy.type = RUN;
					}
				}
				else if (enemy.move_time < 60){
					enemy.type = DEFAULT;
				}
				else if (enemy.move_time == 61){
					if (enemy.is_move == MOVE){
						enemy.attack = true;
					}
				}
				if (enemy.move_time == 80 && enemy.type == ATTACK_TOP){
					enemy.attack = true;
				}
				if (enemy.move_time == 90 && enemy.type == ATTACK_MIDDLE){
					enemy.attack = true;
				}
			}
			else{
				enemy.type = DEFAULT;
			}


			//重力処理
			if (enemy.is_gravity == MOVE){
				enemy.vector.y() += enemy.gravity;
				enemy.camera.y() += enemy.vector.y();

				if (enemy.vector.y() <= enemy.gravity_max){
					enemy.vector.y() = enemy.gravity_max;
				}
			}
			else {
				enemy.vector.y() = 0;
				enemy.camera.y() = 0;
			}



			//**************************************************************************************************
			//ローリング処理
			//**************************************************************************************************

			if (enemy.is_move == MOVE){
				if (enemy.rolling == true){
					enemy.rolling_flag = MOVE;
					enemy.time2 = 0;
					enemy.rolling = false;
				}
			}


			if (enemy.rolling_flag == MOVE)
			{
				enemy.rolling_count++;
				enemy.is_gravity = STOP;
				enemy.type = ROLLING;
				if (enemy.direction == CharaInfo::RIGHT)
				{
					if (enemy.rolling_count <= enemy.invin_time){
						enemy.is_move = STOP;
						enemy.is_invin = true;
						enemy.pos.x() += (enemy.move_speed * 0.5) * 2;
					}
					if (enemy.rolling_count > enemy.invin_time){
						enemy.is_invin = false;
					}
					if (enemy.rolling_count >= enemy.invin_time * 2){
						enemy.rolling_flag = STOP;
						enemy.is_move = MOVE;
						enemy.rolling_count = 0;
						enemy.type = DEFAULT;
					}
				}
				if (enemy.direction == CharaInfo::LEFT)
				{
					if (enemy.rolling_count <= enemy.invin_time){
						enemy.is_move = STOP;
						enemy.is_invin = true;
						enemy.pos.x() -= (enemy.move_speed * 0.5) * 2;
					}
					if (enemy.rolling_count > enemy.invin_time){

						enemy.is_invin = false;
					}
					if (enemy.rolling_count >= enemy.invin_time * 2){
						enemy.rolling_flag = STOP;
						enemy.is_move = MOVE;
						enemy.rolling_count = 0;
						enemy.type = DEFAULT;
					}
				}
			}


			//***************************************************************************************************
			//攻撃処理
			//***************************************************************************************************
			if (enemy.direction == CharaInfo::RIGHT){
				sword.hit_range.x() = 512;
				sword.hit_pos.x() = enemy.pos.x() + enemy.size.x() / 2;
				sword.hit_pos.y() = enemy.pos.y() + enemy.size.y() / 2;
			}
			if (enemy.direction == CharaInfo::LEFT){
				sword.hit_range.x() = 512;
				sword.hit_pos.x() = enemy.pos.x() + enemy.size.x() / 2 - 512;
				sword.hit_pos.y() = enemy.pos.y() + enemy.size.y() / 2;
			}
			if (enemy.is_move == MOVE){
				if (enemy.rolling_flag == STOP){
					if (sword.attack_start == false){
						if (enemy.attack == true){
							sword.attack_flag_first = true;
							sword.attack_start = true;
							enemy.is_move = STOP;
							enemy.stop_camera_x = STOP;
							enemy.time2 = 0;

							enemy.attack = false;
						}
					}
				}
			}
			if (sword.attack_start == true){
				if (sword.attack_flag_first == true){
					sword.attack_count++;
					enemy.type = ATTACK_TOP;
					if (sword.attack_count == sword.attack_start_time1){
						sword.attack_is_dec = true;
					}
					else{
						sword.attack_is_dec = false;
					}
					if (sword.attack_count > 10 && sword.attack_count < 30){
						if (enemy.rolling_flag == STOP){
							if (enemy.attack == true){
								sword.attack_flag_second = true;
								enemy.attack = false;
							}
						}
					}
					if (sword.attack_count > sword.attack_end_time_top){
						sword.attack_count = 0;
						if (sword.attack_flag_second == false){
							enemy.is_move = MOVE;
							enemy.stop_camera_x = MOVE;
							sword.attack_start = false;
						}
						sword.attack_flag_first = false;
					}
				}
				if (sword.attack_flag_first == false){
					if (sword.attack_flag_second == true){
						sword.attack_count++;
						enemy.type = ATTACK_MIDDLE;
						if (sword.attack_count > 12 && sword.attack_count < 27){
							if (enemy.direction == CharaInfo::RIGHT){
								enemy.pos.x() += enemy.move_speed / 4;
							}
							if (enemy.direction == CharaInfo::LEFT){
								enemy.pos.x() -= enemy.move_speed / 4;
							}
						}
						if (sword.attack_count == sword.attack_start_time2){
							sword.attack_is_dec = true;
						}
						else{
							sword.attack_is_dec = false;
						}
						if (enemy.rolling_flag == STOP){
							if (enemy.attack == true){
								sword.attack_flag_third = true;
								enemy.attack = false;
							}
						}
						if (sword.attack_count > sword.attack_end_time_middle){
							sword.attack_count = 0;
							if (sword.attack_flag_third == false){
								enemy.is_move = MOVE;
								enemy.stop_camera_x = MOVE;
								sword.attack_start = false;
							}
							sword.attack_flag_second = false;
						}
					}
				}

				if (sword.attack_flag_second == false){
					if (sword.attack_flag_third == true){
						sword.attack_count++;
						enemy.type = ATTACK_UNDER;
						if (sword.attack_count > 2 && sword.attack_count < 17){
							if (enemy.direction == CharaInfo::RIGHT){
								enemy.pos.x() += enemy.move_speed / 4;
							}
							if (enemy.direction == CharaInfo::LEFT){
								enemy.pos.x() -= enemy.move_speed / 4;
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
							enemy.is_move = MOVE;
							enemy.stop_camera_x = MOVE;
							sword.attack_start = false;
							sword.attack_flag_third = false;
						}
					}
				}
			}


			if (sword2.attack_is_dec == true){

				if (enemy.is_invin == false){
					if (swordCollision(enemy.pos, enemy.size, sword2.hit_pos, sword2.hit_range)){
						enemy.HP -= player.power;
						enemy.nockback_flag = true;
						if (enemy.pos.x() > player.pos.x())
							enemy.nockback = 1;
						if (enemy.pos.x() < player.pos.x())
							enemy.nockback = -1;
						tx.hit_sound.play();
					}
				}
			}
			if (enemy.nockback_flag == true){
				enemy.hit_count++;
				enemy.flashing++;
				if (enemy.hit_count < enemy.nockback_time){
					enemy.is_move = STOP;
					enemy.pos.x() += 3 * enemy.nockback;
				}
				else{
					enemy.nockback_flag = false;
					enemy.hit_count = 0;
					enemy.flashing = 0;
					enemy.is_move = MOVE;
				}
			}
			//***************************************************************************************************
			//アニメーションのフレームリセット
			//***************************************************************************************************

			if (sword.attack_start == false && enemy.rolling_flag == STOP && enemy.type != RUN)
			{
				enemy.type = DEFAULT;
			}
			if (enemy.HP < 0){
				enemy.HP = 0;
				enemy.is_exists = CharaInfo::DEAD;
				enemy.time2 = 0;
				player.max_money += enemy.money;
				kill++;
			}

		}
	}
}

void boss1_enemyMove(Enemy& enemy, Sword& sword, Player& player, Sword sword2, Textures& tx){

	if (enemy.pos.x() + enemy.size.x() > -WIDTH / 2 && enemy.pos.x() < WIDTH / 2 &&
		enemy.pos.y() + enemy.size.y() > -HEIGHT / 2 && enemy.pos.y() < HEIGHT / 2){
		if (enemy.is_exists == CharaInfo::LIVE){
			if (circleCollision(player.pos, enemy.pos, enemy.look_area)){
				enemy.move_time = enemy.move_time++ % 150;
				if (player.pos.x() > enemy.pos.x()){
					if (enemy.is_move == MOVE)
						enemy.direction = CharaInfo::RIGHT;
				}
				if (player.pos.x() < enemy.pos.x()){
					if (enemy.is_move == MOVE)
						enemy.direction = CharaInfo::LEFT;
				}
				if (player.pos.x() > enemy.pos.x() + enemy.look_area / 3){
					if (enemy.is_move == MOVE){
						enemy.pos.x() += enemy.move_speed * 0.8;
						enemy.type = RUN;
					}
				}
				else if (player.pos.x() <= enemy.pos.x() - enemy.look_area / 3){
					if (enemy.is_move == MOVE){
						enemy.pos.x() -= enemy.move_speed * 0.8;
						enemy.type = RUN;
					}
				}
				else if (enemy.move_time <= 40){
					enemy.type = DEFAULT;
				}
				else if (enemy.move_time == 45){
					if (enemy.is_move == MOVE){
						enemy.rolling = true;
						enemy.type = ROLLING;
					}
				}
				else if (enemy.move_time == 90){
					if (enemy.is_move == MOVE){
						enemy.attack = true;
					}
				}
				if (enemy.move_time == 110 && enemy.type == ATTACK_TOP){
					enemy.attack = true;
				}
				if (enemy.move_time == 140 && enemy.type == ATTACK_MIDDLE){
					enemy.attack = true;
				}
			}
			else{
				enemy.type = DEFAULT;
			}


			//重力処理
			if (enemy.is_gravity == MOVE){
				enemy.vector.y() += enemy.gravity;
				enemy.camera.y() += enemy.vector.y();

				if (enemy.vector.y() <= enemy.gravity_max){
					enemy.vector.y() = enemy.gravity_max;
				}
			}
			else {
				enemy.vector.y() = 0;
				enemy.camera.y() = 0;
			}



			//**************************************************************************************************
			//ローリング処理
			//**************************************************************************************************

			if (enemy.is_move == MOVE){
				if (enemy.rolling == true){
					enemy.rolling_flag = MOVE;
					enemy.time2 = 0;
					enemy.rolling = false;
				}
			}


			if (enemy.rolling_flag == MOVE)
			{
				enemy.rolling_count++;
				enemy.is_gravity = STOP;
				enemy.type = ROLLING;
				if (enemy.direction == CharaInfo::RIGHT)
				{
					if (enemy.rolling_count <= enemy.invin_time){
						enemy.is_move = STOP;
						enemy.is_invin = true;
						enemy.pos.x() += (enemy.move_speed * 0.5) * 2;
					}
					if (enemy.rolling_count > enemy.invin_time){
						enemy.is_invin = false;
					}
					if (enemy.rolling_count >= enemy.invin_time * 2){
						enemy.rolling_flag = STOP;
						enemy.is_move = MOVE;
						enemy.rolling_count = 0;
						enemy.type = DEFAULT;
					}
				}
				if (enemy.direction == CharaInfo::LEFT)
				{
					if (enemy.rolling_count <= enemy.invin_time){
						enemy.is_move = STOP;
						enemy.is_invin = true;
						enemy.pos.x() -= (enemy.move_speed * 0.5) * 2;
					}
					if (enemy.rolling_count > enemy.invin_time){

						enemy.is_invin = false;
					}
					if (enemy.rolling_count >= enemy.invin_time * 2){
						enemy.rolling_flag = STOP;
						enemy.is_move = MOVE;
						enemy.rolling_count = 0;
						enemy.type = DEFAULT;
					}
				}
			}


			//***************************************************************************************************
			//攻撃処理
			//***************************************************************************************************
			if (enemy.direction == CharaInfo::RIGHT){
				sword.hit_range.x() = 512;
				sword.hit_pos.x() = enemy.pos.x() + enemy.size.x() / 2;
				sword.hit_pos.y() = enemy.pos.y() + enemy.size.y() / 2;
			}
			if (enemy.direction == CharaInfo::LEFT){
				sword.hit_range.x() = 512;
				sword.hit_pos.x() = enemy.pos.x() + enemy.size.x() / 2 - 512;
				sword.hit_pos.y() = enemy.pos.y() + enemy.size.y() / 2;
			}
			if (enemy.is_move == MOVE){
				if (enemy.rolling_flag == STOP){
					if (sword.attack_start == false){
						if (enemy.attack == true){
							sword.attack_flag_first = true;
							sword.attack_start = true;
							enemy.is_move = STOP;
							enemy.stop_camera_x = STOP;
							enemy.time2 = 0;

							enemy.attack = false;
						}
					}
				}
			}
			if (sword.attack_start == true){
				if (sword.attack_flag_first == true){
					sword.attack_count++;
					enemy.type = ATTACK_TOP;
					if (sword.attack_count == sword.attack_start_time1){
						sword.attack_is_dec = true;
					}
					else{
						sword.attack_is_dec = false;
					}
					if (sword.attack_count > 10 && sword.attack_count < 30){		//アタック入力が入る時間
						if (enemy.rolling_flag == STOP){
							if (enemy.attack == true){
								sword.attack_flag_second = true;
								enemy.attack = false;
							}
						}
					}
					if (sword.attack_count > sword.attack_end_time_top){
						sword.attack_count = 0;
						if (sword.attack_flag_second == false){
							enemy.is_move = MOVE;
							enemy.stop_camera_x = MOVE;
							sword.attack_start = false;
						}
						sword.attack_flag_first = false;
					}
				}
				if (sword.attack_flag_first == false){
					if (sword.attack_flag_second == true){
						sword.attack_count++;
						enemy.type = ATTACK_MIDDLE;
						if (sword.attack_count > 12 && sword.attack_count < 27){
							if (enemy.direction == CharaInfo::RIGHT){
								enemy.pos.x() += enemy.move_speed / 4;
							}
							if (enemy.direction == CharaInfo::LEFT){
								enemy.pos.x() -= enemy.move_speed / 4;
							}
						}
						if (sword.attack_count == sword.attack_start_time2){
							sword.attack_is_dec = true;
						}
						else{
							sword.attack_is_dec = false;
						}


						if (enemy.rolling_flag == STOP){
							if (enemy.attack == true){		//アタック入力が入る時間
								sword.attack_flag_third = true;
								enemy.attack = false;
							}
						}

						if (sword.attack_count > sword.attack_end_time_middle){
							sword.attack_count = 0;
							if (sword.attack_flag_third == false){
								enemy.is_move = MOVE;
								enemy.stop_camera_x = MOVE;
								sword.attack_start = false;
							}
							sword.attack_flag_second = false;
						}
					}
				}

				if (sword.attack_flag_second == false){
					if (sword.attack_flag_third == true){
						sword.attack_count++;
						enemy.type = ATTACK_UNDER;
						if (sword.attack_count > 2 && sword.attack_count < 17){
							if (enemy.direction == CharaInfo::RIGHT){
								enemy.pos.x() += enemy.move_speed / 4;
							}
							if (enemy.direction == CharaInfo::LEFT){
								enemy.pos.x() -= enemy.move_speed / 4;
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
							enemy.is_move = MOVE;
							enemy.stop_camera_x = MOVE;
							sword.attack_start = false;
							sword.attack_flag_third = false;
						}
					}
				}
			}


			if (sword2.attack_is_dec == true){

				if (enemy.is_invin == false){
					if (swordCollision(enemy.pos, enemy.size, sword2.hit_pos, sword2.hit_range)){
						enemy.HP -= player.power;
						enemy.nockback_flag = true;
						if (enemy.pos.x() > player.pos.x())
							enemy.nockback = 1;
						if (enemy.pos.x() < player.pos.x())
							enemy.nockback = -1;
						tx.hit_sound.play();
					}
				}
			}
			if (enemy.nockback_flag == true){
				enemy.hit_count++;
				enemy.flashing++;
				if (enemy.hit_count < enemy.nockback_time){
					enemy.is_move = STOP;
					enemy.pos.x() += 3 * enemy.nockback;
				}
				else{
					enemy.nockback_flag = false;
					enemy.hit_count = 0;
					enemy.flashing = 0;
					enemy.is_move = MOVE;
				}
			}
			//***************************************************************************************************
			//アニメーションのフレームリセット
			//***************************************************************************************************

			if (sword.attack_start == false && enemy.rolling_flag == STOP && enemy.type != RUN)
			{
				enemy.type = DEFAULT;
			}
			if (enemy.HP < 0){
				enemy.HP = 0;
				enemy.is_exists = CharaInfo::DEAD;
				enemy.time2 = 0;
				player.max_money += enemy.money;
				kill++;
			}

		}
	}
}

//*********************************************************************************************//
//enemyのアニメーション																		   //	
//*********************************************************************************************//
void enemyDraw(Player player,Enemy& enemy, Sword& sword, Textures& tx){

	if (enemy.pos.x() + enemy.size.x() > -WIDTH / 2 && enemy.pos.x() < WIDTH / 2 &&
		enemy.pos.y() + enemy.size.y() > -HEIGHT / 2 && enemy.pos.y() < HEIGHT / 2){
		if (enemy.is_exists == CharaInfo::LIVE){
			if (enemy.enemy_attack_top_animation[8].time <= 0 || enemy.enemy_attack_middle_animation[3].time <= 0 || enemy.enemy_attack_under_animation[3].time <= 0){
				enemy.enemy_attack_top_animation[0].time = 3;
				enemy.enemy_attack_top_animation[1].time = 2;
				enemy.enemy_attack_top_animation[2].time = 3;
				enemy.enemy_attack_top_animation[3].time = 15;
				enemy.enemy_attack_top_animation[4].time = 1;
				enemy.enemy_attack_top_animation[5].time = 1;
				enemy.enemy_attack_top_animation[6].time = 12;
				enemy.enemy_attack_top_animation[7].time = 3;
				enemy.enemy_attack_top_animation[8].time = 4;

				enemy.enemy_attack_middle_animation[0].time = 12;
				enemy.enemy_attack_middle_animation[1].time = 15;
				enemy.enemy_attack_middle_animation[2].time = 1;
				enemy.enemy_attack_middle_animation[3].time = 7;

				enemy.enemy_attack_under_animation[0].time = 3;
				enemy.enemy_attack_under_animation[1].time = 1;
				enemy.enemy_attack_under_animation[2].time = 14;
				enemy.enemy_attack_under_animation[3].time = 6;
				enemy.index = 0;
			}


			drawFillBox(enemy.pos.x() - 50, enemy.pos.y() + enemy.size.y() + 50,
						enemy.HP_line, 30, Color::black, 0, Vec2f(1, 1), Vec2f(0, 0));

			drawFillBox(enemy.pos.x() - 50, enemy.pos.y() + enemy.size.y() + 50,
						enemy.HP_line * (enemy.HP / enemy.HP_max), 30, Color::lime);

			if (enemy.type != ROLLING && enemy.type != LADDER_CLIMB){
				drawTextureBox(sword.pos.x(), sword.pos.y(),
							   sword.size.x(), sword.size.y(),
							   0, 0,
							   sword.cut_size.x(), sword.cut_size.y(),
							   tx.sword, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
							   sword.angle, sword.zoom, Vec2f(0, sword.size.y() / 2));
			}





			const Vec2f displace = Vec2f(20, 50);

			switch (enemy.type)
			{
			case DEFAULT:
				enemy.se_flag = false;
				if (enemy.direction == CharaInfo::RIGHT){
					enemy_animation(enemy, 3, 20, 0);
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.default_type, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = 1;
					switch (enemy.time){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = -160 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = -160 * one_angle;
						break;
					case 2:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = -160 * one_angle;
						break;

					}
				}
				else if (enemy.direction == CharaInfo::LEFT){
					enemy_animation(enemy, 3, 20, 4);
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.default_type, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = -1;
					switch (enemy.time){
					case 4:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = 160 * one_angle;
						sword.zoom.x() = -1;
						break;
					case 5:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = 160 * one_angle;
						sword.zoom.x() = -1;
						break;
					case 6:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = 160 * one_angle;
						sword.zoom.x() = -1;
						break;

					}
				}




				break;
			case RUN:
				if (enemy.direction == CharaInfo::RIGHT){
					enemy_animation(enemy, 5, 6, 0);
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.run, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = 1;
					switch (enemy.time){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = -160 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x() + 10, enemy.pos.y() + enemy.size.y() / 2 + displace.y() - 2);
						sword.angle = -160 * one_angle;
						break;
					case 2:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x() + 15, enemy.pos.y() + enemy.size.y() / 2 + displace.y() - 1);
						sword.angle = -160 * one_angle;
						break;
					case 3:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x() + 25, enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = -160 * one_angle;
						break;
					case 4:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x() + 10, enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = -160 * one_angle;
						break;
					}
				}
				else if (enemy.direction == CharaInfo::LEFT){
					enemy_animation(enemy, 5, 6, 8);
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.run, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = -1;
					switch (enemy.time){
					case 8:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = 160 * one_angle;
						break;
					case 9:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x() - 10, enemy.pos.y() + enemy.size.y() / 2 + displace.y() - 2);
						sword.angle = 160 * one_angle;
						break;
					case 10:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x() - 15, enemy.pos.y() + enemy.size.y() / 2 + displace.y() - 1);
						sword.angle = 160 * one_angle;

						break;
					case 11:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x() - 25, enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = 160 * one_angle;

						break;
					case 12:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x() - 10, enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = 160 * one_angle;

						break;
					}
				}
				break;
			case ATTACK_TOP:
				enemy_animation_delay(enemy.cut_pos, enemy.cut_size, enemy.enemy_attack_top_animation[enemy.index].num, enemy.enemy_attack_top_animation[enemy.index].time, enemy.index);

				if (enemy.direction == CharaInfo::RIGHT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.attack_top_right, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = 1;
					switch (enemy.index){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 60,
										  enemy.pos.y() + enemy.size.y() / 2 + 80);
						sword.angle = -162 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 5,
										  enemy.pos.y() + enemy.size.y() / 2 + 189);
						sword.angle = 208 * one_angle;
						break;
					case 2:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 20,
										  enemy.pos.y() + enemy.size.y() / 2 + 218);
						sword.angle = 206 * one_angle;
						break;
					case 3:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 107,
										  enemy.pos.y() + enemy.size.y() / 2 + 125);
						sword.angle = 208 * one_angle;
						break;
					case 4:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 131,
										  enemy.pos.y() + enemy.size.y() / 2 + 81);
						sword.angle = 80 * one_angle;
						tx.attack_sound.play();
						break;
					case 5:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 160,
										  enemy.pos.y() + enemy.size.y() / 2 - 60);
						sword.angle = 7 * one_angle;
						break;
					case 6:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 66,
										  enemy.pos.y() + enemy.size.y() / 2 - 186);
						sword.angle = 0 * one_angle;
						break;
					case 7:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 10,
										  enemy.pos.y() + enemy.size.y() / 2 - 50);
						sword.angle = -7 * one_angle;
						break;
					case 8:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 100,
										  enemy.pos.y() + enemy.size.y() / 2 + 40);
						sword.angle = -17 * one_angle;
						break;

					}
				}
				else if (enemy.direction == CharaInfo::LEFT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.attack_top_left, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = 1;

					switch (enemy.index){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 60,
										  enemy.pos.y() + enemy.size.y() / 2 + 80);
						sword.angle = -12 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 5,
										  enemy.pos.y() + enemy.size.y() / 2 + 189);
						sword.angle = -28 * one_angle;
						break;
					case 2:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 20,
										  enemy.pos.y() + enemy.size.y() / 2 + 218);
						sword.angle = -26 * one_angle;
						break;
					case 3:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 107,
										  enemy.pos.y() + enemy.size.y() / 2 + 125);
						sword.angle = -28 * one_angle;
						break;
					case 4:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 131,
										  enemy.pos.y() + enemy.size.y() / 2 + 81);
						sword.angle = 100 * one_angle;
						tx.attack_sound.play();
						break;
					case 5:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 160,
										  enemy.pos.y() + enemy.size.y() / 2 - 60);
						sword.angle = 187 * one_angle;
						break;
					case 6:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 66,
										  enemy.pos.y() + enemy.size.y() / 2 - 186);
						sword.angle = 180 * one_angle;
						break;
					case 7:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 10,
										  enemy.pos.y() + enemy.size.y() / 2 - 50);
						sword.angle = 187 * one_angle;
						break;
					case 8:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 100,
										  enemy.pos.y() + enemy.size.y() / 2 + 40);
						sword.angle = 197 * one_angle;
						break;

					}
				}

				break;
			case ATTACK_MIDDLE:
				enemy_animation_delay(enemy.cut_pos, enemy.cut_size, enemy.enemy_attack_middle_animation[enemy.index].num, enemy.enemy_attack_middle_animation[enemy.index].time, enemy.index);

				if (enemy.direction == CharaInfo::RIGHT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.attack_middle_right, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = 1;
					switch (enemy.index){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 95,
										  enemy.pos.y() + enemy.size.y() / 2 + 92);
						sword.angle = -16 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 100,
										  enemy.pos.y() + enemy.size.y() / 2 - 50);
						sword.angle = -0 * one_angle;
						if (enemy.se_flag == false){
							tx.attack_sound.play();
							enemy.se_flag = true;
						}
						break;
					case 2:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 50,
										  enemy.pos.y() + enemy.size.y() / 2);
						sword.angle = -7 * one_angle;

						break;
					case 3:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 20,
										  enemy.pos.y() + enemy.size.y() / 2 + 45);
						sword.angle = -16 * one_angle;
						break;
					}
				}
				else if (enemy.direction == CharaInfo::LEFT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.attack_middle_left, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = 1;
					switch (enemy.index){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 95,
										  enemy.pos.y() + enemy.size.y() / 2 + 92);
						sword.angle = 196 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 100,
										  enemy.pos.y() + enemy.size.y() / 2 - 50);
						sword.angle = 180 * one_angle;
						if (enemy.se_flag == false){
							tx.attack_sound.play();
							enemy.se_flag = true;
						}
						break;
					case 2:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 50,
										  enemy.pos.y() + enemy.size.y() / 2);
						sword.angle = 187 * one_angle;
						break;
					case 3:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 20,
										  enemy.pos.y() + enemy.size.y() / 2 + 45);
						sword.angle = 196 * one_angle;
						break;
					}
				}
				break;

			case ATTACK_UNDER:
				enemy_animation_delay(enemy.cut_pos, enemy.cut_size, enemy.enemy_attack_under_animation[enemy.index].num, enemy.enemy_attack_under_animation[enemy.index].time, enemy.index);

				if (enemy.direction == CharaInfo::RIGHT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y() + enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y() + enemy.cut_size.y(),
								   tx.attack_under_right, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, Vec2f(0, 0));
					sword.zoom.x() = 1;
					switch (enemy.index){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 26,
										  enemy.pos.y() + enemy.size.y() / 2 + 132);
						sword.angle = -16 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 14,
										  enemy.pos.y() + enemy.size.y() / 2 + 208);
						sword.angle = -3 * one_angle;
						tx.attack_sound.play();
						break;
					case 2:
						if (enemy.enemy_attack_under_animation[2].time < 7){
							sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 10,
											  enemy.pos.y() + enemy.size.y() / 2 + 208);
							sword.angle = 110 * one_angle;
						}
						if (enemy.enemy_attack_under_animation[2].time >= 7){
							sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 10,
											  enemy.pos.y() + enemy.size.y() / 2 + 208);
							sword.angle = 80 * one_angle;
						}
						break;
					case 3:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 20,
										  enemy.pos.y() + enemy.size.y() / 2 + 105);
						sword.angle = 168 * one_angle;
						break;
					}
				}
				else if (enemy.direction == CharaInfo::LEFT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y() + enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y() + enemy.cut_size.y(),
								   tx.attack_under_left, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, Vec2f(0, 0));
					sword.zoom.x() = 1;
					switch (enemy.index){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 26,
										  enemy.pos.y() + enemy.size.y() / 2 + 132);
						sword.angle = 196 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 14,
										  enemy.pos.y() + enemy.size.y() / 2 + 208);
						sword.angle = 183 * one_angle;
						tx.attack_sound.play();
						break;
					case 2:
						if (enemy.enemy_attack_under_animation[2].time < 7){
							sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 10,
											  enemy.pos.y() + enemy.size.y() / 2 + 208);
							sword.angle = 80 * one_angle;
						}
						if (enemy.enemy_attack_under_animation[2].time >= 7){
							sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 10,
											  enemy.pos.y() + enemy.size.y() / 2 + 208);
							sword.angle = 110 * one_angle;
						}
						break;
					case 3:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 20,
										  enemy.pos.y() + enemy.size.y() / 2 + 105);
						sword.angle = 12 * one_angle;
						break;
					}
				}

				break;
			case ROLLING:
				enemy_animation(enemy, 5, 8, 0);
				if (enemy.direction == CharaInfo::RIGHT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.rolling_right, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
				}
				else if (enemy.direction == CharaInfo::LEFT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.rolling_left, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
				}
				break;
			case LADDER_CLIMB:
				enemy_animation(enemy, 4, 8, 0);
				drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
							   enemy.cut_size.x(), enemy.cut_size.y(),
							   enemy.cut_pos.x(), enemy.cut_pos.y(),
							   enemy.cut_size.x(), enemy.cut_size.y(),
							   tx.ladder, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
							   enemy.angle, Vec2f(1.2, 1), Vec2f(100, 0));
				break;
			}
		}
		if (enemy.dead_trans >= 0){
			if (enemy.is_exists == CharaInfo::DEAD){
				enemy_animation(enemy, 30, 3, 0);
				drawTextureBox(enemy.pos.x() - 250, enemy.pos.y() - 100,
							   enemy.cut_size.x(), enemy.cut_size.y(),
							   enemy.cut_pos.x(), enemy.cut_pos.y(),
							   enemy.cut_size.x(), enemy.cut_size.y(),
							   tx.dead, Color(1, 1, 1, enemy.dead_trans),
							   enemy.angle, Vec2f(1.5, 1.5), Vec2f(0, 0));
				enemy.dead_trans -= 0.01;

			}
		}
	}

	
	std::string kill_count = std::to_string(kill);
	
	if (player.debug == true)
	tx.font.draw("ころしたかず  " + kill_count, Vec2f(-1500, -800), Color::yellow);
}

void enemy2Draw(Player player, Enemy& enemy, Sword& sword, Textures& tx){

	if (enemy.pos.x() + enemy.size.x() > -WIDTH / 2 && enemy.pos.x() < WIDTH / 2 &&
		enemy.pos.y() + enemy.size.y() > -HEIGHT / 2 && enemy.pos.y() < HEIGHT / 2){
		if (enemy.is_exists == CharaInfo::LIVE){
			if (enemy.enemy_attack_top_animation[8].time <= 0 || enemy.enemy_attack_middle_animation[3].time <= 0 || enemy.enemy_attack_under_animation[3].time <= 0){
				enemy.enemy_attack_top_animation[0].time = 3;
				enemy.enemy_attack_top_animation[1].time = 2;
				enemy.enemy_attack_top_animation[2].time = 3;
				enemy.enemy_attack_top_animation[3].time = 15;
				enemy.enemy_attack_top_animation[4].time = 1;
				enemy.enemy_attack_top_animation[5].time = 1;
				enemy.enemy_attack_top_animation[6].time = 12;
				enemy.enemy_attack_top_animation[7].time = 3;
				enemy.enemy_attack_top_animation[8].time = 4;

				enemy.enemy_attack_middle_animation[0].time = 12;
				enemy.enemy_attack_middle_animation[1].time = 15;
				enemy.enemy_attack_middle_animation[2].time = 1;
				enemy.enemy_attack_middle_animation[3].time = 7;

				enemy.enemy_attack_under_animation[0].time = 3;
				enemy.enemy_attack_under_animation[1].time = 1;
				enemy.enemy_attack_under_animation[2].time = 14;
				enemy.enemy_attack_under_animation[3].time = 6;
				enemy.index = 0;
			}


			drawFillBox(enemy.pos.x() - 50, enemy.pos.y() + enemy.size.y() + 50,
						enemy.HP_line, 30, Color::black, 0, Vec2f(1, 1), Vec2f(0, 0));

			drawFillBox(enemy.pos.x() - 50, enemy.pos.y() + enemy.size.y() + 50,
						enemy.HP_line * (enemy.HP / enemy.HP_max), 30, Color::lime);

			if (enemy.type != ROLLING && enemy.type != LADDER_CLIMB){
				drawTextureBox(sword.pos.x(), sword.pos.y(),
							   sword.size.x(), sword.size.y(),
							   0, 0,
							   sword.cut_size.x(), sword.cut_size.y(),
							   tx.sword, Color(0, 1, 0, 0.5 + 0.5* cos(enemy.flashing)),
							   sword.angle, sword.zoom, Vec2f(0, sword.size.y() / 2));
			}

			const Vec2f displace = Vec2f(20, 50);
			switch (enemy.type)
			{
			case DEFAULT:
				enemy.se_flag = false;
				if (enemy.direction == CharaInfo::RIGHT){
					enemy_animation(enemy, 3, 20, 0);
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.default_type, Color(0, 1, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = 1;
					switch (enemy.time){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = -160 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = -160 * one_angle;
						break;
					case 2:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = -160 * one_angle;
						break;

					}
				}
				else if (enemy.direction == CharaInfo::LEFT){
					enemy_animation(enemy, 3, 20, 4);
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.default_type, Color(0, 1, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = -1;
					switch (enemy.time){
					case 4:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = 160 * one_angle;
						sword.zoom.x() = -1;
						break;
					case 5:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = 160 * one_angle;
						sword.zoom.x() = -1;
						break;
					case 6:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = 160 * one_angle;
						sword.zoom.x() = -1;
						break;

					}
				}




				break;
			case RUN:
				if (enemy.direction == CharaInfo::RIGHT){
					enemy_animation(enemy, 5, 6, 0);
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.run, Color(0, 1, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = 1;
					switch (enemy.time){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = -160 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x() + 10, enemy.pos.y() + enemy.size.y() / 2 + displace.y() - 2);
						sword.angle = -160 * one_angle;
						break;
					case 2:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x() + 15, enemy.pos.y() + enemy.size.y() / 2 + displace.y() - 1);
						sword.angle = -160 * one_angle;
						break;
					case 3:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x() + 25, enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = -160 * one_angle;
						break;
					case 4:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x() + 10, enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = -160 * one_angle;
						break;
					}
				}
				else if (enemy.direction == CharaInfo::LEFT){
					enemy_animation(enemy, 5, 6, 8);
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.run, Color(0, 1, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = -1;
					switch (enemy.time){
					case 8:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = 160 * one_angle;
						break;
					case 9:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x() - 10, enemy.pos.y() + enemy.size.y() / 2 + displace.y() - 2);
						sword.angle = 160 * one_angle;
						break;
					case 10:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x() - 15, enemy.pos.y() + enemy.size.y() / 2 + displace.y() - 1);
						sword.angle = 160 * one_angle;

						break;
					case 11:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x() - 25, enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = 160 * one_angle;

						break;
					case 12:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x() - 10, enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = 160 * one_angle;

						break;
					}
				}
				break;
			case ATTACK_TOP:
				enemy_animation_delay(enemy.cut_pos, enemy.cut_size, enemy.enemy_attack_top_animation[enemy.index].num, enemy.enemy_attack_top_animation[enemy.index].time, enemy.index);

				if (enemy.direction == CharaInfo::RIGHT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.attack_top_right, Color(0, 1, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = 1;
					switch (enemy.index){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 60,
										  enemy.pos.y() + enemy.size.y() / 2 + 80);
						sword.angle = -162 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 5,
										  enemy.pos.y() + enemy.size.y() / 2 + 189);
						sword.angle = 208 * one_angle;
						break;
					case 2:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 20,
										  enemy.pos.y() + enemy.size.y() / 2 + 218);
						sword.angle = 206 * one_angle;
						break;
					case 3:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 107,
										  enemy.pos.y() + enemy.size.y() / 2 + 125);
						sword.angle = 208 * one_angle;
						break;
					case 4:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 131,
										  enemy.pos.y() + enemy.size.y() / 2 + 81);
						sword.angle = 80 * one_angle;
						tx.attack_sound.play();
						break;
					case 5:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 160,
										  enemy.pos.y() + enemy.size.y() / 2 - 60);
						sword.angle = 7 * one_angle;
						break;
					case 6:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 66,
										  enemy.pos.y() + enemy.size.y() / 2 - 186);
						sword.angle = 0 * one_angle;
						break;
					case 7:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 10,
										  enemy.pos.y() + enemy.size.y() / 2 - 50);
						sword.angle = -7 * one_angle;
						break;
					case 8:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 100,
										  enemy.pos.y() + enemy.size.y() / 2 + 40);
						sword.angle = -17 * one_angle;
						break;

					}
				}
				else if (enemy.direction == CharaInfo::LEFT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.attack_top_left, Color(0, 1, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = 1;

					switch (enemy.index){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 60,
										  enemy.pos.y() + enemy.size.y() / 2 + 80);
						sword.angle = -12 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 5,
										  enemy.pos.y() + enemy.size.y() / 2 + 189);
						sword.angle = -28 * one_angle;
						break;
					case 2:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 20,
										  enemy.pos.y() + enemy.size.y() / 2 + 218);
						sword.angle = -26 * one_angle;
						break;
					case 3:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 107,
										  enemy.pos.y() + enemy.size.y() / 2 + 125);
						sword.angle = -28 * one_angle;
						break;
					case 4:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 131,
										  enemy.pos.y() + enemy.size.y() / 2 + 81);
						sword.angle = 100 * one_angle;
						tx.attack_sound.play();
						break;
					case 5:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 160,
										  enemy.pos.y() + enemy.size.y() / 2 - 60);
						sword.angle = 187 * one_angle;
						break;
					case 6:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 66,
										  enemy.pos.y() + enemy.size.y() / 2 - 186);
						sword.angle = 180 * one_angle;
						break;
					case 7:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 10,
										  enemy.pos.y() + enemy.size.y() / 2 - 50);
						sword.angle = 187 * one_angle;
						break;
					case 8:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 100,
										  enemy.pos.y() + enemy.size.y() / 2 + 40);
						sword.angle = 197 * one_angle;
						break;

					}
				}

				break;
			case ATTACK_MIDDLE:
				enemy_animation_delay(enemy.cut_pos, enemy.cut_size, enemy.enemy_attack_middle_animation[enemy.index].num, enemy.enemy_attack_middle_animation[enemy.index].time, enemy.index);

				if (enemy.direction == CharaInfo::RIGHT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.attack_middle_right, Color(0, 1, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = 1;
					switch (enemy.index){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 95,
										  enemy.pos.y() + enemy.size.y() / 2 + 92);
						sword.angle = -16 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 100,
										  enemy.pos.y() + enemy.size.y() / 2 - 50);
						sword.angle = -0 * one_angle;
						if (enemy.se_flag == false){
							tx.attack_sound.play();
							enemy.se_flag = true;
						}
						break;
					case 2:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 50,
										  enemy.pos.y() + enemy.size.y() / 2);
						sword.angle = -7 * one_angle;

						break;
					case 3:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 20,
										  enemy.pos.y() + enemy.size.y() / 2 + 45);
						sword.angle = -16 * one_angle;
						break;
					}
				}
				else if (enemy.direction == CharaInfo::LEFT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.attack_middle_left, Color(0, 1, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = 1;
					switch (enemy.index){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 95,
										  enemy.pos.y() + enemy.size.y() / 2 + 92);
						sword.angle = 196 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 100,
										  enemy.pos.y() + enemy.size.y() / 2 - 50);
						sword.angle = 180 * one_angle;
						if (enemy.se_flag == false){
							tx.attack_sound.play();
							enemy.se_flag = true;
						}
						break;
					case 2:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 50,
										  enemy.pos.y() + enemy.size.y() / 2);
						sword.angle = 187 * one_angle;
						break;
					case 3:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 20,
										  enemy.pos.y() + enemy.size.y() / 2 + 45);
						sword.angle = 196 * one_angle;
						break;
					}
				}
				break;

			case ATTACK_UNDER:
				enemy_animation_delay(enemy.cut_pos, enemy.cut_size, enemy.enemy_attack_under_animation[enemy.index].num, enemy.enemy_attack_under_animation[enemy.index].time, enemy.index);

				if (enemy.direction == CharaInfo::RIGHT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y() + enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y() + enemy.cut_size.y(),
								   tx.attack_under_right, Color(0, 1, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, Vec2f(0, 0));
					sword.zoom.x() = 1;
					switch (enemy.index){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 26,
										  enemy.pos.y() + enemy.size.y() / 2 + 132);
						sword.angle = -16 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 14,
										  enemy.pos.y() + enemy.size.y() / 2 + 208);
						sword.angle = -3 * one_angle;
						tx.attack_sound.play();
						break;
					case 2:
						if (enemy.enemy_attack_under_animation[2].time < 7){
							sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 10,
											  enemy.pos.y() + enemy.size.y() / 2 + 208);
							sword.angle = 110 * one_angle;
						}
						if (enemy.enemy_attack_under_animation[2].time >= 7){
							sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 10,
											  enemy.pos.y() + enemy.size.y() / 2 + 208);
							sword.angle = 80 * one_angle;
						}
						break;
					case 3:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 20,
										  enemy.pos.y() + enemy.size.y() / 2 + 105);
						sword.angle = 168 * one_angle;
						break;
					}
				}
				else if (enemy.direction == CharaInfo::LEFT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y() + enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y() + enemy.cut_size.y(),
								   tx.attack_under_left, Color(0, 1, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, Vec2f(0, 0));
					sword.zoom.x() = 1;
					switch (enemy.index){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 26,
										  enemy.pos.y() + enemy.size.y() / 2 + 132);
						sword.angle = 196 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 14,
										  enemy.pos.y() + enemy.size.y() / 2 + 208);
						sword.angle = 183 * one_angle;
						tx.attack_sound.play();
						break;
					case 2:
						if (enemy.enemy_attack_under_animation[2].time < 7){
							sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 10,
											  enemy.pos.y() + enemy.size.y() / 2 + 208);
							sword.angle = 80 * one_angle;
						}
						if (enemy.enemy_attack_under_animation[2].time >= 7){
							sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 10,
											  enemy.pos.y() + enemy.size.y() / 2 + 208);
							sword.angle = 110 * one_angle;
						}
						break;
					case 3:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 20,
										  enemy.pos.y() + enemy.size.y() / 2 + 105);
						sword.angle = 12 * one_angle;
						break;
					}
				}

				break;
			case ROLLING:
				enemy_animation(enemy, 5, 8, 0);
				if (enemy.direction == CharaInfo::RIGHT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.rolling_right, Color(0, 1, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
				}
				else if (enemy.direction == CharaInfo::LEFT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.rolling_left, Color(0, 1, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
				}
				break;
			case LADDER_CLIMB:
				enemy_animation(enemy, 4, 8, 0);
				drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
							   enemy.cut_size.x(), enemy.cut_size.y(),
							   enemy.cut_pos.x(), enemy.cut_pos.y(),
							   enemy.cut_size.x(), enemy.cut_size.y(),
							   tx.ladder, Color(0, 1, 0, 0.5 + 0.5* cos(enemy.flashing)),
							   enemy.angle, Vec2f(1.2, 1), Vec2f(100, 0));
				break;
			}
		}
		if (enemy.dead_trans >= 0){
			if (enemy.is_exists == CharaInfo::DEAD){
				enemy_animation(enemy, 30, 3, 0);
				drawTextureBox(enemy.pos.x() - 250, enemy.pos.y() - 100,
							   enemy.cut_size.x(), enemy.cut_size.y(),
							   enemy.cut_pos.x(), enemy.cut_pos.y(),
							   enemy.cut_size.x(), enemy.cut_size.y(),
							   tx.dead, Color(1, 1, 1, enemy.dead_trans),
							   enemy.angle, Vec2f(1.5, 1.5), Vec2f(0, 0));
				enemy.dead_trans -= 0.01;
			}
		}
	}


	std::string kill_count = std::to_string(kill);
	
	if (player.debug == true)
	tx.font.draw("ころしたかず  " + kill_count, Vec2f(-1500, -800), Color::yellow);
}

void boss1_enemyDraw(Player player, Enemy& enemy, Sword& sword, Textures& tx){

	if (enemy.pos.x() + enemy.size.x() > -WIDTH / 2 && enemy.pos.x() < WIDTH / 2 &&
		enemy.pos.y() + enemy.size.y() > -HEIGHT / 2 && enemy.pos.y() < HEIGHT / 2){
		if (enemy.is_exists == CharaInfo::LIVE){
			if (enemy.enemy_attack_top_animation[8].time <= 0 || enemy.enemy_attack_middle_animation[3].time <= 0 || enemy.enemy_attack_under_animation[3].time <= 0){
				enemy.enemy_attack_top_animation[0].time = 3;
				enemy.enemy_attack_top_animation[1].time = 2;
				enemy.enemy_attack_top_animation[2].time = 3;
				enemy.enemy_attack_top_animation[3].time = 15;
				enemy.enemy_attack_top_animation[4].time = 1;
				enemy.enemy_attack_top_animation[5].time = 1;
				enemy.enemy_attack_top_animation[6].time = 12;
				enemy.enemy_attack_top_animation[7].time = 3;
				enemy.enemy_attack_top_animation[8].time = 4;

				enemy.enemy_attack_middle_animation[0].time = 12;
				enemy.enemy_attack_middle_animation[1].time = 15;
				enemy.enemy_attack_middle_animation[2].time = 1;
				enemy.enemy_attack_middle_animation[3].time = 7;

				enemy.enemy_attack_under_animation[0].time = 3;
				enemy.enemy_attack_under_animation[1].time = 1;
				enemy.enemy_attack_under_animation[2].time = 14;
				enemy.enemy_attack_under_animation[3].time = 6;
				enemy.index = 0;
			}


			drawFillBox(enemy.pos.x() - 50, enemy.pos.y() + enemy.size.y() + 50,
						enemy.HP_line, 30, Color::black, 0, Vec2f(1, 1), Vec2f(0, 0));

			drawFillBox(enemy.pos.x() - 50, enemy.pos.y() + enemy.size.y() + 50,
						enemy.HP_line * (enemy.HP / enemy.HP_max), 30, Color::lime);

			if (enemy.type != ROLLING && enemy.type != LADDER_CLIMB){
				drawTextureBox(sword.pos.x(), sword.pos.y(),
							   sword.size.x(), sword.size.y(),
							   0, 0,
							   sword.cut_size.x(), sword.cut_size.y(),
							   tx.sword, Color(1, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
							   sword.angle, sword.zoom, Vec2f(0, sword.size.y() / 2));
			}
			const Vec2f displace = Vec2f(20, 50);

			switch (enemy.type)
			{
			case DEFAULT:
				enemy.se_flag = false;
				if (enemy.direction == CharaInfo::RIGHT){
					enemy_animation(enemy, 3, 20, 0);
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.default_type, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = 1;
					switch (enemy.time){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = -160 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = -160 * one_angle;
						break;
					case 2:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = -160 * one_angle;
						break;

					}
				}
				else if (enemy.direction == CharaInfo::LEFT){
					enemy_animation(enemy, 3, 20, 4);
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.default_type, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = -1;
					switch (enemy.time){
					case 4:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = 160 * one_angle;
						sword.zoom.x() = -1;
						break;
					case 5:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = 160 * one_angle;
						sword.zoom.x() = -1;
						break;
					case 6:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = 160 * one_angle;
						sword.zoom.x() = -1;
						break;

					}
				}
				break;
			case RUN:
				if (enemy.direction == CharaInfo::RIGHT){
					enemy_animation(enemy, 5, 6, 0);
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.run, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = 1;
					switch (enemy.time){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = -160 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x() + 10, enemy.pos.y() + enemy.size.y() / 2 + displace.y() - 2);
						sword.angle = -160 * one_angle;
						break;
					case 2:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x() + 15, enemy.pos.y() + enemy.size.y() / 2 + displace.y() - 1);
						sword.angle = -160 * one_angle;
						break;
					case 3:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x() + 25, enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = -160 * one_angle;
						break;
					case 4:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + displace.x() + 10, enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = -160 * one_angle;
						break;
					}
				}
				else if (enemy.direction == CharaInfo::LEFT){
					enemy_animation(enemy, 5, 6, 8);
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.run, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = -1;
					switch (enemy.time){
					case 8:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x(), enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = 160 * one_angle;
						break;
					case 9:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x() - 10, enemy.pos.y() + enemy.size.y() / 2 + displace.y() - 2);
						sword.angle = 160 * one_angle;
						break;
					case 10:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x() - 15, enemy.pos.y() + enemy.size.y() / 2 + displace.y() - 1);
						sword.angle = 160 * one_angle;

						break;
					case 11:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x() - 25, enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = 160 * one_angle;

						break;
					case 12:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - displace.x() - 10, enemy.pos.y() + enemy.size.y() / 2 + displace.y());
						sword.angle = 160 * one_angle;

						break;
					}
				}
				break;
			case ATTACK_TOP:
				enemy_animation_delay(enemy.cut_pos, enemy.cut_size, enemy.enemy_attack_top_animation[enemy.index].num, enemy.enemy_attack_top_animation[enemy.index].time, enemy.index);

				if (enemy.direction == CharaInfo::RIGHT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.attack_top_right, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = 1;
					switch (enemy.index){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 60,
										  enemy.pos.y() + enemy.size.y() / 2 + 80);
						sword.angle = -162 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 5,
										  enemy.pos.y() + enemy.size.y() / 2 + 189);
						sword.angle = 208 * one_angle;
						break;
					case 2:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 20,
										  enemy.pos.y() + enemy.size.y() / 2 + 218);
						sword.angle = 206 * one_angle;
						break;
					case 3:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 107,
										  enemy.pos.y() + enemy.size.y() / 2 + 125);
						sword.angle = 208 * one_angle;
						break;
					case 4:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 131,
										  enemy.pos.y() + enemy.size.y() / 2 + 81);
						sword.angle = 80 * one_angle;
						tx.attack_sound.play();
						break;
					case 5:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 160,
										  enemy.pos.y() + enemy.size.y() / 2 - 60);
						sword.angle = 7 * one_angle;
						break;
					case 6:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 66,
										  enemy.pos.y() + enemy.size.y() / 2 - 186);
						sword.angle = 0 * one_angle;
						break;
					case 7:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 10,
										  enemy.pos.y() + enemy.size.y() / 2 - 50);
						sword.angle = -7 * one_angle;
						break;
					case 8:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 100,
										  enemy.pos.y() + enemy.size.y() / 2 + 40);
						sword.angle = -17 * one_angle;
						break;

					}
				}
				else if (enemy.direction == CharaInfo::LEFT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.attack_top_left, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = 1;

					switch (enemy.index){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 60,
										  enemy.pos.y() + enemy.size.y() / 2 + 80);
						sword.angle = -12 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 5,
										  enemy.pos.y() + enemy.size.y() / 2 + 189);
						sword.angle = -28 * one_angle;
						break;
					case 2:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 20,
										  enemy.pos.y() + enemy.size.y() / 2 + 218);
						sword.angle = -26 * one_angle;
						break;
					case 3:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 107,
										  enemy.pos.y() + enemy.size.y() / 2 + 125);
						sword.angle = -28 * one_angle;
						break;
					case 4:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 131,
										  enemy.pos.y() + enemy.size.y() / 2 + 81);
						sword.angle = 100 * one_angle;
						tx.attack_sound.play();
						break;
					case 5:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 160,
										  enemy.pos.y() + enemy.size.y() / 2 - 60);
						sword.angle = 187 * one_angle;
						break;
					case 6:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 66,
										  enemy.pos.y() + enemy.size.y() / 2 - 186);
						sword.angle = 180 * one_angle;
						break;
					case 7:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 10,
										  enemy.pos.y() + enemy.size.y() / 2 - 50);
						sword.angle = 187 * one_angle;
						break;
					case 8:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 100,
										  enemy.pos.y() + enemy.size.y() / 2 + 40);
						sword.angle = 197 * one_angle;
						break;

					}
				}

				break;
			case ATTACK_MIDDLE:
				enemy_animation_delay(enemy.cut_pos, enemy.cut_size, enemy.enemy_attack_middle_animation[enemy.index].num, enemy.enemy_attack_middle_animation[enemy.index].time, enemy.index);

				if (enemy.direction == CharaInfo::RIGHT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.attack_middle_right, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = 1;
					switch (enemy.index){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 95,
										  enemy.pos.y() + enemy.size.y() / 2 + 92);
						sword.angle = -16 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 100,
										  enemy.pos.y() + enemy.size.y() / 2 - 50);
						sword.angle = -0 * one_angle;
						if (enemy.se_flag == false){
							tx.attack_sound.play();
							enemy.se_flag = true;
						}
						break;
					case 2:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 50,
										  enemy.pos.y() + enemy.size.y() / 2);
						sword.angle = -7 * one_angle;
						break;
					case 3:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 20,
										  enemy.pos.y() + enemy.size.y() / 2 + 45);
						sword.angle = -16 * one_angle;
						break;
					}
				}
				else if (enemy.direction == CharaInfo::LEFT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.attack_middle_left, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
					sword.zoom.x() = 1;
					switch (enemy.index){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 95,
										  enemy.pos.y() + enemy.size.y() / 2 + 92);
						sword.angle = 196 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 100,
										  enemy.pos.y() + enemy.size.y() / 2 - 50);
						sword.angle = 180 * one_angle;
						if (enemy.se_flag == false){
							tx.attack_sound.play();
							enemy.se_flag = true;
						}
						break;
					case 2:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 50,
										  enemy.pos.y() + enemy.size.y() / 2);
						sword.angle = 187 * one_angle;
						break;
					case 3:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 20,
										  enemy.pos.y() + enemy.size.y() / 2 + 45);
						sword.angle = 196 * one_angle;
						break;
					}
				}
				break;

			case ATTACK_UNDER:
				enemy_animation_delay(enemy.cut_pos, enemy.cut_size, enemy.enemy_attack_under_animation[enemy.index].num, enemy.enemy_attack_under_animation[enemy.index].time, enemy.index);
				if (enemy.direction == CharaInfo::RIGHT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y() + enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y() + enemy.cut_size.y(),
								   tx.attack_under_right, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, Vec2f(0, 0));
					sword.zoom.x() = 1;
					switch (enemy.index){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 26,
										  enemy.pos.y() + enemy.size.y() / 2 + 132);
						sword.angle = -16 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 14,
										  enemy.pos.y() + enemy.size.y() / 2 + 208);
						sword.angle = -3 * one_angle;
						tx.attack_sound.play();
						break;
					case 2:
						if (enemy.enemy_attack_under_animation[2].time < 7){
							sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 10,
											  enemy.pos.y() + enemy.size.y() / 2 + 208);
							sword.angle = 110 * one_angle;
						}
						if (enemy.enemy_attack_under_animation[2].time >= 7){
							sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 10,
											  enemy.pos.y() + enemy.size.y() / 2 + 208);
							sword.angle = 80 * one_angle;
						}
						break;
					case 3:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 20,
										  enemy.pos.y() + enemy.size.y() / 2 + 105);
						sword.angle = 168 * one_angle;
						break;
					}
				}
				else if (enemy.direction == CharaInfo::LEFT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y() + enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y() + enemy.cut_size.y(),
								   tx.attack_under_left, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, Vec2f(0, 0));
					sword.zoom.x() = 1;
					switch (enemy.index){
					case 0:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 26,
										  enemy.pos.y() + enemy.size.y() / 2 + 132);
						sword.angle = 196 * one_angle;
						break;
					case 1:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 14,
										  enemy.pos.y() + enemy.size.y() / 2 + 208);
						sword.angle = 183 * one_angle;
						tx.attack_sound.play();
						break;
					case 2:
						if (enemy.enemy_attack_under_animation[2].time < 7){
							sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 10,
											  enemy.pos.y() + enemy.size.y() / 2 + 208);
							sword.angle = 80 * one_angle;
						}
						if (enemy.enemy_attack_under_animation[2].time >= 7){
							sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 - 10,
											  enemy.pos.y() + enemy.size.y() / 2 + 208);
							sword.angle = 110 * one_angle;
						}
						break;
					case 3:
						sword.pos = Vec2f(enemy.pos.x() + enemy.size.x() / 2 + 20,
										  enemy.pos.y() + enemy.size.y() / 2 + 105);
						sword.angle = 12 * one_angle;
						break;
					}
				}

				break;
			case ROLLING:
				enemy_animation(enemy, 5, 8, 0);
				if (enemy.direction == CharaInfo::RIGHT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.rolling_right, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
				}
				else if (enemy.direction == CharaInfo::LEFT){
					drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   enemy.cut_pos.x(), enemy.cut_pos.y(),
								   enemy.cut_size.x(), enemy.cut_size.y(),
								   tx.rolling_left, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
								   enemy.angle, enemy.zoom, enemy.center);
				}
				break;
			case LADDER_CLIMB:
				enemy_animation(enemy, 4, 8, 0);
				drawTextureBox(enemy.pos.x() + enemy.centering_size, enemy.pos.y(),
							   enemy.cut_size.x(), enemy.cut_size.y(),
							   enemy.cut_pos.x(), enemy.cut_pos.y(),
							   enemy.cut_size.x(), enemy.cut_size.y(),
							   tx.ladder, Color(0, 0, 0, 0.5 + 0.5* cos(enemy.flashing)),
							   enemy.angle, Vec2f(1.2, 1), Vec2f(100, 0));
				break;
			}
		}
		if (enemy.dead_trans >= 0){
			if (enemy.is_exists == CharaInfo::DEAD){
				enemy_animation(enemy, 30, 3, 0);
				drawTextureBox(enemy.pos.x() - 250, enemy.pos.y() - 100,
							   enemy.cut_size.x(), enemy.cut_size.y(),
							   enemy.cut_pos.x(), enemy.cut_pos.y(),
							   enemy.cut_size.x(), enemy.cut_size.y(),
							   tx.dead, Color(1, 1, 1, enemy.dead_trans),
							   enemy.angle, Vec2f(1.5, 1.5), Vec2f(0, 0));
				enemy.dead_trans -= 0.01;

			}
		}
	}


	std::string kill_count = std::to_string(kill);
	if (player.debug == true)
	tx.font.draw("ころしたかず  " + kill_count, Vec2f(-1500, -800), Color::yellow);
}

