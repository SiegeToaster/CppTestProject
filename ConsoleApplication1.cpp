// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

vector<pair<string, int>> bullshit(const string& str) {
	// https://stackoverflow.com/questions/890164/how-can-i-split-a-string-by-a-delimiter-into-an-array
	bool started = false;
	bool inQuotes = false;
	string nextStr;
	unsigned long nextInt = 50;
	vector<pair<string, int>> result;

	// For each character in the string
	for (string::const_iterator it = str.begin() + 1 /* skip 1st open bracket */; it != str.end() - 1 /* skip last closing bracket */; it++) {
		/*
		* Wait for first '[', start vector
		* Then seperate each nested array (always 2 elements), [0] = string literal, [1] = integer
		* Wait for a comma, start a new vector
		* wait for the closing ']', return
		*/

		if (started) {
			if (*it == ',')
				continue;
			if (*it == '"') {
				inQuotes = !inQuotes;
				continue;
			}
			if (*it == ']') {
				started = false;
				continue;
			}
			
			if (inQuotes) {
				nextStr += *it;
			}
			else {
				char* end;
				const char* temp = &*it;
				nextInt = strtol(temp, &end, 10);
			}
		}
		else {
			if (*it == ',') {
				result.push_back(make_pair(nextStr, nextInt));
			}
			else if (*it == '[') {
				started = true;
				nextStr = "";
			}
		}
	}

	result.push_back(make_pair(nextStr, nextInt));
	return result;
}

int main()
{	
	const string testString = "[[\"berb8\",0],[\"Umbermoon\",0],[\"[DELETED]\",2],[\"Grant \",1],[\"Siege\",0],[\"PotionCast\",1],[\"McKendrick\",0]]";
	vector<pair<string, int>> testResult = bullshit(testString);
	for (int i = 0; i < testResult.size(); i++) {
		cout << testResult.at(i).first;
		cout << ',';
		cout << testResult.at(i).second;
		cout << '\n';
	}
}
