#include "User.h"
#include <iostream>
#include <algorithm>
#include <map>
#include<vector>


using namespace std;
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


	if (!userExists) { // لو اليوزر مش عندي ضيفه
		contacts.push_back(u);
		msgcounter(u);
	}
}
void User::msgcounter(User) {
	//loop through each contact and count the number of messages exchanged 
	for (auto contact : contacts) {
		int numOfmsgs = 0;
		//count number of sent messages for this contact 
		for (auto msg : sent) {
			if (msg.get_sender() == contact.id) {
				numOfmsgs++;
			}
		}
		//count number of received messages from this contact 
		for (auto msg : inbox) {
			if (msg.get_receiver() == contact.id) {
				numOfmsgs++;
			}
		}
		numberOfmsg.insert(make_pair(contact, numOfmsgs));
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

bool User::cmp(const pair<int, int>& a, const pair<int, int>& b)
{
	return a.second < b.second;
}
void User::viewcontacts() {
	vector < pair<User, int>>sortedContacts(numberOfmsg.begin(), numberOfmsg.end());
	sort(sortedContacts.begin(), sortedContacts.end(), cmp);
		
	

}
