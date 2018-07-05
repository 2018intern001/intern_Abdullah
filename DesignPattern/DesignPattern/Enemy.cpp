#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
	hp = 30000;
	sp = 1000;
}


Enemy::~Enemy()
{
}


const string Enemy::GetName()
{
	string type = "Enemy";
	string idToStr = to_string(id);
	return type.append(idToStr);
}