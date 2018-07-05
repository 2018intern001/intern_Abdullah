class Unit;
#pragma once
#include <list>    
#include <string>
#include "stdafx.h"
#include "StatusEffect.h"
#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;



class StatusEffect
{
public:
	StatusEffect();
	~StatusEffect();

	int expiresInHowManyTurns;
	virtual string Name();
	virtual bool ShouldExpire();
	virtual void DecreaseTurn();

	/**
	Executes any status effect actions.

	@param Affect unit with the status effect.
	@return true if the unit should not play.
	false if it should continue playing.
	*/
	virtual bool StatusEffectAction(Unit* unit);
};

