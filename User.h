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
	deque<Message> sent;
	vector<Message> inbox;
	map<User , int> contacts;
	vector <Message> FavouriteMessages;
	vector <User> blockedContacts;
	int newMsgs = 0; 
	int reported;
	int key;
	
public:
	User();
	User(string username, string password, int id);
	bool operator<(const User& other) const;
	int getid();
	string getUsername();
	string getPassword();
	void addcontact(User contact);
	void removecontact(User contact);
	void viewcontacts();
	void viewSent();
	void viewReceived();
	//bool cmp(const pair<int, int>& a, const pair<int, int>& b);
	int msgcounter(User contact);
	void favourite(Message msg);
	void RemoveOldestFavorite();
	void viewFavorites();
	void searchContact(int id);
	void viewContactMessages(User &contact); 
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
	void blockContact(User& contact);
	bool Blocked(int ID);
	
};

