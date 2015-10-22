#pragma once
#include "lib/framework.hpp"
#include "Constant.h"
#include "Screen.h"
#include "Struct.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

enum MapType{
	MAP_TYPE_TUTORIAL,
	MAP_TYPE_STARTMAP,				//最初の町
	MAP_TYPE_ROCK1,
	MAP_TYPE_ROCK2,
	MAP_TYPE_GRASS1,
	MAP_TYPE_GRASS2,


	MAP_TEXT_MAX,					//マップの最大数
};

enum MapImage{						// ブロックの画像

	LADDER_image,					//はしご
	LADDER_TOP_image,				//はしごの一番上
	GATE_image,
	BLOCK_KANE,
	FONT_BACK,
	FONT_GRASS1,
	FONT_GRASS2,
	FONT_ROCK1,
	FONT_ROCK2,




	IMAGE_MAX, //画像の最大数
};

struct MapData{					//マップの情報
	Vec2f pos;					//ブロックの開始位置
	Vec2f size;					//ブロックのサイズ
	Vec2f cut_pos;				//ブロックの切り取り開始位置
	Vec2f cut_size;				//ブロックの切り取りサイズ
	char id;					//マップのテキストデータを代入するやつ

	int map_area;				//今どこのエリアにいるか
	bool start_flag;			//プレイヤーの開始位置一度だけ読み込み
	int time;
	int time2;
};

enum BlockNumber{				//ブロックの数
	LENGTH = 20,				//ブロックの数縦20個
	WIDE = 50,					//ブロックの数横50個
};

enum BlockCategory{
	AIR_BLOCK = '0',				//何もないブロック
	FLOOR_BLOCK_TOP = '1',			//上の当り判定をを持ったブロック
	FLOOR_BLOCK_LR = '2',			//右の当り判定を持ったブロック
	FLOOR_BLOCK_LEFT = '3',			//左の当り判定を持ったブロック
	FLOOR_BLOCK_CEILIlNG = '4',		//天井のブロック
	LADDER = '5',					//はしごブロック
	LADDER_TOP = '6',				//はしごの上判定を持ったブロック

	PLAYER_START_POS = '8',			//プレイヤー開始位置
	BACK_BLOCK = 'b',				//最初のステージに戻るブロック
	START_MAP = 'S',
	STAGE_ROCK1 = 'Q',				//ステージ1-1
	STAGE_ROCK2 = 'W',
	STAGE_GRASS1 = 'Z',
	STAGE_GRASS2 = 'X',
	ENEMY_01 = 'D',
	ENEMY_02 = 'C',

	STATUS_CHANGE = 'M',
};

void mapAdjust();

void mapTypeInit();

void mapImageInit();

void mapChipDraw(Player player,int mappattern, std::string& now_area);

void mapCollision(Player& player, Sword sword, int& scene, Textures& tx);

void mapCollision_enemy(Enemy& enemy, Player player, Sword sword, int pop_num, int pattern);

void boss_mapCollision_enemy(Enemy& enemy, Player player, Sword sword, int pop_num, int pattern);

Vec2f enemyStartInit(int pop_num,int pattern);

Vec2f boss_enemyStartInit(int pop_num, int pattern);