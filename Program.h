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
	User *liveUser;
	bool exit;
	int intChoice;
	char check;
	unordered_map<int, User> users;
public:
	//menu functions
	Program();
	void loop();
	void loginMenu();
	void userMenu(User &liveUser);
	void Inbox(User &liveUser);
	void contactMenu(User& liveUser, User& contact);

	//functionality
	int login();
	void signup();
	void sendmessage(User &liveUser);
	void undolastmessage(User &liveUser);
	void addSendertoContacts(User& liveUser, Message msg);

	//helper functions
	int getInt();
	void printDivider();
	int usernameToID(string username);
	User* idToUser(int id);
	void printCentered(string str);
	void validateContact();
	//file handling
	void loadfile();
	void loadContacts();
	void savefile();
	void saveContacts();

	~Program();
};

