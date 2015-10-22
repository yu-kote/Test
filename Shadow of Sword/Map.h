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
	MAP_TYPE_STARTMAP,				//�ŏ��̒�
	MAP_TYPE_ROCK1,
	MAP_TYPE_ROCK2,
	MAP_TYPE_GRASS1,
	MAP_TYPE_GRASS2,


	MAP_TEXT_MAX,					//�}�b�v�̍ő吔
};

enum MapImage{						// �u���b�N�̉摜

	LADDER_image,					//�͂���
	LADDER_TOP_image,				//�͂����̈�ԏ�
	GATE_image,
	BLOCK_KANE,
	FONT_BACK,
	FONT_GRASS1,
	FONT_GRASS2,
	FONT_ROCK1,
	FONT_ROCK2,




	IMAGE_MAX, //�摜�̍ő吔
};

struct MapData{					//�}�b�v�̏��
	Vec2f pos;					//�u���b�N�̊J�n�ʒu
	Vec2f size;					//�u���b�N�̃T�C�Y
	Vec2f cut_pos;				//�u���b�N�̐؂���J�n�ʒu
	Vec2f cut_size;				//�u���b�N�̐؂���T�C�Y
	char id;					//�}�b�v�̃e�L�X�g�f�[�^����������

	int map_area;				//���ǂ��̃G���A�ɂ��邩
	bool start_flag;			//�v���C���[�̊J�n�ʒu��x�����ǂݍ���
	int time;
	int time2;
};

enum BlockNumber{				//�u���b�N�̐�
	LENGTH = 20,				//�u���b�N�̐��c20��
	WIDE = 50,					//�u���b�N�̐���50��
};

enum BlockCategory{
	AIR_BLOCK = '0',				//�����Ȃ��u���b�N
	FLOOR_BLOCK_TOP = '1',			//��̓��蔻������������u���b�N
	FLOOR_BLOCK_LR = '2',			//�E�̓��蔻����������u���b�N
	FLOOR_BLOCK_LEFT = '3',			//���̓��蔻����������u���b�N
	FLOOR_BLOCK_CEILIlNG = '4',		//�V��̃u���b�N
	LADDER = '5',					//�͂����u���b�N
	LADDER_TOP = '6',				//�͂����̏㔻����������u���b�N

	PLAYER_START_POS = '8',			//�v���C���[�J�n�ʒu
	BACK_BLOCK = 'b',				//�ŏ��̃X�e�[�W�ɖ߂�u���b�N
	START_MAP = 'S',
	STAGE_ROCK1 = 'Q',				//�X�e�[�W1-1
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