#ifndef TOOL_H
#define TOOL_H

#include <iostream>

using namespace std;

class Tool
{
public:
	static string readLine();
	static string toLower(string line);
	static bool tryParseInt(string input, int* out);
	static bool tryReadInt(int* out);
	static int randomNumber(int min, int max);
	static void pressToContinue();
};

#endif // TOOL_H
