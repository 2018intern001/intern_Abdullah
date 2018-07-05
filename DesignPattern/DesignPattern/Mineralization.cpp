#include "stdafx.h"
#include "Mineralization.h"
#include "Unit.h"
#include "Normal.h"
using namespace std;


Mineralization::Mineralization()
{
	expiresInHowManyTurns = 3;
}


Mineralization::~Mineralization()
{
}

string Mineralization::Name()
{
	string status = "Mineralization (";
	return status.append(to_string(expiresInHowManyTurns)).append(")");
}

bool Mineralization::StatusEffectAction(Unit* unit) {

	cout << "\t" << unit->GetName() << " is Mineralized.\n";

	DecreaseTurn();

	if (ShouldExpire())
	{
		unit->statusEffect = new Normal();
	}

	return true;
}