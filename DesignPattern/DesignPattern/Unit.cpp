#include "stdafx.h"
#include "Unit.h"
#include "StatusEffect.h"
#include "Normal.h"
#include "Paralysis.h"
#include "Mineralization.h"
#include "Poison.h"
#include <iomanip>

vector<Unit*> Unit::units;
Unit* Unit::currentUnit;
int Unit::currentUnitIndex;
StatusEffect *statusEffect;

void Unit::PrintUnitsStatus()
{
	cout << '\n';
	for (Unit *u : units) {
		if (u->hp > 0)
			cout << u->GetName() << '\t' << "HP: " << setw(5) << u->hp << "\tSP: " << setw(4) << u->sp << "\tStatus Effect: " << u->statusEffect->Name() << '\n';
		else
			cout << u->GetName() << " is dead...\n";
	}
}

Unit::Unit()
{
	name = "Unit";
	hp = 30000;
	sp = 3000;
	id = GenerateID();
	statusEffect = new Normal();
	//cout <<  dynamic_cast<Normal*>(&statusEffect);
}


Unit::~Unit()
{
}

void Unit::Move()
{
	if (hp == 0) {
		cout << '\t' << GetName() << " is dead.\n ";
		return;
	}
	if (!statusEffect->StatusEffectAction(this)) {
		if (hp > 0) {
			ReduceHealth(-1000);
			cout << '\t' << GetName() << " moved and recovered 1000 HP." << '\n';
		}
	}
}

void Unit::Attack()
{
	if (hp == 0) {
		cout << '\t' << GetName() << " is dead.\n ";
		return;
	}
	if (!statusEffect->StatusEffectAction(this)) {
		int attackValue = RandomRange(1500, 3000);
		cout << '\t' << GetName() << " attacked " << NextUnit()->GetName() << " for " << attackValue << " damage. " << '\n';
		NextUnit()->ReduceHealth(attackValue);
	}
}

int Unit::RandomRange(int low, int high) {
	int range = high - low;
	int randomRange = rand() % range;
	return randomRange + low;
}

void Unit::Special()
{
	if (hp == 0) {
		cout << '\t' << GetName() << " is dead.\n ";
		return;
	}
	if (!statusEffect->StatusEffectAction(this)) {
		if (sp >= 1000) {
			
			cout << '\t' << GetName() << " used special attack! ";
			ReduceSP(1000);

			int random_variable = rand() % 3;

			if (random_variable == 0) {
				NextUnit()->statusEffect = new Poison();
				cout << NextUnit()->GetName() << " is now Poisoned!\n";
			}
			else if (random_variable == 1) {
				NextUnit()->statusEffect = new Paralysis();
				cout << NextUnit()->GetName() << " is now Paralyzed!\n";
			}
			else if (random_variable == 2) {
				NextUnit()->statusEffect = new Mineralization();
				cout << NextUnit()->GetName() << " is now Mineralized!\n";
			}
		}
		else
		{
			cout << '\t' << NextUnit()->GetName() << " has no more SP! Special failed.\n";
		}
	}
}

void Unit::Defend()
{
	if (hp == 0) {
		cout << '\t' << GetName() << " is dead.\n ";
		return;
	}
	if (!statusEffect->StatusEffectAction(this)) {
		ReduceSP(-1000);
		cout << '\t' << GetName() << " defended and recovered 1000 SP." << '\n';
	}
}

void Unit::ReduceHealth(int reduceBy) {
	hp -= reduceBy;
	if (hp < 0) { hp = 0; }
	if (hp > 30000) { hp = 30000; }
}

void Unit::ReduceSP(int reduceBy) {
	sp -= reduceBy;
	if (sp < 0) { sp = 0; }
	if (sp > 5000) { sp = 5000; }
}

void Unit::IterateToNextUnit()
{
	int unitsSize = units.size();
	currentUnitIndex++;
	currentUnit = units[currentUnitIndex%unitsSize];
}

Unit* Unit::NextUnit() {
	int unitsSize = units.size();
	int currentIndex = currentUnitIndex;
	currentIndex++;
	Unit* nextUnit = units[currentIndex%unitsSize];
	int iterationCount = 2;
	while (nextUnit->hp == 0 && iterationCount < unitsSize) {
		currentIndex++;
		iterationCount++;
		nextUnit = units[currentIndex%unitsSize];
	}
	string name = nextUnit->GetName();
	return nextUnit;
}

int Unit::GenerateID()
{
	static int s_id = 0;
	return ++s_id;
}

const string Unit::GetName()
{
	string type = "Unit";
	string idToStr = to_string(id);
	return type.append(idToStr);
}

void Unit::AIAction() {
	if (hp < 1) {
		//cout << '\t' << GetName() << " is dead!" << '\n';
		return;
	}
	int random_variable = rand() % 4;
	//cout << random_variable << '\n';
	if (random_variable == 0) {
		Move();
	}
	else if (random_variable == 1) {
		Attack();
	}
	else if (random_variable == 2) {
		Defend();
	}
	else if (random_variable == 3) {
		Special();
	}
}