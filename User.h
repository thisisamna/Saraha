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
	deque<Message> sent; //stack
	vector<Message> inbox;
	deque <Message> FavouriteMessages; //queue
	map<User, int> contacts;
	vector <User> blockedContacts;
	int reported;
public:
	int newMsgs = 0;
	//constructors
	User();
	User(string username, string password, int id);
	User(string name, string pass, int ID, int _reported, int _newMsgs); //for file

	//getters
	int getid() const;
	string getUsername();
	string getPassword();
	map<User, int> getContacts();
	deque <Message> getFavouriteMessages();
	vector <Message> getInbox();
	deque <Message> getSent();
	int getReported();
	vector<User> getBlockedContacts();
	Message getInboxMessage(int msgID);

	//functionality
	void addcontact(User contact); //khira
	void removecontact(User contact); //khira
	void blockContact(User& contact); //khira
	void favourite(Message msg); //habiba 
	void RemoveOldestFavorite(); // habiba 
	void notify(); //khira
	void beReported(); //amna
	bool isBanned(); //amna
	bool Blocked(int ID); //khira
	bool searchContact(int id);  //rana

	//display
	void viewcontacts(); //rana
	void viewSent(); //amna
	void viewReceived(); //amna
	void viewFavorites(); //habiba
	void viewContactMessages(User &contact);  //khira

	//helper functions
	int msgcounter(User contact); //rana
	bool operator<(const User& other) const; 
	bool comparePassword(string pass);
	void addToSent(Message msg);// only used in load
	void addToSent(Message msg,User &recevier); //fatma
	void addToInbox(Message msg); //only used in load
	void addToInbox(Message msg, User &Sender); //fatma
	Message popSent();
	void removeFromInbox(Message msg); //fatma

};

