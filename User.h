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
private:
	int id; 
	string username; 
	string password; 
	deque<Message> sent;
	vector<Message> inbox;
	deque <Message> FavouriteMessages;
	map<User, int> contacts;
	vector <User> blockedContacts;
	int reported;
	
public:
	int newMsgs = 0;
	User();
	User(string username, string password, int id);
	User(string name, string pass, int ID, int _reported, int _newMsgs);
	bool operator<(const User& other) const;
	int getid() const;
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
	void addToSent(Message msg);// only used in load
	void addToSent(Message msg,User &recevier);
	void addToInbox(Message msg); //only used in load
	void addToInbox(Message msg, User &Sender);
	Message popSent();
	void removeFromInbox(Message msg);
	void beReported();
	bool isBanned();
	void notify();
	void blockContact(User& contact);
	bool Blocked(int ID);
	map<User, int> getContacts();
	deque <Message> getFavouriteMessages();
	vector <Message> getInbox();
	deque <Message> getSent();
	int getReported();
	vector<User> getBlockedContacts();

};

