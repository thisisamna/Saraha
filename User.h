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
	int id; //change
	string username; //change
	string password; //change
	//vector<User> contacts; //working but waste of memory because we have sorted contacts, let's deal with it at the end
	deque<Message> sent;
	vector<Message> inbox;
	map<User , int>contacts;
	vector <Message> FavouriteMessages;
	int newMsgs = 0; // khira -- incremencts every time a msge is sent to a user and once the user opens their inbox the variable is set to 0 again
	int reported;
	
public:
	User();
	User(string username, string password, int id);
	bool operator<(const User& other) const;
	int getid();
	string getUsername();
	string getPassword();
	void addcontact(User contact);
	void removecontact(User &u);
	//void searchcontact(); //boolean?
	void viewcontacts();
	void viewSent();
	void viewReceived();
	void viewMessageOptions(int i);
	//bool cmp(const pair<int, int>& a, const pair<int, int>& b);
	int msgcounter(User contact);
	void favourite(Message msg);
	void RemoveOldestFavorite();
	void viewFavorites();
	void searchContactbyid(int id);
	void viewContactMessages(User contact); // khira -- view msges sent by a specific user
	void searchContactbyname(string username);
	//helper functions
    Message getInboxMessage(int msgID);
	bool comparePassword(string pass);
	void addToSent(Message msg,User &recevier);
	void addToInbox(Message msg, User &Sender);
	Message popSent();
	void removeFromInbox(Message msg);
	void beReported();
	bool isBanned();
	void notify();
	
};

