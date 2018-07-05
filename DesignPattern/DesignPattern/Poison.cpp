#include "stdafx.h"
#include "Poison.h"
#include "Unit.h"
#include "Normal.h"


Poison::Poison()
{
	expiresInHowManyTurns = 3;
}

Poison::~Poison()
{
}

string Poison::Name()
{
	string status = "Poison (";
	return status.append(to_string(expiresInHowManyTurns)).append(")");
}

bool Poison::StatusEffectAction(Unit* unit) {

	int damage = Unit::RandomRange(2000, 3000);

	unit->ReduceHealth(damage);

	cout << "\t" << unit->GetName() << " is Poisoned and takes " << damage << " damage.\n";

	DecreaseTurn();

	if (ShouldExpire())
	{
		unit->statusEffect = new Normal();
	}

	return false;
}