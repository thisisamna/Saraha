#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "User.h"

using namespace std;

class Program
{
	int choice;
	unordered_map<int, User> usersToID;
	unordered_map<string, pair<int, User>> usersToUsername;
public:
	//menu functions
	void loginMenu();
	void userMenu();
	void singup();
    User* login();
	//helper functions
	User getUser(int id);
	User getUser(string username);

	void printCentered(string str);

};

