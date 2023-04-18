#pragma once

#include "Message.h"

#include <string>
#include <vector>
using namespace std;

class User
{
public:
	int id;
	string username;
	string password;
	vector<User> contacts; //vector until we choose the right data structure
	vector<Message> sent;
	vector<Message> inbox;
public:
	//void singup();
	//void login();
	void addcontact(User u); //return boolean?
	void removecontact(User u);
	//void sendmessage();
	//void unsend();
	//void searchcontact(); //boolean?
	//void viewcontacts();
	void viewSent();
	void viewReceived();
	//void favourite();
	//void RemoveOldestavorite();
	//void viewFavorites();
	
	//helper functions
};

