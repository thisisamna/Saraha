#pragma once

#include "Message.h"

#include <string>
#include <vector>
using namespace std;

class User
{

	int ID;
	string username;
	string password;
	vector<User> contacts; //vector until we choose the right data structure
	vector<Message> sent;
	vector<Message> recieved;

public:
	//void singup();
	//void login();
	void addcontact(User u); //return boolean?
	void removecontact(User u);
	//void sendmessage();
	//void unsend();
	//void searchcontact(); //boolean?
	//void viewcontacts();
	//void viewsent();
	//void viewreceived();
	//void favourite();
	//void popfavorite();
	//void viewfavorite();


};

