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

Command* Command::_instance = nullptr;
vector<string> possibleCommands{ "move","attack", "defend", "undo", "redo" };

Command::Command()
{
	if (!_instance) {
		_instance = this;
	}
	
}

Command* Command::Instance() {
	if (!_instance) {
		_instance = new Command;
	}
	return _instance;
};

Command::~Command()
{
}


bool Command::CommandIsValid(string input)
{
	for (const string &text : possibleCommands) {
		if (!text.compare(input)) {
			return true;
		}
	}
	return false;
}

bool Command::RunCommand(string input, bool record)
{
	int unitsCount = Unit::units.size();
	if (!input.compare("move"))
	{
		Unit::currentUnit->Move();
		if(record) RecordCommand(input);
		return true;
	}
	else if (!input.compare("attack"))
	{
		Unit::currentUnit->Attack();
		if (record) RecordCommand(input);
		return true;
	}
	else if (!input.compare("special"))
	{
		Unit::currentUnit->Special();
		if (record) RecordCommand(input);
		return true;
	}
	else if (!input.compare("defend"))
	{
		Unit::currentUnit->Defend();
		if (record) RecordCommand(input);
		return true;
	}
	else if (!input.compare("exit"))
	{
		// Do nothing...
		return true;
	}
	else if (!input.compare("undo"))
	{
		UndoCommand();
		return true;
	}
	else if (!input.compare("redo"))
	{
		RedoCommand();
		return true;
	}
	else
	{
		cout << "Invalid input.\n";
		return false;
	}
}

void Command::RecordCommand(string input)
{
	listOfCommands.push_back(input);
	redoCommandsList.clear();
}

void Command::UndoCommand()
{
	if (listOfCommands.size() == 0) {
		cout << "\tThere is nothing to undo.\n";
		return;
	}
	string lastCommand = listOfCommands.back();
	listOfCommands.pop_back();

	cout << "Command: " << lastCommand << " was undone. " << listOfCommands.size() << " more commands can be undone.\n\n";
	Command::Instance()->RunCommand(lastCommand, false);

	
	redoCommandsList.push_back(lastCommand);
	

	
}

void Command::RedoCommand()
{
	if (redoCommandsList.size() == 0) {
		cout << "\tThere is nothing to redo.\n";
		return;
	}
	string lastCommand = redoCommandsList.back();
	redoCommandsList.pop_back();

	cout << "Command: " << lastCommand << " was redone. " << redoCommandsList.size() << " more commands can be redone.\n\n";	

	Command::Instance()->RunCommand(lastCommand,true);
}

