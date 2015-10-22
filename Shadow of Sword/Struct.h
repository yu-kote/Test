#pragma once
#include "lib/framework.hpp"
#include "Screen.h"



struct MovingObject{
	Vec2f pos;						//動くものの始点
	Vec2f size;						//動くもののサイズ
	Vec2f cut_pos;					//画像切り取り開始位置
	Vec2f cut_size;					//画像切り取りサイズ

	int direction;					//向き
	int is_exists;					//存在しているか
	const float gravity = -0.3f;		//動くものにかかる重力
	const float gravity_max = -2.0f;	//最大の重力
	int centering_size = -100;

	int type;

	int time;
	int time2;
	int angle;
	Vec2f zoom;
	Vec2f center;
	int attack_time;

	int index;



	Vec2f camera;					//一応カメラだけど、ベクトルみたいになっとる
	bool stop_camera_x;				//x軸カメラの動きを止める
	bool stop_camera_y;				//y軸カメラの動きを止める


	int move_speed = 13;			//プレイヤーの動く速度
	Vec2f vector;					//プレイヤーのベクトル
	bool is_invin;					//プレイヤーが無敵かどうか
	int invin_time;
	bool animation_reset;			//プレイヤーが防御しているかどうか
	bool is_attack;					//プレイヤーが攻撃しているかどうか

	bool start_flag;				//プレイヤーを初期位置にもどすフラグ
	bool is_move;					//プレイヤーを操作できるかどうか
	bool is_gravity;				//重力がかかっているかどうか

	bool is_hitfloor;				//地面に当たっているかどうか

	int rolling_count;				//ローリング時間
	bool rolling_flag;				//ローリングし始めるフラグ

	float camera_centering = 0.04;	//カメラセンタリングスピード
	int centeriing_pos = 200;

	float flashing;

	float HP = 100;
	float HP_max = 100;
	int HP_line = 500;
	int power = 21;
	bool nockback_flag;
	int nockback_time;
	int nockback;
	int hit_count;

	float dead_trans = 1;

	float money = 0;
	float max_money = 0;
	bool money_flag = false;

	bool se_flag = false;



	float hp_money = 0;
	float power_money = 0;

};

struct Animation{
	int num;
	int time;
};

struct Player : MovingObject {
	bool ladder_flag;				//はしご登りはじめるフラグ
	bool is_ladder_top;				//はしごを登っているかどうか
	int ladder_top_count;			//はしごてっぺんカウント
	bool change_ladder_top;			//はしごてっぺんの判定変化フラグ
	bool ladder_down_flag;			//はしごを下がるフラグ

	int stage_serect = 0;
	int p_HP_line;

	int start_count = -1;

	bool title_startflag = false;

	bool debug = false;
};

struct Enemy : MovingObject{
	float look_area;
	bool is_moving;
	int move_time;
	bool attack;
	bool rolling;
	bool run_right;
	bool run_left;
	int popnum;


	Animation enemy_attack_top_animation[9];
	Animation enemy_attack_middle_animation[4];
	Animation enemy_attack_under_animation[4];
};

struct Sword{
	bool attack_start;
	bool attack_flag_first;
	bool attack_flag_second;
	bool attack_flag_third;
	int attack_count;
	bool attack_is_hit;
	int attack_start_time1;
	int attack_start_time2;
	int attack_start_time3;
	int attack_end_time_top;
	int attack_end_time_middle;
	int attack_end_time_under;
	bool attack_is_dec;


	Vec2f pos;
	Vec2f size;
	Vec2f cut_size;
	Vec2f cut_pos;
	float angle;

	Vec2f zoom;

	float attack_power;
	int range;


	Vec2f hit_pos;
	Vec2f hit_range;

	int type;


	int time = 0;
	int time2 = 0;


};

struct Textures {
	Texture default_type;
	Texture run;
	Texture attack_top_right;
	Texture attack_top_left;
	Texture attack_middle_right;
	Texture attack_middle_left;
	Texture attack_under_right;
	Texture attack_under_left;
	Texture rolling_right;
	Texture rolling_left;
	Texture sword;
	Texture sword_kane;
	Texture sword_kane2;
	Texture sword_kane3;
	Texture sword_kane4;
	Texture sword_kane5;
	Texture sword_kane6;
	Texture sword_dai1;
	Texture sword_hyt;
	Texture sword_hyt2;
	Texture sword_hyt3;

	Texture sword_uthii;
	Texture ladder;
	Texture dead;
	Texture title;
	Texture start;
	Texture press;

	Font font = Font("res/KodomoRounded.otf");
	Media attack_sound;	//剣を振る音
	Media hit_sound;	//ヒット音
	Media tuto_sound;	//チュートリアル
	Media cursor;
	Media warp;
	Media buy;
	Media higurasi;
};

namespace CharaInfo{
	enum ObjectDirection{ //動くものの向き
		RIGHT, //右向き
		LEFT, //左向き
	};

	enum Objectexists{ //動くものが生きているかどうか
		DEAD, //死んでいる
		LIVE, //生きている
	};
}

enum Is_Stop{ //止まっているかどうか
	MOVE, //動いている
	STOP, // 止まっている
};

enum Chara_Type{
	DEFAULT,		//デフォルト立ち
	RUN,			//走っている
	ATTACK_TOP,		//一段階攻撃
	ATTACK_MIDDLE,	//二段階攻撃
	ATTACK_UNDER,	//三段階攻撃
	ROLLING,		//ローリング
	LADDER_CLIMB,	//登る
};

struct mapAnimation{
	Vec2f cut_pos;
	Vec2f cut_size = Vec2f(256, 256);
	int time;
	int time2;




};
