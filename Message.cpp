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
	cout << "From: " << sender << "\n";
	cout << content << "\n\n";
}

string Message::getContent()
{
	return content;
}

int Message::getSender() {
	return sender;
}
int Message::getReceiver() {
	return receiver_id;
}

void Message:: setReceiver(int r) {
	receiver_id = r;
}

Message::Message(int id,string username_recevier,string msg) {
	sender = id;
	receiver = username_recevier;
	content = msg;

}
