// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <curl\curl.h>

using namespace std;

#pragma comment(lib,"ws2_32.lib")

vector<pair<string, bool>> parse(const string& str) {
	bool started = false;
	bool inQuotes = false;
	string nextStr;
	unsigned long nextInt = 0;
	vector<pair<string, bool>> result;

	// For each character in the string
	for (string::const_iterator it = str.begin() + 1 /* skip 1st open bracket */; it != str.end() - 1 /* skip last closing bracket */; it++) {
		/*
		* Wait for first '[', start vector
		* Then separate each nested array (always 2 elements), [0] = string literal, [1] = integer
		* Wait for a comma, start a new vector
		* wait for the closing ']', return
		*/

		if (started) {
			if (*it == '"') {
				inQuotes = !inQuotes;
				continue;
			}
			if (*it == ',' && !inQuotes)
				continue;
			if (*it == ']' && !inQuotes) {
				started = false;
				continue;
			}
			
			if (inQuotes) {
				nextStr += *it;
			}
			else if (nextInt == 0) { // accounts for 10, 20, 30, ...
				char* end;
				const char* temp = &*it;
				nextInt = strtol(temp, &end, 10);
			}
		}
		else {
			if (*it == ',') {
				result.push_back(make_pair(nextStr, nextInt /* Auto converted to bool (not 0 is true) */));
				nextInt = 0;
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

int httpTest(string url, string other) {
	
}

int main()
{	
	const string input = "[[\"berb8\",70],[\"Umbermoon\",0],[\"[DELETED]\",2],[\"Grant \",1],[\"Siege\",0],[\"PotionCast\",1],[\"McKendrick\",0]]";
	vector<pair<string, bool>> inputVec = parse(input);
	/*
	for (int i = 0; i < inputVec.size(); i++) {
		cout << inputVec.at(i).first;
		cout << ':';
		cout << !inputVec.at(i).second;
		cout << '\n';
	}
	*/
	string host = "sheets.googleapis.com";
	string otherBS = "/v4/spreadsheets/1jz9qTfvp5hRZGuyN7HidmstlfEkVtcUe7kynWi0bUlY/values:batchGet?ranges=Medal%20Hall!A3%3AD&key=AIzaSyBABnhAmIU_u2gitsTZWC33bNteka64-5o";
	return httpTest(host, otherBS);
}
