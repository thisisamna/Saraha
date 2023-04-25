#include "User.h"
#include <iostream>
using namespace std;
//This is an example
void User::addcontact(User u)
{
	bool userExists = false; // ترو لو اليوزر موجود بالفعل عندي

	for (User it : contacts) 
	{
		if (it.id == u.id)
		{
			cout << "\nUser already exists\n";
			userExists = true;
			break;
		}
	}// to check if user already exists


	if(!userExists) // لو اليوزر مش عندي ضيفه
		contacts.push_back(u);

}

void User::removecontact(User u)
{
	int i = -1;

	for (User it : contacts)
	{
		i++;
		if (it.id == u.id)
			break;
	}
	contacts.erase(contacts.begin() + i);
}


void User::viewSent()
{
	if (sent.empty())
	{
		cout << "You haven't sent any messages yet.";
	}
	else
	{
		for(auto msg:sent)
		{
			msg.viewAsSent();
		}
	}
}

void User::viewReceived()
{
	if (inbox.empty())
	{
		cout << "Your inbox is empty.";
	}
	else
	{
		for (auto msg : sent)
		{
			msg.viewAsReceived();
		}
	}
}



