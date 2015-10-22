#pragma once
#include "lib/framework.hpp"
#include "Constant.h"
#include "Struct.h"
#include "Screen.h"
#include "Enemy.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "Map.h"

void textureInit(Textures& tx);

void gameInit(Textures& tx);

void gameUpdate(Textures& tx, int& scene);

void gameDraw(Textures& tx);

void charaInit();

void charaMove(Textures& tx, int& scene);

void charaDraw(Textures& tx);

void status_shop(Textures& tx, int& scene);

void gameover(Textures& tx, int& scene);

void title(Textures& tx, int& scene);