﻿#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "User.h"

using namespace std;

class Program
{
	User* liveUser;
	bool exit;
	int choice;
	unordered_map<int, User> usersToID;
	unordered_map<string, pair<int, User>> usersToUsername;
public:
	//menu functions
	void mainMenu();
	void userMenu(User* liveUser);
	void Inbox(User* liveUser);
	void singup();
    User* login(User user); //حيرجع بوينتر للهاش ماب الكبيرة
	//helper functions
	User idToUser(int id);
	User usernameToUser(string username);
	void addSender(Message msg);
	void printCentered(string str);

};

