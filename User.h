#pragma once
#include "Message.h"
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <deque>
#include <iostream>
#include<queue>
using namespace std;

class User
{
public:
	int id; //change
	string username; //change
	string password; //change
	//vector<User> contacts; //working but waste of memory because we have sorted contacts, let's deal with it at the end
	deque<Message> sent;
	vector<Message> inbox;
	map<User , int>contacts;
	vector <Message> FavouriteMessages;
	int newMsgs = 0; // khira -- incremencts every time a msge is sent to a user and once the user opens their inbox the variable is set to 0 again
	
	
public:
	User();
	User(string username, string password, int id);
	bool operator<(const User& other) const;
	int getid();

	string getUsername();
	void addcontact(User &liveUser, User &Added); //return boolean?
	void removecontact(User &u);
	//void searchcontact(); //boolean?
	void viewcontacts(User& liveuser);
	void viewSent();
	void viewReceived();
	void viewMessageOptions(int i);
	//bool cmp(const pair<int, int>& a, const pair<int, int>& b);
	int msgcounter(User &u, User &liveUser);
	void favourite(Message msg);
	void RemoveOldestFavorite();
	void viewFavorites();
	void searchContactbyid(int id);
	void searchContactbyname(string username);
	//helper functions
    Message getInboxMessage(int msgID);
	bool comparePassword(string pass);
	void addToSent(Message msg,User &liveUser,User &recevier);
	void addToInbox(Message msg,User &liveUser, User &Sender);
	Message popSent();
	void removeFromInbox(Message msg);
	
};

