#include "stdafx.h"
#include "Paralysis.h"
#include "Unit.h"
#include "Normal.h"


Paralysis::Paralysis()
{
	expiresInHowManyTurns = 3;
}


Paralysis::~Paralysis()
{
}

string Paralysis::Name()
{
	string status = "Paralysis (";
	return status.append(to_string(expiresInHowManyTurns)).append(")");
}


bool Paralysis::StatusEffectAction(Unit* unit){
	probabilityOfFailure = 50;
	int random_variable = rand() % 100;

	DecreaseTurn();

	if (ShouldExpire())
	{
		unit->statusEffect = new Normal();
	}
	
	//cout << random_variable << '\n';
	if (random_variable <50) {
		
		return false;
	}
	else {
		cout << "\t" << unit->GetName() << " is Paralysed.\n";
		return true;
	}

}
