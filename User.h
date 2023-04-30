#pragma once
#include "Message.h"
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <deque>
#include <iostream>
using namespace std;

class User
{
	int id;
	string username;
	string password;
	vector<User> contacts; //working but waste of memory because we have sorted contacts, let's deal with it at the end
	deque<Message> sent;
	vector<Message> inbox;
	vector<pair<User, int>>sortedContacts;
	vector <Message> FavouriteMessages;

	
public:
	User();
	User(string username, string password, int id);
	int getid();
	string getUsername();
	void addcontact(User u); //return boolean?
	void removecontact(User u);
	void sendmessage();
	void unsend();
	//void searchcontact(); //boolean?
	void viewcontacts();
	void viewSent();
	void viewReceived();
	void viewMessageOptions(int i);
	//bool cmp(const pair<int, int>& a, const pair<int, int>& b);
	void msgcounter(User u);
	void favourite(Message msg);
	void RemoveOldestFavorite();
	//void viewFavorites();
	//helper functions
    Message getInboxMessage(int msgID);
	bool comparePassword(string pass);
	void addToSent(Message msg);
	void addToInbox(Message msg);
	Message popSent();
	void removeFromInbox(Message msg);
};

