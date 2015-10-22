#include "Map.h"


std::ifstream* map_type_list[MAP_TEXT_MAX]; //テキストからマップ情報を取得
Texture* texture_list[IMAGE_MAX]; //画像データを配列で用意
std::vector <std::vector< MapData >> map(LENGTH, std::vector<MapData>(WIDE));
mapAnimation map_anime;


//四角と四角の当たり判定
bool boxCollision(Vec2f box_pos, Vec2f box_size, Vec2f box1_pos, Vec2f box1_size) {

	return (
		box_pos.x() < box1_pos.x() + box1_size.x() &&
		box_pos.x() + box_size.x() > box1_pos.x() &&
		box_pos.y() < box1_pos.y() + box1_size.y() &&
		box_pos.y() + box_size.y() > box1_pos.y());
}

//四角と四角の地面操作判定
bool boxFloorCollision(Vec2f box_pos, Vec2f box_size, Vec2f box1_pos, Vec2f box1_size) {

	return (
		box_pos.x() < box1_pos.x() + box1_size.x() &&
		box_pos.x() + box_size.x() > box1_pos.x() &&
		box_pos.y() - 5 < box1_pos.y() + box1_size.y() &&
		box_pos.y() > box1_pos.y());
}

//四角と四角の地面操作判定
bool enemyboxFloorCollision(Vec2f box_pos, Vec2f box_size, Vec2f box1_pos, Vec2f box1_size) {

	return (
		box_pos.x() < box1_pos.x() + box1_size.x() &&
		box_pos.x() + box_size.x() > box1_pos.x() &&
		box_pos.y() - 50 < box1_pos.y() + box1_size.y() &&
		box_pos.y() > box1_pos.y());
}

//点と四角の当り判定
bool pointCollision(Vec2f pos, Vec2f size, Vec2f box_pos, Vec2f box_size){

	Vec2f center_pos = Vec2f(pos.x() + size.x() / 2, pos.y() + size.y() / 2);

	return (
		center_pos.x() > box_pos.x() &&
		center_pos.x() < box_pos.x() + box_size.x() &&
		center_pos.y() > box_pos.y() &&
		center_pos.y() < box_pos.y() + box_size.y());

}


//GATEアニメーション
//struct&   動く物体の構造体
//count     使いたい枚数
//frame     何フレームでアニメーションするか
//num		何番目からアニメーションするか
void gate_animation(mapAnimation& map, int count, int change_frame, int num){
	map.time = (map.time2++ / change_frame) % count + num;

	map.cut_pos.x() = (map.time % 4) * map.cut_size.x();
	map.cut_pos.y() = (map.time / 8) * map.cut_size.y();
}

//*********************************************************************************************//
//敵の配置//	
//*********************************************************************************************//
Vec2f enemyStartInit(int pop_num, int pattern){
	int index = 0;
	switch (pattern){ //何のマップか
	case MAP_TYPE_TUTORIAL:	// ステージ1－1
		for (int y = 0; y < LENGTH; y++){
			for (int x = 0; x < WIDE; x++){
				*map_type_list[MAP_TYPE_TUTORIAL] >> map[y][x].id; //テキスト情報を代入
				switch (map[y][x].id){
				case ENEMY_01:
					if (pop_num == index++){
						return Vec2f(map[y][x].pos.x(), map[y][x].pos.y() + 10);
					}
					break;
				case ENEMY_02:
					break;
				}
			}
		}
		break;
	case MAP_TYPE_STARTMAP: //始まりの町
		for (int y = 0; y < LENGTH; y++){
			for (int x = 0; x < WIDE; x++){
				*map_type_list[MAP_TYPE_STARTMAP] >> map[y][x].id; //テキスト情報を代入
				switch (map[y][x].id){
				case ENEMY_01:
					if (pop_num == index++){
						return Vec2f(map[y][x].pos.x(), map[y][x].pos.y() + 10);
					}
					break;
				case ENEMY_02:
					break;
				}
			}
		}
		break;
	case MAP_TYPE_ROCK1:
		for (int y = 0; y < LENGTH; y++){
			for (int x = 0; x < WIDE; x++){
				*map_type_list[MAP_TYPE_ROCK1] >> map[y][x].id; //テキスト情報を代入
				switch (map[y][x].id){
				case ENEMY_01:
					if (pop_num == index++){
						return Vec2f(map[y][x].pos.x(), map[y][x].pos.y() + 10);
					}
					break;
				case ENEMY_02:
					break;
				}
			}
		}
		break;
	case MAP_TYPE_ROCK2:
		for (int y = 0; y < LENGTH; y++){
			for (int x = 0; x < WIDE; x++){
				*map_type_list[MAP_TYPE_ROCK2] >> map[y][x].id; //テキスト情報を代入
				switch (map[y][x].id){
				case ENEMY_01:
					if (pop_num == index++){
						return Vec2f(map[y][x].pos.x(), map[y][x].pos.y() + 10);
					}
					break;
				case ENEMY_02:
					break;
				}
			}
		}
		break;
	case MAP_TYPE_GRASS1:
		for (int y = 0; y < LENGTH; y++){
			for (int x = 0; x < WIDE; x++){
				*map_type_list[MAP_TYPE_GRASS1] >> map[y][x].id; //テキスト情報を代入
				switch (map[y][x].id){
				case ENEMY_01:
					if (pop_num == index++){
						return Vec2f(map[y][x].pos.x(), map[y][x].pos.y() + 10);
					}
					break;
				case ENEMY_02:
					break;
				}
			}
		}
		break;
	case MAP_TYPE_GRASS2:
		for (int y = 0; y < LENGTH; y++){
			for (int x = 0; x < WIDE; x++){
				*map_type_list[MAP_TYPE_GRASS2] >> map[y][x].id; //テキスト情報を代入
				switch (map[y][x].id){
				case ENEMY_01:
					if (pop_num == index++){
						return Vec2f(map[y][x].pos.x(), map[y][x].pos.y() + 10);
					}
					break;
				case ENEMY_02:
					break;
				}
			}
		}
		break;
	}
}

