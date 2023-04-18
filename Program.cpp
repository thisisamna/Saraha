#include "Program.h"
#include "wtypes.h"
#include <iostream>

void Program::mainMenu()
{
	printCentered("S a r a h a");
	printCentered("Annonymously send and receive messages.");
}

void Program::printCentered(string str)
{
	int maxwidth = 80;
	stringstream ss;
	int padding = maxwidth - str.size() / 2;
	for (int i = 0; i < padding;  i++) 
	{
		ss << " ";
	}
	ss << str;
	for (int i = 0; i < padding; i++)
	{
		ss << " ";
	}
	ss << endl;
	cout << ss.str();
}

