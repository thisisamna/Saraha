#pragma once
#include <string>
#include <iostream>
using namespace std;
class Message
{
private:
	int senderID; 
	int receiverID;
	string receiverUsername; 
	string content;
	bool isRead = false;

public:
	//constructors
	Message();
	Message(int sender_ID, int receiver_ID, string receiver_username, string msg);
	
	//setters and getters
	string getContent();
	int getSenderID();
	int getReceiverID();
	string getReceiverUsername();
	bool getIsRead();
	void setIsRead(bool is_read);

	//helper functions
	void viewAsSent();
	void viewAsReceived();
	bool equals(Message msg);



};


