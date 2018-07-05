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

//enum StatusEffect { None, KO, Freeze, Shock, Poison, Paralyze, Confused, Charm, Stone, Sleep};

class Unit
{
public:
	static vector<Unit*> units;
	static Unit* currentUnit;
	static int currentUnitIndex;

	static void PrintUnitsStatus();

	string name;
	int id;// = generateID();
	int hp; // Health
	int sp; // Special Attacks
	StatusEffect* statusEffect;

	Unit();
	~Unit();

	virtual void Move();
	virtual void Attack();
	static int RandomRange(int low, int high);
	virtual void Special();
	virtual void Defend();

	void ReduceHealth(int reduceBy);

	void ReduceSP(int reduceBy);

	static void IterateToNextUnit();

	static Unit * NextUnit();

	int GenerateID();
	virtual const string GetName();
	virtual void AIAction();
};
