#include "Message.h"
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