Vec2f boss_enemyStartInit(int pop_num, int pattern){
	int index = 0;
	switch (pattern){ //何のマップか
	case MAP_TYPE_ROCK2:
		for (int y = 0; y < LENGTH; y++){
			for (int x = 0; x < WIDE; x++){
				*map_type_list[MAP_TYPE_ROCK2] >> map[y][x].id; //テキスト情報を代入
				switch (map[y][x].id){
				case ENEMY_02:
					if (pop_num == index++){
						return Vec2f(map[y][x].pos.x(), map[y][x].pos.y() + 10);
					}
					break;
				}
			}
		}
		break;
	default:
		break;
	}
}

//*********************************************************************************************//
//マップの座標初期化																		   //	
//*********************************************************************************************//
void mapAdjust(){ //マップの位置初期化

	map.resize(WIDE * 2);
	for (int i = 0; i < LENGTH; i++)
		map[i].resize(LENGTH * 2);

	map_anime.cut_pos = Vec2f(0, 0);
	map_anime.time = 0;
	map_anime.time2 = 0;
	for (int y = 0; y < LENGTH; y++){
		for (int x = 0; x < WIDE; x++){
			map[y][x].size = Vec2f(400, 400);
			map[y][x].pos.x() = -WIDTH / 2 + map[y][x].size.x() * x;
			map[y][x].pos.y() = HEIGHT*2.6 - map[y][x].size.y() * y - map[y][x].size.y();
			map[y][x].cut_pos = Vec2f(0, 0);
			map[y][x].cut_size = Vec2f(256, 256);
		}
	}
}

//*********************************************************************************************//
//マップのテキストデータ初期化																   //	
//*********************************************************************************************//
void mapTypeInit(){ //マップ初期化

	const char* text_name[MAP_TEXT_MAX]{
		"res/MapList/tutorial.txt",
			"res/MapList/maptype_01.txt",
			"res/MapList/stage_rock1-1.txt",
			"res/MapList/stage_rock1-2.txt",
			"res/MapList/stage_grass1-1.txt",
			"res/MapList/stage_grass1-2.txt",




	};

	for (int index = 0; index < MAP_TEXT_MAX; index++){
		map_type_list[index] = new std::ifstream(text_name[index]);
	}


}

//*********************************************************************************************//
//マップの画像初期化																	   //	
//*********************************************************************************************//
void mapImageInit() // ブロックの画像初期化
{
	const char* texture_name[IMAGE_MAX]{
		"res/Image/Field/ladder.png",
			"res/Image/Field/ladder_top.png",
			"res/Image/Field/gate.png",
			"res/Image/Field/block.png",
			"res/Image/Field/font_back.png",
			"res/Image/Field/font_grass1.png",
			"res/Image/Field/font_grass2.png",
			"res/Image/Field/font_rock1.png",
			"res/Image/Field/font_rock2.png",



	};

	for (int index = 0; index < IMAGE_MAX; index++){
		texture_list[index] = new Texture(texture_name[index]);

	}

}

