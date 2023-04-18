#include "Program.h"

#include <iostream>

void Program::loginMenu()
{
	printCentered("S a r a h a");
	printCentered("Annonymously send and receive messages.");
	cout << "Welcome!" << endl;
	cout << "Do you have an account? (y/N)\n\n" << endl; //bug here, two newlines fix it but why?

	cin >>choice;

	switch (choice) {
	case 'y':
	case 'Y':
		printCentered("L o g   i n");
		//login
		break;
	case 'n':;
	case 'N':
		printCentered("S i g n   u p");
		//signup
		break;
	default:
		cout << "Invalid entry, try again!";
	}
}

User Program::getUser(int id)
{
	User user;
	auto it = users.find(id);
	user = it->second;
	return user;
}

void Program::printCentered(string str)
{
	int maxwidth = 70;
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
	cout << ss.str() << endl;
}

