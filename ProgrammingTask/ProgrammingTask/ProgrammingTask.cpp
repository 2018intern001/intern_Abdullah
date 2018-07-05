// ProgrammingTask.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib> // for exit()
using namespace std;

bool isPlus(const char c)
{
	if (c == 0) return 0;
	return c == '+';
}

bool isMultiply(const char c)
{
	if (c == 0) return 0;
	return c == '*';
}

bool isEquals(const char c)
{
	if (c == 0) return 0;
	return c == '=';
}

bool isDigit(const char c)
{
	if (c == 0) return 0;
	return strchr("0123456789", c) != 0;
}

int main()
{	

	cout << endl;

	ifstream inf("formulas.txt");

	// If we couldn't open the input file stream for reading
	if (!inf)
	{
		// Print an error and exit
		cerr << "formulas.txt could not be opened for reading!" << endl;
		exit(1);
	}

	// While there are formulas to read
	while (inf)
	{
		string strInput;
		string currentNumber;
		char lastExpression;
		int total = 0;
		int result = 0;
		getline(inf, strInput);
		cout << strInput << endl;

		for (char& c : strInput) {
			if (isdigit(c)) {
				currentNumber.append(1, c);
			}
			else
			{
				if (total == 0 && (isPlus(c) || isMultiply(c))) {
					total = stoi(currentNumber);
					lastExpression = c;
				}
				else if (isPlus(lastExpression)) {
					total += stoi(currentNumber);
					lastExpression = c;
				}
				else if (isMultiply(lastExpression))
				{
					total *= stoi(currentNumber);
					lastExpression = c;
				}
				cout << "Left  hand side: " << total << endl;
				currentNumber = "";
			}
		}

		if (!strInput.empty()) {
			// This is to print the last number in the line.
			total = stoi(currentNumber);
			cout << "Right hand side: " << total << endl;
			currentNumber = "";
		}
		
		/*string leftHandSide, rightHandSide;

		std::string delimiter = "=";

		size_t pos = 0;
		string token;
		while ((pos = strInput.find(delimiter)) != string::npos) {
			leftHandSide = strInput.substr(0, pos);
			cout << "Left Hand Side: " << leftHandSide << endl;
			strInput.erase(0, pos + delimiter.length());
		}

		rightHandSide = strInput;
		cout << "Right Hand Side: " << rightHandSide << endl;*/

	}

	string input;
	cin >> input;

    return 0;
}