//*********************************************************************************************//
//マップの画像＆敵の表示																	   //	
//*********************************************************************************************//
void mapChipDraw(Player player, int mappattern, std::string& now_area){ //マップの描画


	gate_animation(map_anime, 30, 3, 0);
	switch (mappattern){ //何のマップか
	case MAP_TYPE_STARTMAP: //始まりの町
		now_area = "きょてん";
		for (int y = 0; y < LENGTH; y++){
			for (int x = 0; x < WIDE; x++){

				*map_type_list[MAP_TYPE_STARTMAP] >> map[y][x].id; //テキスト情報を代入

				if (map[y][x].pos.x() >= -WIDTH / 2 - 500 && map[y][x].pos.x() <= WIDTH / 2 + 500
					&& map[y][x].pos.y() >= -HEIGHT / 2 - 500 && map[y][x].pos.y() <= HEIGHT / 2 + 500){


					switch (map[y][x].id){
					case AIR_BLOCK:
						break;
					case FLOOR_BLOCK_TOP:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   64, 63,
									   *texture_list[BLOCK_KANE], Color::red,
									   0, Vec2f(1.1, 1.12), Vec2f(0, 0));
						break;
					case FLOOR_BLOCK_LR:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   64, 63,
									   *texture_list[BLOCK_KANE], Color::red,
									   0, Vec2f(1.1, 1.12), Vec2f(0, 0));
						break;
					case FLOOR_BLOCK_LEFT:
						break;
					case FLOOR_BLOCK_CEILIlNG:
						break;
					case LADDER:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   128, 128,
									   *texture_list[LADDER_image], Color::white);
						break;
					case LADDER_TOP:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y() + map[y][x].size.y(),
									   0, 0,
									   128, 256,
									   *texture_list[LADDER_TOP_image], Color::white);
						break;
					case PLAYER_START_POS:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::yellow);
						break;
					case BACK_BLOCK:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::white);
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_BACK], Color::white);
						break;
					case STAGE_ROCK1:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], color256(128, 0, 0));

						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_ROCK1], Color::white);

						break;
					case STAGE_ROCK2:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], color256(128, 0, 0));
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_ROCK2], Color::white);
						break;
					case STAGE_GRASS1:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::green);
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_GRASS1], Color::white);
						break;
					case STAGE_GRASS2:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::green);
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_GRASS2], Color::white);
						break;
					case STATUS_CHANGE:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::cyan);
						break;
					}
				}
			}
		}
		break;

	case MAP_TYPE_TUTORIAL:

		now_area = "くんれんじょ";// ステージ1－1

		for (int y = 0; y < LENGTH; y++){
			for (int x = 0; x < WIDE; x++){
				*map_type_list[MAP_TYPE_TUTORIAL] >> map[y][x].id; //テキスト情報を代入
				if (map[y][x].pos.x() >= -WIDTH / 2 - 500 && map[y][x].pos.x() <= WIDTH / 2 + 500
					&& map[y][x].pos.y() >= -HEIGHT / 2 - 500 && map[y][x].pos.y() <= HEIGHT / 2 + 500){

					switch (map[y][x].id){
					case AIR_BLOCK:
						break;
					case FLOOR_BLOCK_TOP:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   64, 63,
									   *texture_list[BLOCK_KANE], Color::red,
									   0, Vec2f(1.1, 1.12), Vec2f(0, 0));
						break;
					case FLOOR_BLOCK_LR:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   64, 63,
									   *texture_list[BLOCK_KANE], Color::red,
									   0, Vec2f(1.1, 1.12), Vec2f(0, 0));

						break;
					case FLOOR_BLOCK_LEFT:
						break;
					case FLOOR_BLOCK_CEILIlNG:
						break;
					case LADDER:
						drawTextureBox(
							map[y][x].pos.x(), map[y][x].pos.y(),
							map[y][x].size.x(), map[y][x].size.y(),
							0, 0,
							128, 128,
							*texture_list[LADDER_image], Color::white);

						break;
					case LADDER_TOP:
						drawTextureBox(
							map[y][x].pos.x(), map[y][x].pos.y(),
							map[y][x].size.x(), map[y][x].size.y() + map[y][x].size.y(),
							0, 0,
							128, 256,
							*texture_list[LADDER_TOP_image], Color::white);

						break;
					case BACK_BLOCK:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::green);
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_BACK], Color::white);
						break;
					case PLAYER_START_POS:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::yellow);
						break;
					case START_MAP:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::white);
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_BACK], Color::white);
						break;
					case STAGE_ROCK1:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::green);
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_ROCK1], Color::white);
						break;
					case STAGE_ROCK2:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], color256(128, 0, 0));
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_ROCK2], Color::white);
						break;
					case STAGE_GRASS1:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::green);
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_GRASS1], Color::white);
						break;
					case STAGE_GRASS2:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::green);
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_GRASS2], Color::white);
						break;
					case STATUS_CHANGE:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::cyan);
						break;
					}
				}
			}
		}
		break;
	case MAP_TYPE_ROCK1:
		now_area = "岩　山　１";// ステージ1－1
		for (int y = 0; y < LENGTH; y++){
			for (int x = 0; x < WIDE; x++){
				*map_type_list[MAP_TYPE_ROCK1] >> map[y][x].id; //テキスト情報を代入
				if (map[y][x].pos.x() >= -WIDTH / 2 - 500 && map[y][x].pos.x() <= WIDTH / 2 + 500
					&& map[y][x].pos.y() >= -HEIGHT / 2 - 500 && map[y][x].pos.y() <= HEIGHT / 2 + 500){

					switch (map[y][x].id){
					case AIR_BLOCK:
						break;
					case FLOOR_BLOCK_TOP:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   64, 63,
									   *texture_list[BLOCK_KANE], Color::red,
									   0, Vec2f(1.1, 1.12), Vec2f(0, 0));
						break;
					case FLOOR_BLOCK_LR:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   64, 63,
									   *texture_list[BLOCK_KANE], Color::red,
									   0, Vec2f(1.1, 1.12), Vec2f(0, 0));
						break;
					case FLOOR_BLOCK_LEFT:
						break;
					case FLOOR_BLOCK_CEILIlNG:
						break;
					case LADDER:
						drawTextureBox(
							map[y][x].pos.x(), map[y][x].pos.y(),
							map[y][x].size.x(), map[y][x].size.y(),
							0, 0,
							128, 128,
							*texture_list[LADDER_image], Color::white);
						break;
					case LADDER_TOP:
						drawTextureBox(
							map[y][x].pos.x(), map[y][x].pos.y(),
							map[y][x].size.x(), map[y][x].size.y() + map[y][x].size.y(),
							0, 0,
							128, 256,
							*texture_list[LADDER_TOP_image], Color::white);
						break;
					case BACK_BLOCK:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::white);
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_BACK], Color::white);
						break;
					case PLAYER_START_POS:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::yellow);
						break;
					case STAGE_ROCK1:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], color256(128, 0, 0));
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_ROCK1], Color::white);
						break;
					case STAGE_ROCK2:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], color256(128, 0, 0));
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_ROCK2], Color::white);
						break;
					case STAGE_GRASS1:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::green);
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_GRASS1], Color::white);
						break;
					case STAGE_GRASS2:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::green);
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_GRASS2], Color::white);
						break;
					case STATUS_CHANGE:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::cyan);
						break;
					}
				}
			}
		}
		break;
	case MAP_TYPE_ROCK2:
		now_area = "岩　山　２";// ステージ1－1
		for (int y = 0; y < LENGTH; y++){
			for (int x = 0; x < WIDE; x++){
				*map_type_list[MAP_TYPE_ROCK2] >> map[y][x].id; //テキスト情報を代入
				if (map[y][x].pos.x() >= -WIDTH / 2 - 500 && map[y][x].pos.x() <= WIDTH / 2 + 500
					&& map[y][x].pos.y() >= -HEIGHT / 2 - 500 && map[y][x].pos.y() <= HEIGHT / 2 + 500){

					switch (map[y][x].id){
					case AIR_BLOCK:
						break;
					case FLOOR_BLOCK_TOP:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   64, 63,
									   *texture_list[BLOCK_KANE], Color::red,
									   0, Vec2f(1.1, 1.12), Vec2f(0, 0));
						break;
					case FLOOR_BLOCK_LR:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   64, 63,
									   *texture_list[BLOCK_KANE], Color::red,
									   0, Vec2f(1.1, 1.12), Vec2f(0, 0));
						break;
					case FLOOR_BLOCK_LEFT:
						break;
					case FLOOR_BLOCK_CEILIlNG:
						break;
					case LADDER:
						drawTextureBox(
							map[y][x].pos.x(), map[y][x].pos.y(),
							map[y][x].size.x(), map[y][x].size.y(),
							0, 0,
							128, 128,
							*texture_list[LADDER_image], Color::white);
						break;
					case LADDER_TOP:
						drawTextureBox(
							map[y][x].pos.x(), map[y][x].pos.y(),
							map[y][x].size.x(), map[y][x].size.y() + map[y][x].size.y(),
							0, 0,
							128, 256,
							*texture_list[LADDER_TOP_image], Color::white);
						break;
					case BACK_BLOCK:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::white);
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_BACK], Color::white);
						break;
					case PLAYER_START_POS:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::yellow);
						break;
					case STAGE_ROCK1:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], color256(128, 0, 0));
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_ROCK1], Color::white);
						break;
					case STAGE_ROCK2:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], color256(128, 0, 0));
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_ROCK2], Color::white);
						break;
					case STAGE_GRASS1:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::green);
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_GRASS1], Color::white);
						break;
					case STAGE_GRASS2:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::green);
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_GRASS2], Color::white);
						break;
					case STATUS_CHANGE:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::cyan);
						break;
					}
				}
			}
		}
		break;
	case MAP_TYPE_GRASS1: //始まりの町
		now_area = "草　原　１";
		for (int y = 0; y < LENGTH; y++){
			for (int x = 0; x < WIDE; x++){
				*map_type_list[MAP_TYPE_GRASS1] >> map[y][x].id; //テキスト情報を代入
				if (map[y][x].pos.x() >= -WIDTH / 2 - 500 && map[y][x].pos.x() <= WIDTH / 2 + 500
					&& map[y][x].pos.y() >= -HEIGHT / 2 - 500 && map[y][x].pos.y() <= HEIGHT / 2 + 500){

					switch (map[y][x].id){
					case AIR_BLOCK:
						break;
					case FLOOR_BLOCK_TOP:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   64, 63,
									   *texture_list[BLOCK_KANE], Color::red,
									   0, Vec2f(1.1, 1.12), Vec2f(0, 0));
						break;
					case FLOOR_BLOCK_LR:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   64, 63,
									   *texture_list[BLOCK_KANE], Color::red,
									   0, Vec2f(1.1, 1.12), Vec2f(0, 0));
						break;
					case FLOOR_BLOCK_LEFT:
						break;
					case FLOOR_BLOCK_CEILIlNG:
						break;
					case LADDER:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   128, 128,
									   *texture_list[LADDER_image], Color::white);
						break;
					case LADDER_TOP:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y() + map[y][x].size.y(),
									   0, 0,
									   128, 256,
									   *texture_list[LADDER_TOP_image], Color::white);
						break;
					case PLAYER_START_POS:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::yellow);
						break;
					case BACK_BLOCK:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::white);
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_BACK], Color::white);
						break;
					case STAGE_ROCK1:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], color256(128, 0, 0));

						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_ROCK1], Color::white);

						break;
					case STAGE_ROCK2:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], color256(128, 0, 0));
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_ROCK2], Color::white);
						break;
					case STAGE_GRASS1:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::green);
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_GRASS1], Color::white);
						break;
					case STAGE_GRASS2:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::green);
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_GRASS2], Color::white);
						break;
					case STATUS_CHANGE:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::cyan);
						break;
					}
				}
			}
		}
		break;
	case MAP_TYPE_GRASS2: //始まりの町
		now_area = "草　原　2";
		for (int y = 0; y < LENGTH; y++){
			for (int x = 0; x < WIDE; x++){
				*map_type_list[MAP_TYPE_GRASS2] >> map[y][x].id; //テキスト情報を代入

				if (map[y][x].pos.x() >= -WIDTH / 2 - 500 && map[y][x].pos.x() <= WIDTH / 2 + 500
					&& map[y][x].pos.y() >= -HEIGHT / 2 - 500 && map[y][x].pos.y() <= HEIGHT / 2 + 500){

					switch (map[y][x].id){
					case AIR_BLOCK:
						break;
					case FLOOR_BLOCK_TOP:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   64, 63,
									   *texture_list[BLOCK_KANE], Color::red,
									   0, Vec2f(1.1, 1.12), Vec2f(0, 0));
						break;
					case FLOOR_BLOCK_LR:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   64, 63,
									   *texture_list[BLOCK_KANE], Color::red,
									   0, Vec2f(1.1, 1.12), Vec2f(0, 0));
						break;
					case FLOOR_BLOCK_LEFT:
						break;
					case FLOOR_BLOCK_CEILIlNG:
						break;
					case LADDER:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   128, 128,
									   *texture_list[LADDER_image], Color::white);
						break;
					case LADDER_TOP:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y() + map[y][x].size.y(),
									   0, 0,
									   128, 256,
									   *texture_list[LADDER_TOP_image], Color::white);
						break;
					case PLAYER_START_POS:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::yellow);
						break;
					case BACK_BLOCK:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::white);
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_BACK], Color::white);
						break;
					case STAGE_ROCK1:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], color256(128, 0, 0));

						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_ROCK1], Color::white);

						break;
					case STAGE_ROCK2:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], color256(128, 0, 0));
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_ROCK2], Color::white);
						break;
					case STAGE_GRASS1:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::green);
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_GRASS1], Color::white);
						break;
					case STAGE_GRASS2:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::green);
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y() + 80,
									   map[y][x].size.x(), map[y][x].size.y(),
									   0, 0,
									   256, 256,
									   *texture_list[FONT_GRASS2], Color::white);
						break;
					case STATUS_CHANGE:
						drawTextureBox(map[y][x].pos.x(), map[y][x].pos.y(),
									   map[y][x].size.x(), map[y][x].size.y(),
									   map_anime.cut_pos.x(), map_anime.cut_pos.y(),
									   map[y][x].cut_size.x(), map[y][x].cut_size.y(),
									   *texture_list[GATE_image], Color::cyan);
						break;
					}

				}
			}
		}
		break;

	}
}

