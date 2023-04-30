#include "Message.h"
#include <map>
#include <iostream>
void Message::viewAsSent()
{
	cout << "To: " << receiverUsername << "\n";
	cout << content << "\n\n";
}
void Message::viewAsReceived()
{
	cout << "From: " << senderID << "\n";
	cout << content << "\n\n";
}

string Message::getContent()
{
	return content;
}

int Message::getSenderID() {
	return senderID;
}
int Message::getReceiverID() {
	return receiverID;
}

string Message::getReceiverUsername()
{
	return receiverUsername;
}


Message::Message(int sender_ID, int receiver_ID, string receiver_username ,string msg) {
	senderID = sender_ID;
	receiverID = receiver_ID;
	receiverUsername = receiver_username;
	content = msg;
}
