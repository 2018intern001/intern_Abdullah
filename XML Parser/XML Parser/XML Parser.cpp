// XML Parser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <algorithm> 
#include <cctype>
#include <locale>
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

int main()
{
	//string filename = "input.xml";
	string filename = "KOFXIII_StringTable.xml";
	string element = "MESSAGE";
	string attribute = "ID"; // message ID;
	string attributeName = "SUPER_SPECIAL_FINISH_COUNT"; // ID="attribute";
	string languageKey = "ko";
	// string tag = "object";
	bool stripOtherTags = false;

	string text = getFile(filename);
	vector<string> all = getData(text, element, attribute, attributeName);
	for (string &s : all)
	{
		if (stripOtherTags) 
			stripTags(s);
		cout << s << '\n';
	}

	string ntext;// = accumulate(begin(all), end(all), ntext);
	ntext = accumulate(begin(all), end(all), ntext);
	//cout << ntext;

	all = getData(ntext, "DATA", "KEY", languageKey);
	for (string &s : all)
	{
		//if (stripOtherTags)
			stripTags(s);
			find_and_replace(s, "&#44", ",");
			
		cout << s << '\n';
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
