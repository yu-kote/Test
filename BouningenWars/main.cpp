//
// アプリ雛形
// 

// GameTemplateで用意されている機能
// の全てをインクルード
#include "lib/framework.hpp"
#include <iostream>
#include <string>
#include <ctime>
using namespace std;



int main() {
	// アプリウインドウを生成
	// TIPS:必ず、最初に生成する事

	AppEnv env(3000, 2000,
		false,
		true);
	int gamen = 0;

	Texture title1("res/title/daimei1.png");
	Texture title2("res/title/daimei2.png");
	Texture title3("res/title/daimei3.png");
	Texture start1("res/title/start1.png");
	Texture start2("res/title/start2.png");
	Texture start3("res/title/start3.png");
	Texture start4("res/title/start4.png");
	Texture start5("res/title/start5.png");
	Texture start6("res/title/start6.png");
	Texture end1("res/title/end1.png");
	Texture end2("res/title/end2.png");
	Texture end3("res/title/end3.png");
	Texture end4("res/title/end4.png");
	Texture end5("res/title/end5.png");
	Texture end6("res/title/end6.png");
	Texture clear[3] = {
		Texture ("res/clear/clear1.png"),
		Texture ("res/clear/clear2.png"),
		Texture ("res/clear/clear3.png"),
	};
	Texture option("res/title/option.png");
	Texture BGM("res/title/optionBGM.png");
	Texture ziki_C("res/title/optionColor.png");
	Texture back("res/title/back.png");
	Texture plus("res/title/purasu.png");
	Texture minus("res/title/mainasu.png");

	//効果音
	Media ken_sound("res/oto/katana-slash5.wav");	//剣を振る音
	Media teki_sound("res/oto/sword-slash3.wav");	//ヒット音
	Media tyuto_sound("res/oto/hit01.wav");	//チュートリアル
	Media pon_sound("res/oto/teki-up.wav");	//敵ポップ音


	Texture bou("res/character/runman.png"); //自機画像
	Texture bou1("res/character/runman_h .png"); //自機画像反転
	Texture ken("res/ken/ken.png");	//攻撃画像
	Texture dead("res/character/syoumetu.png");


	//オプション
	float sound = 1.0;


	Random rand;
	rand.setSeed(std::time(nullptr));
	float ziki_CR = rand(0.0f, 1.0f);
	float ziki_CG = rand(0.0f, 1.0f);
	float ziki_CB = rand(0.0f, 1.0f);
	bool bgin_flag = false;
	Color ziki_color = Color(ziki_CR, ziki_CG, ziki_CB);
	while (1){
		env.begin();


		float zimen_R = 0.627;	//地面色R
		float zimen_G = 0.392;	//地面色G 
		float zimen_B = 0;		//地面色B
		//自機の変数
		float ziki_x = 0;	//自機の始点ｘ
		float ziki_y = 0;	//自機の始点ｙ
		float ziki_ax = 0;	//自機の当り判定補正値ｘ
		float ziki_ay = 0;	//自機の当り判定補正値ｙ
		float speed = 0.1;	//自機のスピード
		float kasoku = 0;	//自機の加速度
		bool jump = true;	//ジャンプ地面
		bool jump_s1 = true;	//ジャンプ障害物
		float jump_p = 80;	//ジャンプ力
		ziki_y = -500;	//自機の補正値ｘ
		ziki_x = -500;	//自機の補正値ｙ
		int gazou_haba1 = 532;
		int gazou_haba2 = 256;

		
		bool ziki_muki = false;	//自機の向き
		int c_size_x = 130;	//自機の画像幅
		int c_size_y = 200;	//自機の画像高さ
		int z_size_x = 216;	//自機の画像切り取り幅
		int z_size_y = 216;	//自機の画像切り取り高さ
		int size_hosei = 75;	//画像の位置調整
		int bou1_time = 0;	//デフォルト立ちタイム
		int jump_time = 0;	//ジャンプタイム
		bool run = false;	//走る画像判定
		int run_time = 0;	//走るタイム
		float ziki_hpmax = 1000;	//最大HP
		float ziki_nowhp = 0;		//今のHP
		ziki_nowhp = ziki_hpmax;
		float ziki_hpba = 200;	//HPの長さ
		int hpba_x = -30;	//HPバーの位置ｘ
		int hpba_y = 230;	//HPバーの位置ｙ
		int hpba_haba = 5;	//HPバーの太さ
		bool ziki_hitflag = false;	//自機に攻撃がヒットしているかの判定

		//剣１情報
		
		int k_size_x = 350;	//攻撃画像幅
		int k_size_y = 300;	//攻撃画像高さ
		int ken_x_m = 130;	//右攻撃画像始点座標ｘ
		int ken_y_m = 0;	//右攻撃画像始点座標ｙ
		int ken_x_h = -350;	//左攻撃画像始点座標ｘ
		int ken_y_h = 0;	//左攻撃画像始点座標ｙ
		float ken_width = 1.3;	//剣の拡大率幅
		float ken_hight = 0.5;	//剣の拡大率高さ
		float ken_hight2 = 1;	//剣の拡大率高さ２
		int ken_time1_m = 0;		//右攻撃表示速度
		int ken_time2_m = 3;	//右攻撃表示速度２
		int ken_time3_m = 12;	//右攻撃速度の剰余
		int ken_time1_h = 0;	//左攻撃表示速度
		int ken_time2_h = 3;	//左攻撃表示速度２
		int ken_time3_h = 12;	//左攻撃速度の剰余
		bool ken_f = false;	//自機攻撃判定１
		bool ken_f2 = false;	//自機攻撃判定２
		bool ken_hitflag_m = false;		//右の剣が当たっているかどうか
		bool ken_hitflag_h = false;		//左の剣が当たっているかどうか
		int ken_ax_m1 = 0;		//剣の左下当り判定ｘ（右）
		int ken_ay_m1 = 0;		//剣の左下当り判定ｙ
		int ken_ay_m2 = 0;		//剣の左上当り判定ｙ
		int ken_ax_m3 = 0;		//剣の右下当り判定ｘ
		int ken_ax_h1 = 0;		//剣の左下当り判定ｘ（左）
		int ken_ay_h1 = 0;		//剣の左下当り判定ｙ
		int ken_ay_h2 = 0;		//剣の左上当り判定ｙ
		int ken_ax_h3 = 0;		//剣の右下当り判定ｘ

		float ken_power = 20;		//剣の初期攻撃力

		//敵の変数
		const int Ene = 1000;	//すべての敵の数
		const int A = 11;	//P1の敵
		const int B = 21;	//P2の敵
		const int C = 41;	//P3の敵
		const int D = 51;	//P4の敵
		const int E = 10;	//P5の敵
		const int F = 10;	//P6の敵
		const int G = 10;	//P7の敵
		const int H = 10;	//P8の敵
		const int I = 10;	//P9の敵
		const int J = 10;	//P10の敵

		struct Enemy{
			float x;	//敵の始点ｘ
			float y;	//敵の始点ｙ
			float ax;		//敵の座標補正分ｘ
			float ay;		//敵の座標補正分ｙ
			float hpmax;	//敵のHP
			float hpba;	//HPの長さ
			float nowhp;	//今のHP
			int ken_time;	//敵の攻撃速度
			int jump_time;	//敵のジャンプタイム
			int jump_motion2; //ジャンプ画像表示間隔
			int run_time;	//敵の走るタイム
			int def_haba;	//敵の
			int def_time;	//敵のデフォルト立ちタイム
			int kasoku;		//敵の加速度
			int jump_p;		//敵のジャンプ力
			float vy;		//敵にかかる重力
			float K;		//敵の攻撃力
			bool flag;	//敵が出ているかどうか
			bool sound_flag; //敵ポップ音
			bool ken_flag;	//敵が攻撃しているかどうか
			bool muki_flag;		//敵の向き
			bool jump_flag;   //一番下の地面のジャンプフラグ
			bool jump_s1_flag;   //障害物のジャンプフラグ
			bool dead_flag;		//敵が死んでいるかどうか
			int dead_time;		//敵の死亡エフェクトタイム
			float g;	//敵にかかる重力

		};
		Enemy enemy[Ene];

		for (int i = 0; i < Ene; i++){

			enemy[i].x = 0;
			enemy[i].y = 0;
			enemy[i].ax = 0;
			enemy[i].ay = 0;
			enemy[i].hpmax = 50;
			enemy[i].hpba = 200;
			enemy[i].nowhp = 0;
			enemy[i].nowhp = enemy[i].hpmax;
			enemy[i].ken_time = 0;
			enemy[i].jump_time = 0;
			enemy[i].jump_motion2 = 0;
			enemy[i].run_time = 0;
			enemy[i].def_haba = 0;
			enemy[i].def_time = 0;
			enemy[i].kasoku = 0;
			enemy[i].jump_p = 0;
			enemy[i].vy = 0;
			enemy[i].K = 10;
			enemy[i].flag = false;
			enemy[i].sound_flag = false;
			enemy[i].ken_flag = false;
			enemy[i].muki_flag = false;
			enemy[i].jump_flag = false;
			enemy[i].jump_s1_flag = false;
			enemy[i].dead_flag = false;
			enemy[i].dead_time = false;
			enemy[i].g = -5;
		}

		//敵の体力変化代入式
		for (int i = 22; i < C; i++){
			enemy[i].hpmax = 30;
			enemy[i].nowhp = enemy[i].hpmax;


		}
		for (int i = 41; i < D; i++){
			enemy[i].hpmax = 100;
			enemy[i].nowhp = enemy[i].hpmax;

		}
		int E1[Ene];	//敵のナンバー
		for (int i = 0; i < Ene; i++){
			E1[i] = i;
		}

		//敵の初期位置　描画

		for (int i = 5; i < Ene; i++){
			enemy[E1[i]].x = rand(-1700, 1500);
			enemy[E1[i]].y = 1100;
		}

		//ボスの体力変化代入式
		enemy[21].hpmax = 600;
		enemy[21].nowhp = enemy[21].hpmax;
		enemy[21].y = 1100;
		enemy[21].x = -1300;
		enemy[51].hpmax = 1500;
		enemy[51].nowhp = enemy[51].hpmax;

		enemy[E1[0]].x = 200; enemy[E1[0]].y = 1100;
		enemy[E1[1]].x = 500; enemy[E1[1]].y = 1100;
		enemy[E1[2]].x = 900; enemy[E1[2]].y = 1100;
		enemy[E1[3]].x = 100; enemy[E1[3]].y = 1100;

		//撃破アニメーション
		
		int dead_time = 0;	//画像間隔
		int dead_x = 0;		//画像位置ｘ
		int dead_y = 0;		//画像位置ｙ
		int dead_count = 5;		//画像カウン
		int dead_count_bos = 50;
		int dead_motion = 0; //画像表示位置
		int kill_count = 0;

		//フィールド情報
		int ground_time = 0;	//フィールドの時間
		int ground_time2 = 0;
		int ground_time3 = 0;
		float g = -5;	//重力
		float vy = 0;	//自機ベクトルｙ
		float vx = 0;	//自機ベクトルｘ

		//敵のナンバーポインタ
		int* a;		//敵の数の要素数を入れるポインタの箱
		int e_name = 0;		//敵の数の要素数
		a = &e_name;		//代入式

		int chara_def = 0;		//デフォルト立ちの画像の切り取り開始位置
		int run_motion = 0;		//走る画像の切り取り開始位置
		int jump_motion = 0;	//ジャンプ画像の切り取り開始位置
		int ken_motion = 0;		//剣の画像の切り取り開始位置

		//チュートリアル処理
		Font font("res/KodomoRounded.otf");
		bool tyuto_1 = false;
		bool tyuto_2 = false;
		bool tyuto_3 = false;
		bool tyuto_4 = false;
		bool teki_pon = false;

		//タイトル画面画像
		
		int title_count_daimei = 0;
		int title_count_start = 0;
		int title_count_end = 0;
		int title_x = -2048;
		int title_y = -1024;
		int title_ax = 4096;
		int title_ay = 2048;
		int start_x = -1100;
		int start_y = -450;
		int start_ax = start_x + 800;
		int start_ay = start_y + 250;
		int end_x = 400;
		int end_y = -450;
		int end_ax = end_x + 600;
		int end_ay = end_y + 250;
		int option_x = 800;
		int option_y = -1000;
		int option_ax = option_x + 1024;
		int option_ay = option_y + 256;
		int plus_x = 100;
		int plus_y = -450;
		int plus_s = 150;
		int plus_ax = plus_x + plus_s;
		int plus_ay = plus_y + plus_s;
		int minus_x = 890;
		int minus_y = -450;
		int minus_ax = minus_x + plus_s;
		int minus_ay = minus_y + plus_s;
		int bgm_x = 260;
		int bgm_y = -450;
		int color_x = -1000;
		int color_y = -450;
		int color_ax = color_x + 470;
		int color_ay = color_y + 230;



		bool start_flag = false;
		bool end_flag = false;
		bool title_flag = true;
		bool option_flag = false;
		int size = 1024;
		int size2 = 256;



		//タイトル
		while (gamen == 0){
			env.begin();
			if (!env.isOpen()){ return 0; }
			env.bgColor(Color::white); //背景を白にする
			font.size(50);
			font.draw("Press A or D", Vec2f(-1400, -800), Color::black);
			font.draw("Push K or SPACE", Vec2f(-1400, -850), Color::black);

			ken_sound.gain(sound);
			teki_sound.gain(sound);
			tyuto_sound.gain(sound);
			pon_sound.gain(sound);

			//自機データ
			if (bgin_flag == false){
				ziki_color = Color(1.0f, 1.0f, 1.0f);
				bgin_flag = true;
			}

			//自機の座標補正
			ziki_ax = ziki_x + c_size_x;
			ziki_ay = ziki_y + c_size_y;

			//自機の操作
			if (env.isPressKey('D')){
				if (ziki_muki == true){
					kasoku = 0;
				}
				ziki_x += speed*kasoku;
				run = true;
				ziki_muki = false;
			}
			else if (env.isPressKey('A')){
				if (ziki_muki == false){
					kasoku = 0;
				}
				ziki_x -= speed*kasoku;
				run = true;
				ziki_muki = true;
			}
			else{
				kasoku = 0;
				run = false;
				run_time = 0;
			}

			if (kasoku >= 190){
				kasoku = 190;
			}
			kasoku += 10;

			if (env.isPushKey(GLFW_KEY_SPACE) || env.isPushKey('W')){
				if (jump == true || jump_s1 == true){
					vy = jump_p;
					jump = false;
					jump_s1 = false;
				}
			}
			if (env.isPushKey('K')){
				ken_f = true;
				ken_f2 = true;
				ken_sound.pitch(1.5f);
				ken_sound.play();
			}


			//自機の重力処理
			vy += g;
			ziki_y += vy;

			//自機の地面判定
			if (ziki_y < -900){
				ziki_y = -900;
				jump = true;
				jump_s1 = true;
				vy = 0;
			}
			//壁の当り判定
			if (ziki_x < -1500){
				ziki_x = -1500;
			}
			if (ziki_x > 1370){
				ziki_x = 1370;
			}

			//自機のモーションデータ
			

			//デフォルト立ち
			//右向き
			if (run == false){
				bou1_time = (bou1_time + 1) % 30;

				if (jump == true || jump_s1 == true){
					if (ziki_muki == false){
						if (bou1_time == 0){ chara_def = gazou_haba2 * 3; }
						if (bou1_time == (10 * 1)){ chara_def = gazou_haba2 * 4; }
						if (bou1_time == (10 * 2)){ chara_def = gazou_haba2 * 5; }
						drawTextureBox(ziki_x, ziki_y - 6,
							c_size_x, c_size_y,
							chara_def + size_hosei, 0,
							z_size_x, z_size_y,
							bou, ziki_color,
							0, Vec2f(1.8, 1.5), Vec2f(0, 0));
					}

					//左向き
					else if (ziki_muki == true){
						if (bou1_time == 0){ chara_def = gazou_haba2 * 3; }
						if (bou1_time == (10 * 1)){ chara_def = gazou_haba2 * 4; }
						if (bou1_time == (10 * 2)){ chara_def = gazou_haba2 * 5; }
						drawTextureBox(ziki_x, ziki_y - 6,
							c_size_x, c_size_y,
							chara_def + size_hosei, 0,
							z_size_x, z_size_y,
							bou1, ziki_color,
							0, Vec2f(1.8, 1.5), Vec2f(0, 0));
					}
				}
			}

			//ジャンプモーション
			//右向きジャンプ
			if (jump == false && jump_s1 == false){
				if (ziki_muki == false){
					if ((vy == 80 && vy == 50) || (vy == -50 && vy == -80)){ jump_motion = gazou_haba1 * 6; }
					else if ((vy == 50 && vy >= 0) || (vy == -50 && vy == 0)){ jump_motion = gazou_haba1 * 7; }
					drawTextureBox(ziki_x - 90, ziki_y - 6,
						c_size_x, c_size_y,
						jump_motion + size_hosei, 0,
						z_size_x, z_size_y,
						bou, ziki_color,
						0, Vec2f(1.8, 1.5), Vec2f(0, 0));
				}

				//左向きジャンプ
				else if (ziki_muki == true){
					if ((vy == 80 && vy == 50) || (vy == -50 && vy == -80)){ jump_motion = gazou_haba1 * 6; }
					else if ((vy == 50 && vy >= 0) || (vy == -50 && vy == 0)){ jump_motion = gazou_haba1 * 7; }
					drawTextureBox(ziki_x - 100, ziki_y - 6,
						c_size_x, c_size_y,
						jump_motion + size_hosei, 0,
						z_size_x, z_size_y,
						bou1, ziki_color,
						0, Vec2f(1.8, 1.5), Vec2f(0, 0));
				}
			}


			//右に走る
			if (run == true){
				run_time = (run_time + 1) % 40;
				if (jump == true || jump_s1 == true){
					if (ziki_muki == false){
						if (run_time == 0){ run_motion = 0; }
						else if (run_time == (10 * 1)){ run_motion = gazou_haba2 * 1; }
						else if (run_time == (10 * 2)){ run_motion = gazou_haba2 * 2; }
						else if (run_time == (10 * 3)){ run_motion = gazou_haba2 * 1; }
						drawTextureBox(ziki_x, ziki_y - 6,
							c_size_x, c_size_y,
							run_motion + size_hosei, 0,
							z_size_x, z_size_y,
							bou, ziki_color,
							0, Vec2f(1.8, 1.5), Vec2f(0, 0));
					}
					//左に走る
					else if (ziki_muki == true){

						if (run_time == 0){ run_motion = 0; }
						else if (run_time == (10 * 1)){ run_motion = gazou_haba2 * 1; }
						else if (run_time == (10 * 2)){ run_motion = gazou_haba2 * 2; }
						else if (run_time == (10 * 3)){ run_motion = gazou_haba2 * 1; }
						drawTextureBox(ziki_x, ziki_y - 6,
							c_size_x, c_size_y,
							run_motion + size_hosei, 0,
							z_size_x, z_size_y,
							bou1, ziki_color,
							0, Vec2f(1.8, 1.5), Vec2f(0, 0));
					}
				}
			}
			else {
				run_time = 0;
			}

			//攻撃モーション
			ken_ax_m1 = ziki_x + ken_x_m;				//剣の左下当り判定ｘ（右）
			ken_ay_m1 = ziki_y + ken_y_m;				//剣の左下当り判定ｙ
			ken_ay_m2 = ken_ay_m1 + k_size_y;		//剣の左上当り判定ｙ
			ken_ax_m3 = ken_ax_m1 + k_size_x;		//剣の右下当り判定ｘ

			ken_ax_h1 = ziki_x + ken_x_h;				//剣の左下当り判定ｘ（左）
			ken_ay_h1 = ziki_y + ken_y_h;				//剣の左下当り判定ｙ
			ken_ay_h2 = ken_ay_h1 + k_size_y;		//剣の左上当り判定ｙ
			ken_ax_h3 = ken_ax_h1 + k_size_x;		//剣の右下当り判定ｘ

			//右に攻撃
			if (ziki_muki == false){
				if (ken_f == true){
					ken_time1_m = (ken_time1_m + 1) % ken_time3_m;
					if (ken_time1_m == 1){ ken_motion = 0; }
					else if (ken_time1_m == (ken_time2_m * 1)){ ken_motion = gazou_haba1 * 1; }
					else if (ken_time1_m == (ken_time2_m * 2)){ ken_motion = gazou_haba1 * 2; }
					else if (ken_time1_m == (ken_time2_m * 3)){ ken_motion = gazou_haba1 * 3; }
					drawTextureBox(ken_ax_m1 - 30, ken_ay_m1,
						k_size_x, k_size_y,
						ken_motion, 0,
						360, 330,
						ken, ziki_color,
						0,
						Vec2f(1, 1),
						Vec2f(0, 0));
				}
			}

			//左に攻撃
			if (ziki_muki == true){
				if (ken_f2 == true){
					ken_time1_h = (ken_time1_h + 1) % ken_time3_h;

					if (ken_time1_h == 1){ ken_motion = 0; }
					else if (ken_time1_h == (ken_time2_m * 1)){ ken_motion = gazou_haba1 * 1; }
					else if (ken_time1_h == (ken_time2_m * 2)){ ken_motion = gazou_haba1 * 2; }
					else if (ken_time1_h == (ken_time2_m * 3)){ ken_motion = gazou_haba1 * 3; }
					drawTextureBox(ken_ax_h1 + 380, ken_ay_h1,
						k_size_x, k_size_y,
						ken_motion, 0,
						360, 330,
						ken, ziki_color,
						0,
						Vec2f(-1, 1),
						Vec2f(0, 0));
				}
			}
			if (ziki_muki == true){ ken_time1_m = 0; }
			if (ziki_muki == false){ ken_time1_h = 0; }
			if (ken_time1_m == 0){ ken_f = false; ken_hitflag_m = false; }
			if (ken_time1_h == 0){ ken_f2 = false; ken_hitflag_h = false; }






			if (title_flag == true){
				//スタート当り判定
				if (ken_f == true){
					if (ken_hitflag_m == false){
						if (ken_ax_m1 <= start_ax && ken_ax_m3 >= start_x){
							if (ken_ay_m1 <= start_ay && ken_ay_m2 >= start_y){
								teki_sound.play();
								ken_hitflag_m = true;
								start_flag = true;
							}
						}
					}
				}
				if (ken_f2 == true){
					if (ken_hitflag_h == false){
						if (ken_ax_h1 <= start_ax && ken_ax_h3 >= start_x){
							if (ken_ay_h1 <= start_ay && ken_ay_h2 >= start_y){
								teki_sound.play();
								ken_hitflag_h = true;
								start_flag = true;
							}
						}
					}
				}
				//END当り判定
				if (ken_f == true){
					if (ken_hitflag_m == false){
						if (ken_ax_m1 <= end_ax && ken_ax_m3 >= end_x){
							if (ken_ay_m1 <= end_ay && ken_ay_m2 >= end_y){
								teki_sound.play();
								ken_hitflag_m = true;
								end_flag = true;
							}
						}
					}
				}

				if (ken_f2 == true){
					if (ken_hitflag_h == false){
						if (ken_ax_h1 <= end_ax && ken_ax_h3 >= end_x){
							if (ken_ay_h1 <= end_ay && ken_ay_h2 >= end_y){
								teki_sound.play();
								ken_hitflag_h = true;
								end_flag = true;
							}
						}
					}
				}

				//Option当り判定
				if (ken_f == true){
					if (ken_hitflag_m == false){
						if (ken_ax_m1 <= option_ax && ken_ax_m3 >= option_x){
							if (ken_ay_m1 <= option_ay && ken_ay_m2 >= option_y){
								teki_sound.play();
								ken_hitflag_m = true;
								option_flag = true;
								title_flag = false;
							}
						}
					}
				}

				if (ken_f2 == true){
					if (ken_hitflag_h == false){
						if (ken_ax_h1 <= option_ax && ken_ax_h3 >= option_x){
							if (ken_ay_h1 <= option_ay && ken_ay_h2 >= option_y){
								teki_sound.play();
								ken_hitflag_h = true;
								option_flag = true;
								title_flag = false;
							}
						}
					}
				}



				title_count_daimei = (title_count_daimei + 1) % 30;
				if (title_count_daimei < 10){
					drawTextureBox(title_x, title_y,
						title_ax, title_ay,
						0, 0,
						title_ax, title_ay,
						title1, Color::white);
				}
				else if (title_count_daimei <= 20){
					drawTextureBox(title_x, title_y,
						title_ax, title_ay,
						0, 0,
						title_ax, title_ay,
						title2, Color::white);
				}
				else if (title_count_daimei <= 30){
					drawTextureBox(title_x, title_y,
						title_ax, title_ay,
						0, 0,
						title_ax, title_ay,
						title3, Color::white);
				}

				if (start_flag == false){
					drawTextureBox(title_x, title_y,
						title_ax, title_ay,
						0, 0,
						title_ax, title_ay,
						start1, Color::white);
				}
				if (end_flag == false){
					drawTextureBox(title_x, title_y,
						title_ax, title_ay,
						0, 0,
						title_ax, title_ay,
						end1, Color::white);
				}

				if (start_flag == true){
					title_count_start++;
					if (title_count_start < 5){
						drawTextureBox(title_x, title_y,
							title_ax, title_ay,
							0, 0,
							title_ax, title_ay,
							start2, Color::white);
					}
					else if (title_count_start < 10){
						drawTextureBox(title_x, title_y,
							title_ax, title_ay,
							0, 0,
							title_ax, title_ay,
							start3, Color::white);
					}
					else if (title_count_start < 15){
						drawTextureBox(title_x, title_y,
							title_ax, title_ay,
							0, 0,
							title_ax, title_ay,
							start4, Color::white);
					}
					else if (title_count_start < 20){
						drawTextureBox(title_x, title_y,
							title_ax, title_ay,
							0, 0,
							title_ax, title_ay,
							start5, Color::white);
					}
					else if (title_count_start < 25){
						drawTextureBox(title_x, title_y,
							title_ax, title_ay,
							0, 0,
							title_ax, title_ay,
							start6, Color::white);
					}
				}
				if (title_count_start == 25){
					title_count_start = 0;
					gamen = 1;
				}


				if (end_flag == true){
					title_count_end++;
					if (title_count_end < 5){
						drawTextureBox(title_x, title_y,
							title_ax, title_ay,
							0, 0,
							title_ax, title_ay,
							end2, Color::white);
					}
					else if (title_count_end < 10){
						drawTextureBox(title_x, title_y,
							title_ax, title_ay,
							0, 0,
							title_ax, title_ay,
							end3, Color::white);
					}
					else if (title_count_end < 15){
						drawTextureBox(title_x, title_y,
							title_ax, title_ay,
							0, 0,
							title_ax, title_ay,
							end4, Color::white);
					}
					else if (title_count_end < 20){
						drawTextureBox(title_x, title_y,
							title_ax, title_ay,
							0, 0,
							title_ax, title_ay,
							end5, Color::white);
					}
					else if (title_count_end < 25){
						drawTextureBox(title_x, title_y,
							title_ax, title_ay,
							0, 0,
							title_ax, title_ay,
							end6, Color::white);
					}
				}
				if (title_count_end == 25){
					title_count_end = 0;
					return 0;
				}

				drawTextureBox(option_x, option_y,
					1024, 256,
					0, 0,
					1024, 256,
					option, Color::white);
			}

			if (option_flag == true && title_flag == false){
				drawTextureBox(option_x, option_y,
					size, size2,
					0, 0,
					size, size2,
					back, Color::white);
				drawTextureBox(bgm_x, bgm_y,
					size, size2,
					0, 0,
					size, size2,
					BGM, Color::white);
				drawTextureBox(start_x, start_y,
					size, size2,
					0, 0,
					size, size2,
					ziki_C, Color::white);
				drawTextureBox(plus_x, plus_y,
					plus_s, plus_s,
					0, 0,
					size2, size2,
					plus, Color::white);
				drawTextureBox(minus_x, minus_y,
					plus_s, plus_s,
					0, 0,
					size2, size2,
					minus, Color::white);


				//Back当り判定
				if (ken_f == true){
					if (ken_hitflag_m == false){
						if (ken_ax_m1 <= option_ax && ken_ax_m3 >= option_x){
							if (ken_ay_m1 <= option_ay && ken_ay_m2 >= option_y){
								teki_sound.play();
								ken_hitflag_m = true;
								option_flag = false;
								title_flag = true;
							}
						}
					}
				}

				if (ken_f2 == true){
					if (ken_hitflag_h == false){
						if (ken_ax_h1 <= option_ax && ken_ax_h3 >= option_x){
							if (ken_ay_h1 <= option_ay && ken_ay_h2 >= option_y){
								teki_sound.play();
								ken_hitflag_h = true;
								option_flag = false;
								title_flag = true;
							}
						}
					}
				}


				//Color当り判定
				if (ken_f == true){
					if (ken_hitflag_m == false){
						if (ken_ax_m1 <= color_ax && ken_ax_m3 >= color_x){
							if (ken_ay_m1 <= color_ay && ken_ay_m2 >= color_y){
								teki_sound.play();
								ken_hitflag_m = true;
								ziki_CR = rand(0.0f, 1.0f);
								ziki_CG = rand(0.0f, 1.0f);
								ziki_CB = rand(0.0f, 1.0f);
								ziki_color = Color(ziki_CR, ziki_CG, ziki_CB);
							}
						}
					}
				}

				if (ken_f2 == true){
					if (ken_hitflag_h == false){
						if (ken_ax_h1 <= color_ax && ken_ax_h3 >= color_x){
							if (ken_ay_h1 <= color_ay && ken_ay_h2 >= color_y){
								teki_sound.play();
								ken_hitflag_h = true;
								ziki_CR = rand(0.0f, 1.0f);
								ziki_CG = rand(0.0f, 1.0f);
								ziki_CB = rand(0.0f, 1.0f);
								ziki_color = Color(ziki_CR, ziki_CG, ziki_CB);
							}
						}
					}
				}


				//plus当り判定
				if (ken_f == true){
					if (ken_hitflag_m == false){
						if (ken_ax_m1 <= plus_ax && ken_ax_m3 >= plus_x){
							if (ken_ay_m1 <= plus_ay && ken_ay_m2 >= plus_y){
								teki_sound.play();
								ken_hitflag_m = true;
								sound += 0.2f;
							}
						}
					}
				}

				if (ken_f2 == true){
					if (ken_hitflag_h == false){
						if (ken_ax_h1 <= plus_ax && ken_ax_h3 >= plus_x){
							if (ken_ay_h1 <= plus_ay && ken_ay_h2 >= plus_y){
								teki_sound.play();
								ken_hitflag_h = true;
								sound += 0.2f;
							}
						}
					}
				}


				//minus当り判定
				if (ken_f == true){
					if (ken_hitflag_m == false){
						if (ken_ax_m1 <= minus_ax && ken_ax_m3 >= minus_x){
							if (ken_ay_m1 <= minus_ay && ken_ay_m2 >= minus_y){
								teki_sound.play();
								ken_hitflag_m = true;
								sound -= 0.2f;
							}
						}
					}
				}

				if (ken_f2 == true){
					if (ken_hitflag_h == false){
						if (ken_ax_h1 <= minus_ax && ken_ax_h3 >= minus_x){
							if (ken_ay_h1 <= minus_ay && ken_ay_h2 >= minus_y){
								teki_sound.play();
								ken_hitflag_h = true;
								sound -= 0.2f;
							}
						}
					}
				}

				if (sound > 1.2f){
					sound = 1.0f;
				}
				if (sound <= 0.0f){
					sound = 0.0f;
				}
			}



			//drawBox(option_x, option_y, size, size2, 5, Color::black);
			//drawBox(color_x, color_y, 470, 230, 5, Color::black);
			//drawBox(plus_x, plus_y, size2, size2, 5, Color::black);
			//drawBox(minus_x, minus_y, size2, size2, 5, Color::black);
			//drawBox(end_x, end_y, 600, 250, 5, Color::black);


			env.end();
		}
		env.flushInput();
		//本編開始
		while (gamen==1) {
			env.begin();
			if (!env.isOpen()){ return 0; }
			env.bgColor(Color::white); //背景を白にする

			//チュートリアル
			string sousa1 = "Press D みぎにいどう";
			string sousa2 = "Press A ひだりにいどう";
			string sousa3 = "Push W or SPACE じゃんぷ";
			string sousa4 = "Push K こうげき";
			font.size(50);
			if (tyuto_1 == false){
				font.draw(sousa1, Vec2f(-1000, 500), Color::black);
				if (env.isPushKey('D')){
					tyuto_1 = true;
					tyuto_2 = true;
					tyuto_sound.play();
				}
			}
			if (tyuto_2 == true){
				font.draw(sousa2, Vec2f(-1000, 500), Color::black);
				if (env.isPushKey('A')){
					tyuto_2 = false;
					tyuto_3 = true;
					tyuto_sound.play();
				}
			}
			if (tyuto_3 == true){
				font.draw(sousa3, Vec2f(-1000, 500), Color::black);
				if (env.isPushKey(GLFW_KEY_SPACE) || env.isPushKey('W')){
					tyuto_3 = false;
					tyuto_4 = true;
					tyuto_sound.play();
				}
			}
			if (tyuto_4 == true){
				font.draw(sousa4, Vec2f(-1000, 500), Color::black);
				if (env.isPushKey('K')){
					tyuto_4 = false;
					teki_pon = true;
					tyuto_sound.play();
				}
			}


			float g = -5;	//重

			//自機データ

			//自機の座標補正
			ziki_ax = ziki_x + c_size_x;
			ziki_ay = ziki_y + c_size_y;

			//自機の操作
			if (env.isPressKey('D')){
				if (ziki_muki == true){
					kasoku = 0;
				}
				ziki_x += speed*kasoku;
				run = true;
				ziki_muki = false;
			}
			else if (env.isPressKey('A')){
				if (ziki_muki == false){
					kasoku = 0;
				}
				ziki_x -= speed*kasoku;
				run = true;
				ziki_muki = true;
			}
			else{
				kasoku = 0;
				run = false;
				run_time = 0;
			}

			if (kasoku >= 190){
				kasoku = 190;
			}
			kasoku += 10;

			if (env.isPushKey(GLFW_KEY_SPACE) || env.isPushKey('W')){
				if (jump == true || jump_s1 == true){
					vy = jump_p;
					jump = false;
					jump_s1 = false;
				}
			}
			if (env.isPushKey('K')){
				ken_f = true;
				ken_f2 = true;
				ken_sound.pitch(1.5f);
				ken_sound.play();
			}


			//自機の重力処理
			vy += g;
			ziki_y += vy;


			//自機の地面判定
			if (ziki_y < -600){
				ziki_y = -600;
				jump = true;
				jump_s1 = true;
				vy = 0;
			}
			//壁の当り判定
			if (ziki_x < -1500){
				ziki_x = -1500;
			}
			if (ziki_x > 1370){
				ziki_x = 1370;
			}

			//自機の障害物当り判定
			//空中
			if (jump == false){
				if (kasoku <= 100){		//加速度が１００以下の場合
					if (ziki_x + c_size_x > 500 && ziki_x + c_size_x <= 510 && ziki_y >= -600 && ziki_y < -230){
						ziki_x = 500 - c_size_x;
					}
					else if (ziki_x < 800 && ziki_x >= 790 && ziki_y >= -600 && ziki_y < -230){
						ziki_x = 800;
					}
					else if (ziki_x + c_size_x > 500 && ziki_x < 800 && ziki_y > -600 && ziki_y <= -230){
						ziki_y = -300;
						vy = 0;
						jump_s1 = true;
					}
					else{
						jump_s1 = false;
					}
				}

				if (kasoku > 100){		//加速度が１０１以上の場合
					if (ziki_x + c_size_x > 500 && ziki_x + c_size_x <= 520 && ziki_y >= -600 && ziki_y < -230){
						ziki_x = 500 - c_size_x;
					}

					if (ziki_x < 800 && ziki_x >= 780 && ziki_y >= -600 && ziki_y < -230){
						ziki_x = 800;
					}
					else if (ziki_x + c_size_x > 500 && ziki_x < 800 && ziki_y > -600 && ziki_y <= -230){
						ziki_y = -300;
						vy = 0;
						jump_s1 = true;
					}
					else{
						jump_s1 = false;
					}
				}
			}

			//地上
			else if (kasoku <= 100){
				if (ziki_x + c_size_x > 500 && ziki_x + c_size_x <= 510 && ziki_y >= -600 && ziki_y < -300){
					ziki_x = 500 - c_size_x;
				}

				if (ziki_x < 800 && ziki_x >= 790 && ziki_y >= -600 && ziki_y < -300){
					ziki_x = 800;
				}
			}
			else if (kasoku > 100){
				if (ziki_x + c_size_x > 500 && ziki_x + c_size_x <= 520 && ziki_y >= -600 && ziki_y < -300){
					ziki_x = 500 - c_size_x;
				}

				if (ziki_x < 800 && ziki_x >= 780 && ziki_y >= -600 && ziki_y < -300){
					ziki_x = 800;
				}
			}




			//自機のモーションデータ
			


			//デフォルト立ち
			//右向き
			if (run == false){
				bou1_time = (bou1_time + 1) % 30;

				if (jump == true || jump_s1 == true){
					if (ziki_muki == false){
						if (bou1_time == 0){ chara_def = gazou_haba2 * 3; }
						if (bou1_time == (10 * 1)){ chara_def = gazou_haba2 * 4; }
						if (bou1_time == (10 * 2)){ chara_def = gazou_haba2 * 5; }
						drawTextureBox(ziki_x, ziki_y - 6,
							c_size_x, c_size_y,
							chara_def + size_hosei, 0,
							z_size_x, z_size_y,
							bou, ziki_color,
							0, Vec2f(1.8, 1.5), Vec2f(0, 0));
					}

					//左向き
					else if (ziki_muki == true){
						if (bou1_time == 0){ chara_def = gazou_haba2 * 3; }
						if (bou1_time == (10 * 1)){ chara_def = gazou_haba2 * 4; }
						if (bou1_time == (10 * 2)){ chara_def = gazou_haba2 * 5; }
						drawTextureBox(ziki_x, ziki_y - 6,
							c_size_x, c_size_y,
							chara_def + size_hosei, 0,
							z_size_x, z_size_y,
							bou1, ziki_color,
							0, Vec2f(1.8, 1.5), Vec2f(0, 0));
					}
				}
			}

			//ジャンプモーション
			//右向きジャンプ
			if (jump == false && jump_s1 == false){
				if (ziki_muki == false){
					if ((vy == 80 && vy == 50) || (vy == -50 && vy == -80)){ jump_motion = gazou_haba1 * 6; }
					else if ((vy == 50 && vy >= 0) || (vy == -50 && vy == 0)){ jump_motion = gazou_haba1 * 7; }
					drawTextureBox(ziki_x - 90, ziki_y - 6,
						c_size_x, c_size_y,
						jump_motion + size_hosei, 0,
						z_size_x, z_size_y,
						bou, ziki_color,
						0, Vec2f(1.8, 1.5), Vec2f(0, 0));
				}

				//左向きジャンプ
				else if (ziki_muki == true){
					if ((vy == 80 && vy == 50) || (vy == -50 && vy == -80)){ jump_motion = gazou_haba1 * 6; }
					else if ((vy == 50 && vy >= 0) || (vy == -50 && vy == 0)){ jump_motion = gazou_haba1 * 7; }
					drawTextureBox(ziki_x - 100, ziki_y - 6,
						c_size_x, c_size_y,
						jump_motion + size_hosei, 0,
						z_size_x, z_size_y,
						bou1, ziki_color,
						0, Vec2f(1.8, 1.5), Vec2f(0, 0));
				}
			}


			//右に走る
			if (run == true){
				run_time = (run_time + 1) % 40;
				if (jump == true || jump_s1 == true){
					if (ziki_muki == false){
						if (run_time == 0){ run_motion = 0; }
						else if (run_time == (10 * 1)){ run_motion = gazou_haba2 * 1; }
						else if (run_time == (10 * 2)){ run_motion = gazou_haba2 * 2; }
						else if (run_time == (10 * 3)){ run_motion = gazou_haba2 * 1; }
						drawTextureBox(ziki_x, ziki_y - 6,
							c_size_x, c_size_y,
							run_motion + size_hosei, 0,
							z_size_x, z_size_y,
							bou, ziki_color,
							0, Vec2f(1.8, 1.5), Vec2f(0, 0));
					}
					//左に走る
					else if (ziki_muki == true){

						if (run_time == 0){ run_motion = 0; }
						else if (run_time == (10 * 1)){ run_motion = gazou_haba2 * 1; }
						else if (run_time == (10 * 2)){ run_motion = gazou_haba2 * 2; }
						else if (run_time == (10 * 3)){ run_motion = gazou_haba2 * 1; }
						drawTextureBox(ziki_x, ziki_y - 6,
							c_size_x, c_size_y,
							run_motion + size_hosei, 0,
							z_size_x, z_size_y,
							bou1, ziki_color,
							0, Vec2f(1.8, 1.5), Vec2f(0, 0));
					}
				}
			}
			else {
				run_time = 0;
			}


			//攻撃モーション
			ken_ax_m1 = ziki_x + ken_x_m;				//剣の左下当り判定ｘ（右）
			ken_ay_m1 = ziki_y + ken_y_m;				//剣の左下当り判定ｙ
			ken_ay_m2 = ken_ay_m1 + k_size_y;		//剣の左上当り判定ｙ
			ken_ax_m3 = ken_ax_m1 + k_size_x;		//剣の右下当り判定ｘ


			ken_ax_h1 = ziki_x + ken_x_h;				//剣の左下当り判定ｘ（左）
			ken_ay_h1 = ziki_y + ken_y_h;				//剣の左下当り判定ｙ
			ken_ay_h2 = ken_ay_h1 + k_size_y;		//剣の左上当り判定ｙ
			ken_ax_h3 = ken_ax_h1 + k_size_x;		//剣の右下当り判定ｘ




			//右に攻撃
			if (ziki_muki == false){
				if (ken_f == true){
					ken_time1_m = (ken_time1_m + 1) % ken_time3_m;

					if (ken_time1_m == 1){ ken_motion = 0; }
					else if (ken_time1_m == (ken_time2_m * 1)){ ken_motion = gazou_haba1 * 1; }
					else if (ken_time1_m == (ken_time2_m * 2)){ ken_motion = gazou_haba1 * 2; }
					else if (ken_time1_m == (ken_time2_m * 3)){ ken_motion = gazou_haba1 * 3; }
					drawTextureBox(ken_ax_m1 - 30, ken_ay_m1,
						k_size_x, k_size_y,
						ken_motion, 0,
						360, 330,
						ken, ziki_color,
						0,
						Vec2f(1, 1),
						Vec2f(0, 0));
				}
			}

			//左に攻撃
			if (ziki_muki == true){
				if (ken_f2 == true){
					ken_time1_h = (ken_time1_h + 1) % ken_time3_h;

					if (ken_time1_h == 1){ ken_motion = 0; }
					else if (ken_time1_h == (ken_time2_m * 1)){ ken_motion = gazou_haba1 * 1; }
					else if (ken_time1_h == (ken_time2_m * 2)){ ken_motion = gazou_haba1 * 2; }
					else if (ken_time1_h == (ken_time2_m * 3)){ ken_motion = gazou_haba1 * 3; }
					drawTextureBox(ken_ax_h1 + 380, ken_ay_h1,
						k_size_x, k_size_y,
						ken_motion, 0,
						360, 330,
						ken, ziki_color,
						0,
						Vec2f(-1, 1),
						Vec2f(0, 0));
				}
			}

			if (ziki_muki == true){ ken_time1_m = 0; }
			if (ziki_muki == false){ ken_time1_h = 0; }
			if (ken_time1_m == 0){ ken_f = false; ken_hitflag_m = false; }
			if (ken_time1_h == 0){ ken_f2 = false; ken_hitflag_h = false; }

			//敵の出現重力

			for (int i = 0; i < Ene; i++){
				enemy[i].g = -5;
			}

			for (int i = 0; i < Ene; i++){
				if (enemy[i].vy < -50){
					enemy[i].vy = -50;
				}
				if (enemy[i].y < 1100 && enemy[i].y > 600){
					enemy[i].g = -0.4;
				}
			}
			for (int i = 22; i < C; i++){
				enemy[i].g = -1;

			}




			//****************************************************************************************************************************************************************
			//敵一体目のデータ
			if (teki_pon == true){
				//フィールドタイム
				ground_time += 1;

				if (ground_time > 0){
					*a = 0;

					if (enemy[E1[e_name]].flag == false){
						if (enemy[E1[e_name]].sound_flag == false){
							pon_sound.pitch(2.0f);
							pon_sound.play();
							enemy[E1[e_name]].sound_flag = true;
						}
						enemy[E1[e_name]].vy += enemy[E1[e_name]].g;
						enemy[E1[e_name]].y += enemy[E1[e_name]].vy;

						//敵一体目の体力
						drawFillBox(enemy[E1[e_name]].x + hpba_x, enemy[E1[e_name]].y + hpba_y, enemy[E1[e_name]].hpba, hpba_haba, Color::red);
						Color color = Color::red;

						//敵の移動処理
						enemy[E1[e_name]].def_time = (enemy[E1[e_name]].def_time + 1) % 30;

						if (enemy[E1[e_name]].def_time >= 10 && enemy[E1[e_name]].def_time <= 20){
							enemy[E1[e_name]].x -= 1;
							enemy[E1[e_name]].muki_flag = true;
						}
						else{ enemy[E1[e_name]].muki_flag = false; }
						if (enemy[E1[e_name]].x <= -1700){
							enemy[E1[e_name]].x = 1500;
						}

						//敵の地面判定
						if (enemy[E1[e_name]].y <= -600){
							enemy[E1[e_name]].y = -600;
							enemy[E1[e_name]].vy = 0;
							enemy[E1[e_name]].jump_s1_flag = false;
							enemy[E1[e_name]].jump_flag = false;
						}
						else {
							enemy[E1[e_name]].jump_s1_flag = true;
							enemy[E1[e_name]].jump_flag = true;
						}
						//右向き
						if (enemy[E1[e_name]].muki_flag == false){
							if (enemy[E1[e_name]].def_time == 0){ enemy[E1[e_name]].def_haba = gazou_haba2 * 3; }
							if (enemy[E1[e_name]].def_time == (10 * 1)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 4; }
							if (enemy[E1[e_name]].def_time == (10 * 2)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 5; }
							drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y - 6,
								c_size_x, c_size_y,
								enemy[E1[e_name]].def_haba + size_hosei, 0,
								z_size_x, z_size_y,
								bou, color,
								0, Vec2f(1.8, 1.5), Vec2f(0, 0));
						}


						//左向き
						if (enemy[E1[e_name]].muki_flag == true){
							if (enemy[E1[e_name]].def_time == 0){ enemy[E1[e_name]].def_haba = gazou_haba2 * 3; }
							if (enemy[E1[e_name]].def_time == (10 * 1)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 4; }
							if (enemy[E1[e_name]].def_time == (10 * 2)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 5; }
							drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y - 6,
								c_size_x, c_size_y,
								enemy[E1[e_name]].def_haba + size_hosei, 0,
								z_size_x, z_size_y,
								bou1, color,
								0, Vec2f(1.8, 1.5), Vec2f(0, 0));
						}

						//当り判定
						for (int i = 0; i < Ene; i++){
							enemy[i].ax = enemy[i].x + c_size_x;		//敵の右下当り判定ｘ
							enemy[i].ay = enemy[i].y + c_size_y;		//敵の左上当り判定ｙ
						}
						teki_sound.pitch(1.5f);

						if (ken_f == true){
							if (ken_hitflag_m == false){
								if (ken_ax_m1 <= enemy[E1[e_name]].ax && ken_ax_m3 >= enemy[E1[e_name]].x){
									if (ken_ay_m1 <= enemy[E1[e_name]].ay && ken_ay_m2 >= enemy[E1[e_name]].y){
										teki_sound.play();
										ken_hitflag_m = true;
										enemy[E1[e_name]].nowhp -= ken_power; //1
										enemy[E1[e_name]].hpba = (enemy[E1[e_name]].nowhp / enemy[E1[e_name]].hpmax) * enemy[E1[e_name]].hpba;
									}
								}
							}
						}

						if (ken_f2 == true){
							if (ken_hitflag_h == false){
								if (ken_ax_h1 <= enemy[E1[e_name]].ax && ken_ax_h3 >= enemy[E1[e_name]].x){
									if (ken_ay_h1 <= enemy[E1[e_name]].ay && ken_ay_h2 >= enemy[E1[e_name]].y){
										teki_sound.play();
										ken_hitflag_h = true;
										enemy[E1[e_name]].nowhp -= ken_power; //1
										enemy[E1[e_name]].hpba = (enemy[E1[e_name]].nowhp / enemy[E1[e_name]].hpmax) * enemy[E1[e_name]].hpba;
									}
								}
							}
						}
						if (ziki_hitflag == false){
							if (enemy[E1[e_name]].x <= ziki_ax && enemy[E1[e_name]].ax >= ziki_x && enemy[E1[e_name]].y <= ziki_ay && enemy[E1[e_name]].ay >= ziki_y){
								ziki_nowhp -= enemy[E1[e_name]].K;
								ziki_hpba = (ziki_nowhp / ziki_hpmax) * ziki_hpba;
								ziki_hitflag = true;
								teki_sound.play();
							}
						}
						if (enemy[E1[e_name]].def_time <= 2){
							ziki_hitflag = false;
						}
						if (enemy[E1[e_name]].nowhp <= 0){
							if (enemy[E1[e_name]].flag == false){
								ziki_nowhp += 100;
								ziki_hpba = (ziki_nowhp / ziki_hpmax) * ziki_hpba;
								kill_count += 1;
								enemy[E1[e_name]].flag = true;
								enemy[E1[e_name]].dead_flag = true;
							}
						}
					}

					if (enemy[E1[e_name]].dead_flag == true){
						enemy[e_name].dead_time++;
						if (enemy[e_name].dead_time == 0){ dead_motion = 0; }
						else if (enemy[e_name].dead_time == (dead_count * 1)){ dead_motion = gazou_haba2 * 1; }
						else if (enemy[e_name].dead_time == (dead_count * 2)){ dead_motion = gazou_haba2 * 2; }
						else if (enemy[e_name].dead_time == (dead_count * 3)){ dead_motion = gazou_haba2 * 3; }
						else if (enemy[e_name].dead_time == (dead_count * 4)){ dead_motion = gazou_haba2 * 4; }
						else if (enemy[e_name].dead_time == (dead_count * 5)){ dead_motion = gazou_haba2 * 5; }
						else if (enemy[e_name].dead_time == (dead_count * 6)){ dead_motion = gazou_haba2 * 6; }
						else if (enemy[e_name].dead_time == (dead_count * 7)){ dead_motion = gazou_haba2 * 7; }
						drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y,
							gazou_haba2, gazou_haba2,
							dead_motion, 0,
							gazou_haba2, gazou_haba2,
							dead, Color::white);
					}
					if (enemy[e_name].dead_time >= 45){
						enemy[e_name].dead_time = 0;
						enemy[E1[e_name]].dead_flag = false;
					}
				}

				//敵2体目

				if (ground_time > 150){
					*a = 1;
					if (enemy[E1[e_name]].flag == false){
						if (enemy[E1[e_name]].sound_flag == false){
							pon_sound.pitch(2.0f);
							pon_sound.play();
							enemy[E1[e_name]].sound_flag = true;
						}
						enemy[E1[e_name]].vy += enemy[E1[e_name]].g;
						enemy[E1[e_name]].y += enemy[E1[e_name]].vy;

						//敵一体目の体力
						drawFillBox(enemy[E1[e_name]].x + hpba_x, enemy[E1[e_name]].y + hpba_y, enemy[E1[e_name]].hpba, hpba_haba, Color::red);
						Color color = Color::red;

						//敵の移動処理
						enemy[E1[e_name]].def_time = (enemy[E1[e_name]].def_time + 1) % 30;
						if (enemy[E1[e_name]].def_time >= 10 && enemy[E1[e_name]].def_time <= 20){
							enemy[E1[e_name]].x -= 1;
							enemy[E1[e_name]].muki_flag = true;
						}
						else{ enemy[E1[e_name]].muki_flag = false; }
						if (enemy[E1[e_name]].x <= -1700){
							enemy[E1[e_name]].x = 1500;
						}

						//敵の地面判定
						if (enemy[E1[e_name]].y <= -600){
							enemy[E1[e_name]].y = -600;
							enemy[E1[e_name]].vy = 0;
							enemy[E1[e_name]].jump_s1_flag = false;
							enemy[E1[e_name]].jump_flag = false;
						}
						else {
							enemy[E1[e_name]].jump_s1_flag = true;
							enemy[E1[e_name]].jump_flag = true;
						}
						//右向き
						if (enemy[E1[e_name]].muki_flag == false){
							if (enemy[E1[e_name]].def_time == 0){ enemy[E1[e_name]].def_haba = gazou_haba2 * 3; }
							if (enemy[E1[e_name]].def_time == (10 * 1)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 4; }
							if (enemy[E1[e_name]].def_time == (10 * 2)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 5; }
							drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y - 6,
								c_size_x, c_size_y,
								enemy[E1[e_name]].def_haba + size_hosei, 0,
								z_size_x, z_size_y,
								bou, color,
								0, Vec2f(1.8, 1.5), Vec2f(0, 0));
						}


						//左向き
						if (enemy[E1[e_name]].muki_flag == true){
							if (enemy[E1[e_name]].def_time == 0){ enemy[E1[e_name]].def_haba = gazou_haba2 * 3; }
							if (enemy[E1[e_name]].def_time == (10 * 1)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 4; }
							if (enemy[E1[e_name]].def_time == (10 * 2)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 5; }
							drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y - 6,
								c_size_x, c_size_y,
								enemy[E1[e_name]].def_haba + size_hosei, 0,
								z_size_x, z_size_y,
								bou1, color,
								0, Vec2f(1.8, 1.5), Vec2f(0, 0));
						}

						//当り判定
						for (int i = 0; i < Ene; i++){
							enemy[i].ax = enemy[i].x + c_size_x;		//敵の右下当り判定ｘ
							enemy[i].ay = enemy[i].y + c_size_y;		//敵の左上当り判定ｙ
						}
						teki_sound.pitch(1.5f);

						if (ken_f == true){
							if (ken_hitflag_m == false){
								if (ken_ax_m1 <= enemy[E1[e_name]].ax && ken_ax_m3 >= enemy[E1[e_name]].x){
									if (ken_ay_m1 <= enemy[E1[e_name]].ay && ken_ay_m2 >= enemy[E1[e_name]].y){
										teki_sound.play();
										ken_hitflag_m = true;
										enemy[E1[e_name]].nowhp -= ken_power; //1
										enemy[E1[e_name]].hpba = (enemy[E1[e_name]].nowhp / enemy[E1[e_name]].hpmax) * enemy[E1[e_name]].hpba;
									}
								}
							}
						}

						if (ken_f2 == true){
							if (ken_hitflag_h == false){
								if (ken_ax_h1 <= enemy[E1[e_name]].ax && ken_ax_h3 >= enemy[E1[e_name]].x){
									if (ken_ay_h1 <= enemy[E1[e_name]].ay && ken_ay_h2 >= enemy[E1[e_name]].y){
										teki_sound.play();
										ken_hitflag_h = true;
										enemy[E1[e_name]].nowhp -= ken_power; //1
										enemy[E1[e_name]].hpba = (enemy[E1[e_name]].nowhp / enemy[E1[e_name]].hpmax) * enemy[E1[e_name]].hpba;
									}
								}
							}
						}
						if (ziki_hitflag == false){
							if (enemy[E1[e_name]].x <= ziki_ax && enemy[E1[e_name]].ax >= ziki_x && enemy[E1[e_name]].y <= ziki_ay && enemy[E1[e_name]].ay >= ziki_y){
								ziki_nowhp -= enemy[E1[e_name]].K;
								ziki_hpba = (ziki_nowhp / ziki_hpmax) * ziki_hpba;
								ziki_hitflag = true;
								teki_sound.play();
							}
						}
						if (enemy[E1[e_name]].def_time <= 2){
							ziki_hitflag = false;
						}
						if (enemy[E1[e_name]].nowhp <= 0){
							if (enemy[E1[e_name]].flag == false){
								ziki_nowhp += 100;
								ziki_hpba = (ziki_nowhp / ziki_hpmax) * ziki_hpba;
								kill_count += 1;
								enemy[E1[e_name]].flag = true;
								enemy[E1[e_name]].dead_flag = true;
							}
						}
					}

					if (enemy[E1[e_name]].dead_flag == true){
						enemy[e_name].dead_time++;
						if (enemy[e_name].dead_time == 0){ dead_motion = 0; }
						else if (enemy[e_name].dead_time == (dead_count * 1)){ dead_motion = gazou_haba2 * 1; }
						else if (enemy[e_name].dead_time == (dead_count * 2)){ dead_motion = gazou_haba2 * 2; }
						else if (enemy[e_name].dead_time == (dead_count * 3)){ dead_motion = gazou_haba2 * 3; }
						else if (enemy[e_name].dead_time == (dead_count * 4)){ dead_motion = gazou_haba2 * 4; }
						else if (enemy[e_name].dead_time == (dead_count * 5)){ dead_motion = gazou_haba2 * 5; }
						else if (enemy[e_name].dead_time == (dead_count * 6)){ dead_motion = gazou_haba2 * 6; }
						else if (enemy[e_name].dead_time == (dead_count * 7)){ dead_motion = gazou_haba2 * 7; }
						drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y,
							gazou_haba2, gazou_haba2,
							dead_motion, 0,
							gazou_haba2, gazou_haba2,
							dead, Color::white);
					}
					if (enemy[e_name].dead_time >= 45){
						enemy[e_name].dead_time = 0;
						enemy[E1[e_name]].dead_flag = false;
					}
				}


				//敵3体目

				if (ground_time > 400){
					*a = 2;
					if (enemy[E1[e_name]].flag == false){
						if (enemy[E1[e_name]].sound_flag == false){
							pon_sound.pitch(2.0f);
							pon_sound.play();
							enemy[E1[e_name]].sound_flag = true;
						}
						enemy[E1[e_name]].vy += enemy[E1[e_name]].g;
						enemy[E1[e_name]].y += enemy[E1[e_name]].vy;

						//敵一体目の体力
						drawFillBox(enemy[E1[e_name]].x + hpba_x, enemy[E1[e_name]].y + hpba_y, enemy[E1[e_name]].hpba, hpba_haba, Color::red);
						Color color = Color::red;

						//敵の移動処理

						enemy[E1[e_name]].def_time = (enemy[E1[e_name]].def_time + 1) % 30;

						if (enemy[E1[e_name]].def_time >= 10 && enemy[E1[e_name]].def_time <= 20){
							enemy[E1[e_name]].x -= 3;
							enemy[E1[e_name]].muki_flag = true;
						}
						else{ enemy[E1[e_name]].muki_flag = false; }
						if (enemy[E1[e_name]].x <= -1700){
							enemy[E1[e_name]].x = 1500;
						}

						//敵の地面判定
						if (enemy[E1[e_name]].y <= -600){
							enemy[E1[e_name]].y = -600;
							enemy[E1[e_name]].vy = 0;
							enemy[E1[e_name]].jump_s1_flag = false;
							enemy[E1[e_name]].jump_flag = false;
						}
						else {
							enemy[E1[e_name]].jump_s1_flag = true;
							enemy[E1[e_name]].jump_flag = true;
						}
						//右向き
						if (enemy[E1[e_name]].muki_flag == false){
							if (enemy[E1[e_name]].def_time == 0){ enemy[E1[e_name]].def_haba = gazou_haba2 * 3; }
							if (enemy[E1[e_name]].def_time == (10 * 1)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 4; }
							if (enemy[E1[e_name]].def_time == (10 * 2)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 5; }
							drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y - 6,
								c_size_x, c_size_y,
								enemy[E1[e_name]].def_haba + size_hosei, 0,
								z_size_x, z_size_y,
								bou, color,
								0, Vec2f(1.8, 1.5), Vec2f(0, 0));
						}


						//左向き
						if (enemy[E1[e_name]].muki_flag == true){
							if (enemy[E1[e_name]].def_time == 0){ enemy[E1[e_name]].def_haba = gazou_haba2 * 3; }
							if (enemy[E1[e_name]].def_time == (10 * 1)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 4; }
							if (enemy[E1[e_name]].def_time == (10 * 2)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 5; }
							drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y - 6,
								c_size_x, c_size_y,
								enemy[E1[e_name]].def_haba + size_hosei, 0,
								z_size_x, z_size_y,
								bou1, color,
								0, Vec2f(1.8, 1.5), Vec2f(0, 0));
						}

						//当り判定
						for (int i = 0; i < Ene; i++){
							enemy[i].ax = enemy[i].x + c_size_x;		//敵の右下当り判定ｘ
							enemy[i].ay = enemy[i].y + c_size_y;		//敵の左上当り判定ｙ
						}
						teki_sound.pitch(1.5f);

						if (ken_f == true){
							if (ken_hitflag_m == false){
								if (ken_ax_m1 <= enemy[E1[e_name]].ax && ken_ax_m3 >= enemy[E1[e_name]].x){
									if (ken_ay_m1 <= enemy[E1[e_name]].ay && ken_ay_m2 >= enemy[E1[e_name]].y){
										teki_sound.play();
										ken_hitflag_m = true;
										enemy[E1[e_name]].nowhp -= ken_power; //1
										enemy[E1[e_name]].hpba = (enemy[E1[e_name]].nowhp / enemy[E1[e_name]].hpmax) * enemy[E1[e_name]].hpba;
									}
								}
							}
						}

						if (ken_f2 == true){
							if (ken_hitflag_h == false){
								if (ken_ax_h1 <= enemy[E1[e_name]].ax && ken_ax_h3 >= enemy[E1[e_name]].x){
									if (ken_ay_h1 <= enemy[E1[e_name]].ay && ken_ay_h2 >= enemy[E1[e_name]].y){
										teki_sound.play();
										ken_hitflag_h = true;
										enemy[E1[e_name]].nowhp -= ken_power; //1
										enemy[E1[e_name]].hpba = (enemy[E1[e_name]].nowhp / enemy[E1[e_name]].hpmax) * enemy[E1[e_name]].hpba;
									}
								}
							}
						}
						if (ziki_hitflag == false){
							if (enemy[E1[e_name]].x <= ziki_ax && enemy[E1[e_name]].ax >= ziki_x && enemy[E1[e_name]].y <= ziki_ay && enemy[E1[e_name]].ay >= ziki_y){
								ziki_nowhp -= enemy[E1[e_name]].K;
								ziki_hpba = (ziki_nowhp / ziki_hpmax) * ziki_hpba;
								ziki_hitflag = true;
								teki_sound.play();
							}
						}
						if (enemy[E1[e_name]].def_time <= 2){
							ziki_hitflag = false;
						}
						if (enemy[E1[e_name]].nowhp <= 0){
							if (enemy[E1[e_name]].flag == false){
								ziki_nowhp += 100;
								ziki_hpba = (ziki_nowhp / ziki_hpmax) * ziki_hpba;
								kill_count += 1;
								enemy[E1[e_name]].flag = true;
								enemy[E1[e_name]].dead_flag = true;
							}
						}
					}

					if (enemy[E1[e_name]].dead_flag == true){
						enemy[e_name].dead_time++;
						if (enemy[e_name].dead_time == 0){ dead_motion = 0; }
						else if (enemy[e_name].dead_time == (dead_count * 1)){ dead_motion = gazou_haba2 * 1; }
						else if (enemy[e_name].dead_time == (dead_count * 2)){ dead_motion = gazou_haba2 * 2; }
						else if (enemy[e_name].dead_time == (dead_count * 3)){ dead_motion = gazou_haba2 * 3; }
						else if (enemy[e_name].dead_time == (dead_count * 4)){ dead_motion = gazou_haba2 * 4; }
						else if (enemy[e_name].dead_time == (dead_count * 5)){ dead_motion = gazou_haba2 * 5; }
						else if (enemy[e_name].dead_time == (dead_count * 6)){ dead_motion = gazou_haba2 * 6; }
						else if (enemy[e_name].dead_time == (dead_count * 7)){ dead_motion = gazou_haba2 * 7; }
						drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y,
							gazou_haba2, gazou_haba2,
							dead_motion, 0,
							gazou_haba2, gazou_haba2,
							dead, Color::white);
					}
					if (enemy[e_name].dead_time >= 45){
						enemy[e_name].dead_time = 0;
						enemy[E1[e_name]].dead_flag = false;
					}
				}


				//敵4体目

				if (ground_time > 400){
					*a = 3;
					if (enemy[E1[e_name]].flag == false){
						if (enemy[E1[e_name]].sound_flag == false){
							pon_sound.pitch(2.0f);
							pon_sound.play();
							enemy[E1[e_name]].sound_flag = true;
						}
						enemy[E1[e_name]].vy += enemy[E1[e_name]].g;
						enemy[E1[e_name]].y += enemy[E1[e_name]].vy;

						//敵一体目の体力
						drawFillBox(enemy[E1[e_name]].x + hpba_x, enemy[E1[e_name]].y + hpba_y, enemy[E1[e_name]].hpba, hpba_haba, Color::red);
						Color color = Color::red;

						//敵の移動処理

						enemy[E1[e_name]].def_time = (enemy[E1[e_name]].def_time + 1) % 30;

						if (enemy[E1[e_name]].def_time >= 10 && enemy[E1[e_name]].def_time <= 20){
							enemy[E1[e_name]].x -= 3;
							enemy[E1[e_name]].muki_flag = true;
						}
						else{ enemy[E1[e_name]].muki_flag = false; }
						if (enemy[E1[e_name]].x <= -1700){
							enemy[E1[e_name]].x = 1500;
						}

						//敵の地面判定
						if (enemy[E1[e_name]].y <= -600){
							enemy[E1[e_name]].y = -600;
							enemy[E1[e_name]].vy = 0;
							enemy[E1[e_name]].jump_s1_flag = false;
							enemy[E1[e_name]].jump_flag = false;
						}
						else {
							enemy[E1[e_name]].jump_s1_flag = true;
							enemy[E1[e_name]].jump_flag = true;
						}
						//右向き
						if (enemy[E1[e_name]].muki_flag == false){
							if (enemy[E1[e_name]].def_time == 0){ enemy[E1[e_name]].def_haba = gazou_haba2 * 3; }
							if (enemy[E1[e_name]].def_time == (10 * 1)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 4; }
							if (enemy[E1[e_name]].def_time == (10 * 2)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 5; }
							drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y - 6,
								c_size_x, c_size_y,
								enemy[E1[e_name]].def_haba + size_hosei, 0,
								z_size_x, z_size_y,
								bou, color,
								0, Vec2f(1.8, 1.5), Vec2f(0, 0));
						}


						//左向き
						if (enemy[E1[e_name]].muki_flag == true){
							if (enemy[E1[e_name]].def_time == 0){ enemy[E1[e_name]].def_haba = gazou_haba2 * 3; }
							if (enemy[E1[e_name]].def_time == (10 * 1)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 4; }
							if (enemy[E1[e_name]].def_time == (10 * 2)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 5; }
							drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y - 6,
								c_size_x, c_size_y,
								enemy[E1[e_name]].def_haba + size_hosei, 0,
								z_size_x, z_size_y,
								bou1, color,
								0, Vec2f(1.8, 1.5), Vec2f(0, 0));
						}

						//当り判定
						for (int i = 0; i < Ene; i++){
							enemy[i].ax = enemy[i].x + c_size_x;		//敵の右下当り判定ｘ
							enemy[i].ay = enemy[i].y + c_size_y;		//敵の左上当り判定ｙ
						}
						teki_sound.pitch(1.5f);

						if (ken_f == true){
							if (ken_hitflag_m == false){
								if (ken_ax_m1 <= enemy[E1[e_name]].ax && ken_ax_m3 >= enemy[E1[e_name]].x){
									if (ken_ay_m1 <= enemy[E1[e_name]].ay && ken_ay_m2 >= enemy[E1[e_name]].y){
										teki_sound.play();
										ken_hitflag_m = true;
										enemy[E1[e_name]].nowhp -= ken_power; //1
										enemy[E1[e_name]].hpba = (enemy[E1[e_name]].nowhp / enemy[E1[e_name]].hpmax) * enemy[E1[e_name]].hpba;
									}
								}
							}
						}

						if (ken_f2 == true){
							if (ken_hitflag_h == false){
								if (ken_ax_h1 <= enemy[E1[e_name]].ax && ken_ax_h3 >= enemy[E1[e_name]].x){
									if (ken_ay_h1 <= enemy[E1[e_name]].ay && ken_ay_h2 >= enemy[E1[e_name]].y){
										teki_sound.play();
										ken_hitflag_h = true;
										enemy[E1[e_name]].nowhp -= ken_power; //1
										enemy[E1[e_name]].hpba = (enemy[E1[e_name]].nowhp / enemy[E1[e_name]].hpmax) * enemy[E1[e_name]].hpba;
									}
								}
							}
						}
						if (ziki_hitflag == false){
							if (enemy[E1[e_name]].x <= ziki_ax && enemy[E1[e_name]].ax >= ziki_x && enemy[E1[e_name]].y <= ziki_ay && enemy[E1[e_name]].ay >= ziki_y){
								ziki_nowhp -= enemy[E1[e_name]].K;
								ziki_hpba = (ziki_nowhp / ziki_hpmax) * ziki_hpba;
								ziki_hitflag = true;
								teki_sound.play();
							}
						}
						if (enemy[E1[e_name]].def_time <= 2){
							ziki_hitflag = false;
						}
						if (enemy[E1[e_name]].nowhp <= 0){
							if (enemy[E1[e_name]].flag == false){
								ziki_nowhp += 100;
								ziki_hpba = (ziki_nowhp / ziki_hpmax) * ziki_hpba;
								kill_count += 1;
								enemy[E1[e_name]].flag = true;
								enemy[E1[e_name]].dead_flag = true;
							}
						}
					}

					if (enemy[E1[e_name]].dead_flag == true){
						enemy[e_name].dead_time++;
						if (enemy[e_name].dead_time == 0){ dead_motion = 0; }
						else if (enemy[e_name].dead_time == (dead_count * 1)){ dead_motion = gazou_haba2 * 1; }
						else if (enemy[e_name].dead_time == (dead_count * 2)){ dead_motion = gazou_haba2 * 2; }
						else if (enemy[e_name].dead_time == (dead_count * 3)){ dead_motion = gazou_haba2 * 3; }
						else if (enemy[e_name].dead_time == (dead_count * 4)){ dead_motion = gazou_haba2 * 4; }
						else if (enemy[e_name].dead_time == (dead_count * 5)){ dead_motion = gazou_haba2 * 5; }
						else if (enemy[e_name].dead_time == (dead_count * 6)){ dead_motion = gazou_haba2 * 6; }
						else if (enemy[e_name].dead_time == (dead_count * 7)){ dead_motion = gazou_haba2 * 7; }
						drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y,
							gazou_haba2, gazou_haba2,
							dead_motion, 0,
							gazou_haba2, gazou_haba2,
							dead, Color::white);
					}
					if (enemy[e_name].dead_time >= 45){
						enemy[e_name].dead_time = 0;
						enemy[E1[e_name]].dead_flag = false;
					}
				}

				if (kill_count >= 4){
					for (int i = 5; i < A; i++){
						//敵5~10体目

						if (ground_time > 220 + i * 50){
							*a = i;
							if (enemy[E1[e_name]].flag == false){
								if (enemy[E1[e_name]].sound_flag == false){
									pon_sound.pitch(2.0f);
									pon_sound.play();
									enemy[E1[e_name]].sound_flag = true;
								}
								enemy[E1[e_name]].vy += enemy[E1[e_name]].g;
								enemy[E1[e_name]].y += enemy[E1[e_name]].vy;

								//敵一体目の体力
								drawFillBox(enemy[E1[e_name]].x + hpba_x, enemy[E1[e_name]].y + hpba_y, enemy[E1[e_name]].hpba, hpba_haba, Color::red);
								Color color = Color::red;

								//敵の移動処理

								enemy[E1[e_name]].def_time = (enemy[E1[e_name]].def_time + 1) % 30;

								if (enemy[E1[e_name]].def_time >= 10 && enemy[E1[e_name]].def_time <= 20){
									enemy[E1[e_name]].x -= rand(0, 10);
									enemy[E1[e_name]].muki_flag = true;
								}
								else{ enemy[E1[e_name]].muki_flag = false; }

								if (enemy[E1[e_name]].x <= -1700){
									enemy[E1[e_name]].x = 1500;
								}

								//敵の地面判定
								if (enemy[E1[e_name]].y <= -600){
									enemy[E1[e_name]].y = -600;
									enemy[E1[e_name]].vy = 0;
									enemy[E1[e_name]].jump_s1_flag = false;
									enemy[E1[e_name]].jump_flag = false;
								}
								else {
									enemy[E1[e_name]].jump_flag = true;
								}
								//右向き
								if (enemy[E1[e_name]].muki_flag == false){
									if (enemy[E1[e_name]].def_time == 0){ enemy[E1[e_name]].def_haba = gazou_haba2 * 3; }
									if (enemy[E1[e_name]].def_time == (10 * 1)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 4; }
									if (enemy[E1[e_name]].def_time == (10 * 2)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 5; }
									drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y - 6,
										c_size_x, c_size_y,
										enemy[E1[e_name]].def_haba + size_hosei, 0,
										z_size_x, z_size_y,
										bou, color,
										0, Vec2f(1.8, 1.5), Vec2f(0, 0));
								}


								//左向き
								if (enemy[E1[e_name]].muki_flag == true){
									if (enemy[E1[e_name]].def_time == 0){ enemy[E1[e_name]].def_haba = gazou_haba2 * 3; }
									if (enemy[E1[e_name]].def_time == (10 * 1)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 4; }
									if (enemy[E1[e_name]].def_time == (10 * 2)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 5; }
									drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y - 6,
										c_size_x, c_size_y,
										enemy[E1[e_name]].def_haba + size_hosei, 0,
										z_size_x, z_size_y,
										bou1, color,
										0, Vec2f(1.8, 1.5), Vec2f(0, 0));
								}

								//当り判定
								for (int i = 0; i < Ene; i++){
									enemy[i].ax = enemy[i].x + c_size_x;		//敵の右下当り判定ｘ
									enemy[i].ay = enemy[i].y + c_size_y;		//敵の左上当り判定ｙ
								}
								teki_sound.pitch(1.5f);

								if (ken_f == true){
									if (ken_hitflag_m == false){
										if (ken_ax_m1 <= enemy[E1[e_name]].ax && ken_ax_m3 >= enemy[E1[e_name]].x){
											if (ken_ay_m1 <= enemy[E1[e_name]].ay && ken_ay_m2 >= enemy[E1[e_name]].y){
												teki_sound.play();
												ken_hitflag_m = true;
												enemy[E1[e_name]].nowhp -= ken_power; //1
												enemy[E1[e_name]].hpba = (enemy[E1[e_name]].nowhp / enemy[E1[e_name]].hpmax) * enemy[E1[e_name]].hpba;
											}
										}
									}
								}

								if (ken_f2 == true){
									if (ken_hitflag_h == false){
										if (ken_ax_h1 <= enemy[E1[e_name]].ax && ken_ax_h3 >= enemy[E1[e_name]].x){
											if (ken_ay_h1 <= enemy[E1[e_name]].ay && ken_ay_h2 >= enemy[E1[e_name]].y){
												teki_sound.play();
												ken_hitflag_h = true;
												enemy[E1[e_name]].nowhp -= ken_power; //1
												enemy[E1[e_name]].hpba = (enemy[E1[e_name]].nowhp / enemy[E1[e_name]].hpmax) * enemy[E1[e_name]].hpba;
											}
										}
									}
								}
								if (ziki_hitflag == false){
									if (enemy[E1[e_name]].x <= ziki_ax && enemy[E1[e_name]].ax >= ziki_x && enemy[E1[e_name]].y <= ziki_ay && enemy[E1[e_name]].ay >= ziki_y){
										ziki_nowhp -= enemy[E1[e_name]].K;
										ziki_hpba = (ziki_nowhp / ziki_hpmax) * ziki_hpba;
										ziki_hitflag = true;
										teki_sound.play();
									}
								}
								if (enemy[E1[e_name]].def_time <= 2){
									ziki_hitflag = false;
								}
								if (enemy[E1[e_name]].nowhp <= 0){
									if (enemy[E1[e_name]].flag == false){
										ziki_nowhp += 100;
										ziki_hpba = (ziki_nowhp / ziki_hpmax) * ziki_hpba;
										kill_count += 1;
										enemy[E1[e_name]].flag = true;
										enemy[E1[e_name]].dead_flag = true;
									}
								}
							}
						}
						if (enemy[E1[e_name]].dead_flag == true){
							enemy[e_name].dead_time++;
							if (enemy[e_name].dead_time == 0){ dead_motion = 0; }
							else if (enemy[e_name].dead_time == (dead_count * 1)){ dead_motion = gazou_haba2 * 1; }
							else if (enemy[e_name].dead_time == (dead_count * 2)){ dead_motion = gazou_haba2 * 2; }
							else if (enemy[e_name].dead_time == (dead_count * 3)){ dead_motion = gazou_haba2 * 3; }
							else if (enemy[e_name].dead_time == (dead_count * 4)){ dead_motion = gazou_haba2 * 4; }
							else if (enemy[e_name].dead_time == (dead_count * 5)){ dead_motion = gazou_haba2 * 5; }
							else if (enemy[e_name].dead_time == (dead_count * 6)){ dead_motion = gazou_haba2 * 6; }
							else if (enemy[e_name].dead_time == (dead_count * 7)){ dead_motion = gazou_haba2 * 7; }
							drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y,
								gazou_haba2, gazou_haba2,
								dead_motion, 0,
								gazou_haba2, gazou_haba2,
								dead, Color::white);
						}
						if (enemy[e_name].dead_time >= 45){
							enemy[e_name].dead_time = 0;
							enemy[E1[e_name]].dead_flag = false;
						}
					}
				}
				//敵11~20体目
				if (kill_count >= 10){
					for (int i = 11; i < B; i++){
						if (ground_time > i * 100){
							*a = i;
							if (enemy[E1[e_name]].flag == false){
								if (enemy[E1[e_name]].sound_flag == false){
									pon_sound.pitch(2.0f);
									pon_sound.play();
									enemy[E1[e_name]].sound_flag = true;
								}
								enemy[E1[e_name]].vy += enemy[E1[e_name]].g;
								enemy[E1[e_name]].y += enemy[E1[e_name]].vy;

								//敵一体目の体力
								drawFillBox(enemy[E1[e_name]].x + hpba_x, enemy[E1[e_name]].y + hpba_y, enemy[E1[e_name]].hpba, hpba_haba, Color::red);
								Color color = Color::red;

								//敵の移動処理

								enemy[E1[e_name]].def_time = (enemy[E1[e_name]].def_time + 1) % 30;

								if (enemy[E1[e_name]].def_time >= 10 && enemy[E1[e_name]].def_time <= 20){
									enemy[E1[e_name]].x -= rand(0, 10);
									enemy[E1[e_name]].muki_flag = true;
								}
								else{ enemy[E1[e_name]].muki_flag = false; }

								if (enemy[E1[e_name]].x <= -1700){
									enemy[E1[e_name]].x = 1500;
								}


								//敵の地面判定
								if (enemy[E1[e_name]].y <= -600){
									enemy[E1[e_name]].y = -600;
									enemy[E1[e_name]].vy = 0;
									enemy[E1[e_name]].jump_s1_flag = false;
									enemy[E1[e_name]].jump_flag = false;
								}
								else {
									enemy[E1[e_name]].jump_flag = true;
								}
								//右向き
								if (enemy[E1[e_name]].muki_flag == false){
									if (enemy[E1[e_name]].def_time == 0){ enemy[E1[e_name]].def_haba = gazou_haba2 * 3; }
									if (enemy[E1[e_name]].def_time == (10 * 1)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 4; }
									if (enemy[E1[e_name]].def_time == (10 * 2)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 5; }
									drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y - 6,
										c_size_x, c_size_y,
										enemy[E1[e_name]].def_haba + size_hosei, 0,
										z_size_x, z_size_y,
										bou, color,
										0, Vec2f(1.8, 1.5), Vec2f(0, 0));
								}

								//左向き
								if (enemy[E1[e_name]].muki_flag == true){
									if (enemy[E1[e_name]].def_time == 0){ enemy[E1[e_name]].def_haba = gazou_haba2 * 3; }
									if (enemy[E1[e_name]].def_time == (10 * 1)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 4; }
									if (enemy[E1[e_name]].def_time == (10 * 2)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 5; }
									drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y - 6,
										c_size_x, c_size_y,
										enemy[E1[e_name]].def_haba + size_hosei, 0,
										z_size_x, z_size_y,
										bou1, color,
										0, Vec2f(1.8, 1.5), Vec2f(0, 0));
								}

								//当り判定
								for (int i = 0; i < Ene; i++){
									enemy[i].ax = enemy[i].x + c_size_x;		//敵の右下当り判定ｘ
									enemy[i].ay = enemy[i].y + c_size_y;		//敵の左上当り判定ｙ
								}
								teki_sound.pitch(1.5f);

								if (ken_f == true){
									if (ken_hitflag_m == false){
										if (ken_ax_m1 <= enemy[E1[e_name]].ax && ken_ax_m3 >= enemy[E1[e_name]].x){
											if (ken_ay_m1 <= enemy[E1[e_name]].ay && ken_ay_m2 >= enemy[E1[e_name]].y){
												teki_sound.play();
												ken_hitflag_m = true;
												enemy[E1[e_name]].nowhp -= ken_power; //1
												enemy[E1[e_name]].hpba = (enemy[E1[e_name]].nowhp / enemy[E1[e_name]].hpmax) * enemy[E1[e_name]].hpba;
											}
										}
									}
								}
								if (ken_f2 == true){
									if (ken_hitflag_h == false){
										if (ken_ax_h1 <= enemy[E1[e_name]].ax && ken_ax_h3 >= enemy[E1[e_name]].x){
											if (ken_ay_h1 <= enemy[E1[e_name]].ay && ken_ay_h2 >= enemy[E1[e_name]].y){
												teki_sound.play();
												ken_hitflag_h = true;
												enemy[E1[e_name]].nowhp -= ken_power; //1
												enemy[E1[e_name]].hpba = (enemy[E1[e_name]].nowhp / enemy[E1[e_name]].hpmax) * enemy[E1[e_name]].hpba;
											}
										}
									}
								}
								if (ziki_hitflag == false){
									if (enemy[E1[e_name]].x <= ziki_ax && enemy[E1[e_name]].ax >= ziki_x && enemy[E1[e_name]].y <= ziki_ay && enemy[E1[e_name]].ay >= ziki_y){
										ziki_nowhp -= enemy[E1[e_name]].K;
										ziki_hpba = (ziki_nowhp / ziki_hpmax) * ziki_hpba;
										ziki_hitflag = true;
										teki_sound.play();
									}
								}
								if (enemy[E1[e_name]].def_time <= 2){
									ziki_hitflag = false;
								}
								if (enemy[E1[e_name]].nowhp <= 0){
									if (enemy[E1[e_name]].flag == false){
										ziki_nowhp += 100;
										ziki_hpba = (ziki_nowhp / ziki_hpmax) * ziki_hpba;
										kill_count += 1;
										enemy[E1[e_name]].flag = true;
										enemy[E1[e_name]].dead_flag = true;
									}
								}
							}
						}
						if (enemy[E1[e_name]].dead_flag == true){
							enemy[e_name].dead_time++;
							if (enemy[e_name].dead_time == 0){ dead_motion = 0; }
							else if (enemy[e_name].dead_time == (dead_count * 1)){ dead_motion = gazou_haba2 * 1; }
							else if (enemy[e_name].dead_time == (dead_count * 2)){ dead_motion = gazou_haba2 * 2; }
							else if (enemy[e_name].dead_time == (dead_count * 3)){ dead_motion = gazou_haba2 * 3; }
							else if (enemy[e_name].dead_time == (dead_count * 4)){ dead_motion = gazou_haba2 * 4; }
							else if (enemy[e_name].dead_time == (dead_count * 5)){ dead_motion = gazou_haba2 * 5; }
							else if (enemy[e_name].dead_time == (dead_count * 6)){ dead_motion = gazou_haba2 * 6; }
							else if (enemy[e_name].dead_time == (dead_count * 7)){ dead_motion = gazou_haba2 * 7; }
							drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y,
								gazou_haba2, gazou_haba2,
								dead_motion, 0,
								gazou_haba2, gazou_haba2,
								dead, Color::white);
						}
						if (enemy[e_name].dead_time >= 45){
							enemy[e_name].dead_time = 0;
							enemy[E1[e_name]].dead_flag = false;
						}
					}
				}


				//敵21体目ボス
				if (kill_count >= 20){
					if (ground_time > 1500){
						*a = 21;
						if (enemy[E1[e_name]].flag == false){
							if (enemy[E1[e_name]].sound_flag == false){
								pon_sound.pitch(2.0f);
								pon_sound.play();
								enemy[E1[e_name]].sound_flag = true;
							}
							enemy[E1[e_name]].vy += enemy[E1[e_name]].g;
							enemy[E1[e_name]].y += enemy[E1[e_name]].vy;

							//敵一体目の体力
							drawFillBox(enemy[E1[e_name]].x + hpba_x, enemy[E1[e_name]].y + hpba_y, enemy[E1[e_name]].hpba, hpba_haba, Color::red);
							Color color = Color::cyan;

							//敵の地面判定
							if (enemy[E1[e_name]].y <= -600){
								enemy[E1[e_name]].y = -600;
								enemy[E1[e_name]].vy = 0;
								enemy[E1[e_name]].jump_s1_flag = false;
								enemy[E1[e_name]].jump_flag = false;
							}
							//ジャンプジャンプジャンプ
							enemy[E1[e_name]].jump_time = (enemy[E1[e_name]].jump_time + 1) % 5;
							if (enemy[E1[e_name]].jump_time == 1){
								if (enemy[E1[e_name]].jump_flag == false || enemy[E1[e_name]].jump_s1_flag == false){
									enemy[E1[e_name]].vy = 90;
									enemy[E1[e_name]].jump_flag = true;
									enemy[E1[e_name]].jump_s1_flag = true;
								}
							}

							//敵の移動処理
							//一定間隔で移動
							
								enemy[E1[e_name]].def_time = (enemy[E1[e_name]].def_time + 1) % 15;
								if (enemy[E1[e_name]].def_time >= 5 && enemy[E1[e_name]].def_time <= 10){
									if (ziki_x <= enemy[E1[e_name]].x){
										enemy[E1[e_name]].x -= 5;
										enemy[E1[e_name]].muki_flag = true; //左向き
									}
									else{
										enemy[E1[e_name]].muki_flag = false;
									}
									if (ziki_x >= enemy[E1[e_name]].x){
										enemy[E1[e_name]].x += 5;
										enemy[E1[e_name]].muki_flag = false; //右向き
									}
									else{
										enemy[E1[e_name]].muki_flag = true;
									}
								}
							

							if (enemy[E1[e_name]].jump_flag == true && enemy[E1[e_name]].jump_s1_flag == true){
								if (enemy[E1[e_name]].muki_flag = false){
									if ((enemy[E1[e_name]].vy == 40 && vy == 20) || (enemy[E1[e_name]].vy == -20 && vy == -40)){ jump_motion = gazou_haba1 * 6; }
									else if ((enemy[E1[e_name]].vy == 20 && vy == 0) || (enemy[E1[e_name]].vy == -20 && vy == 0)){ jump_motion = gazou_haba1 * 7; }
									drawTextureBox(enemy[E1[e_name]].x - 90, enemy[E1[e_name]].y - 6,
										c_size_x, c_size_y,
										jump_motion + size_hosei, 0,
										z_size_x, z_size_y,
										bou, color,
										0, Vec2f(1.8, 1.5), Vec2f(0, 0));
								}
								else if (enemy[E1[e_name]].muki_flag = true){
									if ((enemy[E1[e_name]].vy == 40 && vy == 20) || (enemy[E1[e_name]].vy == -20 && vy == -40)){ jump_motion = gazou_haba1 * 6; }
									else if ((enemy[E1[e_name]].vy == 20 && vy == 0) || (enemy[E1[e_name]].vy == -20 && vy == 0)){ jump_motion = gazou_haba1 * 7; }
									drawTextureBox(enemy[E1[e_name]].x - 100, enemy[E1[e_name]].y - 6,
										c_size_x, c_size_y,
										jump_motion + size_hosei, 0,
										z_size_x, z_size_y,
										bou1, color,
										0, Vec2f(1.8, 1.5), Vec2f(0, 0));
								}

							}
							//端っこにワープ
							if (enemy[E1[e_name]].x <= -1700){
								enemy[E1[e_name]].x = 1500;
							}
							if (enemy[E1[e_name]].x >= 1500){
								enemy[E1[e_name]].x = -1700;
							}


							//右向き
							if (enemy[E1[e_name]].jump_flag == false || enemy[E1[e_name]].jump_s1_flag == false){
								if (enemy[E1[e_name]].muki_flag == false){
									if (enemy[E1[e_name]].def_time == 0){ enemy[E1[e_name]].def_haba = gazou_haba2 * 3; }
									if (enemy[E1[e_name]].def_time == (10 * 1)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 4; }
									if (enemy[E1[e_name]].def_time == (10 * 2)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 5; }
									drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y - 6,
										c_size_x, c_size_y,
										enemy[E1[e_name]].def_haba + size_hosei, 0,
										z_size_x, z_size_y,
										bou, color,
										0, Vec2f(1.8, 1.5), Vec2f(0, 0));
								}

								//左向き
								if (enemy[E1[e_name]].muki_flag == true){
									if (enemy[E1[e_name]].def_time == 0){ enemy[E1[e_name]].def_haba = gazou_haba2 * 3; }
									if (enemy[E1[e_name]].def_time == (10 * 1)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 4; }
									if (enemy[E1[e_name]].def_time == (10 * 2)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 5; }
									drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y - 6,
										c_size_x, c_size_y,
										enemy[E1[e_name]].def_haba + size_hosei, 0,
										z_size_x, z_size_y,
										bou1, color,
										0, Vec2f(1.8, 1.5), Vec2f(0, 0));
								}
							}
							//当り判定
							for (int i = 0; i < Ene; i++){
								enemy[i].ax = enemy[i].x + c_size_x;		//敵の右下当り判定ｘ
								enemy[i].ay = enemy[i].y + c_size_y;		//敵の左上当り判定ｙ
							}
							teki_sound.pitch(1.5f);

							if (ken_f == true){
								if (ken_hitflag_m == false){
									if (ken_ax_m1 <= enemy[E1[e_name]].ax && ken_ax_m3 >= enemy[E1[e_name]].x){
										if (ken_ay_m1 <= enemy[E1[e_name]].ay && ken_ay_m2 >= enemy[E1[e_name]].y){
											teki_sound.play();
											ken_hitflag_m = true;
											enemy[E1[e_name]].nowhp -= ken_power;
											enemy[E1[e_name]].hpba = (enemy[E1[e_name]].nowhp / enemy[E1[e_name]].hpmax) * enemy[E1[e_name]].hpba;
										}
									}
								}
							}
							if (ken_f2 == true){
								if (ken_hitflag_h == false){
									if (ken_ax_h1 <= enemy[E1[e_name]].ax && ken_ax_h3 >= enemy[E1[e_name]].x){
										if (ken_ay_h1 <= enemy[E1[e_name]].ay && ken_ay_h2 >= enemy[E1[e_name]].y){
											teki_sound.play();
											ken_hitflag_h = true;
											enemy[E1[e_name]].nowhp -= ken_power;
											enemy[E1[e_name]].hpba = (enemy[E1[e_name]].nowhp / enemy[E1[e_name]].hpmax) * enemy[E1[e_name]].hpba;
										}
									}
								}
							}
							if (ziki_hitflag == false){
								if (enemy[E1[e_name]].x <= ziki_ax && enemy[E1[e_name]].ax >= ziki_x && enemy[E1[e_name]].y <= ziki_ay && enemy[E1[e_name]].ay >= ziki_y){
									ziki_nowhp -= enemy[E1[e_name]].K;
									ziki_hpba = (ziki_nowhp / ziki_hpmax) * ziki_hpba;
									ziki_hitflag = true;
									teki_sound.play();
								}
							}
							if (enemy[E1[e_name]].def_time <= 2){
								ziki_hitflag = false;
							}
							if (enemy[E1[e_name]].hpba <= 1){
								if (enemy[E1[e_name]].flag == false){
									ziki_nowhp += 100;
									ziki_hpba = (ziki_nowhp / ziki_hpmax) * ziki_hpba;
									kill_count += 1;
									enemy[E1[e_name]].flag = true;
									enemy[E1[e_name]].dead_flag = true;
								}
							}
						}
					}
					if (enemy[E1[e_name]].dead_flag == true){
						enemy[e_name].dead_time++;
						if (enemy[e_name].dead_time == 0){ dead_motion = 0; }
						else if (enemy[e_name].dead_time == (dead_count * 1)){ dead_motion = gazou_haba2 * 1; }
						else if (enemy[e_name].dead_time == (dead_count * 2)){ dead_motion = gazou_haba2 * 2; }
						else if (enemy[e_name].dead_time == (dead_count * 3)){ dead_motion = gazou_haba2 * 3; }
						else if (enemy[e_name].dead_time == (dead_count * 4)){ dead_motion = gazou_haba2 * 4; }
						else if (enemy[e_name].dead_time == (dead_count * 5)){ dead_motion = gazou_haba2 * 5; }
						else if (enemy[e_name].dead_time == (dead_count * 6)){ dead_motion = gazou_haba2 * 6; }
						else if (enemy[e_name].dead_time == (dead_count * 7)){ dead_motion = gazou_haba2 * 7; }
						drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y,
							gazou_haba2, gazou_haba2,
							dead_motion, 0,
							gazou_haba2, gazou_haba2,
							dead, Color::white);
					}
					if (enemy[e_name].dead_time >= 45){
						enemy[e_name].dead_time = 0;
						enemy[E1[e_name]].dead_flag = false;
					}
				}

				//敵22~40体目
				if (kill_count >= 21){
					ground_time2++;
					for (int i = 22; i < C; i++){
						if (ground_time2 > -2200 + i * 90){
							*a = i;
							if (enemy[E1[e_name]].flag == false){
								if (enemy[E1[e_name]].sound_flag == false){
									pon_sound.pitch(2.0f);
									pon_sound.play();
									enemy[E1[e_name]].sound_flag = true;
								}
								enemy[E1[e_name]].vy += enemy[E1[e_name]].g;
								enemy[E1[e_name]].y += enemy[E1[e_name]].vy;

								//敵一体目の体力
								drawFillBox(enemy[E1[e_name]].x + hpba_x, enemy[E1[e_name]].y + hpba_y, enemy[E1[e_name]].hpba, hpba_haba, Color::red);
								Color color = Color::cyan;

								//敵の地面判定
								if (enemy[E1[e_name]].y <= -600){
									enemy[E1[e_name]].y = -600;
									enemy[E1[e_name]].vy = 0;
									enemy[E1[e_name]].jump_s1_flag = false;
									enemy[E1[e_name]].jump_flag = false;
								}


								//ジャンプジャンプジャンプ
								enemy[E1[e_name]].jump_time = (enemy[E1[e_name]].jump_time + 1) % 80;
								if (enemy[E1[e_name]].jump_time == 1){
									if (enemy[E1[e_name]].jump_flag == false || enemy[E1[e_name]].jump_s1_flag == false){
										enemy[E1[e_name]].vy = 40;
										enemy[E1[e_name]].jump_flag = true;
										enemy[E1[e_name]].jump_s1_flag = true;
									}
								}

								//敵の移動処理
								//一定間隔で移動
								
									enemy[E1[e_name]].def_time = (enemy[E1[e_name]].def_time + 1) % 30;
									if (enemy[E1[e_name]].def_time >= 10 && enemy[E1[e_name]].def_time <= 20){
										if (ziki_x <= enemy[E1[e_name]].x){
											enemy[E1[e_name]].x -= 8;
											enemy[E1[e_name]].muki_flag = true; //左向き
										}
										else{
											enemy[E1[e_name]].muki_flag = false;
										}
										if (ziki_x >= enemy[E1[e_name]].x){
											enemy[E1[e_name]].x += 8;
											enemy[E1[e_name]].muki_flag = false; //右向き
										}
										else{
											enemy[E1[e_name]].muki_flag = true;
										}
									}
								

								if (enemy[E1[e_name]].jump_flag == true && enemy[E1[e_name]].jump_s1_flag == true){
									if (enemy[E1[e_name]].muki_flag = false){
										if ((enemy[E1[e_name]].vy == 40 && vy == 20) || (enemy[E1[e_name]].vy == -20 && vy == -40)){ jump_motion = gazou_haba1 * 6; }
										else if ((enemy[E1[e_name]].vy == 20 && vy == 0) || (enemy[E1[e_name]].vy == -20 && vy == 0)){ jump_motion = gazou_haba1 * 7; }
										drawTextureBox(enemy[E1[e_name]].x - 90, enemy[E1[e_name]].y - 6,
											c_size_x, c_size_y,
											jump_motion + size_hosei, 0,
											z_size_x, z_size_y,
											bou, color,
											0, Vec2f(1.8, 1.5), Vec2f(0, 0));
									}
									else if (enemy[E1[e_name]].muki_flag = true){
										if ((enemy[E1[e_name]].vy == 40 && vy == 20) || (enemy[E1[e_name]].vy == -20 && vy == -40)){ jump_motion = gazou_haba1 * 6; }
										else if ((enemy[E1[e_name]].vy == 20 && vy == 0) || (enemy[E1[e_name]].vy == -20 && vy == 0)){ jump_motion = gazou_haba1 * 7; }
										drawTextureBox(enemy[E1[e_name]].x - 100, enemy[E1[e_name]].y - 6,
											c_size_x, c_size_y,
											jump_motion + size_hosei, 0,
											z_size_x, z_size_y,
											bou1, color,
											0, Vec2f(1.8, 1.5), Vec2f(0, 0));
									}

								}
								//端っこにワープ
								if (enemy[E1[e_name]].x <= -1700){
									enemy[E1[e_name]].x = 1500;
								}
								if (enemy[E1[e_name]].x >= 1500){
									enemy[E1[e_name]].x = -1700;
								}


								//右向き
								if (enemy[E1[e_name]].jump_flag == false || enemy[E1[e_name]].jump_s1_flag == false){
									if (enemy[E1[e_name]].muki_flag == false){
										if (enemy[E1[e_name]].def_time == 0){ enemy[E1[e_name]].def_haba = gazou_haba2 * 3; }
										if (enemy[E1[e_name]].def_time == (10 * 1)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 4; }
										if (enemy[E1[e_name]].def_time == (10 * 2)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 5; }
										drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y - 6,
											c_size_x, c_size_y,
											enemy[E1[e_name]].def_haba + size_hosei, 0,
											z_size_x, z_size_y,
											bou, color,
											0, Vec2f(1.8, 1.5), Vec2f(0, 0));
									}

									//左向き
									if (enemy[E1[e_name]].muki_flag == true){
										if (enemy[E1[e_name]].def_time == 0){ enemy[E1[e_name]].def_haba = gazou_haba2 * 3; }
										if (enemy[E1[e_name]].def_time == (10 * 1)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 4; }
										if (enemy[E1[e_name]].def_time == (10 * 2)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 5; }
										drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y - 6,
											c_size_x, c_size_y,
											enemy[E1[e_name]].def_haba + size_hosei, 0,
											z_size_x, z_size_y,
											bou1, color,
											0, Vec2f(1.8, 1.5), Vec2f(0, 0));
									}
								}
								//当り判定
								for (int i = 0; i < Ene; i++){
									enemy[i].ax = enemy[i].x + c_size_x;		//敵の右下当り判定ｘ
									enemy[i].ay = enemy[i].y + c_size_y;		//敵の左上当り判定ｙ
								}
								teki_sound.pitch(1.5f);

								if (ken_f == true){
									if (ken_hitflag_m == false){
										if (ken_ax_m1 <= enemy[E1[e_name]].ax && ken_ax_m3 >= enemy[E1[e_name]].x){
											if (ken_ay_m1 <= enemy[E1[e_name]].ay && ken_ay_m2 >= enemy[E1[e_name]].y){
												teki_sound.play();
												ken_hitflag_m = true;
												enemy[E1[e_name]].nowhp -= ken_power; //1
												enemy[E1[e_name]].hpba = (enemy[E1[e_name]].nowhp / enemy[E1[e_name]].hpmax) * enemy[E1[e_name]].hpba;
											}
										}
									}
								}
								if (ken_f2 == true){
									if (ken_hitflag_h == false){
										if (ken_ax_h1 <= enemy[E1[e_name]].ax && ken_ax_h3 >= enemy[E1[e_name]].x){
											if (ken_ay_h1 <= enemy[E1[e_name]].ay && ken_ay_h2 >= enemy[E1[e_name]].y){
												teki_sound.play();
												ken_hitflag_h = true;
												enemy[E1[e_name]].nowhp -= ken_power; //1
												enemy[E1[e_name]].hpba = (enemy[E1[e_name]].nowhp / enemy[E1[e_name]].hpmax) * enemy[E1[e_name]].hpba;
											}
										}
									}
								}
								if (ziki_hitflag == false){
									if (enemy[E1[e_name]].x <= ziki_ax && enemy[E1[e_name]].ax >= ziki_x && enemy[E1[e_name]].y <= ziki_ay && enemy[E1[e_name]].ay >= ziki_y){
										ziki_nowhp -= enemy[E1[e_name]].K;
										ziki_hpba = (ziki_nowhp / ziki_hpmax) * ziki_hpba;
										ziki_hitflag = true;
										teki_sound.play();
									}
								}
								if (enemy[E1[e_name]].def_time <= 2){
									ziki_hitflag = false;
								}
								if (enemy[E1[e_name]].nowhp <= 0){
									if (enemy[E1[e_name]].flag == false){
										ziki_nowhp += 100;
										ziki_hpba = (ziki_nowhp / ziki_hpmax) * ziki_hpba;
										kill_count += 1;
										enemy[E1[e_name]].flag = true;
										enemy[E1[e_name]].dead_flag = true;
									}
								}
							}
						}
						if (enemy[E1[e_name]].dead_flag == true){
							enemy[e_name].dead_time++;
							if (enemy[e_name].dead_time == 0){ dead_motion = 0; }
							else if (enemy[e_name].dead_time == (dead_count * 1)){ dead_motion = gazou_haba2 * 1; }
							else if (enemy[e_name].dead_time == (dead_count * 2)){ dead_motion = gazou_haba2 * 2; }
							else if (enemy[e_name].dead_time == (dead_count * 3)){ dead_motion = gazou_haba2 * 3; }
							else if (enemy[e_name].dead_time == (dead_count * 4)){ dead_motion = gazou_haba2 * 4; }
							else if (enemy[e_name].dead_time == (dead_count * 5)){ dead_motion = gazou_haba2 * 5; }
							else if (enemy[e_name].dead_time == (dead_count * 6)){ dead_motion = gazou_haba2 * 6; }
							else if (enemy[e_name].dead_time == (dead_count * 7)){ dead_motion = gazou_haba2 * 7; }
							drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y,
								gazou_haba2, gazou_haba2,
								dead_motion, 0,
								gazou_haba2, gazou_haba2,
								dead, Color::white);
						}
						if (enemy[e_name].dead_time >= 45){
							enemy[e_name].dead_time = 0;
							enemy[E1[e_name]].dead_flag = false;
						}
					}
					//敵41~50体目
					if (kill_count >= 40){
						ground_time3++;
						for (int i = 41; i < D; i++){
							if (ground_time3 > -6000 + i * 150){
								*a = i;
								if (enemy[E1[e_name]].flag == false){
									if (enemy[E1[e_name]].sound_flag == false){
										pon_sound.pitch(2.0f);
										pon_sound.play();
										enemy[E1[e_name]].sound_flag = true;
									}
									enemy[E1[e_name]].vy += enemy[E1[e_name]].g;
									enemy[E1[e_name]].y += enemy[E1[e_name]].vy;

									//敵一体目の体力
									drawFillBox(enemy[E1[e_name]].x + hpba_x, enemy[E1[e_name]].y + hpba_y, enemy[E1[e_name]].hpba, hpba_haba, Color::red);
									Color color = Color::purple;
									//敵の地面判定
									if (enemy[E1[e_name]].y <= -600){
										enemy[E1[e_name]].y = -600;
										enemy[E1[e_name]].vy = 0;
										enemy[E1[e_name]].jump_s1_flag = false;
										enemy[E1[e_name]].jump_flag = false;
									}


									//ジャンプジャンプジャンプ
									enemy[E1[e_name]].jump_time = (enemy[E1[e_name]].jump_time + 1) % 20;
									if (enemy[E1[e_name]].jump_time == 1){
										if (enemy[E1[e_name]].jump_flag == false || enemy[E1[e_name]].jump_s1_flag == false){
											enemy[E1[e_name]].vy = 40;
											enemy[E1[e_name]].jump_flag = true;
											enemy[E1[e_name]].jump_s1_flag = true;
										}
									}

									//敵の移動処理
									//一定間隔で移動
									
										enemy[E1[e_name]].def_time = (enemy[E1[e_name]].def_time + 1) % 30;
										if (enemy[E1[e_name]].def_time >= 10 && enemy[E1[e_name]].def_time <= 20){
											if (ziki_x <= enemy[E1[e_name]].x){
												enemy[E1[e_name]].x -= 10;
												enemy[E1[e_name]].muki_flag = true; //左向き
											}
											else{
												enemy[E1[e_name]].muki_flag = false;
											}
											if (ziki_x >= enemy[E1[e_name]].x){
												enemy[E1[e_name]].x += 10;
												enemy[E1[e_name]].muki_flag = false; //右向き
											}
											else{
												enemy[E1[e_name]].muki_flag = true;
											}
										}
									

									if (enemy[E1[e_name]].jump_flag == true && enemy[E1[e_name]].jump_s1_flag == true){
										if (enemy[E1[e_name]].muki_flag = false){
											if ((enemy[E1[e_name]].vy == 40 && vy == 20) || (enemy[E1[e_name]].vy == -20 && vy == -40)){ jump_motion = gazou_haba1 * 6; }
											else if ((enemy[E1[e_name]].vy == 20 && vy == 0) || (enemy[E1[e_name]].vy == -20 && vy == 0)){ jump_motion = gazou_haba1 * 7; }
											drawTextureBox(enemy[E1[e_name]].x - 90, enemy[E1[e_name]].y - 6,
												c_size_x, c_size_y,
												jump_motion + size_hosei, 0,
												z_size_x, z_size_y,
												bou, color,
												0, Vec2f(1.8, 1.5), Vec2f(0, 0));
										}
										else if (enemy[E1[e_name]].muki_flag = true){
											if ((enemy[E1[e_name]].vy == 40 && vy == 20) || (enemy[E1[e_name]].vy == -20 && vy == -40)){ jump_motion = gazou_haba1 * 6; }
											else if ((enemy[E1[e_name]].vy == 20 && vy == 0) || (enemy[E1[e_name]].vy == -20 && vy == 0)){ jump_motion = gazou_haba1 * 7; }
											drawTextureBox(enemy[E1[e_name]].x - 100, enemy[E1[e_name]].y - 6,
												c_size_x, c_size_y,
												jump_motion + size_hosei, 0,
												z_size_x, z_size_y,
												bou1, color,
												0, Vec2f(1.8, 1.5), Vec2f(0, 0));
										}

									}
									//端っこにワープ
									if (enemy[E1[e_name]].x <= -1700){
										enemy[E1[e_name]].x = 1500;
									}
									if (enemy[E1[e_name]].x >= 1500){
										enemy[E1[e_name]].x = -1700;
									}


									//右向き
									if (enemy[E1[e_name]].jump_flag == false || enemy[E1[e_name]].jump_s1_flag == false){
										if (enemy[E1[e_name]].muki_flag == false){
											if (enemy[E1[e_name]].def_time == 0){ enemy[E1[e_name]].def_haba = gazou_haba2 * 3; }
											if (enemy[E1[e_name]].def_time == (10 * 1)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 4; }
											if (enemy[E1[e_name]].def_time == (10 * 2)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 5; }
											drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y - 6,
												c_size_x, c_size_y,
												enemy[E1[e_name]].def_haba + size_hosei, 0,
												z_size_x, z_size_y,
												bou, color,
												0, Vec2f(1.8, 1.5), Vec2f(0, 0));
										}

										//左向き
										if (enemy[E1[e_name]].muki_flag == true){
											if (enemy[E1[e_name]].def_time == 0){ enemy[E1[e_name]].def_haba = gazou_haba2 * 3; }
											if (enemy[E1[e_name]].def_time == (10 * 1)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 4; }
											if (enemy[E1[e_name]].def_time == (10 * 2)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 5; }
											drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y - 6,
												c_size_x, c_size_y,
												enemy[E1[e_name]].def_haba + size_hosei, 0,
												z_size_x, z_size_y,
												bou1, color,
												0, Vec2f(1.8, 1.5), Vec2f(0, 0));
										}
									}
									//当り判定
									for (int i = 0; i < Ene; i++){
										enemy[i].ax = enemy[i].x + c_size_x;		//敵の右下当り判定ｘ
										enemy[i].ay = enemy[i].y + c_size_y;		//敵の左上当り判定ｙ
									}
									teki_sound.pitch(1.5f);

									if (ken_f == true){
										if (ken_hitflag_m == false){
											if (ken_ax_m1 <= enemy[E1[e_name]].ax && ken_ax_m3 >= enemy[E1[e_name]].x){
												if (ken_ay_m1 <= enemy[E1[e_name]].ay && ken_ay_m2 >= enemy[E1[e_name]].y){
													teki_sound.play();
													ken_hitflag_m = true;
													enemy[E1[e_name]].nowhp -= ken_power; //1
													enemy[E1[e_name]].hpba = (enemy[E1[e_name]].nowhp / enemy[E1[e_name]].hpmax) * enemy[E1[e_name]].hpba;
												}
											}
										}
									}
									if (ken_f2 == true){
										if (ken_hitflag_h == false){
											if (ken_ax_h1 <= enemy[E1[e_name]].ax && ken_ax_h3 >= enemy[E1[e_name]].x){
												if (ken_ay_h1 <= enemy[E1[e_name]].ay && ken_ay_h2 >= enemy[E1[e_name]].y){
													teki_sound.play();
													ken_hitflag_h = true;
													enemy[E1[e_name]].nowhp -= ken_power; //1
													enemy[E1[e_name]].hpba = (enemy[E1[e_name]].nowhp / enemy[E1[e_name]].hpmax) * enemy[E1[e_name]].hpba;
												}
											}
										}
									}
									if (ziki_hitflag == false){
										if (enemy[E1[e_name]].x <= ziki_ax && enemy[E1[e_name]].ax >= ziki_x && enemy[E1[e_name]].y <= ziki_ay && enemy[E1[e_name]].ay >= ziki_y){
											ziki_nowhp -= enemy[E1[e_name]].K;
											ziki_hpba = (ziki_nowhp / ziki_hpmax) * ziki_hpba;
											ziki_hitflag = true;
											teki_sound.play();
										}
									}
									if (enemy[E1[e_name]].def_time <= 2){
										ziki_hitflag = false;
									}
									if (enemy[E1[e_name]].nowhp <= 0){
										if (enemy[E1[e_name]].flag == false){
											ziki_nowhp += 100;
											ziki_hpba = (ziki_nowhp / ziki_hpmax) * ziki_hpba;
											kill_count += 1;
											enemy[E1[e_name]].flag = true;
											enemy[E1[e_name]].dead_flag = true;
										}
									}
								}
							}
							if (enemy[E1[e_name]].dead_flag == true){
								enemy[e_name].dead_time++;
								if (enemy[e_name].dead_time == 0){ dead_motion = 0; }
								else if (enemy[e_name].dead_time == (dead_count * 1)){ dead_motion = gazou_haba2 * 1; }
								else if (enemy[e_name].dead_time == (dead_count * 2)){ dead_motion = gazou_haba2 * 2; }
								else if (enemy[e_name].dead_time == (dead_count * 3)){ dead_motion = gazou_haba2 * 3; }
								else if (enemy[e_name].dead_time == (dead_count * 4)){ dead_motion = gazou_haba2 * 4; }
								else if (enemy[e_name].dead_time == (dead_count * 5)){ dead_motion = gazou_haba2 * 5; }
								else if (enemy[e_name].dead_time == (dead_count * 6)){ dead_motion = gazou_haba2 * 6; }
								else if (enemy[e_name].dead_time == (dead_count * 7)){ dead_motion = gazou_haba2 * 7; }
								drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y,
									gazou_haba2, gazou_haba2,
									dead_motion, 0,
									gazou_haba2, gazou_haba2,
									dead, Color::white);
							}
							if (enemy[e_name].dead_time >= 45){
								enemy[e_name].dead_time = 0;
								enemy[E1[e_name]].dead_flag = false;
							}
						}
					}
				
					//敵51体目ボス
					if (kill_count >= 50){
						if (ground_time > 0){
							*a = 51;
							if (enemy[E1[e_name]].flag == false){
								if (enemy[E1[e_name]].sound_flag == false){
									pon_sound.pitch(2.0f);
									pon_sound.play();
									enemy[E1[e_name]].x = 1300; enemy[E1[e_name]].y = 1100;
									enemy[E1[e_name]].hpba = 1500;
									enemy[E1[e_name]].sound_flag = true;
								}

								enemy[1].g = -4;
								enemy[E1[e_name]].vy += enemy[E1[e_name]].g;
								enemy[E1[e_name]].y += enemy[E1[e_name]].vy;

								//敵一体目の体力
								drawFillBox(enemy[E1[e_name]].x + hpba_x, enemy[E1[e_name]].y + hpba_y * 3, enemy[E1[e_name]].hpba, hpba_haba, Color::red);
								Color color = Color::black;

								//敵の地面判定
								if (enemy[E1[e_name]].y <= -600){
									enemy[E1[e_name]].y = -600;
									enemy[E1[e_name]].vy = 0;
									enemy[E1[e_name]].jump_s1_flag = false;
									enemy[E1[e_name]].jump_flag = false;
								}


								//ジャンプジャンプジャンプ
								enemy[E1[e_name]].jump_time = (enemy[E1[e_name]].jump_time + 1) % 70;
								if (enemy[E1[e_name]].jump_time == 0){
									if (enemy[E1[e_name]].jump_flag == false || enemy[E1[e_name]].jump_s1_flag == false){
										enemy[E1[e_name]].vy = 100;
										enemy[E1[e_name]].jump_flag = true;
										enemy[E1[e_name]].jump_s1_flag = true;
									}
								}

								//敵の移動処理
								//一定間隔で移動
								
									enemy[E1[e_name]].def_time = (enemy[E1[e_name]].def_time + 1) % 30;
									if (enemy[E1[e_name]].def_time >= 10 && enemy[E1[e_name]].def_time <= 20){
										if (ziki_x <= enemy[E1[e_name]].x){
											enemy[E1[e_name]].x -= 10;
											enemy[E1[e_name]].muki_flag = true; //左向き
										}
										else{
											enemy[E1[e_name]].muki_flag = false;
										}
										if (ziki_x >= enemy[E1[e_name]].x){
											enemy[E1[e_name]].x += 10;
											enemy[E1[e_name]].muki_flag = false; //右向き
										}
										else{
											enemy[E1[e_name]].muki_flag = true;
										}
									}
								

								if (enemy[E1[e_name]].jump_flag == true && enemy[E1[e_name]].jump_s1_flag == true){
									if (enemy[E1[e_name]].muki_flag = false){
										if ((enemy[E1[e_name]].vy == 40 && vy == 20) || (enemy[E1[e_name]].vy == -20 && vy == -40)){ jump_motion = gazou_haba1 * 6; }
										else if ((enemy[E1[e_name]].vy == 20 && vy == 0) || (enemy[E1[e_name]].vy == -20 && vy == 0)){ jump_motion = gazou_haba1 * 7; }
										drawTextureBox(enemy[E1[e_name]].x - 90*3, enemy[E1[e_name]].y - 6,
											c_size_x * 3, c_size_y * 3,
											jump_motion + size_hosei, 0,
											z_size_x, z_size_y,
											bou, color,
											0, Vec2f(1.8, 1.5), Vec2f(0, 0));
									}
									else if (enemy[E1[e_name]].muki_flag = true){
										if ((enemy[E1[e_name]].vy == 40 && vy == 20) || (enemy[E1[e_name]].vy == -20 && vy == -40)){ jump_motion = gazou_haba1 * 6; }
										else if ((enemy[E1[e_name]].vy == 20 && vy == 0) || (enemy[E1[e_name]].vy == -20 && vy == 0)){ jump_motion = gazou_haba1 * 7; }
										drawTextureBox(enemy[E1[e_name]].x - 100*3, enemy[E1[e_name]].y - 6,
											c_size_x * 3, c_size_y * 3,
											jump_motion + size_hosei, 0,
											z_size_x, z_size_y,
											bou1, color,
											0, Vec2f(1.8, 1.5), Vec2f(0, 0));
									}

								}
								//端っこにワープ
								if (enemy[E1[e_name]].x <= -1700){
									enemy[E1[e_name]].x = 1500;
								}
								if (enemy[E1[e_name]].x >= 1500){
									enemy[E1[e_name]].x = -1700;
								}


								//右向き
								if (enemy[E1[e_name]].jump_flag == false || enemy[E1[e_name]].jump_s1_flag == false){
									if (enemy[E1[e_name]].muki_flag == false){
										if (enemy[E1[e_name]].def_time == 0){ enemy[E1[e_name]].def_haba = gazou_haba2 * 3; }
										if (enemy[E1[e_name]].def_time == (10 * 1)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 4; }
										if (enemy[E1[e_name]].def_time == (10 * 2)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 5; }
										drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y - 6,
											c_size_x * 3, c_size_y * 3,
											enemy[E1[e_name]].def_haba + size_hosei, 0,
											z_size_x, z_size_y,
											bou, color,
											0, Vec2f(1.8, 1.5), Vec2f(0, 0));
									}

									//左向き
									if (enemy[E1[e_name]].muki_flag == true){
										if (enemy[E1[e_name]].def_time == 0){ enemy[E1[e_name]].def_haba = gazou_haba2 * 3; }
										if (enemy[E1[e_name]].def_time == (10 * 1)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 4; }
										if (enemy[E1[e_name]].def_time == (10 * 2)){ enemy[E1[e_name]].def_haba = gazou_haba2 * 5; }
										drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y - 6,
											c_size_x * 3, c_size_y * 3,
											enemy[E1[e_name]].def_haba + size_hosei, 0,
											z_size_x, z_size_y,
											bou1, color,
											0, Vec2f(1.8, 1.5), Vec2f(0, 0));
									}
								}
								//当り判定

								enemy[51].ax = enemy[51].x + c_size_x * 3;		//敵の右下当り判定ｘ
								enemy[51].ay = enemy[51].y + c_size_y * 3;		//敵の左上当り判定ｙ

								teki_sound.pitch(1.5f);
								if (ken_f == true){
									if (ken_hitflag_m == false){
										if (ken_ax_m1 <= enemy[E1[e_name]].ax && ken_ax_m3 >= enemy[E1[e_name]].x){
											if (ken_ay_m1 <= enemy[E1[e_name]].ay && ken_ay_m2 >= enemy[E1[e_name]].y){
												teki_sound.play();
												ken_hitflag_m = true;
												enemy[E1[e_name]].nowhp -= ken_power;
												enemy[E1[e_name]].hpba = (enemy[E1[e_name]].nowhp / enemy[E1[e_name]].hpmax) * enemy[E1[e_name]].hpba;
											}
										}
									}
								}
								if (ken_f2 == true){
									if (ken_hitflag_h == false){
										if (ken_ax_h1 <= enemy[E1[e_name]].ax && ken_ax_h3 >= enemy[E1[e_name]].x){
											if (ken_ay_h1 <= enemy[E1[e_name]].ay && ken_ay_h2 >= enemy[E1[e_name]].y){
												teki_sound.play();
												ken_hitflag_h = true;
												enemy[E1[e_name]].nowhp -= ken_power;
												enemy[E1[e_name]].hpba = (enemy[E1[e_name]].nowhp / enemy[E1[e_name]].hpmax) * enemy[E1[e_name]].hpba;
											}
										}
									}
								}
								if (ziki_hitflag == false){
									if (enemy[E1[e_name]].x <= ziki_ax && enemy[E1[e_name]].ax >= ziki_x && enemy[E1[e_name]].y <= ziki_ay && enemy[E1[e_name]].ay >= ziki_y){
										ziki_nowhp -= enemy[E1[e_name]].K;
										ziki_hpba = (ziki_nowhp / ziki_hpmax) * ziki_hpba;
										ziki_hitflag = true;
										teki_sound.play();
									}
								}
								if (enemy[E1[e_name]].def_time <= 2){
									ziki_hitflag = false;
								}
								if (enemy[E1[e_name]].hpba <= 2){
									if (enemy[E1[e_name]].flag == false){
										ziki_nowhp += 1000;
										ziki_hpba = (ziki_nowhp / ziki_hpmax) * ziki_hpba;
										kill_count += 1;
										enemy[E1[e_name]].flag = true;
										enemy[E1[e_name]].dead_flag = true;
									}
								}
							}
						}
						if (enemy[E1[e_name]].dead_flag == true){
							enemy[e_name].dead_time++;
							if (enemy[e_name].dead_time == 1){ dead_motion = 0; }
							else if (enemy[e_name].dead_time == (dead_count_bos * 1)){ dead_motion = gazou_haba2 * 1; }
							else if (enemy[e_name].dead_time == (dead_count_bos * 2)){ dead_motion = gazou_haba2 * 2; }
							else if (enemy[e_name].dead_time == (dead_count_bos * 3)){ dead_motion = gazou_haba2 * 3; }
							else if (enemy[e_name].dead_time == (dead_count_bos * 4)){ dead_motion = gazou_haba2 * 4; }
							else if (enemy[e_name].dead_time == (dead_count_bos * 5)){ dead_motion = gazou_haba2 * 5; }
							else if (enemy[e_name].dead_time == (dead_count_bos * 6)){ dead_motion = gazou_haba2 * 6; }
							else if (enemy[e_name].dead_time == (dead_count_bos * 7)){ dead_motion = gazou_haba2 * 7; }
							drawTextureBox(enemy[E1[e_name]].x, enemy[E1[e_name]].y,
								gazou_haba2 * 3, gazou_haba2 * 3,
								dead_motion, 0,
								gazou_haba2, gazou_haba2,
								dead, Color::white);
						}
						if (enemy[e_name].dead_time >= 400){
							enemy[e_name].dead_time = 0;
							enemy[E1[e_name]].dead_flag = false;
							gamen = 2;
						}
					}




					}
				

			}

			if (ziki_hpba <= 3 || env.isPushKey('Y')){
				gamen = 3;
			}


			//自機の体力
			if (ziki_hpba >= 200){
				ziki_hpba = 200;
			}
			if (ziki_nowhp >= ziki_hpmax){
				ziki_nowhp = ziki_hpmax;
			}


			drawFillBox(ziki_x + hpba_x, ziki_y + hpba_y, ziki_hpba, hpba_haba, Color::green);

			//当り判定確認
			//drawBox(teki_ax1[0], teki_ay1[0], c_size_x, c_size_y, 3, Color::blue);
			//drawBox(ken_ax_m1, ken_ay_m1, k_size_x, k_size_y, 3, Color::blue);
			//drawBox(ken_ax_h1, ken_ay_h1, k_size_x, k_size_y, 3, Color::blue);



			for (int i = 0; i < 22; i++){
				if (enemy[i].jump_flag == true){
					if (enemy[i].x + c_size_x > 500 && enemy[i].x + c_size_x <= 510 && enemy[i].y >= -600 && enemy[i].y < -230){
						enemy[i].x = 500 - c_size_x;
					}
					else if (enemy[i].x < 800 && enemy[i].x >= 790 && enemy[i].y >= -600 && enemy[i].y < -230){
						enemy[i].x = 800;
					}
					else if (enemy[i].x + c_size_x > 500 && enemy[i].x < 800 && enemy[i].y > -600 && enemy[i].y <= -230){
						enemy[i].y = -300;
						enemy[i].vy = 0;
						enemy[i].jump_s1_flag = false;
					}
					else{
						enemy[i].jump_s1_flag = true;
						}
				}

				//地上
				else if (enemy[i].kasoku < 100){
					if (enemy[i].x + c_size_x > 500 && enemy[i].x + c_size_x <= 510 && enemy[i].y >= -600 && enemy[i].y < -300){
						enemy[i].x = 500 - c_size_x;
						enemy[i].vy = 80;
						enemy[i].jump_flag = true;
					}
					if (enemy[i].x < 800 && enemy[i].x >= 790 && enemy[i].y >= -600 && enemy[i].y < -300){
						enemy[i].x = 800;
						enemy[i].vy = 80;
						enemy[i].jump_flag = true;
					}
				}
			}

			for (int i = 41; i < D; i++){
				if (enemy[i].jump_flag == true){
					if (enemy[i].x + c_size_x > 500 && enemy[i].x + c_size_x <= 510 && enemy[i].y >= -600 && enemy[i].y < -230){
						enemy[i].x = 500 - c_size_x;
					}
					else if (enemy[i].x < 800 && enemy[i].x >= 790 && enemy[i].y >= -600 && enemy[i].y < -230){
						enemy[i].x = 800;
					}
					else if (enemy[i].x + c_size_x > 500 && enemy[i].x < 800 && enemy[i].y > -600 && enemy[i].y <= -230){
						enemy[i].y = -300;
						enemy[i].vy = 0;
						enemy[i].jump_s1_flag = false;
					}
					else{
						enemy[i].jump_s1_flag = true;
					}
				}

				//地上
				else if (enemy[i].kasoku < 100){
					if (enemy[i].x + c_size_x > 500 && enemy[i].x + c_size_x <= 510 && enemy[i].y >= -600 && enemy[i].y < -300){
						enemy[i].x = 500 - c_size_x;
						enemy[i].vy = 80;
						enemy[i].jump_flag = true;
					}
					if (enemy[i].x < 800 && enemy[i].x >= 790 && enemy[i].y >= -600 && enemy[i].y < -300){
						enemy[i].x = 800;
						enemy[i].vy = 80;
						enemy[i].jump_flag = true;
					}
				}
			}


			for (int i = 22; i < C; i++){
				if (enemy[i].jump_flag == true){
					if (enemy[i].x + c_size_x > 500 && enemy[i].x + c_size_x <= 510 && enemy[i].y >= -600 && enemy[i].y < -230){
						enemy[i].x = 500 - c_size_x;
					}
					else if (enemy[i].x < 800 && enemy[i].x >= 790 && enemy[i].y >= -600 && enemy[i].y < -230){
						enemy[i].x = 800;
					}
					else if (enemy[i].x + c_size_x > 500 && enemy[i].x < 800 && enemy[i].y > -600 && enemy[i].y <= -230){
						enemy[i].y = -300;
						enemy[i].vy = 0;
						enemy[i].jump_s1_flag = false;
					}
					else{
						enemy[i].jump_s1_flag = true;
					}
				}

				//地上
				else if (enemy[i].kasoku < 100){
					if (enemy[i].x + c_size_x > 500 && enemy[i].x + c_size_x <= 510 && enemy[i].y >= -600 && enemy[i].y < -300){
						enemy[i].x = 500 - c_size_x;
						enemy[i].jump_flag = true;
					}
					if (enemy[i].x < 800 && enemy[i].x >= 790 && enemy[i].y >= -600 && enemy[i].y < -300){
						enemy[i].x = 800;
						enemy[i].jump_flag = true;
					}
				}
			}


			if (enemy[51].jump_flag == true){
				if (enemy[51].x + c_size_x*3 > 500 && enemy[51].x + c_size_x*3 <= 510 && enemy[51].y >= -600 && enemy[51].y < -230){
					enemy[51].x = 500 - c_size_x*3;
				}
				else if (enemy[51].x < 800 && enemy[51].x >= 790 && enemy[51].y >= -600 && enemy[51].y < -230){
					enemy[51].x = 800;
				}
				else if (enemy[51].x + c_size_x * 3 > 500 && enemy[51].x < 800 && enemy[51].y > -600 && enemy[51].y <= -230){
					enemy[51].y = -300;
					enemy[51].vy = 0;
					enemy[51].jump_s1_flag = false;
				}
			}

			//地上
			else if (enemy[51].kasoku < 100){
				if (enemy[51].x + c_size_x*3 > 500 && enemy[51].x + c_size_x * 3 <= 515 && enemy[51].y >= -600 && enemy[51].y < -300){
					enemy[51].x = 500 - c_size_x * 3;
					enemy[51].jump_flag = true;
				}
				if (enemy[51].x < 800 && enemy[51].x >= 785 && enemy[51].y >= -600 && enemy[51].y < -300){
					enemy[51].x = 800;
					enemy[51].jump_flag = true;
				}
			}

			drawFillBox(-1500, -1000, 3000, 400, Color(zimen_R, zimen_G, zimen_B));
			drawFillBox(500, -600, 300, 300, Color(zimen_R, zimen_G, zimen_B));


			string kill = to_string(kill_count);
			font.draw("ころしたかず  " + kill, Vec2f(-1500, -800), Color::black);


			//リスタート処理
			if (env.isPushKey(GLFW_KEY_ESCAPE)){
				gamen = 0;
			}
			if (env.isPushKey('C')){
				gamen = 2;
			}
			if (env.isPushKey('Y')){
				gamen = 3;
			}
			env.end();
		}

		env.flushInput();
		int count = 0;
		while (gamen == 3){
			env.begin();

			if (!env.isOpen()){ return 0; }


			font.size(250);
			font.draw("YOU DEAD", Vec2f(-1000, 0), Color::red);
			count = (count + 1) % 120;
			font.size(100);
			if (count < 30){
				font.draw("Press Enter", Vec2f(-1000, 500), Color::black);
			}
			else if (count < 60){
				font.draw("Press Enter．", Vec2f(-1000, 500), Color::black);
			}
			else if (count < 90){
				font.draw("Press Enter．．", Vec2f(-1000, 500), Color::black);
			}
			else if (count < 120){
				font.draw("Press Enter．．．", Vec2f(-1000, 500), Color::black);
			}
			if (env.isPushKey(GLFW_KEY_ENTER)){
				gamen = 0;
			}

			if (env.isPushKey(GLFW_KEY_ESCAPE)){
				gamen = 0;
			}

			env.end();
		}

		int k = 0;
		int t = 0;
		env.flushInput();
		while (gamen == 2){
			env.begin();
			if (!env.isOpen()){ return 0; }
			

           k = (t++ / 10) % 3;

			drawTextureBox(title_x, title_y,
					title_ax, title_ay,
					0, 0,
					title_ax, title_ay,
					clear[k], Color::white);
	
			count = (count + 1) % 120;
			font.size(100);
			if (count < 30){
				font.draw("Press Enter", Vec2f(-1500, -1000), Color::black);
			}
			else if (count < 60){
				font.draw("Press Enter．", Vec2f(-1500, -1000), Color::black);
			}
			else if (count < 90){
				font.draw("Press Enter．．", Vec2f(-1500, -1000), Color::black);
			}
			else if (count < 120){
				font.draw("Press Enter．．．", Vec2f(-1500, -1000), Color::black);
			}

			if (env.isPushKey(GLFW_KEY_ENTER)){
				gamen = 0;
			}


			env.end();
		}


		env.flushInput();


		env.end();
	}

}


