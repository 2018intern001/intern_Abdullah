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

int Calculate(int a, char op, int b)
{
	if (op == '+')   return a + b;
	if (op == '*') return a * b;
	return 0;
}

// This function evaluates all possible values and returns a list of evaluated values.
vector<int> EvaluateAll(vector<string> expr, int low, int high)
{
	vector<int> possibleResults;

	// If there is only one value, it is an operand. Return it.
	if (low == high)
	{
		int value = stoi(expr[low]);
		possibleResults.push_back(value);
		return possibleResults;
	}

	// If there are only three values, it must be a in this format: x(operator)y.
	if (low == (high - 2))
	{		
		int leftSide = stoi(expr[low]);
		char operatorC = expr[low + 1].at(0);
		int rightSide = stoi(expr[low + 2]);
		int num = Calculate(leftSide, operatorC, rightSide);

		int value = stoi(expr[low]);
		possibleResults.push_back(num);
		return possibleResults;
	}

	// every i refers to an operator
	for (int i = low + 1; i <= high; i += 2)
	{
		// operatorLeftSide refers to all the possible values in the left of operator
		vector<int> operatorLeftSide = EvaluateAll(expr, low, i - 1);

		// operatorRightSide refers to all the possible values in the right of operator
		vector<int> operatorRightSide = EvaluateAll(expr, i + 1, high);

		// Take above evaluated all possible values in left side of 'i'
		for (int s1 = 0; s1<operatorLeftSide.size(); s1++)
		{
			// Take above evaluated all possible values in right side of 'i'
			for (int s2 = 0; s2<operatorRightSide.size(); s2++)
			{
				// Calculate value for every pair and add the value to result.
				char operatorC = expr[i].at(0);
				int val = Calculate(operatorLeftSide[s1], operatorC, operatorRightSide[s2]);
				possibleResults.push_back(val);
			}
		}
	}
	return possibleResults;
}

vector<string> ExpressionAsVector(string strInput) {
	vector<string> inputAsVector;
	
	string currentNumber;
	char lastExpression;
	int total = 0;
	int result = 0;
	for (char& c : strInput) {
		if (isdigit(c)) {
			currentNumber.append(1, c);
		}
		else if (isEquals(c)) {
			inputAsVector.push_back(currentNumber);
		}
		else
		{
			if (total == 0 && (isPlus(c) || isMultiply(c))) {
				total = stoi(currentNumber);
				lastExpression = c;

				inputAsVector.push_back(currentNumber);
				string s(1, lastExpression);
				inputAsVector.push_back(s);

			}
			else if (isPlus(lastExpression)) {
				total += stoi(currentNumber);
				lastExpression = c;

				inputAsVector.push_back(currentNumber);
				string s(1, lastExpression);
				inputAsVector.push_back(s);
			}
			else if (isMultiply(lastExpression))
			{
				total *= stoi(currentNumber);
				lastExpression = c;

				inputAsVector.push_back(currentNumber);
				string s(1, lastExpression);
				inputAsVector.push_back(s);
			}

			//cout << "Left  hand side: " << total << endl;
			currentNumber = "";
		}
	}

	return inputAsVector;
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

		getline(inf, strInput);

		string fullFormula = strInput;
		cout << strInput << endl;

		// This will convert the left hand side of the formula as vectors.
		vector<string> inputAsVector = ExpressionAsVector(strInput);

		//// for testing
		//for (string s : inputAsVector) {
		//	cout << s;
		//}

		// This will get the right hand side of the formula to compare results.
		int rightHandSide;
		if (!strInput.empty()) {
			string rightHandSideAsString = strInput.substr(strInput.find("=") + 1);
			rightHandSide = stoi(rightHandSideAsString);
			//cout << "=" << rightHandSide;

			vector<int> possibleValues = EvaluateAll(inputAsVector, 0, inputAsVector.size() - 1);

			bool foundValue = false;
			//For testing
			//cout << endl << "All possible values: " << endl;
			for (int value : possibleValues) {
				//cout << value << endl;
				if (rightHandSide == value) {
					foundValue = true;
					break;
				}
			}
			if (foundValue) {
				cout << "TRUE" << endl;
			}
			else {
				cout << "FALSE" << endl;
			}
		}

	}

	string input;
	cin >> input;

    return 0;
}

