#pragma once
#include "Unit.h"
class Enemy :
	public Unit
{
public:
	Enemy();
	~Enemy();

	virtual const string GetName() override;
};
