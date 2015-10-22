#pragma once
#include "lib/framework.hpp"
#include "Struct.h"
#include "Screen.h"
#include <iostream>
#include <string>

#include "Map.h"

void enemyMove(Enemy& enemy, Sword& sword, Player& player, Sword sword2, Textures& tx);

void enemy2Move(Enemy& enemy, Sword& sword, Player& player, Sword sword2, Textures& tx);

void boss1_enemyMove(Enemy& enemy, Sword& sword, Player& player, Sword sword2, Textures& tx);

void enemyInit(Enemy& enemy, Sword& sword);

void enemy2Init(Enemy& enemy, Sword& sword);

void enemyDraw(Player player, Enemy& enemy, Sword& sword, Textures& tx);

void enemy2Draw(Player player, Enemy& enemy, Sword& sword, Textures& tx);

void boss1_enemyInit(Enemy& enemy, Sword& sword);

void boss1_enemyDraw(Player player, Enemy& enemy, Sword& sword, Textures& tx);

