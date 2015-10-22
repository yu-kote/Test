#pragma once
#include "lib/framework.hpp"
#include "Constant.h"
#define env App::get()
#define  one_angle 0.01745329251994329576923690768489 //M_PI_2/360


class App
{
private:

	App(){}

public:

	static AppEnv& get()
	{
		static AppEnv s_env(WIDTH, HEIGHT, false, true);

		return s_env;
	}
};