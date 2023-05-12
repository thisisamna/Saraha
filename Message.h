#pragma once
#include <string>
#include <iostream>
using namespace std;
class Message
{
private:
	int senderID; 
	int receiverID;
	string receiverUsername; //username
	string content;
	bool isRead = false;

public:
	Message(int sender_ID, int receiver_ID, string receiver_username, string msg);
	Message();
	void viewAsSent();
	void viewAsReceived();
	string getContent();
	int getSenderID();
	int getReceiverID();
	string getReceiverUsername();
	bool equals(Message msg);
	void setIsRead(bool is_read);
	bool getIsRead();


};


