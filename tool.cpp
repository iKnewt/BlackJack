#include "tool.h"
#include <algorithm>


string Tool::toLower(string line) {
	transform(line.begin(), line.end(), line.begin(),(int (*)(int))tolower);
	return line;
}

bool Tool::tryParseInt(string input, int* out) {
	try {
		*out = stoi(input);
		return true;
	}
	catch (const exception&) {
		return false;
	}
}

bool Tool::tryReadInt(int* out) {
	return tryParseInt(readLine(), out);
}

string Tool::readLine() {
	string line = "";
	getline(cin, line);
	return line;
}

void Tool::pressToContinue() {
	cout << "\n\nPress any key to continue";
	Tool::readLine();
}
