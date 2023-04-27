#include "User.h"
#include <iostream>
#include "Message.h"
#include <algorithm>
#include <map>
#include <vector>
#include <stack>
#include <deque>


using namespace std;
User::User() //Wessal
{
}
User::User(string username, string password) //Wessal
{
}
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
{
		contacts.push_back(u);
		msgcounter(u);
	}
}
void User::msgcounter(User) {
	//loop through each contact and count the number of messages exchanged 
	for (auto contact : contacts) {
		int numOfmsgs = 0;
		//count number of sent messages for this contact 

		if (!sent.empty()) {
			for (int i = 0; i < sent.size(); i++) {
				if (sent.front().getSender() == contact.id) {
					numOfmsgs++;
				}
				sent.push_back(sent.front());
				sent.pop_front();
			}
		}
		//count number of received messages from this contact 
		for (auto msg : inbox) {
			if (msg.getReceiver() == contact.id) {
				numOfmsgs++;
			}
		}
		sortedContacts.push_back(make_pair(contact, numOfmsgs));
	}
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
		cout << "You haven't sent any messages yet.\n";
	}
	else
	{
		for (int i = 0; i < sent.size(); i++) 
    {
			sent.front().viewAsSent();
			sent.push_back(sent.front());
			sent.pop_front();
		}
	}
}

void User::viewReceived()
{
	if (inbox.empty())
	{
		cout << "Your inbox is empty.\n";
	}
	else
	{
		for (int i = 0; i < sent.size(); i++) {
			sent.front().viewAsReceived();
			sent.push_back(sent.front());
			sent.pop_front();
		}
	}
} 

void User::viewcontacts() {
	sort(sortedContacts.begin(), sortedContacts.end(), [](pair<User,int>& a, pair<User,int>& b) {
		return a.second > b.second;
		}
	);
	for (auto i : sortedContacts) {
		cout << i.first.id << "		" << i.second << '\n';
	}
}
