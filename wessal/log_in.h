#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include"registration.h"
using namespace std;
class log_in
{
	string username, password;
public:
	void logIn();
	bool IsloggedIn(string username, string password);
	void message();
};

