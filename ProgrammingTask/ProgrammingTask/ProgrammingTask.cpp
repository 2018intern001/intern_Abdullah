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

//// This function evaluates all possible values and
//// returns a list of evaluated values.
//vector<int> evaluateAll(string expr, int low, int high)
//{
//	vector<int> possibleResults;
//
//	// If there is only one character, it must
//	// be a digit (or operand), return it.
//	if (low == high)
//	{
//		possibleResults.push_back(expr[low] - '0');
//		return possibleResults;
//	}
//
//	// If there are only three characters, middle
//	// one must be operator and corner ones must be
//	// operand
//	if (low == (high - 2))
//	{
//		int num = eval(expr[low] - '0', expr[low + 1],
//			expr[low + 2] - '0');
//
//		possibleResults.push_back(num);
//		return possibleResults;
//	}
//
//	// every i refers to an operator
//	for (int i = low + 1; i <= high; i += 2)
//	{
//		// l refers to all the possible values
//		// in the left of operator 'expr[i]'
//		vector<int> l = evaluateAll(expr, low, i - 1);
//
//		// r refers to all the possible values
//		// in the right of operator 'expr[i]'
//		vector<int> r = evaluateAll(expr, i + 1, high);
//
//		// Take above evaluated all possible
//		// values in left side of 'i'
//		for (int s1 = 0; s1<l.size(); s1++)
//		{
//			// Take above evaluated all possible
//			// values in right side of 'i'
//			for (int s2 = 0; s2<r.size(); s2++)
//			{
//				// Calculate value for every pair
//				// and add the value to result.
//				int val = eval(l[s1], expr[i], r[s2]);
//				possibleResults.push_back(val);
//			}
//		}
//	}
//	return possibleResults;
//}

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
		cout << strInput << endl;

		// This will convert the left hand side of the formula as vectors.
		vector<string> inputAsVector = ExpressionAsVector(strInput);

		// for testing
		for (string s : inputAsVector) {
			cout << s;
		}

		// This will get the right hand side of the formula to compare results.
		int rightHandSide;
		if (!strInput.empty()) {
			string rightHandSideAsString = strInput.substr(strInput.find("=") + 1);
			rightHandSide = stoi(rightHandSideAsString);
			cout << "=" << rightHandSide;
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

