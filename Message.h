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
	void viewAsSent();
	void viewAsReceived();
	//int get_sender();
	//int get_receiver();
	Message(int, string, string);
	string getContent();
	int getSenderID();
	int getReceiverID();
	string getReceiverUsername();


	void setReceiver(int r); // had to until we figure out another way

};


