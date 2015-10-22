#include "lib/framework.hpp"
#include "Game.h"
#include "Constant.h"
#include "Screen.h"








int main() {
	env;
	Textures tx;
	textureInit(tx);
	mapImageInit();


	int scene_move = TITLE; //どのシーンか
	gameInit(tx); //本編初期化
	


	while (env.isOpen()) {

		if (env.isPushKey('E'))
			return 0;

		switch (scene_move){
		case TITLE:

			break;
		case GAME:
			gameUpdate(tx,scene_move);

			break;
		case GAMEOVER:

			break;

		}
		env.begin();

		switch (scene_move){
		case TITLE:
			title(tx,scene_move);
			break;
		case GAME:
			gameDraw(tx);
			break;
		case GAMEOVER:
			gameover(tx,scene_move);
			break;
		case SHOP:
			status_shop(tx, scene_move);

			break;
		}
		env.end();
	}
}
