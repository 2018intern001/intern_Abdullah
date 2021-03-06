// DesignPattern.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include <vector>
#include "Unit.h"
#include "Player.h"
#include "Enemy.h"
#include "Command.h"
#include <string>
using namespace std;

void CreatePlayer()
{
	Player *player = new Player();
	Unit::units.push_back(player);
	cout << (*player).GetName() << " was created." << '\n';
};

void CreateEnemy() {
	Enemy *enemy = new Enemy();
	Unit::units.push_back(enemy);
	cout << (*enemy).GetName() << " was created." << '\n';
};

bool UnitIsPlayer(Unit *unit) {
	return dynamic_cast<Player*>(unit);
}

int main()
{	
	CreatePlayer();
	CreateEnemy();
	CreateEnemy();


	cout << "\nGame Starting... (To exit, type \"exit\")" << endl << endl;

	cout << "Command List Explaination: " << endl;
	cout << "\tMove will recover 1000 HP." << endl;
	cout << "\tAttack will attack the NEXT enemy in the list." << endl;
	cout << "\tSpecial will put a special status effect on the NEXT enemy in the list. It costs 1000 SP." << endl;
	cout << "\tDefend will recover 1000 SP." << endl;
	cout << "\tUndo will do the last command." << endl;
	cout << "\tRedo will do the last command that was undone." << endl;

	//for (Unit *u : units) {
		//cout << u->GetName() << '\n';
		//u->Action();
	//}

	Unit::currentUnit = Unit::units[0];
	Unit* currentUnit = Unit::currentUnit;

	bool correctInput = false;

	int unitCount = Unit::units.size();
	int unitsDead = 0;
	

	string input;
	while (input.compare("exit")) {

		currentUnit = Unit::currentUnit;
		
		if (UnitIsPlayer(currentUnit)) {
			//cout << "I am a Player!\n";
			correctInput = false;
			while (!correctInput) {
				cout << '\n';
				Unit::PrintUnitsStatus();

				unitsDead = 0;
				for (Unit *u : Unit::units) {
					if (u->hp == 0)
						unitsDead++;
				}

				if (unitCount - unitsDead == 1)
				{
					if (currentUnit->hp > 0) {
						cout << "\nYOU WIN!\n";
					}
					else
					{
						cout << "\nYOU LOSE!\n";
					}

					input = "exit";
					correctInput = Command::Instance()->RunCommand(input, false);
				}
				else {

					cout << "\nIt is your turn, what do you want to do? (move/attack/special/defend/undo/redo)" << '\n';

					cin >> input;

					cout << '\n';

					correctInput = Command::Instance()->RunCommand(input, true);
					
				}
			}
		}
		else
		{
			currentUnit->AIAction();
		}

		Unit::IterateToNextUnit();
	}
	
	cout << "Game Ending... Bye Bye!" << '\n';
	cin >> input;
    return 0;
}



