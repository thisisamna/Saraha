#pragma once

#include "Message.h"

#include <string>
#include <vector>
using namespace std;

class User
{
private:
	int id;
	string username;
	string password;
	vector<User> contacts; //vector until we choose the right data structure
	vector<Message> sent;
	vector<Message> inbox;
public:
	//void singup();
	//void login();
	//void addContact(); //return boolean?
	//void removeContact();
	//void sendMessage();
	//void unsendLastMessage();
	//void searchForContact(); //boolean?
	//void viewContacts();
	void viewSent();
	void viewReceived();
	//void favourite();
	//void RemoveOldestavorite();
	//void viewFavorites();
	
	//helper functions
};

