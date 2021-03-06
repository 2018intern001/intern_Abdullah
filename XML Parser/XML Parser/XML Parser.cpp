// XML Parser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <algorithm> 
#include <cctype>
#include <locale>
#include <iostream>
#include <sstream>
#include <iterator>
#include <numeric>
#include <iostream>
#include <string>
using namespace std;

string getFile(string filename);                         // Reads whole file into a string buffer
vector<string> getData(const string &text, string tag, string attribute, string attributeName);  // Gets collection of items between given tags
void stripTags(string &text);                            // Strips any tags

// Ultimately recognize the language and message ID and return a string associated with it.

void find_and_replace(string& source, string const& find, string const& replace)
{
	for (string::size_type i = 0; (i = source.find(find, i)) != string::npos;)
	{
		source.replace(i, find.length(), replace);
		i += replace.length();
	}
}

vector<string> resetFiles() {
	string text = getFile("KOFXIII_StringTable.xml");
	vector<string> all = getData(text, "MESSAGE", "KEY", "en");
	return all;
}



int main()
{
	//string filename = "input.xml";
	string filename = "KOFXIII_StringTable.xml";
	string element = "MESSAGE";
	string attribute = "ID"; // message ID;
	string attributeName = "THROW_MOVES"; // ID="attribute";
	string languageKey = "ko";
	// string tag = "object";
	bool stripOtherTags = false;

	string text = getFile(filename);
	vector<string> all = resetFiles();
	//for (string &s : all)
	//{
	//	if (stripOtherTags) 
	//		stripTags(s);
	//	cout << s << '\n';
	//}

	// vector<string> to string.
	//string ntext;// = accumulate(begin(all), end(all), ntext);
	//ntext = accumulate(begin(all), end(all), ntext);
	//cout << ntext;

	


	string input;
	while (input.compare("exit")) {
		// Possible commands: element, attribute, attributeName, run, reset.

		cout << "\nTo change element, attribute, attributeName, type the command followed by the new value. Once you are ready, type run. Then type trim to remove any tags. Type reset to load the file again.\n";

		cout << "\nCurrent Variables:" <<
			"\nelement:\t" << element <<
			"\nattribute:\t" << attribute <<
			"\nattributeName:\t" << attributeName;

		cout << "\n\nPossible commands: element, attribute, attributeName, run, reset, trim, exit." << '\n';
		//cin >> input;
		getline(cin, input);

		std::istringstream iss(input);
		std::vector<std::string> results(std::istream_iterator<std::string>{iss},
			std::istream_iterator<std::string>());

		if (results.size() == 2) {
			string firstInput = results[0];
			string secondInput = results[1];
			//cout << firstInput << '\t' << secondInput;
			if (firstInput == "element") {
				if (secondInput == "none")
					element = "";
				else
					element = secondInput;
			}
			else if (firstInput == "attribute") {
				if (secondInput == "none")
					attribute = "";
				else
					attribute = secondInput;
			}
			else if (firstInput == "attributeName") {
				if (secondInput == "none")
					attributeName = "";
				else
					attributeName = secondInput;
			}
			else {
				cout << "Invalid command.\n";
			}

		}
		else if (results.size() == 1){
			string firstInput = results[0];
			if (firstInput == "run") {
				all = getData(text, element, attribute, attributeName);
				for (string &s : all)
				{
					//if (stripOtherTags)
					//stripTags(s);
					find_and_replace(s, "&#44", ",");


				}

				text.clear();// = accumulate(begin(all), end(all), ntext);
				text = accumulate(begin(all), end(all), text);
				cout << text;
			}
			else if (firstInput == "trim") {
				stripTags(text);
				cout << text ;
			}
			else if (firstInput == "reset") {
				resetFiles();
			}
			else if (firstInput == "exit") {
				// do nothing.
			}
			else
			{
				cout << "Invalid command.\n";
			}
		}
		else {
			cout << "Invalid command.\n";
		}
		//correctInput = Command::Instance()->RunCommand(input, true);
		//input.clear();
		//cin >> input;
	}

	
}




string getFile(string filename)
{
	string buffer;
	char c;

	ifstream in(filename);   if (!in) { cout << filename << " not found";   exit(1); }
	while (in.get(c)) buffer += c;
	in.close();

	return buffer;
}


vector<string> getData(const string &text, string element, string attribute, string attributeName)
{
	vector<string> collection;
	unsigned int pos = 0, start, attributePos = 0, attributeStart, spaceStart;
	bool attributeFound = false;
	while (true)
	{
		// Try to find a element/next element.
		start = text.find("<" + element, pos);   

		// Exit if no more element can be found.
		if (start == string::npos) 
			return collection;

		if (!attribute.empty()) {
			// <MESSAGE ID="THROW_MOVES">
			// <address category = "residence">
			spaceStart = text.find(attribute, start);
			attributeStart = text.find("\"", spaceStart);
			attributeStart++;
			attributePos = text.find("\"", attributeStart);
			if (spaceStart != string::npos && attributeStart != string::npos && attributePos != string::npos) {
				string textInElement = text.substr(attributeStart, attributePos - attributeStart);
				if(textInElement == attributeName){
					//cout << endl << "Attribute: " << textInElement << endl;
					attributeFound = true;
				}
			}
		}

		// Find the end of the first element.
		start = text.find(">", start);
		start++;

		// Find the beginning of the enclousing element.
		pos = text.find("</" + element, start);   
		if (pos == string::npos) 
			return collection;

		if (attribute.empty() || attributeFound) {
			collection.push_back(text.substr(start, pos - start));
			attributeFound = false;
		}
	}
}

void stripTags(string &text)
{
	unsigned int start = 0, pos, lastKnownPos;

	start = text.find("<", start);
	text.erase(0, start);
	start = 0;
	while (start < text.size())
	{
		start = text.find("<", start);    
		
		if (start == string::npos) 
			break;
		pos = text.find(">", start);    
		if (pos == string::npos) 
			break;
		
		text.erase(start, pos - start + 1);
		lastKnownPos = start;
	}

	text.erase(lastKnownPos, text.size());
}
