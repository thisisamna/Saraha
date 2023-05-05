#pragma once
#include "User.h"
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "Message.h"
using namespace std;

class Program
{
	int liveUserID = -1;
	int userCount = 0;
	User liveUser;
	bool exit;
	int choice;
	unordered_map<int, User> users;

public:
	//menu functions
	Program();
	void loop();
	void loginMenu();
	void userMenu(User liveUser);
	void Inbox(User liveUser);
	void signup();
	void sendmessage(User liveUser);
	void undolastmessage(User liveUser);
	int login();
	User* idToUser(int id);
	int usernameToID(string username);
	void addSendertoContacts(Message msg);
	void printCentered(string str);
	void loadfile();
	void savefile();
	~Program();
};

