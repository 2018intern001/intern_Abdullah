#pragma once
#include "stdafx.h"
#include "Command.h"
#include <string>
#include "stdafx.h"
#include <iostream>
#include <list>
#include <vector>
#include "Unit.h"
#include "Player.h"
#include "Enemy.h"
using namespace std;
class Command
{
public:
	Command();
	~Command();

private:
	static Command *_instance;
public:
	vector<string> possibleCommands;

	vector<string> listOfCommands;
	vector<string> redoCommandsList;

	static Command* Instance();

	

	bool CommandIsValid(string input);

	bool RunCommand(string input, bool record);

	void RecordCommand(string input);

	void UndoCommand();

	void RedoCommand();

};

