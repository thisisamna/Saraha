#include "Program.h"

#include <iostream>

void Program::loginMenu()
{
	printCentered("S a r a h a");
	printCentered("Annonymously send and receive messages.");
	cout << "Welcome!" << endl;
	cout << "Do you have an account?\n\n" << endl; //bug here, two newlines fix it but why?
	cout << "1. Yes\n"
		<< "2. No\n";
	cin >>choice;

	switch (choice) {
	case 1:
		printCentered("L o g   i n");
		//login
		break;
	case 2:
		printCentered("S i g n   u p");
		//signup
		break;
	default:
		cout << "Invalid entry, try again!";
	}
}

void Program::userMenu()
{
	cout << "1. Send a message\n"
		<< "2. Inbox\n"
		<< "3. Favorites\n"
		<< "4. Sent messages\n"
		<< "5. My contacts\n"
		<< "6. Logout\n";
	cin >> choice;
	switch (choice)
	{
	case 1:
		//send a message
		break;
	case 2:
		//inbox
		break;
	case 3:
		//favorites
		break;
	case 4:
		//sent messages
		break;
	case 5:
		//contacts
		break;
	case 6:
		//logout
		break;
	default:
		cout << "Invalid entry, try again!";
	}
}
void Program::singup()
{
}
User* Program::login()
{
	return nullptr;
}
User Program::getUser(int id)
{
	User user;
	auto it = usersToID.find(id);
	user = it->second;
	return user;
}

User Program::getUser(string username)
{
	User user;
	auto it = usersToUsername.find(username);
	user = it->second.second; //accessing map of map
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

