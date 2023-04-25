#pragma once
#include <string>
#include <iostream>
#include "Program.h"
using namespace std;
class Message
{
private:
	int sender; //id
	string receiver; //username
	string content;
public:
	void viewAsSent();
	void viewAsReceived();
	int getSender();
};


