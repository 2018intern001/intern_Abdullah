#include "stdafx.h"
#include "StatusEffect.h"
#include "Unit.h"


StatusEffect::StatusEffect()
{
	expiresInHowManyTurns = 1;
}


StatusEffect::~StatusEffect()
{
}


string StatusEffect::Name()
{
	return "Status Effect " + expiresInHowManyTurns;
}

bool StatusEffect::ShouldExpire() {
	if (expiresInHowManyTurns > 0)
		return false;
	return true;
}

void StatusEffect::DecreaseTurn() {
	expiresInHowManyTurns--;
}

bool StatusEffect::StatusEffectAction(Unit* unit)
{
	return false;
}