//*********************************************************************************************//
//マップの当り判定																			   //	
//*********************************************************************************************//
void mapCollision(Player& player, Sword sword, int& scene, Textures& tx){

	for (int y = 0; y < LENGTH; y++){
		for (int x = 0; x < WIDE; x++){


			//地面の種類を識別
			if (boxFloorCollision(player.pos, player.size, map[y][x].pos, map[y][x].size)){
				if (player.is_hitfloor == false){
					if (map[y][x].id == AIR_BLOCK || map[y][x].id == PLAYER_START_POS){
						player.is_move = STOP;
						player.is_gravity = MOVE;
					}
				}
				if (map[y][x].id == FLOOR_BLOCK_TOP){
					player.is_gravity = STOP;
					player.pos.y() = map[y][x].pos.y() + map[y][x].size.y();
					if (player.nockback_flag == false){
						if (sword.attack_start == false){
							player.is_move = MOVE;
						}
					}
					//player.is_ladder_top = true;
					player.is_hitfloor = true;
					//player.change_ladder_top = true;
				}
				else{
					player.is_hitfloor = false;
				}
				if (player.change_ladder_top == true){
					if (map[y][x].id == LADDER_TOP){
						player.is_gravity = STOP;
						player.pos.y() = map[y][x].pos.y() + map[y][x].size.y();
						if (player.nockback_flag == false){
							if (sword.attack_start == false){
								player.is_move = MOVE;
							}
						}
						if (player.rolling_flag == STOP){
							if (env.isPushKey('L')){
								player.ladder_down_flag = true;
								player.change_ladder_top = false;
								player.pos.x() = map[y][x].pos.x() + 100;
								player.time2 = 0;
							}
						}
					}
				}
			}
			map[y][x].pos.y() -= player.camera.y();

			if (player.ladder_flag == true){	//はしご登り始めたら判定
				map[y][x].pos.y() -= player.move_speed;
				player.is_gravity = STOP;
				player.is_move = STOP;
				player.type = LADDER_CLIMB;
				player.is_invin = true;
			}

		}
	}
	for (int y = 0; y < LENGTH; y++){
		for (int x = 0; x < WIDE; x++){


			//プレイヤーposの移動範囲外に出た処理
			if (player.stop_camera_x == MOVE){

				if (player.rolling_flag == STOP){

					if (env.isPressKey('D')){

						if (player.ladder_flag == false){
							player.type = RUN;
						}

						if (player.is_move == MOVE){
							map[y][x].pos.x() -= player.move_speed;
							player.direction = CharaInfo::RIGHT;
						}
					}

					if (env.isPressKey('A')){

						if (player.ladder_flag == false){
							player.type = RUN;
						}

						if (player.is_move == MOVE){
							map[y][x].pos.x() += player.move_speed;
							player.direction = CharaInfo::LEFT;
						}
					}
				}
			}
			if (player.direction == CharaInfo::RIGHT){
				map[y][x].pos.x() += player.camera_centering * (-player.centeriing_pos * 2 - player.pos.x());
				map[y][x].pos.y() += player.camera_centering * (-500 - player.pos.y());
			}

			if (player.direction == CharaInfo::LEFT){
				map[y][x].pos.x() += player.camera_centering * (player.centeriing_pos - player.pos.x());
				map[y][x].pos.y() += player.camera_centering * (-500 - player.pos.y());
			}
		}
	}



	for (int y = 0; y < LENGTH; y++)
	{
		for (int x = 0; x < WIDE; x++){

			// マップごとの当り判定や、ギミックの処理
			switch (map[y][x].id){
			case AIR_BLOCK:
				if (pointCollision(Vec2f(player.pos.x() + 10, player.pos.y()), player.size, Vec2f(map[y][x].pos.x(), map[y][x].pos.y() + 220), Vec2f(map[y][x].size.x() - 20, map[y][x].size.y()))){
					player.ladder_flag = false;
				}
				break;
			case FLOOR_BLOCK_TOP:

				break;
			case FLOOR_BLOCK_LR:
				if (boxCollision(player.pos, player.size, map[y][x].pos, Vec2f(map[y][x].size.x() / 2, map[y][x].size.y()))){
					player.vector.x() = 0;
					player.camera.x() = 0;
					player.pos.x() = map[y][x].pos.x() - player.size.x();
				}
				if (boxCollision(player.pos, player.size, Vec2f(map[y][x].pos.x() + map[y][x].size.x() / 2, map[y][x].pos.y()), Vec2f(map[y][x].size.x() / 2, map[y][x].size.y()))){
					player.vector.x() = 0;
					player.camera.x() = 0;
					player.pos.x() = map[y][x].pos.x() + map[y][x].size.x();
				}
				break;
			case FLOOR_BLOCK_LEFT:
				break;
			case FLOOR_BLOCK_CEILIlNG:
				break;
			case LADDER:
				if (pointCollision(player.pos, player.size, map[y][x].pos, map[y][x].size)){
					if (player.is_move == MOVE){
						if (player.rolling_flag == STOP){
							if (env.isPressKey('L')){
								player.ladder_flag = true;
								player.change_ladder_top = false;
								player.pos.x() = map[y][x].pos.x() + 100;
								player.is_move = STOP;
							}
						}
					}
				}
				break;
			case LADDER_TOP:
				if (player.change_ladder_top == false){
					if (pointCollision(player.pos, player.size, map[y][x].pos, Vec2f(map[y][x].size.x(), map[y][x].size.y() - 50))){
						if (player.ladder_flag == true){
							player.is_ladder_top = true;
						}
					}
				}
				break;
			case PLAYER_START_POS:
				if (player.start_flag == false){
					tx.warp.pitch(3.0f);
					tx.warp.play();
					player.pos.x() = map[y][x].pos.x();
					player.pos.y() = map[y][x].pos.y() + 10;
					tx.higurasi.play();
					player.start_flag = true;
				}
				break;
			case BACK_BLOCK:
				if (pointCollision(player.pos, player.size, map[y][x].pos, map[y][x].size)){
					if (env.isPushKey(GLFW_KEY_ENTER)){
						if (player.type == 0){
							player.stage_serect = MAP_TYPE_STARTMAP;
							player.start_flag = false;
						}
					}
				}
				break;
			case STAGE_ROCK1:
				if (pointCollision(player.pos, player.size, map[y][x].pos, map[y][x].size)){
					if (env.isPushKey(GLFW_KEY_ENTER)){
						if (player.type == 0){
							player.stage_serect = MAP_TYPE_ROCK1;
							player.start_flag = false;

						}
					}
				}
				break;
			case STAGE_ROCK2:
				if (pointCollision(player.pos, player.size, map[y][x].pos, map[y][x].size)){
					if (env.isPushKey(GLFW_KEY_ENTER)){
						if (player.type == 0){
							player.stage_serect = MAP_TYPE_ROCK2;
							player.start_flag = false;

						}
					}
				}
				break;
			case STAGE_GRASS1:
				if (pointCollision(player.pos, player.size, map[y][x].pos, map[y][x].size)){
					if (env.isPushKey(GLFW_KEY_ENTER)){
						if (player.type == 0){
							player.stage_serect = MAP_TYPE_GRASS1;
							player.start_flag = false;

						}
					}
				}
				break;
			case STAGE_GRASS2:
				if (pointCollision(player.pos, player.size, map[y][x].pos, map[y][x].size)){
					if (env.isPushKey(GLFW_KEY_ENTER)){
						if (player.type == 0){
							player.stage_serect = MAP_TYPE_GRASS2;
							player.start_flag = false;

						}
					}
				}
				break;
			case START_MAP:
				if (pointCollision(player.pos, player.size, map[y][x].pos, map[y][x].size)){
					if (env.isPushKey(GLFW_KEY_ENTER)){
						if (player.type == 0){
							player.stage_serect = MAP_TYPE_STARTMAP;
							player.start_flag = false;

						}
					}
				}
				break;
			case STATUS_CHANGE:
				if (pointCollision(player.pos, player.size, map[y][x].pos, map[y][x].size)){
					if (env.isPushKey(GLFW_KEY_ENTER)){
						if (player.type == 0){
							scene = SHOP;
							env.flushInput();
						}
					}
				}
				break;
			}
		}
	}
}

