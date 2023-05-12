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
	cout << "\n"; //line
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

bool Message::equals(Message msg)
{
	if (senderID == msg.getSenderID() && receiverID == msg.getReceiverID() && content == msg.getContent())
		return true;
	else
		return false;
}


Message::Message(int sender_ID, int receiver_ID, string receiver_username ,string msg) {
	senderID = sender_ID;
	receiverID = receiver_ID;
	receiverUsername = receiver_username;
	content = msg;
}
Message::Message()
{

}

void Message::setIsRead(bool is_read)
{
	isRead = is_read;
}

bool Message::getIsRead()
{
	return isRead;
}