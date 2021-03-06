// Lambda.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main()
{
	// Challenge①
	// Returns the addition result of two local variables.
	int add1 = 3;
	int add2 = 7;
	auto addIntLambda = [](int a, int b) -> int {return a + b; };
	int addResult = addIntLambda(add1, add2);
	cout << "\n\nChallenge 1: Returns the addition result of two local variables.\n";
	cout << add1 << "+" << add2 << "=" << addResult << "\n";

	// Challenge②
	// The result of squaring the local variable is stored in the original variable.
	cout << "\n\nChallenge 2: The result of squaring the local variable is stored in the original variable.\n";
	int intToBeSquared = 4;
	cout << "Int to be squared: " << intToBeSquared << "\n";
	auto squareIntPointerLambda = [](int &a) -> void {
		a = a * a; 
	};
	squareIntPointerLambda(intToBeSquared);
	cout << "Int to be squared (after squaring): " << intToBeSquared << "\n";

	// Challenge③
	// Sort the std::vector containing the appropriate number in ascending order.

	cout << "\n\nChallenge 3: Sort the std::vector containing the appropriate number in ascending order.\n";
	vector <int> numberList = { 1,3,2,4,5,7,6,9,8,10,0 };
	// Printing Vector content.
	cout << "Vector before sorting:\n";
	for (int i = 0; i < numberList.size(); i++) { 
		cout << numberList[i] << ", ";
	}
	cout << '\n';
	auto compareIntLambda = [](int a, int b) -> bool {
		return (a < b);
	};
	sort(numberList.begin(), numberList.end(), compareIntLambda);
	// Printing Vector content.
	cout << "Vector after sorting:\n";
	for (int i = 0; i < numberList.size(); i++) {
		cout << numberList[i] << ", ";
	}
	cout << '\n';

	
	string strInput = "";
	getline(cin, strInput);

    return 0;
}

