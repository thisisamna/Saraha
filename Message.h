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
public:
	Message(int sender_ID, int receiver_ID, string receiver_username, string msg);
	void viewAsSent();
	void viewAsReceived();
	string getContent();
	int getSenderID();
	int getReceiverID();
	string getReceiverUsername();



};


