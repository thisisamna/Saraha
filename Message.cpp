#include "Message.h"
#include <map>
#include <iostream>
void Message::viewAsSent()
{
	cout << "To: " << receiver << "\n";
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

void Message:: setReceiver(int r) {
	receiverID = r;
}

Message::Message(int id,string username_recevier,string msg) {
	sender = id;
	receiver = username_recevier;
	content = msg;

}