//*********************************************************************************************//
//マップの当り判定_敵																			   //	
//*********************************************************************************************//
void mapCollision_enemy(Enemy& enemy, Player player, Sword sword, int pop_num, int pattern){
	for (int y = 0; y < LENGTH; y++){
		for (int x = 0; x < WIDE; x++){
			//地面の種類を識別
			if (enemyboxFloorCollision(enemy.pos, enemy.size, map[y][x].pos, map[y][x].size)){
				if (enemy.is_hitfloor == false){
					if (map[y][x].id == AIR_BLOCK){
						enemy.is_move = STOP;
						enemy.is_gravity = MOVE;
					}
				}
				if (map[y][x].id == FLOOR_BLOCK_TOP || map[y][x].id == LADDER_TOP){
					enemy.is_gravity = STOP;
					enemy.pos.y() = map[y][x].pos.y() + map[y][x].size.y();
					if (enemy.nockback_flag == false){
						if (sword.attack_start == false){
							enemy.is_move = MOVE;
						}
					}
					enemy.is_hitfloor = true;
				}
				else{
					enemy.is_hitfloor = false;
				}
			}
		}
	}
	for (int y = 0; y < LENGTH; y++){
		for (int x = 0; x < WIDE; x++){

			// マップごとの当り判定や、ギミックの処理
			switch (map[y][x].id){
			case AIR_BLOCK:
				break;
			case FLOOR_BLOCK_TOP:
				break;
			case FLOOR_BLOCK_LR:
				if (boxCollision(enemy.pos, enemy.size, map[y][x].pos, Vec2f(map[y][x].size.x() / 2, map[y][x].size.y()))){
					enemy.vector.x() = 0;
					enemy.camera.x() = 0;
					enemy.pos.x() = map[y][x].pos.x() - enemy.size.x();
				}
				if (boxCollision(enemy.pos, enemy.size, Vec2f(map[y][x].pos.x() + map[y][x].size.x() / 2, map[y][x].pos.y()), Vec2f(map[y][x].size.x() / 2, map[y][x].size.y()))){
					enemy.vector.x() = 0;
					enemy.camera.x() = 0;
					enemy.pos.x() = map[y][x].pos.x() + map[y][x].size.x();
				}
				break;

			case BACK_BLOCK:
				if (pointCollision(player.pos, player.size, map[y][x].pos, map[y][x].size)){
					if (env.isPushKey(GLFW_KEY_ENTER)){
						enemy.pos = enemyStartInit(pop_num, pattern);
					}
				}
				break;
			case STAGE_ROCK1:
				if (pointCollision(player.pos, player.size, map[y][x].pos, map[y][x].size)){
					if (env.isPushKey(GLFW_KEY_ENTER)){
						enemy.pos = enemyStartInit(pop_num, pattern);
					}
				}
				break;
			case STAGE_ROCK2:
				if (pointCollision(player.pos, player.size, map[y][x].pos, map[y][x].size)){
					if (env.isPushKey(GLFW_KEY_ENTER)){
						enemy.pos = enemyStartInit(pop_num, pattern);
					}
				}
				break;
			case STAGE_GRASS1:
				if (pointCollision(player.pos, player.size, map[y][x].pos, map[y][x].size)){
					if (env.isPushKey(GLFW_KEY_ENTER)){
						enemy.pos = enemyStartInit(pop_num, pattern);
					}
				}
				break;
			case STAGE_GRASS2:
				if (pointCollision(player.pos, player.size, map[y][x].pos, map[y][x].size)){
					if (env.isPushKey(GLFW_KEY_ENTER)){
						enemy.pos = enemyStartInit(pop_num, pattern);
					}
				}
				break;
			case START_MAP:
				if (pointCollision(player.pos, player.size, map[y][x].pos, map[y][x].size)){
					if (env.isPushKey(GLFW_KEY_ENTER)){
						enemy.pos = enemyStartInit(pop_num, pattern);
					}
				}
				break;
			}
		}
	}


	if (enemy.dead_trans >= 0){
		enemy.pos.y() += enemy.camera.y();
		if (player.ladder_flag == true){
			enemy.pos.y() -= player.move_speed;
		}
		if (player.is_move == MOVE){
			if (env.isPressKey('D')){
				if (player.is_hitfloor = true){
					if (player.stop_camera_x == MOVE){
						if (player.nockback_flag == false){
							if (player.rolling_flag == STOP){
								enemy.pos.x() -= player.move_speed;
							}
						}
					}
				}
			}
		}

		if (player.is_move == MOVE){
			if (env.isPressKey('A')){
				if (player.is_hitfloor = true){
					if (player.stop_camera_x == MOVE){
						if (player.nockback_flag == false){
							if (player.rolling_flag == STOP){
								enemy.pos.x() += player.move_speed;
							}
						}
					}
				}
			}
		}
		if (player.direction == CharaInfo::RIGHT){
			enemy.pos.x() += (player.camera_centering) * (-player.centeriing_pos * 2 - player.pos.x());
			enemy.pos.y() += (player.camera_centering) * (-500 - player.pos.y());
		}
		if (player.direction == CharaInfo::LEFT){
			enemy.pos.x() += (player.camera_centering) * (player.centeriing_pos - player.pos.x());
			enemy.pos.y() += (player.camera_centering) * (-500 - player.pos.y());
		}
	}
}

