#pragma once

#include "Message.h"
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <stack>
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
	map<User, int>numberOfmsg;
	
	
public:
	void addcontact(User u); //return boolean?
	void removecontact(User u);
	//void sendmessage();
	//void unsend();
	//void searchcontact(); //boolean?
	void viewcontacts();
	void viewSent();
	void viewReceived();
	bool cmp(const pair<int, int>& a, const pair<int, int>& b);
	void msgcounter(User u);
	//void favourite();
	//void RemoveOldestavorite();
	//void viewFavorites();
	
	//helper functions
};

