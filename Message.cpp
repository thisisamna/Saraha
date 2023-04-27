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

int Message::get_sender() {
	return sender;
}
int Message::get_receiver() {
	return receiver_id;
}
	Message::message(int id,string username_recevier,string msg) {
		sender = id;
		receiver = username_recevier;
		content = msg;

	}
