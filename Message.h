#pragma once
#include <string>
#include <iostream>
using namespace std;
class Message
{
private:
	int sender; //id
	int receiver_id;
	string receiver; //username
	string content;
public:
	void viewAsSent();
	void viewAsReceived();
	int get_sender();
	int get_receiver();
	Message(int, string, string);
	string getContent();
	int getSender();
	int getReceiver();

};


