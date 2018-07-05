#pragma once
#include "Unit.h"
class Player :
	public Unit
{
public:
	Player();
	~Player();

	virtual const string GetName() override;
};
