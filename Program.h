#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "User.h"

using namespace std;

class Program
{
	char choice;
	unordered_map<int, User> users;
public:
	//menu functions
	void loginMenu();
	//void singup();
    //void login();
	//helper functions
	User getUser(int id);
	void printCentered(string str);

};

