#include "stdafx.h"
#include "Normal.h"
#include "Unit.h"

Normal::Normal()
{
	
}


Normal::~Normal()
{
}

string Normal::Name()
{
	return "Normal";
}

bool Normal::StatusEffectAction(Unit * unit)
{
	//expiresInHowManyTurns = 100; // We never want it to expire.
	return false;
}