void boss_mapCollision_enemy(Enemy& enemy, Player player, Sword sword, int pop_num, int pattern){
	for (int y = 0; y < LENGTH; y++){
		for (int x = 0; x < WIDE; x++){
			//地面の種類を識別
			if (enemyboxFloorCollision(enemy.pos, enemy.size, map[y][x].pos, map[y][x].size)){
				if (enemy.is_hitfloor == false){
					if (map[y][x].id == AIR_BLOCK){
						enemy.is_move = STOP;
						enemy.is_gravity = MOVE;
					}
				}
				if (map[y][x].id == FLOOR_BLOCK_TOP || map[y][x].id == LADDER_TOP){
					enemy.is_gravity = STOP;
					enemy.pos.y() = map[y][x].pos.y() + map[y][x].size.y();
					if (enemy.nockback_flag == false){
						if (sword.attack_start == false){
							enemy.is_move = MOVE;
						}
					}
					enemy.is_hitfloor = true;
				}
				else{
					enemy.is_hitfloor = false;
				}
			}
		}
	}

	for (int y = 0; y < LENGTH; y++){
		for (int x = 0; x < WIDE; x++){

			// マップごとの当り判定や、ギミックの処理
			switch (map[y][x].id){
			case AIR_BLOCK:
				break;
			case FLOOR_BLOCK_TOP:
				break;
			case FLOOR_BLOCK_LR:
				if (boxCollision(enemy.pos, enemy.size, map[y][x].pos, Vec2f(map[y][x].size.x() / 2, map[y][x].size.y()))){
					enemy.vector.x() = 0;
					enemy.camera.x() = 0;
					enemy.pos.x() = map[y][x].pos.x() - enemy.size.x();
				}
				if (boxCollision(enemy.pos, enemy.size, Vec2f(map[y][x].pos.x() + map[y][x].size.x() / 2, map[y][x].pos.y()), Vec2f(map[y][x].size.x() / 2, map[y][x].size.y()))){
					enemy.vector.x() = 0;
					enemy.camera.x() = 0;
					enemy.pos.x() = map[y][x].pos.x() + map[y][x].size.x();
				}
				break;
			case STAGE_ROCK2:
				break;
			}
		}
	}

	if (enemy.dead_trans >= 0){
		enemy.pos.y() += enemy.camera.y();
		if (player.ladder_flag == true){
			enemy.pos.y() -= player.move_speed;
		}

		if (player.is_move == MOVE){
			if (env.isPressKey('D')){
				if (player.is_hitfloor = true){
					if (player.stop_camera_x == MOVE){
						if (player.nockback_flag == false){
							if (player.rolling_flag == STOP){
								enemy.pos.x() -= player.move_speed;
							}
						}

					}
				}
			}
		}
		if (player.is_move == MOVE){
			if (env.isPressKey('A')){
				if (player.is_hitfloor = true){
					if (player.stop_camera_x == MOVE){
						if (player.nockback_flag == false){
							if (player.rolling_flag == STOP){
								enemy.pos.x() += player.move_speed;
							}
						}
					}
				}
			}
		}

		if (player.direction == CharaInfo::RIGHT){
			enemy.pos.x() += (player.camera_centering) * (-player.centeriing_pos * 2 - player.pos.x());
			enemy.pos.y() += (player.camera_centering) * (-500 - player.pos.y());
		}
		if (player.direction == CharaInfo::LEFT){
			enemy.pos.x() += (player.camera_centering) * (player.centeriing_pos - player.pos.x());
			enemy.pos.y() += (player.camera_centering) * (-500 - player.pos.y());
		}
	}
}

