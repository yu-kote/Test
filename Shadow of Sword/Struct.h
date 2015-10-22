#pragma once
#include "lib/framework.hpp"
#include "Screen.h"



struct MovingObject{
	Vec2f pos;						//�������̂̎n�_
	Vec2f size;						//�������̂̃T�C�Y
	Vec2f cut_pos;					//�摜�؂���J�n�ʒu
	Vec2f cut_size;					//�摜�؂���T�C�Y

	int direction;					//����
	int is_exists;					//���݂��Ă��邩
	const float gravity = -0.3f;		//�������̂ɂ�����d��
	const float gravity_max = -2.0f;	//�ő�̏d��
	int centering_size = -100;

	int type;

	int time;
	int time2;
	int angle;
	Vec2f zoom;
	Vec2f center;
	int attack_time;

	int index;



	Vec2f camera;					//�ꉞ�J���������ǁA�x�N�g���݂����ɂȂ��Ƃ�
	bool stop_camera_x;				//x���J�����̓������~�߂�
	bool stop_camera_y;				//y���J�����̓������~�߂�


	int move_speed = 13;			//�v���C���[�̓������x
	Vec2f vector;					//�v���C���[�̃x�N�g��
	bool is_invin;					//�v���C���[�����G���ǂ���
	int invin_time;
	bool animation_reset;			//�v���C���[���h�䂵�Ă��邩�ǂ���
	bool is_attack;					//�v���C���[���U�����Ă��邩�ǂ���

	bool start_flag;				//�v���C���[�������ʒu�ɂ��ǂ��t���O
	bool is_move;					//�v���C���[�𑀍�ł��邩�ǂ���
	bool is_gravity;				//�d�͂��������Ă��邩�ǂ���

	bool is_hitfloor;				//�n�ʂɓ������Ă��邩�ǂ���

	int rolling_count;				//���[�����O����
	bool rolling_flag;				//���[�����O���n�߂�t���O

	float camera_centering = 0.04;	//�J�����Z���^�����O�X�s�[�h
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
	bool ladder_flag;				//�͂����o��͂��߂�t���O
	bool is_ladder_top;				//�͂�����o���Ă��邩�ǂ���
	int ladder_top_count;			//�͂����Ă��؂�J�E���g
	bool change_ladder_top;			//�͂����Ă��؂�̔���ω��t���O
	bool ladder_down_flag;			//�͂�����������t���O

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
	Media attack_sound;	//����U�鉹
	Media hit_sound;	//�q�b�g��
	Media tuto_sound;	//�`���[�g���A��
	Media cursor;
	Media warp;
	Media buy;
	Media higurasi;
};

namespace CharaInfo{
	enum ObjectDirection{ //�������̂̌���
		RIGHT, //�E����
		LEFT, //������
	};

	enum Objectexists{ //�������̂������Ă��邩�ǂ���
		DEAD, //����ł���
		LIVE, //�����Ă���
	};
}

enum Is_Stop{ //�~�܂��Ă��邩�ǂ���
	MOVE, //�����Ă���
	STOP, // �~�܂��Ă���
};

enum Chara_Type{
	DEFAULT,		//�f�t�H���g����
	RUN,			//�����Ă���
	ATTACK_TOP,		//��i�K�U��
	ATTACK_MIDDLE,	//��i�K�U��
	ATTACK_UNDER,	//�O�i�K�U��
	ROLLING,		//���[�����O
	LADDER_CLIMB,	//�o��
};

struct mapAnimation{
	Vec2f cut_pos;
	Vec2f cut_size = Vec2f(256, 256);
	int time;
	int time2;




};
