#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	hp = 15000;
	sp = 3000;
}


Player::~Player()
{
}

const string Player::GetName() 
{
	string type = "Player";
	string idToStr = to_string(id);
	return type.append(idToStr);
}
